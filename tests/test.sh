#!/bin/bash

# ---------------------------------------------------------------------------- #
#                              ft_malloc Test Runner                           #
# ---------------------------------------------------------------------------- #
# Description:                                                                 #
#   This script compiles and runs test cases (test0.c to test6.c) located in   #
#   the ./tests directory. It dynamically links against the custom malloc      #
#   implementation (libft_malloc.so) using LD_PRELOAD.                         #
#                                                                              #
# Usage:                                                                       #
#   ./test.sh [TEST_INDEX] [--keep]                                            #
#                                                                              #
# Options:                                                                     #
#   TEST_INDEX   Run only the specified test file (e.g., test3.c).             #
#   --keep       Keep the compiled test binary after execution.                #
#                                                                              #
# Examples:                                                                    #
#   ./test.sh           # Run all tests (test0.c to test6.c)                   #
#   ./test.sh 2         # Run test2.c only                                     #
#   ./test.sh --keep    # Run all tests and keep the binaries                  #
#                                                                              #
# Notes:                                                                       #
#   - Requires libft_malloc.so to be built in the parent directory.            #
#   - Requires GCC.                                                            #
#   - Memory analysis is done via your custom show_alloc_mem, not valgrind.    #
# ---------------------------------------------------------------------------- #

LIB="../libft_malloc.so"
BIN="./.test_exec"
KEEP=0

RED='\033[0;31m'
GREEN='\033[0;32m'
NC='\033[0m'

# Parse arguments
for arg in "$@"; do
    case "$arg" in
        --keep) KEEP=1 ;;
        [0-9]*) TEST_INDEX=$arg ;;
    esac
done

run_test() {
    local index="$1"
    local src="test$index.c"

    echo "-----------------------------"
    echo -e "Test $index: Compiling $src..."

    gcc -I ../include -o "$BIN" "$src" "$LIB"
    if [ $? -ne 0 ]; then
        echo -e "${RED}Compilation failed for $src${NC}"
        return 1
    fi

    echo -e "Running with ${LIB} preloaded..."
    LD_PRELOAD="$LIB" "$BIN"
    if [ $? -eq 139 ]; then
        echo -e "${RED}Segmentation fault (SIGSEGV)${NC}"
    fi

    [ "$KEEP" -eq 0 ] && rm -f "$BIN"
}

# Run selected or all tests
if [ -n "$TEST_INDEX" ]; then
    run_test "$TEST_INDEX"
else
    for i in {0..6}; do
        run_test "$i"
    done
fi
