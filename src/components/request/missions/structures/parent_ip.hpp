#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_PARENT_IP_HPP
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_PARENT_IP_HPP

namespace components::request::structures {

	struct parent_ip {
		size_t ip;

		[[nodiscard]] bool operator==(const parent_ip &ref) const {
			return ip == ref.ip;
		}

		[[nodiscard]] bool operator<(const parent_ip &ref) const {
			return ip < ref.ip;
		}
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_COMPONENTS_REQUEST_MISSIONS_STRUCTURES_PARENT_IP_HPP