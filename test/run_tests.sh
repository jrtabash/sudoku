#!/bin/bash

binary=sudoku
if [ "$1" != "" ]; then
    binary=$1
fi

solution=/tmp/solution.pzl
status=0

function run_test_cases() {
    mode=$1

    for puzzle in $(ls test_puzzles/)
    do
        echo "${mode}: ${puzzle}"
        ${binary} solve -m ${mode} -p test_puzzles/${puzzle} -f -s ${solution} > /dev/null

        ${binary} check -p ${solution} > /dev/null
        if [ $? -ne 0 ]; then
            echo "Check failed"
            status=1
        fi

        cmp ${solution} test_solutions/${puzzle} > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "Comparison failed"
            status=1
        fi
    done
}

run_test_cases "recursive"
run_test_cases "iterative"

if [ ${status} -eq 0 ]; then
    echo "Success"
else
    echo "Failed"
fi

exit ${status}
