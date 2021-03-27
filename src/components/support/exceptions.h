#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_EXCEPTIONS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_EXCEPTIONS_H

#include <exception>

namespace components::support {

    class optional_child_not_set_exception : public std::exception {
    public:
        explicit optional_child_not_set_exception(const std::string &field_name) : field_name(field_name) {
            msg = "Optional child was not set at the initialize part.";
            if (!field_name.empty()) msg += " Illegal field access: " + field_name + ".";
        }

        [[nodiscard]] const char *what() const noexcept {
            return msg.c_str();
        }

    private:
        std::string msg;
        std::string field_name;
    };
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_EXCEPTIONS_H