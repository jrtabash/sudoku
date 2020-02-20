#ifndef SUDOKU_SOLVER_H
#define SUDOKU_SOLVER_H

#include "sudoku_board.h"

namespace Sudoku {

    class Solver {
    public:
        Solver(Board & board);

        bool solve();

    private:
        Board & board_;
    };

}

#endif // SUDOKU_SOLVER_H
