# sudoku
Sudoku command line utility with support for solving, generating, checking and playing sudoku puzzles.

## Examples
### Solve
```bash
sudoku solve -m iterative -p puzzles/example1.pzl
```

### Generate
```bash
sudoku generate -d medium
```

### Play
```bash
sudoku play -b -p puzzles/example1.pzl
```

### Check
Check exit status is 0 if puzzle is correct, 1 otherwise.
```bash
sudoku check -p solved.pzl
sudoku check -w -p unsolved.pzl
```

## Program Usage
```bash
Usage
        sudoku <operation> <options>

Operations
         solve    : Solve puzzle
         generate : Generate puzzle
         check    : Check puzzle
         play     : Play puzzle
         show     : Show puzzle

Options
        -h       : Print usage
        -v       : Verbose mode
        -f       : Force saving if file already exists
        -y       : Pretty print board
        -i       : Show row and column indexes with pretty print option
        -w       : Allow Space when checking a puzzle
        -b       : Allow bad / invalid moves when playing a puzzle
        -p <arg> : Read input puzzle / boad from given filename (required by solve and show)
        -s <arg> : Save resulting puzzle / board to given filename (optional with solve and generate)
        -m <arg> : Solver mode; one of recursive, iterative (optional with solve, default=recursive)
        -d <arg> : Generator difficulty level; one of easy, medium, hard, expert (optional with generate, default=easy)
```
