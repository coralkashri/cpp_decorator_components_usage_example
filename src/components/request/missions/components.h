#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H

#include "basic_components.h"

//namespace components::request::missions {

    template <typename ...Components>
    using components_request_missions_mission_component = components_request_group<components_request_missions_basic_mission<>, Components...>;

    using components_request_missions_mt1_mission = components_request_missions_mission_component<components_request_missions_basic_mt1>;

    using components_request_missions_mt2_mission = components_request_missions_mission_component<components_request_missions_basic_mt2>;

    using components_request_missions_mt_container_mission = components_request_missions_mission_component<>;
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H