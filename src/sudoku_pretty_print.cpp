#include "sudoku_pretty_print.h"
#include "sudoku_alphabet.h"

#include <iostream>

namespace Sudoku {

    PrintInfo::PrintInfo(bool rowIndex, bool colIndex)
        : rowIndex(rowIndex)
        , colIndex(colIndex)
    {
    }

    void prettyPrint(Board const & board, PrintInfo const & info)
    {
        std::string const prefix = (info.rowIndex ? "  " : "");

        if (info.colIndex) {
            std::cout << prefix << "  0   1   2    3   4   5    6   7   8  \n";
        }

        int rowCnt = 0;
        std::cout << prefix << "+-------------------------------------+\n";
        for (auto const & row : board) {
            int colCnt = 0;

            if (info.rowIndex) {
                std::cout << rowCnt << ' ';
            }

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
                    std::cout << prefix << "|===========  ===========  ===========|\n";
                }
                else {
                    std::cout << prefix << "+-------------------------------------+\n";
                }
            }
            else {
                std::cout << prefix << "|-----------||-----------||-----------|\n";
            }
        }
        std::cout.flush();
    }

}
