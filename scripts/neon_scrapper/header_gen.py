import os
import csv

# Declare global variables to hold file contents
file_content = None
neon2rvv_content = None

# First file processing
with open("neon_intrinsics.csv", newline='') as csvfile:
    csv_reader = csv.reader(csvfile)
    header = next(csv_reader)  # Skip the header line if there is one
    # Read the CSV data into a list of rows
    file_content = [row for row in csv_reader]


def mod_neon2rvv():
    current_dir = os.getcwd()
    with open(current_dir + "/../../neon2rvv.h", 'r') as file:
        data = file.read()
        neon2rvv_content = data

    prev_func_name = ""
    for line in file_content:
        func_partial = "FORCE_INLINE "+line[0]+" "+line[1]+"("
        if func_partial not in neon2rvv_content:
            func = "// FORCE_INLINE "+line[0]+" "+line[1]+line[2]+";\n "
            print("func: ", func)
            start_idx = neon2rvv_content.find(prev_func_name)
            insert_idx = neon2rvv_content.find("FORCE_INLINE", start_idx+1)
            neon2rvv_content = neon2rvv_content[:insert_idx] +func+ neon2rvv_content[insert_idx:]

        prev_func_name = func_partial

    with open("modified_neon2rvv.h", 'w') as file:
        file.write(neon2rvv_content)

def mod_impl_h():
    current_dir = os.getcwd()
    with open(current_dir + "/../../tests/impl.h", 'r') as file:
        data = file.read()
        neon2rvv_content = data

    required_length = 79
    prev_func_name = ""
    for line in file_content:
        func_partial = "_("+line[1]+")"
        if func_partial not in neon2rvv_content:
            template = "/*_("+line[1]+")%s*/\\\n"
            spaces_needed = required_length - len(template % "") + 1
            func = template % (" " * spaces_needed)
            print("func: ", func)
            start_idx = neon2rvv_content.find(prev_func_name)
            insert_idx = neon2rvv_content.find("\n", start_idx+1)
            neon2rvv_content = neon2rvv_content[:insert_idx+1] +func+ neon2rvv_content[insert_idx+1:]

        prev_func_name = func_partial

    with open("modified_impl.h", 'w') as file:
        file.write(neon2rvv_content)

def mod_impl_c():
    current_dir = os.getcwd()
    with open(current_dir + "/../../tests/impl.cpp", 'r') as file:
        data = file.read()
        neon2rvv_content = data

    prev_func_name = ""
    for line in file_content:
        func_partial = "result_t test_"+line[1]+"("
        if func_partial not in neon2rvv_content:
            func = "result_t test_"+line[1]+"(const NEON2RVV_TEST_IMPL &impl, uint32_t iter) {\nreturn TEST_UNIMPL;}\n"
            print("func: ", func)
            start_idx = neon2rvv_content.find(prev_func_name)
            insert_idx = neon2rvv_content.find("result_t test_", start_idx+1)
            neon2rvv_content = neon2rvv_content[:insert_idx] +func+ neon2rvv_content[insert_idx:]

        prev_func_name = func_partial

    with open("modified_impl.c", 'w') as file:
        file.write(neon2rvv_content)

# mod_neon2rvv()
# mod_impl_h()
# mod_impl_c()
