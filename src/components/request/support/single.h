#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "../../tools/concepts/concepts.h"
#include "../../tools/decorator_support_functions.h"
#include "../../support/exceptions.h"
#include "../../support/casting.hpp"

namespace components::request::support {

	template<typename T>
	concept SingleComponentContainedType = requires(T t) {
		{ T() };
		{ T() < T() };
		{ T() == T() };
		{ t = T() };
	};

	/**
	 *
	 * @tparam Base
	 * @tparam BaseCore
	 * @tparam T - The type to contain in this component.
	 *          Requirements (see SingleComponentContainedType concept):
	 *              * The type should have default constructor.
	 *              * The type should implement the operator<
	 *              * The type should implement the operator==
	 *              * The type should implement the operator=(const T&)
	 *
	 * @tparam ExtractParamFunction
	 * @tparam Components
	 */
	template<typename Base, typename BaseCore, SingleComponentContainedType T, bool IsOptional,
			T(*ExtractParamFunction)(const boost::property_tree::ptree &), tools::Component<BaseCore> ...Components>
	class single : virtual public tools::base_if_not_exists_t<BaseCore, Components...>,
	               public components::support::casting<T, single<Base, BaseCore, T, IsOptional, ExtractParamFunction, Components...>>,
	               public Components ... {
	private:
		using this_t = single<Base, BaseCore, T, IsOptional, ExtractParamFunction, Components...>;

	public:
		single() : components::support::casting<T, this_t>(param), is_exists(true) {}

		single(const boost::property_tree::ptree &json) : components::support::casting<T, this_t>(param), Components(json)... {
			try {
				param = ExtractParamFunction(json);
				is_exists = true;
			} catch (std::exception &e) {
				if (!IsOptional) throw;
				field_name_if_not_exists = e.what();
			}
		}

		single(const single &ref) :
				components::support::casting<T, this_t>(param),
				param(ref.param),
				is_exists(ref.is_exists),
				Components(static_cast<Components &>(ref))... {}

		virtual ~single() = default;

		[[nodiscard]] virtual std::shared_ptr<Base> clone() const {
			return std::make_shared<single>(*this);
		}

		[[nodiscard]] bool empty() const {
			validate_exists();
			return param == T(); // TODO Consider a better alternative to check whether the field is empty or not (contains an important data or contains nothing).
		}

		bool operator==(const this_t &ref) const {
			validate_exists();
			bool res = ((dynamic_cast<const Components &>(*this) == dynamic_cast<const Components &>(ref)) && ...);
			return res && param == ref.param;
		}

		bool operator<(
				const this_t &ref) const { // TODO Prepare a Unit Test to check this method when there are other components in the inheritance hierarchy
			validate_exists();
			size_t first_to_lower = 0, first_to_bigger = 0;
			bool is_lower = ((++first_to_lower && (dynamic_cast<const Components &>(*this) < dynamic_cast<const Components &>(ref))) || ...);
			bool is_bigger = ((++first_to_bigger && (dynamic_cast<const Components &>(ref) < dynamic_cast<const Components &>(*this))) || ...);
			return is_lower && first_to_lower < first_to_bigger ||
			       first_to_lower == first_to_bigger && param < ref.param;
		}

		void validate_exists() const {
			if (!is_exists) throw components::support::optional_child_not_set_exception(field_name_if_not_exists);
		}

	private:
		T param;
		bool is_exists = false;
		std::string field_name_if_not_exists;
	};

    template<typename T>
    auto constexpr empty_func = [](const boost::property_tree::ptree &) { return T(); };

	template<typename Base, typename BaseCore, SingleComponentContainedType T, tools::Component<BaseCore> ...Components>
	using non_json_single = single<Base, BaseCore, T, true, empty_func<T>, Components...>;
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H