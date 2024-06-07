import os
import shutil
import glob

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
            try:
                shutil.rmtree(directory)
            except Exception as e:
                print(f"Failed to remove {directory}: {e}")
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

def remove_temp_files(directory, unused_files=None):
    if unused_files is None:
        unused_files = ['.DS_Store', '._DS_Store']

    for root, dirs, files in os.walk(directory):
        for file in files:
            if file in unused_files:
                file_path = os.path.join(root, file)
                try:
                    os.remove(file_path)
                    print(f"Removed: {file_path}")
                except Exception as e:
                    print(f"Failed to remove {file_path}: {e}")

        for dir in dirs:
            remove_temp_files(os.path.join(root, dir), unused_files)