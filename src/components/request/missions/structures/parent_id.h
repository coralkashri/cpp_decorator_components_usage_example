#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_PARENT_ID_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_PARENT_ID_H

//namespace components::request::structures {

    struct components_request_structures_parent_id {
        size_t id;

        [[nodiscard]] bool operator==(const components_request_structures_parent_id &ref) const {
            return id == ref.id;
        }

        [[nodiscard]] bool operator<(const components_request_structures_parent_id &ref) const {
            return id < ref.id;
        }
    };
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_PARENT_ID_H