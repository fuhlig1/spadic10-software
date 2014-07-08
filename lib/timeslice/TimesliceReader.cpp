//! \author Michael Krieger

#include "TimesliceReader.hpp"

namespace spadic {

void TimesliceReader::add_timeslice(const fles::Timeslice& ts)
{
    for (size_t c {0}; c < ts.num_components(); c++) {
        for (size_t m {0}; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
            // TODO check sys_id, sys_version
            // TODO check same source address from different components
            add_mc({p, desc.size});
        }
    }
}

std::unordered_set<uint16_t> TimesliceReader::sources()
{
    std::unordered_set<uint16_t> result;
    for (auto& item : _readers) {
        auto addr = item.first;
        result.insert(addr);
    }
    return result;
}

std::unique_ptr<spadic::Message>
TimesliceReader::get_message(uint16_t source_addr)
{
    return _readers[source_addr].get_message();
}

void TimesliceReader::add_mc(const flib_dpb::MicrosliceContents& mc)
{
    for (auto& dtm : mc.dtms()) {
        auto& reader = _readers[dtm.data[0]];
        reader.add_buffer(dtm.data+1, dtm.size-1);
    }
}

} // namespace
