import os
import shutil
import subprocess
import sys
import glob
import json

def clean_project(project_dir):
    # Define directories and files to be cleaned
    intermediate_dir = os.path.join(project_dir, 'Intermediate')
    build_dir = os.path.join(project_dir, 'Build')
    binaries_dir = os.path.join(project_dir, 'Binaries')
    derived_data_cache_dir = os.path.join(project_dir, 'DerivedDataCache')
    saved_dir = os.path.join(project_dir, 'Saved')
    solution_file = os.path.join(project_dir, '*.sln')

    # Function to remove directories
    def remove_directory(directory):
        if os.path.exists(directory):
            shutil.rmtree(directory)
            print(f"Removed directory: {directory}")

    # Function to remove files
    def remove_files(pattern):
        for file in glob.glob(pattern):
            os.remove(file)
            print(f"Removed file: {file}")

    # Clean directories and files
    remove_directory(intermediate_dir)
    remove_directory(build_dir)
    remove_directory(binaries_dir)
    remove_directory(derived_data_cache_dir)
    remove_directory(saved_dir)
    remove_files(solution_file)

def generate_solution(project_dir):
    # Locate the UnrealBuildTool executable
    ubt_path = None
    for root, dirs, files in os.walk(project_dir):
        for file in files:
            if file == 'UnrealBuildTool.exe':
                ubt_path = os.path.join(root, file)
                break
        if ubt_path:
            break

    if ubt_path is None:
        print("UnrealBuildTool.exe not found. Please make sure it is in your project directory.")
        sys.exit(1)

    # Generate new solution file
    if sys.platform == "win32":
        command = [ubt_path, '-projectfiles', '-project=' + project_dir, '-game', '-engine']
    else:
        command = ['mono', ubt_path, '-projectfiles', '-project=' + project_dir, '-game', '-engine']

    subprocess.run(command, cwd=project_dir)
    print("Generated new solution file")

if __name__ == "__main__":
    # Get the current directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Load the configuration file
    current_config = None
    if not os.path.exists(os.path.join(script_dir, 'dev_config.json')):
        # copy file from template
        shutil.copy(os.path.join(script_dir, 'Scripts/dev_config_template.json'), os.path.join(script_dir, 'dev_config.json'))
    with open(os.path.join(script_dir, 'dev_config.json')) as f:
        config = json.load(f)
        if sys.platform == "win32":
            current_config = config['windows']
        elif sys.platform == "linux":
            current_config = config['linux']
        else:
            current_config = config['macos']
    if current_config is None:
        print("No configuration found for this platform.")
        sys.exit(1)
    current_config

    # clean_project(project_path)
    # generate_solution(project_path)
    print("Project cleanup and solution generation complete.")
