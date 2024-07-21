import os
import subprocess

def get_git_root():
    return subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()

def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.readlines()

def is_impl(s):
    not_impl_list = ["p8", "p16", "p32", "p64", "f16"]
    return not any(not_impl in s for not_impl in not_impl_list)

def main():
    git_root = get_git_root()
    file_path = os.path.join(git_root, "tests/impl.h")
    
    try:
        data = read_file(file_path)
    except IOError as e:
        print(f"Error reading file: {e}")
        return

    mother = [line for line in data if "_(" in line]

    impl_cnt = sum(1 for line in mother if is_impl(line))

    print("implCnt: ", float(impl_cnt) / float(len(mother)) if mother else 0)

if __name__ == "__main__":
    main()
