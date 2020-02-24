#ifndef SUDOKU_APPLICATION_H
#define SUDOKU_APPLICATION_H

#include "sudoku_arguments.h"

namespace Sudoku {

    class Application {
    public:
        Application(int argc, char ** argv);

        bool run();

    private:
        bool parse();
        bool process();

        void solve();
        void generate();
        void show();

        void save(Board const & board);
        void print(Board const & board);
        void prettyPrint(Board const & board);

    private:
        Arguments args_;
    };

}

#endif // SUDOKU_APPLICATION_H
