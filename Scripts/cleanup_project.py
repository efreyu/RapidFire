import os
import shutil
import glob

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

def clean_project(project_dir):
    # Define directories and files to be cleaned
    intermediate_dir = os.path.join(project_dir, 'Intermediate')
    build_dir = os.path.join(project_dir, 'Build')
    binaries_dir = os.path.join(project_dir, 'Binaries')
    derived_data_cache_dir = os.path.join(project_dir, 'DerivedDataCache')
    local_derived_data_cache_dir = os.path.join(project_dir, 'LocalDerivedDataCache')
    saved_dir = os.path.join(project_dir, 'Saved')
    solution_file = os.path.join(project_dir, '*.sln')

    # Clean directories and files
    remove_directory(intermediate_dir)
    remove_directory(build_dir)
    remove_directory(binaries_dir)
    remove_directory(derived_data_cache_dir)
    remove_directory(local_derived_data_cache_dir)
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

def cleanup_ddp_cache(project_dir, unreal_engine_path):
    derived_data_cache_dir = os.path.join(project_dir, 'DerivedDataCache')
    remove_directory(derived_data_cache_dir)

    local_derived_data_cache_dir = os.path.join(project_dir, 'LocalDerivedDataCache')
    remove_directory(local_derived_data_cache_dir)

    home_user_folder = os.path.expanduser("~")
    appdata_local_unreal_engine_cache = os.path.join(home_user_folder, 'AppData', 'Local', 'UnrealEngine', 'Common', 'DerivedDataCache')
    remove_directory(appdata_local_unreal_engine_cache)

    unreal_engine_cache = os.path.join(unreal_engine_path, 'Engine', 'DerivedDataCache')
    remove_directory(unreal_engine_cache)
