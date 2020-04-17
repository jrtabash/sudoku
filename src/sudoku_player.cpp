#include "sudoku_player.h"
#include "sudoku_pretty_print.h"

#include <algorithm>
#include <iostream>
#include <string>
#include <stdexcept>

namespace Sudoku {

    Player::Move::LetterSet const Player::Move::letters_ = Player::Move::makeLetterSet();

    void Player::Move::read()
    {
        row = toSize(getInput());
        if (!terminate) {
            col = toSize(getInput());
        }
        if (!terminate) {
            letter = toLetter(getInput());
        }
    }

    int Player::Move::getInput()
    {
        try {
            std::string input;
            std::cin >> input;

            if (std::cin.eof()) {
                terminate = true;
                return 0;
            }

            return std::stoi(input);
        }
        catch (...) {
            throw std::runtime_error("Invalid number");
        }
    }

    std::size_t Player::Move::toSize(int input)
    {
        std::size_t const size = std::size_t(input);

        if (input < 0 || size >= Board::size()) {
            throw std::runtime_error("Invalid index");
        }

        return size;
    }

    Letter Player::Move::toLetter(int input)
    {
        Letter const letter = Letter(input);

        if (letters_.find(letter) == letters_.end()) {
            throw std::runtime_error("Invalid letter");
        }

        return letter;
    }

    Player::Move::LetterSet Player::Move::makeLetterSet()
    {
        auto const letters = Alphabet::all();

        LetterSet letterSet(letters.begin(), letters.end());
        letterSet.insert(Alphabet::space());

        return letterSet;
    }

    Player::Player(Board & board, bool allowBadMoves)
        : board_(board)
        , checker_(board)
        , allowBadMoves_(allowBadMoves)
        , earlyTermination_(false)
    {
        populateFixedCells();
    }

    bool Player::play()
    {
        while (true) {
            displayBoard();

            if (gameOver()) {
                break;
            }

            makeMove();

            if (earlyTermination_) {
                break;
            }
        }

        return !earlyTermination_ && checker_.check(false);
    }

    bool Player::gameOver() const
    {
        for (auto const & row : board_) {
            for (auto const & letter : row) {
                if (letter == Alphabet::space()) {
                    return false;
               }
            }
        }
        return true;
    }

    void Player::displayBoard() const
    {
        static PrintInfo const printInfo = PrintInfo(true, true);
        prettyPrint(board_, printInfo);
    }

    void Player::makeMove()
    {
        static std::string errMsg;

        if (!errMsg.empty()) {
            std::cout << "ERROR: " << errMsg << std::endl;
            errMsg = "";
        }

        std::cout << "** Enter Move as: row# col# letter (use 0 for space, use ctrl-d to exit)\n"
                  << ">> " << std::flush;

        try {
            Move move;
            move.read();
            if (move.terminate) {
                earlyTermination_ = true;
                return;
            }

            if (!fixedCell(move.row, move.col)) {
                board_[move.row][move.col] = move.letter;

                if (!allowBadMoves_ && !checker_.check(true)) {
                    board_[move.row][move.col] = Alphabet::space();
                    errMsg = "Invalid last move";
                }
            }
            else {
                errMsg = "Cannot override fixed cell";
            }
        }
        catch (std::exception const & ex) {
            errMsg = ex.what();
        }
    }

    void Player::populateFixedCells()
    {
        for (std::size_t row = 0; row < board_.size(); ++row) {
            for (std::size_t col = 0; col < board_.size(); ++col) {
                if (board_[row][col] != Alphabet::space()) {
                    fixedCells_.insert(cellKey(row, col));
                }
            }
        }
    }

}
