#!/usr/bin/env python3

import os
import shutil

def install_hooks(src_dir, dest_dir):
    """
    Install git hooks from src_dir to dest_dir, overriding existing hooks.
    """
    if not os.path.exists(dest_dir):
        os.makedirs(dest_dir)

    for filename in os.listdir(src_dir):
        src_file = os.path.join(src_dir, filename)
        dest_file = os.path.join(dest_dir, filename)
        if os.path.isfile(src_file):
            shutil.copy(src_file, dest_file)
            os.chmod(dest_file, 0o755)  # Make the hook executable
            print(f"Installed hook: {filename}")

def main():
    # Get the current directory where this script is located
    script_dir = os.path.dirname(os.path.abspath(__file__))

    # Construct the source hooks directory path
    src_hooks_dir = os.path.join(script_dir, 'githooks')

    # Destination hooks directory in the git directory
    dest_hooks_dir = os.path.abspath(os.path.join(script_dir, '../.git/hooks'))

    install_hooks(src_hooks_dir, dest_hooks_dir)

if __name__ == "__main__":
    main()
