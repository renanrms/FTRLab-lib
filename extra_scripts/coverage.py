Import("env")
import os
import subprocess


def generate_coverage(source, target, env):
    build_dir = env.subst("$BUILD_DIR")
    gcovr_path = os.path.expanduser("~/.platformio/penv/bin/gcovr")

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
        "--html-details", "coverage/index.html",
        "--print-summary",
    ])

    if result.returncode == 0:
        print("\nRelatório HTML gerado em: coverage/index.html")


env.AddCustomTarget(
    name="coverage",
    dependencies=None,
    actions=generate_coverage,
    title="Coverage Report",
    description="Gera relatório HTML de cobertura (execute 'pio test -e native' antes)",
)
