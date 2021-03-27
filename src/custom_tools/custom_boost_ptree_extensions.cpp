#include "custom_boost_ptree_extensions.h"

namespace boost::property_tree {

    std::string to_string(const ptree &json) {
        std::stringstream oss;
        write_json(oss, json);
        return oss.str();
    }

    template <>
    std::optional<ptree> get_optional(const ptree &json, ptree::key_type const &key) {
        std::optional<ptree> res;
        auto boost_optional = json.get_child_optional(key);
        if (boost_optional)
            res = boost_optional.get();
        return res;
    }
}