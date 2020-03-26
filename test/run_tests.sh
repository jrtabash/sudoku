#!/bin/bash

binary=sudoku
if [ "$1" != "" ]; then
    binary=$1
fi

status=0

function test_solve() {
    mode=$1

    solution=/tmp/solution.pzl

    for puzzle in $(ls test_puzzles/)
    do
        echo "Test solve: ${mode} ${puzzle}"
        ${binary} solve -m ${mode} -p test_puzzles/${puzzle} -f -s ${solution} > /dev/null

        ${binary} check -p ${solution} > /dev/null
        if [ $? -ne 0 ]; then
            echo "Solve check failed"
            status=1
        fi

        cmp ${solution} test_solutions/${puzzle} > /dev/null 2>&1
        if [ $? -ne 0 ]; then
            echo "Solve comparison failed"
            status=1
        fi
    done
}

function test_generate() {
    difficulty=$1
    spaces=$2

    puzzle=/tmp/puzzle.pzl

    echo "Test generate: ${difficulty}"
    ${binary} generate -d ${difficulty} -f -s ${puzzle} > /dev/null

    ${binary} check -w -p ${puzzle} > /dev/null
    if [ $? -ne 0 ]; then
        echo "Generate check failed"
        status=1
    fi

    count=$(cat ${puzzle} | sed y/\ /\\n/ | grep -c 0)
    if [ ${count} -ne ${spaces} ]; then
        echo "Generate space count failed"
        status=1
    fi
}

test_solve "recursive"
test_solve "iterative"

test_generate "easy" 15
test_generate "medium" 30
test_generate "hard" 45
test_generate "expert" 60

if [ ${status} -eq 0 ]; then
    echo "Success"
else
    echo "Failed"
fi

exit ${status}
