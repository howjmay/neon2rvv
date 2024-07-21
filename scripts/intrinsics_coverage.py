import os
import subprocess

def get_git_root():
    return subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()

def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.readlines()

def expect_impl(s):
    not_impl_list = ["p8", "p16", "p32", "p64", "f16"]
    return not any(not_impl in s for not_impl in not_impl_list)

def is_impl(s):
    return not("// FORCE_INLINE" in s)

def main():
    git_root = get_git_root()
    file_path = os.path.join(git_root, "neon2rvv.h")
    
    try:
        data = read_file(file_path)
    except IOError as e:
        print(f"Error reading file: {e}")
        return

    mother = [line for line in data if "FORCE_INLINE" in line]

    expected_impl_cnt = sum(1 for line in mother if expect_impl(line))
    is_impl_cnt = sum(1 for line in mother if is_impl(line))
    print("expected_impl_cnt: ", expected_impl_cnt)
    print("is_impl_cnt: ", is_impl_cnt)
    print("ratio: ", float(is_impl_cnt) / float(expected_impl_cnt))

if __name__ == "__main__":
    main()
