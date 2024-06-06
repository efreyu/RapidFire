import os
import shutil
import sys
import subprocess

def generate_project(project_dir, config, platform='win32'):
    exec_command = None
    if platform == 'darwin' or platform == 'win32':
        # using GenerateProjectFiles.sh
        generate_project_script = config["generate_project_script"].replace("{game_version}", config['game_version'])
        exec_command = f'{generate_project_script} -game -project="{project_dir}/{config["project_name"]}"'
    elif platform == 'linux':
        # using UnrealBuildTool, not tested yet
        ubt_path = os.path.join(config['engine_path'], config['build_tool_relative_path'])
        exec_command = f'mono {ubt_path} -projectfiles -project="{project_dir}/{config["project_name"]}" -game -engine'
    else:
        print(f"Platform {platform} not supported.")
        sys.exit(1)

    print(f"{exec_command}")

    subprocess.run(exec_command, shell=True)
    print("Generated new solution file")