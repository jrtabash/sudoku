#include "sudoku_solver.h"

#include <algorithm>
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
                if (board_[row][col] == Alphabet::space()) {
                    for (auto const letter : Alphabet::all()) {
                        if (board_.isAllowed(row, col, letter)) {
                            board_[row][col] = letter;
                            if (solveRecursive()) {
                                return true;
                            }
                            board_[row][col] = Alphabet::space();
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

        auto trySetAt = [this, &stack](std::size_t row, std::size_t col, std::optional<Letter> optLetter = std::nullopt) -> bool {
            auto const letters = Alphabet::all();
            auto iter = optLetter ? std::lower_bound(letters.begin(), letters.end(), *optLetter) : letters.begin();
            for (; iter != letters.end(); ++iter) {
                auto const letter = *iter;
                if (board_.isAllowed(row, col, letter)) {
                    stack.emplace(row, col, letter);
                    board_[row][col] = letter;
                    break;
                }
            }
            return iter != letters.end();
        };

        auto backtrack = [this, trySetAt, &stack](std::size_t & row, std::size_t & col) -> bool {
            while (true) {
                while (!stack.empty() && stack.top().letter == Alphabet::last()) {
                    auto const & top = stack.top();
                    board_[top.row][top.col] = Alphabet::space();
                    stack.pop();
                }

                if (stack.empty()) {
                    return false;
                }

                auto top = stack.top();
                board_[top.row][top.col] = Alphabet::space();
                stack.pop();

                if (!trySetAt(top.row, top.col, Alphabet::next(top.letter))) {
                    continue;
                }

                row = top.row;
                col = top.col;
                return true;
            }
        };

        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] == Alphabet::space()) {
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

    Solver::StackEntry::StackEntry(std::size_t row, std::size_t col, Letter letter)
        : row(row)
        , col(col)
        , letter(letter)
    {
    }

}
