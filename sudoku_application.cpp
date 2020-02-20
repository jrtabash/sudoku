#include "sudoku_application.h"
#include "sudoku_board.h"
#include "sudoku_solver.h"
#include "sudoku_generator.h"
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
            std::cout << "Solving puzzle " << args_.puzzleFilename() << '\n' << std::endl;
        }

        Solver(board).solve();
        board.print();
        save(board);
    }

    void Application::generate()
    {
        if (args_.verbose()) {
            std::cout << "Generating puzzle difficulty " << args_.difficultyString() << '\n' << std::endl;
        }

        Board board;
        Sudoku::Generator(board, args_.difficulty()).generate();
        board.print();
        save(board);
    }

    void Application::show()
    {
        File pFile(args_.puzzleFilename());
        Board board(pFile.load());

        if (args_.verbose()) {
            std::cout << "Showing puzzle " << args_.puzzleFilename() << '\n' << std::endl;
        }

        board.print();
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

}