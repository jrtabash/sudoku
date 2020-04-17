#include "sudoku_arguments.h"

#include <iostream>
#include <stdexcept>

namespace Sudoku {

    std::string const Arguments::Operation_Solve    = "solve";
    std::string const Arguments::Operation_Generate = "generate";
    std::string const Arguments::Operation_Show     = "show";
    std::string const Arguments::Operation_Check    = "check";

    std::string const Arguments::Mode_Recursive = "recursive";
    std::string const Arguments::Mode_Iterative = "iterative";

    std::string const Arguments::Difficulty_Easy   = "easy";
    std::string const Arguments::Difficulty_Medium = "medium";
    std::string const Arguments::Difficulty_Hard   = "hard";
    std::string const Arguments::Difficulty_Expert = "expert";

    Arguments::Arguments(int argc, char ** argv)
        : argc_(argc)
        , argv_(argv)
        , help_(false)
        , verbose_(false)
        , replace_(false)
        , pretty_(false)
        , indexes_(false)
        , allowSpace_(false)
        , mode_(Mode_Recursive)
        , difficulty_(Generator::Difficulty::Easy)
    {
    }

    void Arguments::usage() const {
        std::cout << "Usage\n"
                  << '\t' << argv_[0] << " <operation> <options>\n"
                  << "\nOperations\n"
                  << '\t' << " " << Operation_Solve << "    : Solve puzzle\n"
                  << '\t' << " " << Operation_Generate << " : Generate puzzle\n"
                  << '\t' << " " << Operation_Show << "     : Show puzzle\n"
                  << '\t' << " " << Operation_Check << "    : Check puzzle\n"
                  << "\nOptions\n"
                  << '\t' << "-h       : Print usage\n"
                  << '\t' << "-v       : Verbose mode\n"
                  << '\t' << "-f       : Force saving if file already exists\n"
                  << '\t' << "-y       : Pretty print board\n"
                  << '\t' << "-i       : Show row and column indexes with pretty print option\n"
                  << '\t' << "-w       : Allow Space when checking a puzzle\n"
                  << '\t' << "-p <arg> : Read input puzzle / boad from given filename (required by solve and show)\n"
                  << '\t' << "-s <arg> : Save resulting puzzle / board to given filename (optional with solve and generate)\n"
                  << '\t' << "-m <arg> : Solver mode; one of " << modeListString() << " (optional with solve, default=" << Mode_Recursive << ")\n"
                  << '\t' << "-d <arg> : Generator difficulty level; one of " << difficultyListString() << " (optional with generate, default=" << Difficulty_Easy << ")\n"
                  << std::endl;
    }

    void Arguments::parse() {
        for (int i = 1; i < argc_; ++i) {
            std::string const arg = argv_[i];
            if      (arg == "-h") { help_ = true; return; }
            else if (arg == "-v") { verbose_ = true; }
            else if (arg == "-f") { replace_ = true; }
            else if (arg == "-y") { pretty_ = true; }
            else if (arg == "-i") { indexes_ = true; }
            else if (arg == "-w") { allowSpace_ = true; }
            else if (arg == "-p") { puzzleFilename_ = readArg("-p", i); }
            else if (arg == "-s") { saveFilename_ = readArg("-s", i); }
            else if (arg == "-m") { mode_ = readArg("-m", i); }
            else if (arg == "-d") { difficulty_ = stringToDifficulty(readArg("-d", i)); }
            else if (operation_.empty()) {
                if (arg != Operation_Solve && arg != Operation_Generate && arg != Operation_Show && arg != Operation_Check) {
                    throw std::runtime_error(std::string("Unsupported operation - ") + arg);
                }
                operation_ = arg;
            }
            else {
                throw std::runtime_error(std::string("Unknown argument - ") + arg);
            }
        }

        validate();
    }

    char const * Arguments::readArg(char const * name, int & i) {
        if (++i >= argc_) {
            throw std::runtime_error(std::string("Premature end of arguments - ") + name);
        }
        return argv_[i];
    }

    void Arguments::validate()
    {
        if (operation_.empty()) {
            throw std::runtime_error("Missing operation");
        }

        if (replace_ && saveFilename_.empty()) {
            throw std::runtime_error("Cannot force saving if no save file specified");
        }

        if (isSolveOperation() && puzzleFilename_.empty()) {
            throw std::runtime_error("Solve operation requires input puzzle file");
        }

        if (isGenerateOperation() && !puzzleFilename_.empty()) {
            throw std::runtime_error("Cannot use input puzzle file with generate operation");
        }

        if (isShowOperation()) {
            if (puzzleFilename_.empty()) {
                throw std::runtime_error("Show operation requires input puzzle file");
            }

            if (!saveFilename_.empty()) {
                throw std::runtime_error("Cannot use save puzzle file with show operation");
            }                
        }

        if (!isModeRecursive() && !isModeIterative()) {
            throw std::runtime_error("Invalid mode");
        }
    }

    Generator::Difficulty Arguments::stringToDifficulty(std::string const & str)
    {
        if      (str == Difficulty_Easy)   { return Generator::Difficulty::Easy; }
        else if (str == Difficulty_Medium) { return Generator::Difficulty::Medium; }
        else if (str == Difficulty_Hard)   { return Generator::Difficulty::Hard; }
        else if (str == Difficulty_Expert) { return Generator::Difficulty::Expert; }

        throw std::runtime_error(std::string("Unknown difficulty - ") + str);
        return Generator::Difficulty::Easy;
    }

    std::string const & Arguments::difficultyToString(Generator::Difficulty difficulty)
    {
        static std::string const Unknown = "unknown";

        switch (difficulty) {
        case Generator::Difficulty::Easy:   return Difficulty_Easy;
        case Generator::Difficulty::Medium: return Difficulty_Medium;
        case Generator::Difficulty::Hard:   return Difficulty_Hard;
        case Generator::Difficulty::Expert: return Difficulty_Expert;
        }

        return Unknown;
    }

    std::string Arguments::difficultyListString()
    {
        return Difficulty_Easy + ", " + Difficulty_Medium + ", " + Difficulty_Hard + ", " + Difficulty_Expert;
    }

    std::string Arguments::modeListString()
    {
        return Mode_Recursive + ", " + Mode_Iterative;
    }

}
