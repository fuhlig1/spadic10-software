#include <iostream>
//#include <stdexcept>
#include "TimesliceInputArchive.hpp"
#include "TimesliceDebugger.hpp"

TimesliceDebugger d;

void read_timeslice(const fles::Timeslice& ts)
{
    std::cout << d.dump_timeslice(ts) << std::endl;
    for (auto c = 0; c < ts.num_components(); c++) {
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            auto& desc = ts.descriptor(c, m);
            auto p = ts.content(c, m);
            std::cout << d.dump_microslice(desc, p) << std::endl;
        }
    }
}

int main_(int argc, char* argv[])
{
    fles::TimesliceInputArchive ar(argv[1]);
    while (auto p = ar.get()) {
        read_timeslice(*p);
    }
    return 0;
}

int main(int argc, char* argv[])
{
    try {
        return main_(argc, argv);
    }
    catch (std::logic_error& e) {
        std::cout << "Please specify path to .tsa file." << std::endl;
        return 1;
    }
    catch (boost::archive::archive_exception& e) {
        std::cout << "Could not read \"" << argv[1] <<
                     "\" as .tsa file." << std::endl;
        return 1;
    }
}
