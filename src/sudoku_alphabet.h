#ifndef SUDOKU_LETTERS_H
#define SUDOKU_LETTERS_H

#include <array>

namespace Sudoku {

    using Letter = int;
    using LetterList = std::array<Letter, 9>;

    struct Alphabet {
        static constexpr LetterList all() { return {1, 2, 3, 4, 5, 6, 7, 8, 9 }; }

        static constexpr Letter space() { return 0; }
        static constexpr Letter first() { return 1; }
        static constexpr Letter last()  { return 9; }
        static constexpr Letter end()   { return 10; }

        static inline Letter next(Letter letter) noexcept;
    };

    // --------------------------------------------------------------------------------
    // INLINE

    inline Letter Alphabet::next(Letter letter) noexcept
    {
        return letter < Alphabet::end() ? letter + 1 : Alphabet::end();
    }

}

#endif // SUDOKU_LETTERS_H
