#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_MISSION_TYPES_PARSER_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_MISSION_TYPES_PARSER_H

#include <typeindex>
#include <map>
#include <string>

namespace libraries {

    class mission_types_parser {
    public:
        enum mission_names {
            MT_CONTAINER,
            MT1,
            MT2,
        };

    public:
        static std::type_index get_component(mission_names mission_name);

	    static mission_names get_mission_name(std::type_index component);

	    static mission_names get_mission_name(std::string &&mission_stringify_name);

	    static std::string get_mission_stringify_name(mission_names mission_type);


    private:
	    static const std::map<mission_names, std::type_index> components_mapper;
	    static const std::map<std::string, mission_names> names_mapper;
    };
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_SRC_LIBRARIES_MISSION_TYPES_PARSER_H