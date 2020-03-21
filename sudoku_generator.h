#ifndef SUDOKU_GENERATOR_H
#define SUDOKU_GENERATOR_H

#include "sudoku_alphabet.h"
#include "sudoku_board.h"

#include <random>

namespace Sudoku {

    class Generator {
    public:
        enum class Difficulty : u_int8_t { Easy, Medium, Hard, Expert };

    public:
        Generator(Board & board, Difficulty difficulty);

        void generate();

    private:
        void clearBoard();
        bool generateBoard();
        void applyDifficulty();

        std::size_t numberToRemove() const noexcept;
        std::size_t numberRelatedToRemove() const noexcept;
        std::pair<std::size_t, std::size_t> findRelated(std::size_t row, std::size_t col, Letter letter) const noexcept;

    private:
        static inline unsigned randomPosition();

    private:
        Board & board_;
        Difficulty difficulty_;
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline unsigned Generator::randomPosition()
    {
        static auto randFtn = std::mt19937(std::random_device()());
        return randFtn() % Board::size();
    }

}

#endif // SUDOKU_GENERATOR_H
