#include "sudoku_generator.h"

#include <algorithm>

namespace Sudoku {
    Generator::Generator(Board & board, Difficulty difficulty)
        : board_(board)
        , difficulty_(difficulty)
    {
    }

    void Generator::generate()
    {
        clearBoard();
        generateBoard();
        applyDifficulty();
    }

    void Generator::clearBoard()
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                board_[row][col] = 0;
            }
        }
    }

    bool Generator::generateBoard()
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == 0) {
                    std::array<int, 9> letters = {1, 2, 3, 4, 5, 6, 7, 8, 9 };
                    std::shuffle(letters.begin(), letters.end(), std::mt19937(std::random_device()()));

                    for (auto const letter : letters) {
                        if (board_.isAllowed(row, col, letter)) {
                            board_[row][col] = letter;
                            if (generateBoard()) {
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

    void Generator::applyDifficulty()
    {
        std::size_t const removeCnt = numberToRemove();
        for (std::size_t count = 0; count < removeCnt; ++count) {
            std::size_t row = randomPosition();
            std::size_t col = randomPosition();
            while (board_[row][col] == 0) {
                row = randomPosition();
                col = randomPosition();
            }

            board_[row][col] = 0;
        }
    }

    std::size_t Generator::numberToRemove() const noexcept
    {
        switch (difficulty_) {
        case Difficulty::Easy:   return 15;
        case Difficulty::Medium: return 30;
        case Difficulty::Hard:   return 45;
        case Difficulty::Expert: return 60;
        }

        return 0;
    }

}
