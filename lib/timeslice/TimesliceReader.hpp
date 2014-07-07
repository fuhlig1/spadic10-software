//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include "Timeslice.hpp"
#include "MicrosliceContents.hpp"

namespace spadic {


struct TimesliceReader
{
    void add_timeslice(const fles::Timeslice& ts);

private:
};

} // namespace

#endif
