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
            auto data = reinterpret_cast<const uint16_t*>(p+DESC_OFFSET);
            size_t len = (desc.size-DESC_OFFSET)/sizeof(uint16_t);
            process_raw(data, len);
        }
    }
}

void TimesliceReader::process_raw(const uint16_t *data, size_t len)
{
    if (!len) { return; }
    std::cout << std::endl << "----------- ";
    for (auto i = 0; i < len; i++) {
        if (!(i%4)) { std::cout << std::endl; }
        std::cout << " " << HEX(data[i]);
    }
    std::cout << std::endl;
}

} // namespace
