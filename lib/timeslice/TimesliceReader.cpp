//! \author Michael Krieger

#include "TimesliceReader.hpp"

namespace spadic {

void TimesliceReader::add_timeslice(const fles::Timeslice& ts)
{
    for (size_t c {0}; c < ts.num_components(); c++) {
        for (size_t m {0}; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
            add_mc({p, desc.size});
        }
    }
}

void TimesliceReader::add_mc(const flib_dpb::MicrosliceContents& mc)
{
    for (auto& dtm : mc.dtms()) {
        auto& reader = _readers[dtm.data[0]];
        reader.add_buffer(dtm.data+1, dtm.size-1);
    }
}

} // namespace
