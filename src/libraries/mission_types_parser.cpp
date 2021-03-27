#include "mission_types_parser.h"
#include "components/request/missions/components.h"

namespace libraries {

	const std::map<mission_types_parser::mission_names, std::type_index> mission_types_parser::components_mapper = {
			{mission_names::MT1,          typeid(components::request::missions::mt1_mission)},
			{mission_names::MT2,          typeid(components::request::missions::mt2_mission)},
			{mission_names::MT_CONTAINER, typeid(components::request::missions::mt_container_mission)},
	};

	const std::map<std::string, mission_types_parser::mission_names> mission_types_parser::names_mapper = {
			{"mt1",          mission_names::MT1},
			{"mt2",          mission_names::MT2},
			{"mt3",          mission_names::MT1},
			{"mt4",          mission_names::MT1},
			{"mt_container", mission_names::MT_CONTAINER},
	};

	std::type_index mission_types_parser::get_component(mission_types_parser::mission_names mission_name) {
		return components_mapper.at(mission_name);
	}

	mission_types_parser::mission_names mission_types_parser::get_mission_name(std::type_index component) {
		auto result = std::find_if(components_mapper.begin(), components_mapper.end(), [component](auto &key_val) {
			return key_val.second == component;
		});
		if (result == components_mapper.end())
			throw std::out_of_range("Requested type_index was not found in mission_types_manager.");
		return result->first;
	}

	mission_types_parser::mission_names mission_types_parser::get_mission_name(std::string &&mission_stringify_name) {
		return names_mapper.at(mission_stringify_name);
	}

	std::string mission_types_parser::get_mission_stringify_name(mission_types_parser::mission_names mission_type) {
		auto result = std::find_if(names_mapper.begin(), names_mapper.end(), [mission_type](auto &key_val) {
			return key_val.second == mission_type;
		});
		if (result == names_mapper.end())
			throw std::out_of_range("Requested type_index was not found in mission_types_manager.");
		return result->first;
	}
}