#ifndef CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_H
#define CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_H

#include <memory>

//namespace components::request {

    class components_request_interface {
    public:
        virtual ~components_request_interface() = default;

	    [[nodiscard]] virtual std::shared_ptr<components_request_interface> clone() const = 0;
    };
//}

#endif //CPP_DECORATOR_COMPONENTS_USAGE_EXAMPLE_REQUEST_INTERFACE_H