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
                    auto letters = board_.letters();
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
        std::size_t const removeCntMinus1 = removeCnt - 1;
        std::size_t const removeRelCnt = numberRelatedToRemove();
        std::size_t count = 0;

        while (count++ < removeCnt) {
            std::size_t row = randomPosition();
            std::size_t col = randomPosition();
            while (board_[row][col] == 0) {
                row = randomPosition();
                col = randomPosition();
            }

            auto const letter = board_[row][col];
            board_[row][col] = 0;

            for (std::size_t relCount = 0; relCount < removeRelCnt; ++relCount) {
                if (count < removeCntMinus1) {
                    auto [relRow, relCol] = findRelated(row, col, letter);
                    if (board_[relRow][relCol] != 0) {
                        board_[relRow][relCol] = 0;
                        ++count;
                    }
                }
            }
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

    std::size_t Generator::numberRelatedToRemove() const noexcept
    {
        switch (difficulty_) {
        case Difficulty::Easy:   return 1;
        case Difficulty::Medium: return 2;
        case Difficulty::Hard:   return 2;
        case Difficulty::Expert: return 3;
        }

        return 0;
    }

    std::pair<std::size_t, std::size_t> Generator::findRelated(std::size_t row, std::size_t col, int letter) const noexcept
    {
        for (std::size_t relRow = randomPosition(); relRow < board_.size(); ++relRow) {
            for (std::size_t relCol = randomPosition(); relCol < board_.size(); ++relCol) {
                if (board_[relRow][relCol] == letter) {
                    return std::make_pair(relRow, relCol);
                }
            }
        }
        return std::make_pair(row, col);
    }

}
