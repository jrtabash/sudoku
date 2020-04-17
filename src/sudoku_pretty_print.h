#ifndef SUDOKU_PRETTY_PRINT_H
#define SUDOKU_PRETTY_PRINT_H

#include "sudoku_board.h"

namespace Sudoku {

    struct PrintInfo {
        bool rowIndex = false;
        bool colIndex = false;

        PrintInfo() = default;
        PrintInfo(bool rowIndex, bool colIndex);
    };

    void prettyPrint(Board const & board, PrintInfo const & info = PrintInfo());

}

#endif // SUDOKU_PRETTY_PRINT_H

