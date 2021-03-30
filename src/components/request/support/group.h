#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_GROUP_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_GROUP_H

#include "../../tools/concepts/concepts.h"

//namespace components::request::support {

    template<typename Base, typename BaseCore, components_tools_Component<BaseCore> ...Components>
    class components_request_support_group : virtual public components_tools_base_if_not_exists_t<BaseCore, Components...>,
                  public Components ... {
    private:
        using this_t = components_request_support_group<Base, BaseCore, Components...>;

    public:
	    components_request_support_group() = default;

	    components_request_support_group(const boost::property_tree::ptree &json) : Components(json)... {}

        virtual ~components_request_support_group() = default;

        [[nodiscard]] virtual std::shared_ptr<Base> clone() const {
            return std::make_shared<components_request_support_group>(*this);
        }

        bool operator==(const this_t &ref) const {
            return ((dynamic_cast<const Components&>(*this) == dynamic_cast<const Components&>(ref)) && ...);
        }

        bool operator<(const this_t &ref) const {
            size_t first_to_lower = 0, first_to_bigger = 0;
            bool is_lower = ((++first_to_lower && (dynamic_cast<const Components&>(*this) < dynamic_cast<const Components&>(ref))) || ...);
            bool is_bigger = ((++first_to_bigger && (dynamic_cast<const Components&>(ref) < dynamic_cast<const Components&>(*this))) || ...);
            return is_lower && first_to_lower <= first_to_bigger;
        }
    };
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_GROUP_H