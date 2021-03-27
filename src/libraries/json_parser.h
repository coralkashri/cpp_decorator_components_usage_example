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
		static components::request::interface_core* get_mission_component(std::type_index &ti, const boost::property_tree::ptree &json) {
			return analyze_mission_component(ti, json);
		}

	private:
		static components::request::interface_core* analyze_mission_component(std::type_index &ti, const boost::property_tree::ptree &json) {
			components::request::missions::basic::mission<> mission_md(json);
			auto mission_name = (components::request::missions::basic::mission_type)mission_md;
			switch (mission_name) {
				case mission_types_parser::MT1:
					ti = typeid(components::request::missions::mt1_mission);
					return new components::request::missions::mt1_mission(json);

				case mission_types_parser::MT2:
					ti = typeid(components::request::missions::mt2_mission);
					return new components::request::missions::mt2_mission(json);

				default:
					throw exceptions::mission_name_not_found_in_analyzer_exception(mission_types_parser::get_mission_stringify_name(mission_name));
			}
		}
	};
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_JSON_PARSER_H
