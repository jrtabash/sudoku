#include "sudoku_application.h"
#include "sudoku_board.h"
#include "sudoku_solver.h"
#include "sudoku_generator.h"
#include "sudoku_checker.h"
#include "sudoku_file.h"

#include <iostream>

namespace Sudoku {

    Application::Application(int argc, char ** argv)
        : args_(argc, argv)
    {
    }

    bool Application::run()
    {
        return parse() && process();
    }

    bool Application::parse()
    {
        try {
            args_.parse();
            if (args_.help()) {
                args_.usage();
                return false;
            }
        }
        catch (std::exception const & ex) {
            std::cerr << "Error: " << ex.what() << "\n\n";
            args_.usage();
            return false;
        }

        return true;
    }

    bool Application::process()
    {
        try {
            if (args_.isSolveOperation()) {
                solve();
            }
            else if (args_.isGenerateOperation()) {
                generate();
            }
            else if (args_.isShowOperation()) {
                show();
            }
            else if (args_.isCheckOperation()) {
                return check();
            }
        }
        catch (std::exception const & ex) {
            std::cerr << "Error: " << ex.what() << std::endl;
            return false;
        }

        return true;
    }

    void Application::solve()
    {
        File pFile(args_.puzzleFilename());
        Board board(pFile.load());

        if (args_.verbose()) {
            std::cout << "Solving puzzle " << args_.mode() << ' ' << args_.puzzleFilename() << '\n' << std::endl;
        }

        Solver(board).solve(args_.isModeRecursive() ? Solver::Type::Recursive : Solver::Type::Iterative);
        print(board);
        save(board);
    }

    void Application::generate()
    {
        if (args_.verbose()) {
            std::cout << "Generating puzzle difficulty " << args_.difficultyString() << '\n' << std::endl;
        }

        Board board;
        Sudoku::Generator(board, args_.difficulty()).generate();
        print(board);
        save(board);
    }

    void Application::show()
    {
        File pFile(args_.puzzleFilename());
        Board board(pFile.load());

        if (args_.verbose()) {
            std::cout << "Showing puzzle " << args_.puzzleFilename() << '\n' << std::endl;
        }

        print(board);
    }

    bool Application::check()
    {
        File pFile(args_.puzzleFilename());
        Board board(pFile.load());

        if (args_.verbose()) {
            std::cout << "Checking puzzle (" << (args_.allowSpace() ? "Allow" : "Do not allow") << " space) " << args_.puzzleFilename() << '\n' << std::endl;
        }

        Checker checker(board);
        bool const valid = checker.check(args_.allowSpace());
        std::cout << "Puzzle is " << (valid ? "correct" : "incorrect") << std::endl;
        return valid;
    }

    void Application::save(Board const & board)
    {
        if (!args_.saveFilename().empty()) {
            if (args_.verbose()) {
                std::cout << "Saving board to " << args_.saveFilename() << std::endl;
            }
            File file(args_.saveFilename());
            file.save(board, args_.replace());
        }
    }

    void Application::print(Board const & board)
    {
        if (args_.pretty()) {
            prettyPrint(board);
        }
        else {
            board.write(std::cout, true /*separateBlocks*/);
        }
    }

    void Application::prettyPrint(Board const & board)
    {
        int rowCnt = 0;

        std::cout << "+-------------------------------------+\n";
        for (auto const & row : board) {
            int colCnt = 0;
            for (auto const & col : row) {
                if (col == Alphabet::space()) {
                    std::cout << "|   ";
                }
                else {
                    std::cout << "| " << col << ' ';
                }

                if (++colCnt == 3 || colCnt == 6) {
                    std::cout << '|';
                }
            }
            std::cout << "|\n";
            if ((++rowCnt % board.blocks()) == 0) {
                if (rowCnt == 3 || rowCnt == 6) {
                    std::cout << "|=====================================|\n";
                }
                else {
                    std::cout << "+-------------------------------------+\n";
                }
            }
            else {
                std::cout << "|-------------------------------------|\n";
            }
        }
        std::cout.flush();
    }

}
