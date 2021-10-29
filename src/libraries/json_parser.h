#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_H

#include <typeindex>
#include <boost/property_tree/ptree.hpp>
#include "../components/request/interfaces/interface_core.h"
#include "../components/request/missions/components.h"
#include "mission_types_parser.h"
#include "json_parser_exceptions.hpp"

namespace libraries {

	class json_parser {
	public:
		static components::request::interface_core* get_mission_component(std::type_index &ti, const boost::property_tree::ptree &json);

		static void foo(typename components::request::missions::basic::mission<>* m);

	private:
		static components::request::interface_core* analyze_mission_component(std::type_index &ti, const boost::property_tree::ptree &json);
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_H
