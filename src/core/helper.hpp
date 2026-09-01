#ifndef INCLUDE_TREELANG_CORE_HELPER_HPP
#define INCLUDE_TREELANG_CORE_HELPER_HPP

#include <cstddef>
#include <tuple>

namespace treelang
{
    namespace detail
    {
        template <typename Arr, typename Func>
        constexpr auto transform_array_impl(Arr &&arr, Func &&func)
        {
            using ArrType = std::remove_cvref_t<Arr>;
            constexpr size_t N = std::tuple_size_v<ArrType>;

            using ElemType = decltype(std::forward<Arr>(arr)[0]);
            using ResultType = std::remove_cvref_t<std::invoke_result_t<Func, ElemType>>;

            std::array<ResultType, N> dst{};
            for (size_t i = 0; i < N; ++i) dst[i] = func(std::forward<Arr>(arr)[i]);

            return dst;
        }
    }

    template <typename T, size_t N, typename Func>
    constexpr auto transform_array(const std::array<T, N> &arr, Func &&func)
    {
        return detail::transform_array_impl(arr, std::forward<Func>(func));
    }

    template <typename T, size_t N, typename Func>
    constexpr auto transform_array(std::array<T, N> &&arr, Func &&func)
    {
        return detail::transform_array_impl(std::move(arr), std::forward<Func>(func));
    }
}

#endif  // INCLUDE_TREELANG_CORE_HELPER_HPP