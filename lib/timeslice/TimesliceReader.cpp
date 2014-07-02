//! \author Michael Krieger

#include "TimesliceReader.hpp"
#include <iostream>

namespace spadic {

void TimesliceReader::read(const fles::Timeslice& ts)
{
    std::cout << d.dump_timeslice(ts);
    for (auto c = 0; c < ts.num_components(); c++) {
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
        }
    }
}

} // namespace
