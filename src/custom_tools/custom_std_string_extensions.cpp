#include "custom_std_string_extensions.h"

namespace std {
    std::string unquote(const std::string &src) {
        auto target = src;
        target.erase(remove(target.begin(), target.end(), '\"' ), target.end());
        return target;
    }
}