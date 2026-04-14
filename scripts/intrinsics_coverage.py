import argparse
import os
import re
import subprocess

def get_git_root():
    return subprocess.run(["git", "rev-parse", "--show-toplevel"], capture_output=True, text=True).stdout.strip()

def read_file(file_path):
    with open(file_path, 'r') as file:
        return file.readlines()

def expect_impl(s):
    not_impl_list = ["p8", "p16", "p32", "p64", "p128", "f16"]
    return not any(not_impl in s for not_impl in not_impl_list)

def is_impl(s):
    return not("// FORCE_INLINE" in s)

def badge_color(pct):
    if pct >= 90:
        return "brightgreen"
    if pct >= 75:
        return "green"
    if pct >= 60:
        return "yellowgreen"
    if pct >= 50:
        return "yellow"
    return "red"

def update_readme(git_root, pct):
    readme_path = os.path.join(git_root, "README.md")
    with open(readme_path, 'r') as f:
        content = f.read()

    color = badge_color(pct)
    pct_str = f"{pct:.1f}"
    new_badge = f"![coverage badge](https://img.shields.io/badge/coverage-{pct_str}%25-{color})"
    new_content = re.sub(
        r'!\[coverage badge\]\(https://img\.shields\.io/badge/coverage-[^)]+\)',
        new_badge,
        content
    )

    if new_content != content:
        with open(readme_path, 'w') as f:
            f.write(new_content)
        print(f"README.md updated: {pct_str}% ({color})")
    else:
        print("README.md already up to date.")

def main():
    parser = argparse.ArgumentParser(description="Calculate neon2rvv intrinsics coverage.")
    parser.add_argument("--update-readme", action="store_true",
                        help="Update the coverage badge in README.md")
    args = parser.parse_args()

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
    ratio = float(is_impl_cnt) / float(expected_impl_cnt)
    pct = ratio * 100

    print(f"expected_impl_cnt:  {expected_impl_cnt}")
    print(f"is_impl_cnt:        {is_impl_cnt}")
    print(f"ratio:              {ratio:.4f}  ({pct:.1f}%)")

    if args.update_readme:
        update_readme(git_root, pct)

if __name__ == "__main__":
    main()
