#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H

#include <boost/property_tree/ptree.hpp>
#include "interface.h"
#include "../../tools/decorator_support_functions.h"
#include "../support/single.h"
#include "../support/group.h"
#include "../support/collection.h"

//namespace components::request {

    class components_request_interface_core : public components_request_interface {
    public:
	    components_request_interface_core() = default;

        explicit components_request_interface_core(const boost::property_tree::ptree &json) {}

        virtual ~components_request_interface_core() = default;

        [[nodiscard]] virtual std::shared_ptr<components_request_interface> clone() const {
            return std::make_shared<components_request_interface_core>(*this);
        }

        [[nodiscard]] bool operator==(const components_request_interface_core &ref) const { return true; }
        [[nodiscard]] bool operator<(const components_request_interface_core &ref) const { return false; }
    };

    template <typename ...Components>
    using components_request_component_base_if_not_exists = components_tools_base_if_not_exists_t<components_request_interface_core, Components...>;

    template <typename T>
    concept components_request_Component = components_tools_Component<components_request_interface_core, T>;

    template <typename T, bool IsOptional, T(*ExtractParamFunction)(const boost::property_tree::ptree &), typename ...Components>
    using components_request_single = components_request_support_single<components_request_interface, components_request_interface_core, T, IsOptional, ExtractParamFunction, Components...>;

    template <typename T, typename ...Components>
    using components_request_non_json_single = components_request_support_non_json_single<components_request_interface, components_request_interface_core, T, Components...>;

    template <typename ...Components>
    using components_request_group = components_request_support_group<components_request_interface, components_request_interface_core, Components...>;

    template <typename T, template<typename ...> typename CollectionT,
            bool IsOptional,
            bool(*ExtractColF)(CollectionT<T>&, const boost::property_tree::ptree &, bool is_optional),
            const char* FieldName, unsigned N, std::std_basic_fixed_string<N> FieldHierarchy, typename ...Components>
    using components_request_collection = components_request_support_collection<components_request_interface, components_request_interface_core, T, CollectionT, IsOptional, ExtractColF, FieldName, N, FieldHierarchy, Components...>;
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_CORE_H