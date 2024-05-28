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