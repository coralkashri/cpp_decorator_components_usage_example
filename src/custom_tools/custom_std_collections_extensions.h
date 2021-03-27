#ifndef SDR_KINGDOM_DISPATCHER_CUSTOM_STD_COLLECTIONS_EXTENSIONS_H
#define SDR_KINGDOM_DISPATCHER_CUSTOM_STD_COLLECTIONS_EXTENSIONS_H

namespace std {
    /// @brief Or (||) condition between the elem to every element on the left side collection for equality.
    template <typename T, template<typename...> typename Cont>
    bool operator==(T elem, Cont<T> &&collection) {
        bool res = false;
        for (auto const &col_elem : collection) {
            res = res || elem == col_elem;
        }
        return res;
    }
}

#endif //SDR_KINGDOM_DISPATCHER_CUSTOM_STD_COLLECTIONS_EXTENSIONS_H