#include "sudoku_solver.h"

namespace Sudoku {

    Solver::Solver(Board & board)
        : board_(board)
    {
    }

    bool Solver::solve()
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == 0) {
                    for (auto const letter : board_.letters()) {
                        if (board_.isAllowed(row, col, letter)) {
                            board_[row][col] = letter;
                            if (solve()) {
                                return true;
                            }
                            board_[row][col] = 0;
                        }
                    }
                    return false;
                }
            }
        }
        return true;
    }

}
