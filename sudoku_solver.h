#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "sudoku_board.h"

#include <stack>

namespace Sudoku {

    class Solver {
    public:
        enum class Type : u_int8_t { Recursive, Iterative };

    public:
        Solver(Board & board);

        bool solve(Type type);
        bool solveRecursive();
        bool solveIterative();

    private:
        struct StackEntry {
            std::size_t row;
            std::size_t col;
            int letter;

            StackEntry(std::size_t row, std::size_t col, int letter);
        };

        using Stack = std::stack<StackEntry>;

    private:
        Board & board_;
    };

}

#endif // SUDOKU_SOLVER_H
