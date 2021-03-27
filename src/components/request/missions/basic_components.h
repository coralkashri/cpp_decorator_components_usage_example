#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H

#include "../interfaces/interface_core.h"
#include "components_functions.h"

// Non Json Structures
#include "structures/parent_id.h"
#include "structures/parent_ip.hpp"

namespace components::request::missions::basic {

	template <std::std_basic_fixed_string Hierarchy>
    using ip = single<std::size_t, false, functions::ip_func<Hierarchy>>;

	using mission_ip = ip<"pc">;

    using id = single<std::size_t, false, functions::id_func>;

    using parent_id = non_json_single<structures::parent_id>;

    using parent_ip = non_json_single<structures::parent_ip>;

    using parent_data = group<parent_id, parent_ip>;

    using mission_id = single<std::size_t, false, functions::mission_id_func>;

    using mission_type = single<libraries::mission_types_parser::mission_names, false, functions::mission_type_func>;

    namespace dependency_md {
        template<typename T>
        using collection_t = std::vector<T>;

        using dependency = group<id, ip<"">>;

        using single_component_name = dependency;

        using collection = collection_t<single_component_name>;

        constexpr char field_name[] = "dependencies";

        template<bool IsOptional = false, std::std_basic_fixed_string field_hierarchy = "">
        using dependencies = request::collection<
                single_component_name,
                collection_t,
                IsOptional,
                functions::general_collection_func<collection_t<single_component_name>, field_name>,
                field_name,
                field_hierarchy, field_hierarchy>;
    }

    using mission_identifier = dependency_md::dependency;

    using mt1 = single<structures::mt1, true, functions::mt1_func>;

    using mt2 = single<structures::mt2, false, functions::mt2_func>;

    template<Component ...Components>
    using mission = group<
            // Non Json Components
		    parent_data,

            // Json Components
            mission_id,
		    mission_ip,
            mission_type,
            dependency_md::dependencies<true>,
            Components...
    >;
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_MISSION_BASIC_COMPONENTS_H