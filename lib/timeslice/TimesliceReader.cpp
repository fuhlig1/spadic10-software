//! \author Michael Krieger

#include "TimesliceReader.hpp"
#include <iostream>
#include <iomanip>

// macro stolen from tsclient
#define HEX(X) std::setw(4) << std::setfill('0') << std::hex << (X)

namespace spadic {

void TimesliceReader::read(const fles::Timeslice& ts)
{
    for (auto c = 0; c < ts.num_components(); c++) {
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            for (auto dtm : ts.microslice_contents(c, m)) {
                process_dtm(dtm);
            }
        }
    }
}

void TimesliceReader::process_raw(const fles::MicrosliceContents& mc)
{
    const auto& dtms = mc.dtms();
    if (!dtms.size()) { return; }
    std::cout << std::endl << "-----------";

    // iterate over DTMs
    for (const auto& dtm : dtms) {
    }
}

void TimesliceReader::process_dtm(const fles::DTM& dtm)
{
    // first word is CBMnet source address
    std::cout << std::endl << "      aaaa";
    // rest should be payload
    for (size_t i = 1; i < dtm.size; i++) {
        if (!((i+1)%4)) { std::cout << std::endl; }
        std::cout << " " << HEX(dtm.data[i]);
    }
    std::cout << std::endl;
}

} // namespace
