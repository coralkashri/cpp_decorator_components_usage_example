#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H

#include "basic_components.h"

namespace components::request::missions {

    template <typename ...Components>
    using mission_component = group<basic::mission<>, Components...>;

    using mt1_mission = mission_component<basic::mt1>;

    using mt2_mission = mission_component<basic::mt2>;

    using mt_container_mission = mission_component<>;
}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_MISSIONS_COMPONENTS_H