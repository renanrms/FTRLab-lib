Import("env")
import os
import shutil
import subprocess
import sys


def find_act(project_dir):
    # Prioridade: variável de ambiente > PATH > bin/ local do projeto
    if "ACT_PATH" in os.environ:
        return os.environ["ACT_PATH"]
    found = shutil.which("act")
    if found:
        return found
    local = os.path.join(project_dir, "bin", "act")
    if os.path.isfile(local):
        return local
    return None


def run_ci(source, target, env):
    root = env.subst("$PROJECT_DIR")
    act = find_act(root)

    if not act:
        print("act não encontrado. Instale com:")
        print("  curl -s https://raw.githubusercontent.com/nektos/act/master/install.sh | sudo bash")
        sys.exit(1)

    result = subprocess.run([act, "push"], cwd=root)
    if result.returncode != 0:
        sys.exit(result.returncode)


env.AddCustomTarget(
    name="ci",
    dependencies=None,
    actions=run_ci,
    title="CI local",
    description="Roda o pipeline do GitHub Actions localmente via act",
)
