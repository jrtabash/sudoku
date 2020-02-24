#ifndef SUDOKU_ARGUMENTS_H
#define SUDOKU_ARGUMENTS_H

#include "sudoku_generator.h"

#include <string>

namespace Sudoku {

    class Arguments {
    private:
        static std::string const Operation_Solve;
        static std::string const Operation_Generate;
        static std::string const Operation_Show;

        static std::string const Difficulty_Easy;
        static std::string const Difficulty_Medium;
        static std::string const Difficulty_Hard;
        static std::string const Difficulty_Expert;

    public:
        Arguments(int argc, char ** argv);

        void usage() const;
        void parse();

    public:
        inline bool help() const noexcept;
        inline bool verbose() const noexcept;
        inline bool replace() const noexcept;
        inline bool pretty() const noexcept;
        
        inline std::string const & puzzleFilename() const noexcept;
        inline std::string const & saveFilename() const noexcept;

        inline std::string const & operation() const noexcept;
        inline bool isSolveOperation() const noexcept;
        inline bool isGenerateOperation() const noexcept;
        inline bool isShowOperation() const noexcept;
        
        inline Generator::Difficulty difficulty() const noexcept;
        inline std::string const & difficultyString() const noexcept;

    private:
        char const * readArg(char const * name, int & i);

        void validate();

        static Generator::Difficulty stringToDifficulty(std::string const & str);
        static std::string const & difficultyToString(Generator::Difficulty difficulty);
        static std::string difficultyListString();

    private:
        int argc_;
        char ** argv_;
        bool help_;
        bool verbose_;
        bool replace_;
        bool pretty_;
        std::string puzzleFilename_;
        std::string saveFilename_;
        std::string operation_;
        Generator::Difficulty difficulty_;
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline bool Arguments::help() const noexcept
    {
        return help_;
    }

    inline bool Arguments::verbose() const noexcept
    {
        return verbose_;
    }

    inline bool Arguments::replace() const noexcept
    {
        return replace_;
    }

    inline bool Arguments::pretty() const noexcept
    {
        return pretty_;
    }

    inline std::string const & Arguments::puzzleFilename() const noexcept
    {
        return puzzleFilename_;
    }

    inline std::string const & Arguments::saveFilename() const noexcept
    {
        return saveFilename_;
    }

    inline std::string const & Arguments::operation() const noexcept
    {
        return operation_;
    }

    inline bool Arguments::isSolveOperation() const noexcept
    {
        return operation_ == Operation_Solve;
    }

    inline bool Arguments::isGenerateOperation() const noexcept
    {
        return operation_ == Operation_Generate;
    }

    inline bool Arguments::isShowOperation() const noexcept
    {
        return operation_ == Operation_Show;
    }

    inline Generator::Difficulty Arguments::difficulty() const noexcept
    {
        return difficulty_;
    }

    inline std::string const & Arguments::difficultyString() const noexcept
    {
        return difficultyToString(difficulty_);
    }

}

#endif // SUDOKU_ARGUMENTS_H
