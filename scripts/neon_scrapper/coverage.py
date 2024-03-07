import pandas as pd
import re
import os

current_dir = os.getcwd()
with open(current_dir+"/../../neon2rvv.h", 'r') as file:
    data = file.read()
    result = re.findall(r"^FORCE_INLINE .+? (v.+?)\(.*\)", data, flags=re.MULTILINE)
    intrinsics = set(result)

df = pd.read_csv(current_dir+"/neon_intrinsics.csv")

# for data_type in ["float16_t", "float16x4_t", "float16x8_t", "poly8_t", "poly8x8_t", "poly8x16_t", "poly16_t", "poly16x4_t", "poly16x8_t", "poly64_t", "poly64x1_t", "poly64x2_t", "poly128_t"]:
#     df = df[~df["ReturnType"].str.contains(data_type)]
#     df = df[~df["Arguments"].str.contains(data_type)]
# df.reset_index()
# df.to_csv("neon_filtered.csv", index=False)
# df_unimplemented = df[~df["Name"].isin(intrinsics)]
# df_unimplemented.to_csv("neon_unimplemented.csv", index=False)

primary_group_list = []
secondary_group_list = sorted(list(set(df["Group"].to_list())))

for group in secondary_group_list:
    primary_group_list.append(group.split(" / ")[0])
primary_group_list = sorted(list(set(primary_group_list)))

print("Neon2RVV coverage:")
print("Total", len(intrinsics), "/", len(set(df["Name"].to_list())))

for primary_group in primary_group_list:
    df_primary = df[df["Group"].str.contains(primary_group)]
    primary_set = set(df_primary["Name"].to_list())
    intrinsics_count = len(primary_set)
    intersection = len(intrinsics.intersection(primary_set))
    print(primary_group, "\t", intersection, "/", intrinsics_count)

    for secondary_group in [group for group in secondary_group_list if primary_group in group]:
        df_secondary = df_primary[df_primary["Group"] == secondary_group]
        secondary_set = set(df_secondary["Name"].to_list())
        intrinsics_count = len(secondary_set)
        intersection = len(intrinsics.intersection(secondary_set))
        print("\t", secondary_group, "\t", intersection, "/", intrinsics_count)
    print()
