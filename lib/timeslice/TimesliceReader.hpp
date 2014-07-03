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
    MicrosliceContents(const uint16_t *data, size_t size);
    // TODO construct from MicrosliceDescriptor (but it lacks the data)
    std::vector<DTM> get_dtms() const { return _dtms; };
    size_t size() const { return _size; };
private:
    const uint16_t *_data;
    size_t _size;
    void init_dtms();
    std::vector<DTM> _dtms;
};

struct TimesliceReader
{
    void read(const fles::Timeslice& ts);

private:
    void process_raw(const MicrosliceContents& mc);
};

} // namespace

#endif
