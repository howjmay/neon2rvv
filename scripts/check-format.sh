#!/usr/bin/env bash

set -euxo pipefail

if command -v clang-format-17 >/dev/null 2>&1; then
    CLANG_FORMAT=clang-format-17
elif command -v clang-format >/dev/null 2>&1; then
    CLANG_FORMAT=clang-format
else
    echo "clang-format is required but not installed" >&2
    exit 127
fi

: "${SOURCES:=neon2rvv.h tests/*.cpp tests/*.h}"

for file in ${SOURCES};
do
    ${CLANG_FORMAT} ${file} > expected-format
    diff -u -p --label="${file}" --label="expected coding style" ${file} expected-format
done
exit $(${CLANG_FORMAT} --output-replacements-xml ${SOURCES} | egrep -c "</replacement>")
