#include "sudoku_board.h"

#include <stdexcept>

namespace Sudoku {

    Board::Board(Grid && grid)
        : grid_(grid)
    {
    }

    bool Board::isAllowed(std::size_t row, std::size_t col, Letter letter) const
    {
        // Cell already occupied check
        if (grid_[row][col] != Alphabet::space()) {
            return false;
        }

        // Column Check
        for (std::size_t i = 0; i < grid_.size(); ++i) {
            if (grid_[i][col] == letter) {
                return false;
            }
        }

        // Row Check
        for (std::size_t j = 0; j < grid_.size(); ++j) {
            if (grid_[row][j] == letter) {
                return false;
            }
        }

        // Block Check
        auto const blocks = Board::blocks();
        auto const baseRow = row - (row % blocks);
        auto const baseCol = col - (col % blocks);
        for (std::size_t i = 0; i < blocks; ++i) {
            for (std::size_t j = 0; j < blocks; ++j) {
                if (grid_[baseRow + i][baseCol + j] == letter) {
                    return false;
                }
            }
        }

        return true;
    }

    void Board::read(std::istream & in)
    {
        Grid grid;
        for (std::size_t row = 0; row < Board::size(); ++row) {
            for (std::size_t col = 0; col < Board::size(); ++col) {
                if (!(in >> grid[row][col])) {
                    throw std::runtime_error("Input stream too short");
                }
            }
        }

        int temp = 0;
        if (in >> temp) {
            throw std::runtime_error("Input stream too long");
        }

        grid_ = std::move(grid);
    }

    void Board::write(std::ostream & out) const
    {
        int rowCnt = 0;
        int colCnt = 0;

        for (auto const & row : grid_) {
            for (auto const & cell : row) {
                out << cell << ' ';
                if ((++colCnt % blocks()) == 0) {
                    out << ' ';
                }
            }
            out << '\n';
            if ((++rowCnt % blocks()) == 0) {
                out << '\n';
            }
        }
    }

}
