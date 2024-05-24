import os
import subprocess

def format_code(root_dir='../Source', clang_format_path='clang-format'):
    """
    Recursively calls clang-format for all .cpp and .h files in the given directory.

    :param root_dir: Root directory to start searching for files.
    :param clang_format_path: Path to the clang-format executable. Default is 'clang-format' assuming it is in the system's PATH.
    """
    cwd = os.getcwd()
    sources_path = os.path.join(cwd, root_dir)
    for dirpath, _, filenames in os.walk(sources_path):
        for filename in filenames:
            if filename.endswith('.cpp') or filename.endswith('.h') or filename.endswith('.cs'):
                file_path = os.path.join(dirpath, filename)
                print(f"Formatting {file_path}")
                subprocess.run([clang_format_path, '-i', file_path])

if __name__ == "__main__":
    # Get the current directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))
    # Set the root directory to the Unreal Engine project directory
    root_directory = os.path.join(script_dir, '../Source')
    # Optionally, set the path to the clang-format executable if it's not in your PATH
    clang_format_executable = 'clang-format'  # or specify the full path if needed

    format_code(root_directory, clang_format_executable)
