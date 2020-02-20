#ifndef SUDOKU_BOARD_H
#define SUDOKU_BOARD_H

#include <array>
#include <ostream>

namespace Sudoku {

    class Board {
    public:
        using Row = std::array<int, 9>;
        using Grid = std::array<Row, 9>;

    public:
        Board() = default;
        Board(Grid && grid);

        static constexpr std::size_t size() { return 9; }
        static constexpr std::size_t blocks() { return 3; }

        inline Row const & operator[](int idx) const;
        inline Row & operator[](int idx);

        bool isAllowed(std::size_t row, std::size_t col, int letter) const;

        void read(std::istream & in);
        void write(std::ostream & out) const;
        void print() const;

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

}

#endif // SUDOKU_BOARD_H