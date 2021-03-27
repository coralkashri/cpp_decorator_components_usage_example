#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT2_HPP
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT2_HPP

namespace components::request::structures {

	struct mt2 {
		int p1, p2, p3;

		[[nodiscard]] bool operator==(const mt2 &ref) const {
			return p1 == ref.p1 && p2 == ref.p2 && p3 == ref.p3;
		}

		[[nodiscard]] bool operator<(const mt2 &ref) const {
			return p1 < ref.p1 || p2 < ref.p2 || p3 < ref.p3;
		}
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_MT2_HPP