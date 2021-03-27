#ifndef SDR_KINGDOM_DISPATCHER_CUSTOM_BOOST_PTREE_EXTENSIONS_H
#define SDR_KINGDOM_DISPATCHER_CUSTOM_BOOST_PTREE_EXTENSIONS_H

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>

namespace boost::property_tree {
    template<template<typename ...> typename Cont, typename ContType, typename ReadValFuncT>
    Cont<ContType> as_container(ptree const &pt,
                                ptree::key_type const &key,
                                ReadValFuncT &&read_val_function = [] (auto &&val) { return val.template get_value<ContType>(); }) {
        Cont<ContType> r;
        for (auto &item : pt.get_child(key))
            r.push_back(read_val_function(item.second));
        return r;
    }

    template<template<typename ...> typename Cont, typename ContType, typename ReadValFuncT>
    Cont<ContType> as_container(ptree const &pt,
                                ptree::key_type const &key,
                                const ptree &default_value,
                                ReadValFuncT &&read_val_function = [] (auto &&val) { return val.template get_value<ContType>(); }) {
        Cont<ContType> r;
        for (auto &item : pt.get_child(key, default_value))
            r.push_back(read_val_function(item.second));
        return r;
    }

    std::string to_string(const ptree &json);

    template <typename T>
    std::optional<T> get_optional(const ptree &json, ptree::key_type const &key) {
        std::optional<T> res;
        auto boost_optional = json.template get_optional<T>(key);
        if (boost_optional)
            res = boost_optional.get();
        return res;
    }

    template <> std::optional<ptree> get_optional(const ptree &json, ptree::key_type const &key);
}

#endif //SDR_KINGDOM_DISPATCHER_CUSTOM_BOOST_PTREE_EXTENSIONS_H