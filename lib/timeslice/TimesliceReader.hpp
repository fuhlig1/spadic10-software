//! \author Michael Krieger

/**
 * Read SPADIC Messages out of Timeslices containing Microslices using the
 * "packed DTM" format.
 */

#ifndef SPADIC_TIMESLICE_READER
#define SPADIC_TIMESLICE_READER

#include <unordered_map>
#include <unordered_set>

#include "Message.h"
#include "Timeslice.hpp"
#include "MicrosliceContents.hpp"

namespace spadic {

struct TimesliceReader
{
    TimesliceReader();
    ~TimesliceReader();

    void add_timeslice(const fles::Timeslice& ts);
    std::unordered_set<uint16_t> sources();
    std::unique_ptr<spadic::Message> get_message(uint16_t source_addr);

private:
    struct TimesliceReader_;
    std::unique_ptr<TimesliceReader_> _t;
};

} // namespace

#endif
