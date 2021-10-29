#include "json_parser.h"

namespace libraries {
	components::request::interface_core *
	json_parser::get_mission_component(std::type_index &ti, const boost::property_tree::ptree &json) {
		return analyze_mission_component(ti, json);
	}

	components::request::interface_core *
	json_parser::analyze_mission_component(std::type_index &ti, const boost::property_tree::ptree &json) {
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

	void json_parser::foo(typename components::request::missions::basic::mission<> *m) {

	}
}