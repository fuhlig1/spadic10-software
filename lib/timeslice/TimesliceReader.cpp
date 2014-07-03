//! \author Michael Krieger

#include "TimesliceReader.hpp"
#include <iostream>
#include <iomanip>

// macro stolen from tsclient
#define HEX(X) std::setw(4) << std::setfill('0') << std::hex << (X)

#define DESC_OFFSET 16

namespace spadic {

void TimesliceReader::read(const fles::Timeslice& ts)
{
    for (auto c = 0; c < ts.num_components(); c++) {
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);

            // interpret as 16 bit words, skip descriptor offset
            auto mc_data = reinterpret_cast<const uint16_t*>(p+DESC_OFFSET);
            auto mc_size = (desc.size-DESC_OFFSET)/sizeof(uint16_t);
            fles::MicrosliceContents mc {mc_data, mc_size};
            process_raw(mc);
        }
    }
}

// decode a single microslice
void TimesliceReader::process_raw(const fles::MicrosliceContents& mc)
{
    const auto& dtms = mc.dtms();
    if (!dtms.size()) { return; }
    std::cout << std::endl << "-----------";

    // iterate over DTMs
    for (const auto& dtm : dtms) {
        // first word is CBMnet source address
        uint16_t cbm_addr = dtm.data[0];
        std::cout << std::endl << "      aaaa";
        // rest should be payload
        for(auto i = 1; i < dtm.size; i++) {
            if (!((i+1)%4)) { std::cout << std::endl; }
            std::cout << " " << HEX(dtm.data[i]);
        }
        std::cout << std::endl;
    }
}


} // namespace
