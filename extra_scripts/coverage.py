import subprocess
import shutil
import os
Import("env")


def generate_coverage(source, target, env):
    build_dir = env.subst("$BUILD_DIR")

    # Prefere gcovr do venv do PlatformIO; cai no PATH se não encontrar
    gcovr_pio = os.path.expanduser("~/.platformio/penv/bin/gcovr")
    gcovr_path = gcovr_pio if os.path.isfile(
        gcovr_pio) else (shutil.which("gcovr") or "gcovr")

    gcda_files = [
        f for root, _, files in os.walk(build_dir)
        for f in files if f.endswith(".gcda")
    ]
    if not gcda_files:
        print("\nNenhum arquivo .gcda encontrado. Execute 'pio test -e native' primeiro.")
        return

    os.makedirs("coverage", exist_ok=True)
    result = subprocess.run([
        gcovr_path,
        "--root", ".",
        "--object-directory", build_dir,
        "--filter", "src/",
        "--gcov-ignore-errors=source_not_found",
        "--gcov-ignore-errors=no_working_dir_found",
        "--html-details", "coverage/index.html",
        "--cobertura", "coverage/coverage.xml",
        "--print-summary",
    ])

    if result.returncode == 0:
        print("\nRelatório HTML gerado em: coverage/index.html")
        print("Relatório XML gerado em:  coverage/coverage.xml")


env.AddCustomTarget(
    name="coverage",
    dependencies=None,
    actions=generate_coverage,
    title="Coverage Report",
    description="Gera relatório de cobertura HTML e XML (execute 'pio test -e native' antes)",
)
