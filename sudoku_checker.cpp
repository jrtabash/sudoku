#include "sudoku_checker.h"
#include "sudoku_alphabet.h"

namespace Sudoku {

    Checker::Checker(Board const & board)
        : board_(board)
    {
    }

    bool Checker::check(bool allowSpace) const
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == Alphabet::space()) {
                    if (allowSpace) { continue; }
                    return false;
                }
                else if (!board_.isCorrect(row, col)) {
                    return false;
                }
            }
        }
        return true;
    }

} // Sudoku
