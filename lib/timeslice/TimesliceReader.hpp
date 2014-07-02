//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include "Timeslice.hpp"

namespace spadic {

struct TimesliceReader
{
    void read(const fles::Timeslice& ts);

private:
    void process_raw(const uint16_t *data, size_t len);
};

} // namespace

#endif
