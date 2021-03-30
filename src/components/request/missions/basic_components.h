#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H

#include "../interfaces/interface_core.h"
#include "components_functions.h"

// Non Json Structures
#include "structures/parent_id.h"
#include "structures/parent_ip.hpp"

//namespace components::request::missions::basic {

	template <std::std_basic_fixed_string Hierarchy>
    using components_request_missions_basic_ip = components_request_single<std::size_t, false, components_request_missions_functions_ip_func<Hierarchy>>;

	using components_request_missions_basic_mission_ip = components_request_missions_basic_ip<"pc">;

    using components_request_missions_basic_id = components_request_single<std::size_t, false, components_request_missions_functions_id_func>;

    using components_request_missions_basic_parent_id = components_request_non_json_single<components_request_structures_parent_id>;

    using components_request_missions_basic_parent_ip = components_request_non_json_single<components_request_structures_parent_ip>;

    using components_request_missions_basic_parent_data = components_request_group<components_request_missions_basic_parent_id, components_request_missions_basic_parent_ip>;

    using components_request_missions_basic_mission_id = components_request_single<std::size_t, false, components_request_missions_functions_mission_id_func>;

    using components_request_missions_basic_mission_type = components_request_single<libraries::mission_types_parser::mission_names, false, components_request_missions_functions_mission_type_func>;

    namespace components_request_missions_basic_dependency_md {
        template<typename T>
        using collection_t = std::vector<T>;

        using dependency = components_request_group<components_request_missions_basic_id, components_request_missions_basic_ip<"">>;

        using single_component_name = dependency;

        using collection = collection_t<single_component_name>;

        constexpr char field_name[] = "dependencies";

        template<bool IsOptional = false, std::std_basic_fixed_string field_hierarchy = "">
        using dependencies = components_request_collection<
                single_component_name,
                collection_t,
                IsOptional,
		        components_request_missions_functions_general_collection_func<collection_t<single_component_name>, field_name>,
                field_name,
                field_hierarchy, field_hierarchy>;
    }

    using components_request_missions_basic_mission_identifier = components_request_missions_basic_dependency_md::dependency;

    using components_request_missions_basic_mt1 = components_request_single<components_request_structures_mt1, true, components_request_missions_functions_mt1_func>;

    using components_request_missions_basic_mt2 = components_request_single<components_request_structures_mt2, false, components_request_missions_functions_mt2_func>;

    template<components_request_Component ...Components>
    using components_request_missions_basic_mission = components_request_group<
            // Non Json Components
            components_request_missions_basic_parent_data,

            // Json Components
            components_request_missions_basic_mission_id,
			components_request_missions_basic_mission_ip,
			components_request_missions_basic_mission_type,
		    components_request_missions_basic_dependency_md::dependencies<true>,
            Components...
    >;
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H