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

// decode a single microslice
void TimesliceReader::process_raw(const uint16_t *data, size_t len)
{
    if (!len) { return; }
    std::cout << std::endl << "----------- ";

    // iterate over DTMs
    const uint16_t *end = data + len;
    while (data < end) {
        // first word is framing
        size_t j = 0;
        size_t dtm_len = (data[j++] & 0xFF);
        std::cout << std::endl << " nnll";
        // iterate over DTM contents
        if (dtm_len) {
            // first word is CBMnet source address
            uint16_t cbm_addr = data[j++];
            std::cout << " aaaa";
            // rest should be payload
            size_t dtm_end = j + dtm_len;
            while (j < dtm_end) {
                if (!(j%4)) { std::cout << std::endl; }
                std::cout << " " << HEX(data[j++]);
            }
        }
        // skip padding
        while (j%4) {
            std::cout << " pppp";
            j++;
        }
        data += j;
        std::cout << std::endl;
    }
}

} // namespace
