#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_ACCESS_FUNCTIONS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_ACCESS_FUNCTIONS_H

#include <iostream>

namespace components::tools {

    template <typename RequestedT, typename ComponentT>
    requires (!std::is_pointer_v<ComponentT>)
    inline RequestedT& access_field(ComponentT &component) {
        return (RequestedT&)(component);
    }

	template <typename RequestedT, typename ComponentT>
	requires (std::is_base_of_v<RequestedT, ComponentT>)
	inline RequestedT& access_field(ComponentT *component) {
		return *dynamic_cast<RequestedT *>(component);
	}

	template <typename RequestedT, typename ComponentT>
	requires (std::is_base_of_v<ComponentT, RequestedT>)
	inline RequestedT* access_field(ComponentT *component) {
		return dynamic_cast<RequestedT *>(component);
	}

	template <typename RequestedT, typename RequestedComponentT, typename ComponentT>
	requires (!std::is_base_of_v<ComponentT, RequestedT> && (std::is_base_of_v<ComponentT, RequestedComponentT> || std::is_base_of_v<RequestedComponentT, ComponentT>))
	inline RequestedT& access_field(ComponentT *component) {
		return (RequestedT&)*dynamic_cast<RequestedComponentT*>(component);
	}

    template <typename RequestedT, typename ComponentT>
    RequestedT access_copy_field(ComponentT &component) {
        return (const RequestedT&)(component);
    }

	template <typename RequestedT, typename ComponentT>
	RequestedT access_copy_field(ComponentT *component) {
		return *dynamic_cast<const RequestedT*>(component);
	}

    template <typename RequestedT, typename Collection, typename ComponentT>
    RequestedT& access_collection_element(ComponentT &component, size_t index) {
        return (RequestedT&)((Collection&)component)[index];
    }
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_TOOLS_ACCESS_FUNCTIONS_H