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
        bool process() const;

        void solve() const;
        void generate() const;
        void show() const;
        bool check() const;

        void save(Board const & board) const;
        void print(Board const & board) const;

    private:
        static void prettyPrint(Board const & board);

    private:
        Arguments args_;
    };

}

#endif // SUDOKU_APPLICATION_H
