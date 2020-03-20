#include "sudoku_solver.h"

#include <optional>

namespace Sudoku {

    Solver::Solver(Board & board)
        : board_(board)
    {
    }

    bool Solver::solve(Type type)
    {
        if (type == Type::Recursive) {
            return solveRecursive();
        }
        else {
            return solveIterative();
        }
    }

    bool Solver::solveRecursive()
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == 0) {
                    for (auto const letter : board_.letters()) {
                        if (board_.isAllowed(row, col, letter)) {
                            board_[row][col] = letter;
                            if (solveRecursive()) {
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

    bool Solver::solveIterative()
    {
        Stack stack;

        auto trySetAt = [this, &stack](std::size_t row, std::size_t col, std::optional<int> optLetter = std::nullopt) -> bool {
            auto letter = optLetter ? *optLetter : board_.beginLetter();
            for (; letter != board_.endLetter(); ++letter) {
                if (board_.isAllowed(row, col, letter)) {
                    stack.emplace(row, col, letter);
                    board_[row][col] = letter;
                    break;
                }
            }
            return letter != board_.endLetter();
        };

        auto backtrack = [this, trySetAt, &stack](std::size_t & row, std::size_t & col) -> bool {
            while (true) {
                while (!stack.empty() && stack.top().letter == board_.lastLetter()) {
                    auto const & top = stack.top();
                    board_[top.row][top.col] = board_.emptyLetter();
                    stack.pop();
                }

                if (stack.empty()) {
                    return false;
                }

                auto top = stack.top();
                board_[top.row][top.col] = board_.emptyLetter();
                stack.pop();

                if (!trySetAt(top.row, top.col, ++top.letter)) {
                    continue;
                }

                row = top.row;
                col = top.col;
                return true;
            }
        };

        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == board_.emptyLetter()) {
                    if (!trySetAt(row, col)) {
                        if (!backtrack(row, col)) {
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    Solver::StackEntry::StackEntry(std::size_t row, std::size_t col, int letter)
        : row(row)
        , col(col)
        , letter(letter)
    {
    }

}
