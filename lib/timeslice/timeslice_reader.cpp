#include <iostream>
#include "TimesliceInputArchive.hpp"
#include "TimesliceDebugger.hpp"

TimesliceDebugger d;

void read_timeslice(const fles::Timeslice& ts)
{
    std::cout << d.dump_timeslice(ts);
    for (auto c = 0; c < ts.num_components(); c++) {
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
        }
    }
}

void read_timeslice_archive(const std::string& filename)
{
    fles::TimesliceInputArchive ar(filename);
    while (auto p = ar.get()) {
        read_timeslice(*p);
    }
}

int main(int argc, char* argv[])
{
    std::string filename;
    try {
        filename = argv[1];
        read_timeslice_archive(filename);
        return 0;
    }
    catch (std::logic_error& e) {
        std::cout << "Please specify path to .tsa file." << std::endl;
        return 1;
    }
    catch (boost::archive::archive_exception& e) {
        std::cout << "Could not read \"" << filename <<
                     "\" as .tsa file." << std::endl;
        return 1;
    }
}
