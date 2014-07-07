//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include <unordered_map>
#include "Message.h"
#include "Timeslice.hpp"
#include "MicrosliceContents.hpp"

namespace spadic {

typedef std::unordered_map<uint16_t, spadic::MessageReader> reader_map;

struct TimesliceReader
{
    void add_timeslice(const fles::Timeslice& ts);
    const reader_map& readers() { return _readers; };

private:
    void add_mc(const flib_dpb::MicrosliceContents& mc);
    reader_map _readers; // one MessageReader per CBMnet source address
};

} // namespace

#endif
