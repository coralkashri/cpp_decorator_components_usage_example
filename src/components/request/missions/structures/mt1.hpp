#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT1_HPP
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT1_HPP

#include <iostream>

namespace components::request::structures {

	struct mt1 {
		std::string param1;
		double param2;

		[[nodiscard]] bool operator==(const mt1 &ref) const {
			return param1 == ref.param1 && param2 == ref.param2;
		}

		[[nodiscard]] bool operator<(const mt1 &ref) const {
			return param1 < ref.param1 || param2 < ref.param2;
		}
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT1_HPP
