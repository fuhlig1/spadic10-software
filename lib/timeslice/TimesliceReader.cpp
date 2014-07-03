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
            MicrosliceContents mc;
            mc.data = reinterpret_cast<const uint16_t*>(p+DESC_OFFSET);
            mc.size = (desc.size-DESC_OFFSET)/sizeof(uint16_t);
            process_raw(mc);
        }
    }
}

// decode a single microslice
void TimesliceReader::process_raw(const MicrosliceContents& mc)
{
    if (!mc.size) { return; }
    std::cout << std::endl << "-----------";

    // iterate over DTMs
    for (const DTM& dtm : mc.get_dtms()) {
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

// extract pointers to DTMs from a microslice
std::vector<DTM> MicrosliceContents::get_dtms() const
{
    std::vector<DTM> v;
    const uint16_t *w = data;
    const uint16_t *end = data + size;
    while (w < end) {
        size_t i = 0;
        size_t len = (w[i++] & 0xFF) + 1;
        if (len > 1) {
            v.push_back(DTM {w+i, len});
            i += len;
        }
        i += (~i & 3) + 1; // skip padding (i -> k*4)
        w += i; // update data pointer
    }
    return v;
}

} // namespace
