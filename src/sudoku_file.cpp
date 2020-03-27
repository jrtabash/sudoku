#include "sudoku_file.h"

#include <fstream>
#include <stdexcept>

namespace Sudoku {

    File::File(std::string const & filename)
        : filename_(filename)
    {
    }

    Board File::load()
    {
        auto exception = [this](char const * msg) {
            throw std::runtime_error(
                std::string("Sudoku::File::load: ") + msg + "; file=" + filename_);
        };

        std::ifstream ifs(filename_.c_str());
        if (!ifs.is_open()) {
            exception("Cannot open file for reading");
        }

        Board board;
        try {
            board.read(ifs);
        }
        catch (std::exception const & ex) {
            if (ifs.is_open()) {
                ifs.close();
            }
            exception(ex.what());
        }

        ifs.close();
        return board;
    }

    void File::save(Board const & board, bool replace)
    {
        auto exception = [this](char const * msg) {
            throw std::runtime_error(
                std::string("Sudoku::File::save: ") + msg + "; file=" + filename_);
        };

        if (!replace && exists()) {
            exception("File already exists");
        }

        std::ofstream ofs(filename_.c_str());
        if (!ofs.is_open()) {
            exception("Cannot open file for writing");
        }

        board.write(ofs);
        ofs.close();
    }

    bool File::exists() const
    {
        // return std::filesystem::exists(std::path(filename_));
        std::ifstream ifs(filename_.c_str());
        if (ifs.is_open()) {
            ifs.close();
            return true;
        }
        return false;
    }

}
