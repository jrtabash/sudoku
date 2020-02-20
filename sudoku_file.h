#ifndef SUDOKU_FILE_H
#define SUDOKU_FILE_H

#include "sudoku_board.h"

#include <string>

namespace Sudoku {

    class File {
    public:
        File(std::string const & filename = "");

        inline std::string const & filename() const noexcept;

        Board load();
        void save(Board const & board, bool replace=false);

        bool exists() const;

    private:
        std::string filename_;
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline std::string const & File::filename() const noexcept
    {
        return filename_;
    }

}

#endif // SUDOKU_FILE_H
