#ifndef SUDOKU_CHECKER_H
#define SUDOKU_CHECKER_H

#include "sudoku_board.h"

namespace Sudoku {

    class Checker {
    public:
        Checker(Board const & board);

        bool check(bool allowSpace) const;

    private:
        Board const & board_;
    };

} // Sudoku

#endif // SUDOKU_CHECKER_H
