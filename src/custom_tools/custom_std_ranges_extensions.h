#ifndef SDR_KINGDOM_DISPATCHER_CUSTOM_STD_RANGES_EXTENSIONS_H
#define SDR_KINGDOM_DISPATCHER_CUSTOM_STD_RANGES_EXTENSIONS_H

namespace std {

    template <typename Cont, typename Range>
    Cont convert_range_to(Range &&range) {
        return Cont(range.begin(), range.end());
    }
}

#endif //SDR_KINGDOM_DISPATCHER_CUSTOM_STD_RANGES_EXTENSIONS_H