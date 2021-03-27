#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COLLECTION_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COLLECTION_H

#include "../../support/exceptions.h"
#include "../../support/casting.hpp"
#include "../../tools/concepts/concepts.h"
#include "../../../custom_tools/custom_std_string_extensions.h"
#include "../../../custom_tools/custom_boost_ptree_extensions.h"

namespace components::request::support {

    template<typename Base, typename BaseCore, typename T, template<typename ...> typename CollectionT,
            bool IsOptional,
            bool(*ExtractColF)(CollectionT<T>&, const boost::property_tree::ptree &, bool is_optional),
            const char* FieldName,
            unsigned N, std::std_basic_fixed_string<N> FieldHierarchy,
            tools::Component<BaseCore> ...Components>
    class collection :
            virtual public tools::base_if_not_exists_t<BaseCore, Components...>,
            public components::support::casting<CollectionT<T>, collection<Base, BaseCore, T, CollectionT, IsOptional, ExtractColF, FieldName, N, FieldHierarchy, Components...>>,
            public Components ... {
    private:
        using this_t = collection<Base, BaseCore, T, CollectionT, IsOptional, ExtractColF, FieldName, N, FieldHierarchy, Components...>;

    public:
        collection() : components::support::casting<CollectionT<T>, this_t>(col), is_exists(true) {}

        collection(const boost::property_tree::ptree &json) : components::support::casting<CollectionT<T>, this_t>(col), Components(json)... {
            std::optional<boost::property_tree::ptree> child;
            if (IsOptional)
                child = boost::property_tree::get_optional<boost::property_tree::ptree>(json, std::string(FieldHierarchy));
            else
                child = json.get_child(std::string(FieldHierarchy));
            if (child) is_exists = ExtractColF(col, child.value(), IsOptional);
        }

        collection(const collection &ref) :
	        components::support::casting<CollectionT<T>, this_t>(col),
            col(ref.col),
            is_exists(ref.is_exists),
            Components(static_cast<Components&>(ref))...
        {}

        virtual ~collection() = default;

        [[nodiscard]] virtual std::shared_ptr<Base> clone() const {
            return std::make_shared<collection>(*this);
        }

        bool operator==(const this_t &ref) const {
	        validate_exists();
            bool res = ((dynamic_cast<const Components&>(*this) == dynamic_cast<const Components&>(ref)) && ...);
            return res && col == ref.col;
        }

        bool operator<(const this_t &ref) const { // TODO Prepare a Unit Test to check this method when there are other components in the inheritance hierarchy
	        validate_exists();
            size_t first_to_lower = 0, first_to_bigger = 0;
            bool is_lower = ((++first_to_lower && (dynamic_cast<const Components&>(*this) < dynamic_cast<const Components&>(ref))) || ...);
            bool is_bigger = ((++first_to_bigger && (dynamic_cast<const Components&>(ref) < dynamic_cast<const Components&>(*this))) || ...);
            return is_lower && first_to_lower < first_to_bigger || first_to_lower == first_to_bigger && col < ref.col;
        }

	    void validate_exists() const {
		    if (!is_exists) throw components::support::optional_child_not_set_exception(std::string(FieldHierarchy) + "." + FieldName);
	    }

    private:
        CollectionT<T> col;
        bool is_exists = false;
    };
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COLLECTION_H