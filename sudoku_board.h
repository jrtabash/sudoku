#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include "sudoku_alphabet.h"

#include <array>
#include <ostream>
#include <istream>

namespace Sudoku {

    class Board {
    public:
        using Row = std::array<Letter, 9>;
        using Grid = std::array<Row, 9>;

    public:
        Board() = default;
        Board(Grid && grid);

        static constexpr std::size_t size() { return 9; }
        static constexpr std::size_t blocks() { return 3; }

        inline Row const & operator[](int idx) const;
        inline Row & operator[](int idx);

        inline Grid::const_iterator begin() const noexcept;
        inline Grid::const_iterator end() const noexcept;

        bool isAllowed(std::size_t row, std::size_t col, Letter letter) const;
        bool isCorrect(std::size_t row, std::size_t col) const;

        void read(std::istream & in);
        void write(std::ostream & out) const;

    private:
        Grid grid_ = {};
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline Board::Row const & Board::operator[](int idx) const
    {
        return grid_[idx];
    }

    inline Board::Row & Board::operator[](int idx)
    {
        return grid_[idx];
    }

    inline Board::Grid::const_iterator Board::begin() const noexcept
    {
        return grid_.begin();
    }

    inline Board::Grid::const_iterator Board::end() const noexcept
    {
        return grid_.end();
    }

}

#endif // SUDOKU_BOARD_H
