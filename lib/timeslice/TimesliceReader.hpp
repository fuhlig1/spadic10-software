//! \author Michael Krieger

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include "Timeslice.hpp"
#include "MicrosliceContents.hpp"

namespace spadic {


struct TimesliceReader
{
    void read(const fles::Timeslice& ts);

private:
    void process_raw(const flib_dpb::MicrosliceContents& mc);
    void process_dtm(const flib_dpb::DTM& dtm);
};

} // namespace

#endif
