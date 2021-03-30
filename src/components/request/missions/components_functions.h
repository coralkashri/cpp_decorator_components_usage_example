#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COMPONENTS_REQUEST_MISSIONS_FUNCTIONS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COMPONENTS_REQUEST_MISSIONS_FUNCTIONS_H

#include <iostream>
#include <vector>
#include <boost/property_tree/ptree.hpp>
#include <boost/algorithm/string.hpp>
#include "structures/mt1.hpp"
#include "structures/mt2.hpp"
#include "../../../libraries/mission_types_parser.h"
#include "../../../custom_tools/custom_std_string_extensions.h"
#include "../../../custom_tools/custom_boost_ptree_extensions.h"

//namespace components::request::missions::functions {

	template <std::std_basic_fixed_string Hierarchy>
    auto constexpr inline components_request_missions_functions_ip_func = [](const boost::property_tree::ptree &json) {
    	std::string stringify_hierarchy = std::string(Hierarchy);
    	std::string field_name = "ip";
    	std::string field_path = stringify_hierarchy.empty() ? field_name : stringify_hierarchy + "." + field_name;
        auto stringify_ip = json.get<std::string>(field_path);
        std::vector <std::string> ip_parts;
        boost::split(ip_parts, stringify_ip, boost::is_any_of("."));
        size_t numerical_ip =
                std::stoi(ip_parts[0]) * 16777216 +
                std::stoi(ip_parts[1]) * 65536 +
                std::stoi(ip_parts[2]) * 256 +
                std::stoi(ip_parts[3]);
        return numerical_ip;
    };

    auto constexpr inline components_request_missions_functions_id_func = [](const boost::property_tree::ptree &json) {
        return json.get<size_t>("id");
    };

    auto constexpr inline components_request_missions_functions_mission_id_func = [](const boost::property_tree::ptree &json) {
        return json.get<size_t>("missionId");
    };

    auto constexpr inline components_request_missions_functions_mission_type_func = [](const boost::property_tree::ptree &json) {
    	using libraries::mission_types_parser;
        auto stringify_mission_type = json.get<std::string>("missionType");
        return mission_types_parser::get_mission_name(std::move(stringify_mission_type));
    };

    auto constexpr inline components_request_missions_functions_type_func = [](const boost::property_tree::ptree &json) {
        return json.get<std::string>("type");
    };

    auto constexpr inline components_request_missions_functions_mt1_func = [](const boost::property_tree::ptree &json) {
        const std::string hierarchy = "missionParams";
        return components_request_structures_mt1 {
                .param1 = json.get<std::string>(hierarchy + ".param1"),
                .param2 = json.get<double>(hierarchy + ".param2")
        };
    };

    auto constexpr inline components_request_missions_functions_mt2_func = [](const boost::property_tree::ptree &json) {
		const std::string hierarchy = "missionParams";
		return components_request_structures_mt2 {
				.p1 = json.get<int>(hierarchy + ".p1"),
				.p2 = json.get<int>(hierarchy + ".p2"),
				.p3 = json.get<int>(hierarchy + ".p3")
		};
	};

    template <typename Collection, const char* ColJsonKey>
    auto constexpr inline components_request_missions_functions_general_collection_func = [](Collection &collection, const boost::property_tree::ptree &json, bool is_optional) -> bool {
        std::optional<boost::property_tree::ptree> child;
        if (is_optional)
            child = boost::property_tree::get_optional<boost::property_tree::ptree>(json, ColJsonKey);
        else
            child = json.get_child(ColJsonKey);
        if (!child) return false;
        for (auto &elem : child.value()) {
            collection.emplace_back(elem.second);
        }
        return true;
    };
//}

#endif // CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_COMPONENTS_REQUEST_MISSIONS_FUNCTIONS_H