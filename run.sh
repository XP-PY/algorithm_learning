#!/bin/bash

set -e

if [ $# -eq 0 ]; then
    echo "用法: $0 <目标名>"
    echo "示例: $0 my_executable"
    exit 1
fi

target="$1"

cmake --build --preset debug --target "$target"
"./build/debug/bin/$target"