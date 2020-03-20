# sudoku
Sudoku command line utility with support for solving and generating sudoku puzzles.

## Examples
### Solve
```bash
sudoku solve -p puzzles/example1.pzl
```

### Generate
```bash
sudoku generate -d medium
```

## Program Usage
```bash
Usage
        sudoku <operation> <options>

Operations
         solve    : Solve puzzle
         generate : Generate puzzle
         show     : Show puzzle

Options
        -h       : Print usage
        -v       : Verbose mode
        -f       : Force saving if file already exists
        -y       : Pretty print board
        -p <arg> : Read input puzzle / boad from given filename (required by solve and show)
        -s <arg> : Save resulting puzzle / board to given filename (optional with solve and generate)
        -m <arg> : Solver mode; one of recursive, iterative (optional with solve, default=recursive)
        -d <arg> : Generator difficulty level; one of easy, medium, hard, expert (optional with generate, default=easy)
```
