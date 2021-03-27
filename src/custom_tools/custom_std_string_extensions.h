#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_CUSTOM_STD_STRING_EXTENSIONS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_CUSTOM_STD_STRING_EXTENSIONS_H

#include <string>

namespace std {
    std::string unquote(const std::string &src);

    /* Attention! The following "std_basic_fixed_string" extension is an accepted proposal as described in the following SO response:
     * https://stackoverflow.com/a/58841797/8038186
     * Which means that in the moment it will be implemented by gcc, the following definition must be erased and replaced with the compiler implementation.
     */
    template<unsigned N>
    struct std_basic_fixed_string {
        char buf[N + 1]{};
        constexpr std_basic_fixed_string(char const* s) {
            for (unsigned i = 0; i != N; ++i) buf[i] = s[i];
        }
        constexpr std_basic_fixed_string(const std_basic_fixed_string<N> &ref) {
            for (unsigned i = 0; i != N; ++i) buf[i] = ref.buf[i];
        }
        constexpr operator char const*() const { return buf; }
        constexpr operator unsigned() const { return N; }
    };
    template<unsigned N> std_basic_fixed_string(char const (&)[N]) -> std_basic_fixed_string<N - 1>;
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_CUSTOM_STD_STRING_EXTENSIONS_H