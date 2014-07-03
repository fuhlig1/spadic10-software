//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include "Timeslice.hpp"

namespace spadic {

struct DTM {
    const uint16_t *data;
    size_t size;
};

struct MicrosliceContents {
    const uint16_t *data;
    size_t size;
    std::vector<DTM> get_dtms() const;
};

struct TimesliceReader
{
    void read(const fles::Timeslice& ts);

private:
    void process_raw(const MicrosliceContents& mc);
};

} // namespace

#endif
