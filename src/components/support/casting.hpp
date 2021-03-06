#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_CASTING_HPP
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_CASTING_HPP

#include <type_traits>

namespace components::support {
	namespace detail {
		template< class T, class U >
		concept SameHelper = std::is_same_v<T, U>;
	}

	template< class T, class U >
	concept same_as = detail::SameHelper<T, U> && detail::SameHelper<U, T>;

	template <typename T>
	concept CastingDerived = requires (T t) {
		{ t.validate_exists() } -> same_as<void>;
	};

	/**
	 *
	 * @tparam T
	 * @tparam Derived - The derived class type.
	 *          Requirements:
	 *              * The derived class should implement the public function validate_exists() which should return void.
	 *                  Purpose: To validate if the param was initialized or not.
	 */
	template <typename T, typename Derived>
	class casting {
	public:
		casting(T &param) : param(param) {}
		casting(casting&&) = default;
		casting(const casting&) = default;
		casting& operator=(const casting &ref) {
			param = ref.param;
			return *this;
		}

		virtual ~casting() = default;

		operator T() const {
			static_cast<const Derived&>(*this).validate_exists();
			return param;
		}

		operator const T&() const {
			static_cast<const Derived&>(*this).validate_exists();
			return param;
		}

		operator T&() {
			static_cast<Derived&>(*this).validate_exists();
			return param;
		}

		operator T*() {
			static_cast<Derived&>(*this).validate_exists();
			return &param;
		}

	private:
		T &param;
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_SUPPORT_CASTING_HPP