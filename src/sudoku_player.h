#ifndef SUDOKU_PLAYER_H
#define SUDOKU_PLAYER_H

#include "sudoku_alphabet.h"
#include "sudoku_board.h"
#include "sudoku_checker.h"

#include <unordered_set>

namespace Sudoku {

    class Player {
    public:
        struct Move {
            using LetterSet = std::unordered_set<Letter>;

            bool terminate = false;
            std::size_t row = 0;
            std::size_t col = 0;
            Letter letter = Alphabet::space();

            void read();

        private:
            int getInput();
            static std::size_t toSize(int input);
            static Letter toLetter(int input);

            static LetterSet makeLetterSet();

        private:
            static LetterSet const letters_;
        };

    public:
        Player(Board & board, bool allowBadMoves=true);

        bool play();

        inline bool earlyTermination() const noexcept;

    private:
        inline std::size_t cellKey(std::size_t row, std::size_t col) const noexcept;

        inline bool fixedCell(std::size_t row, std::size_t col) const noexcept;

        bool gameOver() const;
        void displayBoard() const;
        void makeMove();

        void populateFixedCells();

    private:
        std::unordered_set<std::size_t> fixedCells_;
        Board & board_;
        Checker checker_;
        bool allowBadMoves_;
        bool earlyTermination_;
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline bool Player::earlyTermination() const noexcept
    {
        return earlyTermination_;
    }

    inline std::size_t Player::cellKey(std::size_t row, std::size_t col) const noexcept
    {
        return (row * 10) + col;
    }

    inline bool Player::fixedCell(std::size_t row, std::size_t col) const noexcept
    {
        return fixedCells_.find(cellKey(row, col)) != fixedCells_.end();
    }

}

#endif // SUDOKU_PLAYER_H
