#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_DECORATOR_SUPPORT_FUNCTIONS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_DECORATOR_SUPPORT_FUNCTIONS_H

#include <type_traits>

//namespace components::tools {
    class temp_inheritance {};

    template <typename Base, typename ...Decorators>
    struct components_tools_base_if_not_exists {
        static constexpr bool value = sizeof...(Decorators);
        using type = typename std::conditional_t<value, temp_inheritance, Base>;
    };

    template <typename Base, typename ...Decorators>
    using components_tools_base_if_not_exists_t = typename components_tools_base_if_not_exists<Base, Decorators...>::type;

    template <typename Base, typename ...Decorators>
    inline constexpr bool components_tools_base_if_not_exists_v = components_tools_base_if_not_exists<Base, Decorators...>::value;
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_DECORATOR_SUPPORT_FUNCTIONS_H