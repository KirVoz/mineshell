#!/usr/bin/env zsh

# Function to count lines in a C file
count_lines() {
    local file="$1"
    local lines=$(wc -l < "$file")
    echo "$file: $lines lines"
}

# Traverse directories and count lines in C files
traverse_dirs() {
    local dir="$1"
    for entry in "$dir"/*(N); do
        if [[ -d "$entry" ]]; then
            traverse_dirs "$entry"
        elif [[ -f "$entry" && "$entry" == *.c ]]; then
            count_lines "$entry"
        fi
    done
}

# Start traversing from the current directory
traverse_dirs "."
