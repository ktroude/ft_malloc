#!/bin/bash
export LD_LIBRARY_PATH=.
export LD_PRELOAD=./libft_malloc.so

if [[ $1 =~ ^[0-9]+$ ]]; then
    test_num=$1
    echo "=== Lancement du test $test_num ==="
    /usr/bin/time -v ./tests/test$test_num
else
    $@
fi
