#include <array>
#include <cassert>
#include <memory>
#include <type_traits>

#include "core/matrix.hpp"

using treelang::Matrix;
using treelang::MatrixRow;

namespace
{
    void test_copyable_matrix()
    {
        Matrix<int, 3, 4> m;
        for (size_t i = 0; i < 3; ++i)
            for (size_t j = 0; j < 4; ++j) m[i][j] = static_cast<int>(i * 4 + j);

        const auto &cm = m;
        assert(cm[2][3] == 11);

        Matrix<int, 3, 4> c{m};
        assert(c[1][2] == 6);
        c = m;
        assert(c[0][0] == 0);

        Matrix<int, 3, 4> mv = std::move(c);
        assert(mv[1][2] == 6);
        m = std::move(mv);
        assert(m[1][2] == 6);

        std::array<std::array<int, 4>, 3> raw = {
            {{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}}};
        Matrix<int, 3, 4> from_copy{raw};
        assert(from_copy[2][3] == 11);

        auto raw2 = std::array<std::array<int, 4>, 3>{{{0, 1, 2, 3}, {4, 5, 6, 7}, {8, 9, 10, 11}}};
        Matrix<int, 3, 4> from_move{std::move(raw2)};
        assert(from_move[2][0] == 8);

        MatrixRow<int, 4> row{raw[1]};
        assert(row[0] == 4 && row[3] == 7);
        const MatrixRow<int, 4> &crow = row;
        assert(crow[1] == 5);

        static_assert(std::is_default_constructible_v<Matrix<int, 3, 4>>);
        static_assert(std::is_copy_constructible_v<Matrix<int, 3, 4>>);
        static_assert(std::is_move_constructible_v<Matrix<int, 3, 4>>);
        static_assert(std::is_copy_assignable_v<Matrix<int, 3, 4>>);
        static_assert(std::is_move_assignable_v<Matrix<int, 3, 4>>);
    }

    void test_double_matrix()
    {
        Matrix<double, 2, 2> m;
        m[0][0] = 1.5;
        const MatrixRow<double, 2> &r = m[1];
        (void)r;
        assert(m[0][0] == 1.5);
    }

    void test_move_only_matrix()
    {
        Matrix<std::unique_ptr<int>, 2, 2> m;
        for (size_t i = 0; i < 4; ++i)
            m[i / 2][i % 2] = std::make_unique<int>(static_cast<int>(i));

        auto src = std::array<std::array<std::unique_ptr<int>, 2>, 2>{
            {std::array<std::unique_ptr<int>, 2>{std::make_unique<int>(10), std::make_unique<int>(11)},
             std::array<std::unique_ptr<int>, 2>{std::make_unique<int>(12), std::make_unique<int>(13)}}};
        Matrix<std::unique_ptr<int>, 2, 2> mv{std::move(src)};
        assert(*mv[0][0] == 10);
        assert(*mv[1][1] == 13);

        Matrix<std::unique_ptr<int>, 2, 2> dst;
        dst = std::move(mv);
        assert(*dst[1][1] == 13);

        static_assert(!std::is_copy_constructible_v<Matrix<std::unique_ptr<int>, 2, 2>>);
        static_assert(!std::is_copy_assignable_v<Matrix<std::unique_ptr<int>, 2, 2>>);
        static_assert(std::is_move_constructible_v<Matrix<std::unique_ptr<int>, 2, 2>>);
        static_assert(std::is_move_assignable_v<Matrix<std::unique_ptr<int>, 2, 2>>);
    }
}

int main()
{
    test_copyable_matrix();
    test_double_matrix();
    test_move_only_matrix();
    return 0;
}
