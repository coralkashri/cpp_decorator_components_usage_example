#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H

#include <iostream>
#include <boost/property_tree/ptree.hpp>
#include "../../tools/concepts/concepts.h"
#include "../../tools/decorator_support_functions.h"
#include "../../support/exceptions.h"
#include "../../support/casting.hpp"

//namespace components::request::support {

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
			T(*ExtractParamFunction)(
					const boost::property_tree::ptree &), components_tools_Component<BaseCore> ...Components>
	class components_request_support_single
			: virtual public components_tools_base_if_not_exists_t<BaseCore, Components...>,
			  public components_support_casting<T, components_request_support_single<Base, BaseCore, T, IsOptional, ExtractParamFunction, Components...>>,
			  public Components ... {
	private:
		using this_t = components_request_support_single<Base, BaseCore, T, IsOptional, ExtractParamFunction, Components...>;

	public:
		components_request_support_single() : components_support_casting<T, this_t>(param), is_exists(true) {}

		components_request_support_single(const boost::property_tree::ptree &json)
				: components_support_casting<T, this_t>(param), Components(json)... {
			try {
				param = ExtractParamFunction(json);
				is_exists = true;
			} catch (std::exception &e) {
				if (!IsOptional) throw;
				field_name_if_not_exists = e.what();
			}
		}

		components_request_support_single(const components_request_support_single &ref) :
				components_support_casting<T, this_t>(param),
				param(ref.param),
				is_exists(ref.is_exists),
				Components(static_cast<Components &>(ref))... {}

		virtual ~components_request_support_single() = default;

		[[nodiscard]] virtual std::shared_ptr<Base> clone() const {
			return std::make_shared<components_request_support_single>(*this);
		}

		[[nodiscard]] bool empty() const {
			validate_exists();
			return param ==
			       T(); // TODO Consider a better alternative to check whether the field is empty or not (contains an important data or contains nothing).
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
			bool is_lower = ((++first_to_lower && (dynamic_cast<const Components &>(*this) <
			                                       dynamic_cast<const Components &>(ref))) || ...);
			bool is_bigger = ((++first_to_bigger && (dynamic_cast<const Components &>(ref) <
			                                         dynamic_cast<const Components &>(*this))) || ...);
			return is_lower && first_to_lower < first_to_bigger ||
			       first_to_lower == first_to_bigger && param < ref.param;
		}

		void validate_exists() const {
			if (!is_exists) throw components_support_optional_child_not_set_exception(field_name_if_not_exists);
		}

	private:
		T param;
		bool is_exists = false;
		std::string field_name_if_not_exists;
	};

	template<typename T>
	auto constexpr components_request_support_empty_func = [](const boost::property_tree::ptree &) { return T(); };

	template<typename Base, typename BaseCore, SingleComponentContainedType T, components_tools_Component<BaseCore> ...Components>
	using components_request_support_non_json_single = components_request_support_single<Base, BaseCore, T, true, components_request_support_empty_func<T>, Components...>;
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SINGLE_H