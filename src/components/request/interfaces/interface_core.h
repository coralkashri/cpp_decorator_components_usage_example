#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H

#include <boost/property_tree/ptree.hpp>
#include "interface.h"
#include "../../tools/decorator_support_functions.h"
#include "../support/single.h"
#include "../support/group.h"
#include "../support/collection.h"

namespace components::request {

    class interface_core : public interface {
    public:
        interface_core() = default;

        explicit interface_core(const boost::property_tree::ptree &json) {}

        virtual ~interface_core() = default;

        [[nodiscard]] virtual std::shared_ptr<interface> clone() const {
            return std::make_shared<interface_core>(*this);
        }

        [[nodiscard]] bool operator==(const interface_core &ref) const { return true; }
        [[nodiscard]] bool operator<(const interface_core &ref) const { return false; }
    };

    template <typename ...Components>
    using component_base_if_not_exists = typename tools::base_if_not_exists<interface_core, Components...>;

    template <typename T>
    concept Component = tools::Component<interface_core, T>;

    template <typename T, bool IsOptional, T(*ExtractParamFunction)(const boost::property_tree::ptree &), typename ...Components>
    using single = support::single<interface, interface_core, T, IsOptional, ExtractParamFunction, Components...>;

    template <typename T, typename ...Components>
    using non_json_single = support::non_json_single<interface, interface_core, T, Components...>;

    template <typename ...Components>
    using group = support::group<interface, interface_core, Components...>;

    template <typename T, template<typename ...> typename CollectionT,
            bool IsOptional,
            bool(*ExtractColF)(CollectionT<T>&, const boost::property_tree::ptree &, bool is_optional),
            const char* FieldName, unsigned N, std::std_basic_fixed_string<N> FieldHierarchy, typename ...Components>
    using collection = support::collection<interface, interface_core, T, CollectionT, IsOptional, ExtractColF, FieldName, N, FieldHierarchy, Components...>;
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H