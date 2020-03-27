#include "sudoku_application.h"

int main(int argc, char ** argv)
{
    Sudoku::Application sudoku(argc, argv);
    if (!sudoku.run()) {
        return 1;
    }
    return 0;
}
