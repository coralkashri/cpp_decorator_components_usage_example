#include <gtest/gtest.h>
#include <boost/property_tree/ptree.hpp>
#include "components/request/missions/components.h"
#include "../src/components/tools/access_functions.h"
#include "../src/components/support/exceptions.h"
#include "../src/libraries/json_parser.h"
#include "../src/libraries/mission_types_parser.h"

TEST (request_components, operators) {
    boost::property_tree::ptree json1, json2;
    json1.put("id", 5);
    json1.put("ip", "0.0.0.1");

    json2.put("id", 5);
    json2.put("ip", "0.0.0.1");

    components::request::missions::basic::dependency_md::dependency d1(json1), d2(json2);
    EXPECT_TRUE(d1 == d2);
    EXPECT_FALSE(d1 < d2);
    EXPECT_FALSE(d2 < d1);

    json1.erase("ip");
    json1.put("ip", "0.0.1.0");

    components::request::missions::basic::dependency_md::dependency d3(json1), d4(json2);
    EXPECT_FALSE(d3 == d4);
    EXPECT_FALSE(d3 < d4);
    EXPECT_TRUE(d4 < d3);

    json2.erase("id");
    json2.put("id", 6);

    components::request::missions::basic::dependency_md::dependency d5(json1), d6(json2);
    EXPECT_FALSE(d5 == d6);
    EXPECT_TRUE(d5 < d6);
    EXPECT_FALSE(d6 < d5);
}

TEST (request_components, master_split) {
    boost::property_tree::ptree json;
    boost::property_tree::read_json("../tests/support_files/container.json", json);

    components::request::missions::basic::mission<> master_mission(json);
    EXPECT_EQ((size_t)components::tools::access_field<components::request::missions::basic::mission_id>(master_mission), 5);

    size_t iteration = 0;
    for (auto &related_mission_json : json.get_child("missionParams.related_missions")) {
        iteration++;
	    components::request::interface_core* mission = new components::request::missions::mt2_mission(related_mission_json.second);
	    auto mt2_mission = dynamic_cast<components::request::missions::mt2_mission*>(mission);

        // ID
        EXPECT_EQ(*(size_t*)components::tools::access_field<components::request::missions::basic::mission_id>(mt2_mission), 5 + iteration);

        // Parent ID
        (components::tools::access_field<components::request::structures::parent_id, components::request::missions::basic::parent_id>(mt2_mission)).id = (size_t)(components::request::missions::basic::mission_id&)(master_mission);
	    EXPECT_EQ((*(components::request::structures::parent_id*)components::tools::access_field<components::request::missions::basic::parent_id>(mt2_mission)).id, 5);

	    // Prent IP
	    (components::tools::access_field<components::request::structures::parent_ip, components::request::missions::basic::parent_ip>(mt2_mission)).ip = (components::request::missions::basic::mission_ip&)(master_mission);
	    EXPECT_EQ((*(components::request::structures::parent_ip*)components::tools::access_field<components::request::missions::basic::parent_ip>(mt2_mission)).ip, 256);

        // Mission Params
        auto data = components::tools::access_field<components::request::structures::mt2>(*mt2_mission);
        switch (iteration) {
            case 1:
                EXPECT_EQ(data.p1, 10);
                EXPECT_EQ(data.p2, 20);
                EXPECT_EQ(data.p3, 30);
                break;

            case 2:
	            EXPECT_EQ(data.p1, 100);
		        EXPECT_EQ(data.p2, 200);
		        EXPECT_EQ(data.p3, 300);
                break;

            default:
                EXPECT_FALSE(true); // The file is not corresponding to the test, please update the test or restore the file.
                break;
        }

        delete mt2_mission;
    }
    EXPECT_EQ(iteration, 2);
}

TEST (request_components, json_parser) {
	using libraries::mission_types_parser;

	boost::property_tree::ptree json;
	boost::property_tree::read_json("../tests/support_files/json_parser_container.json", json);

	components::request::missions::basic::mission<> master_mission(json);
	size_t iteration = 0;
	for (auto &related_mission_json : json.get_child("missionParams.related_missions")) {
		iteration++;
		std::type_index t = typeid(nullptr);
		components::request::interface_core* mission = libraries::json_parser::get_mission_component(t, related_mission_json.second);
		auto basic_mission_data = dynamic_cast<components::request::missions::basic::mission<>*>(mission);
		libraries::json_parser::foo(basic_mission_data);
		auto mission_name_from_type = mission_types_parser::get_mission_name(t);

//		EXPECT_EQ((size_t)components::tools::access_field<components::request::missions::basic::mission_id>(basic_mission_data), 5 + iteration);

		switch (iteration) {
			case 1:
				EXPECT_EQ(mission_name_from_type, libraries::mission_types_parser::mission_names::MT1);
				break;

			case 2:
				EXPECT_EQ(mission_name_from_type, libraries::mission_types_parser::mission_names::MT2);
				break;

			case 3:
				EXPECT_EQ(mission_name_from_type, libraries::mission_types_parser::mission_names::MT1);
				break;

			case 4:
				EXPECT_EQ(mission_name_from_type, libraries::mission_types_parser::mission_names::MT1);
				break;

			default:
				EXPECT_FALSE(true); // The file is not corresponding to the test, please update the test or restore the file.
				break;
		}

		delete mission;
	}

	EXPECT_EQ(iteration, 4);
}