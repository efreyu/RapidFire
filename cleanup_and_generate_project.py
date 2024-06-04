import os
import shutil
import subprocess
import sys
import glob
import json
import Scripts.cleanup_project as cleanup_project
import Scripts.generate_project as generate_project

if __name__ == "__main__":
    # Get the current directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Load the configuration file
    current_config = None
    current_platform = None
    if not os.path.exists(os.path.join(script_dir, 'dev_config.json')):
        # copy file from template
        shutil.copy(os.path.join(script_dir, 'Scripts/dev_config_template.json'), os.path.join(script_dir, 'dev_config.json'))
    with open(os.path.join(script_dir, 'dev_config.json')) as f:
        config = json.load(f)
        if sys.platform == "win32":
            current_config = config['windows']
        elif sys.platform == "linux":
            current_config = config['linux']
        elif sys.platform == "darwin":
            current_config = config['macos']
        current_platform = sys.platform
    if current_config is None or current_platform is None:
        print("No configuration found for this platform.")
        sys.exit(1)
    engine_path = current_config['engine_path']
    engine_path = engine_path.replace("{game_version}", current_config['game_version'])

    # cleanup project
    cleanup_project.clean_project(script_dir)
    cleanup_project.remove_temp_files(script_dir)

    # generate project
    generate_project.generate_project(script_dir, current_config, current_platform)

    # clean_project(project_path)
    # generate_solution(project_path)
    print("Project cleanup and solution generation complete.")
