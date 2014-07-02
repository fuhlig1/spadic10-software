#include <iostream>
#include <stdexcept>
#include "TimesliceInputArchive.hpp"

void read_timeslice(const fles::Timeslice& ts)
{
    for (auto c = 0; c < ts.num_components(); c++) {
        std::cout << "component " << c << std::endl;
        for (auto m = 0; m < ts.num_microslices(c); m++) {
            //auto& ms_desc = ts.descriptor(c, m);
            //auto p = ts.content(c, m);
            std::cout << "  microslice " << m << std::endl;
        }
    }
}

int main(int argc, char* argv[])
{
    std::cout << argv[1] << std::endl;
    fles::TimesliceInputArchive ar(argv[1]);
    return 0;
}
