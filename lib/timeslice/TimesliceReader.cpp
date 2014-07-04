//! \author Michael Krieger

#include "TimesliceReader.hpp"
#include <iostream>
#include <iomanip>

// macro stolen from tsclient
#define HEX(X) std::setw(4) << std::setfill('0') << std::hex << (X)

namespace spadic {

void TimesliceReader::read(const fles::Timeslice& ts)
{
    for (size_t c {0}; c < ts.num_components(); c++) {
        for (size_t m {0}; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
            process_raw({p, desc.size});
        }
    }
}

void TimesliceReader::process_raw(const flib_dpb::MicrosliceContents& mc)
{
    const auto& dtms = mc.dtms();
    if (!dtms.size()) { return; }
    std::cout << std::endl << "-----------";

    // iterate over DTMs
    for (const auto& dtm : dtms) {
        process_dtm(dtm);
    }
}

void TimesliceReader::process_dtm(const flib_dpb::DTM& dtm)
{
    // first word is CBMnet source address
    std::cout << std::endl << "      aaaa";
    // rest should be payload
    for (size_t i {1}; i < dtm.size; i++) {
        if (!((i+1)%4)) { std::cout << std::endl; }
        std::cout << " " << HEX(dtm.data[i]);
    }
    std::cout << std::endl;
}

} // namespace
