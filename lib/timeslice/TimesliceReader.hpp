//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

//#include "Timeslice.hpp"
#include "TimesliceDebugger.hpp"

namespace spadic {

struct TimesliceReader
{
    void read(const fles::Timeslice& ts);

private:
    TimesliceDebugger d;
};

} // namespace

#endif
