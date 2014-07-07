//! \author Michael Krieger

#include <iostream>
#include "TimesliceInputArchive.hpp"
#include "TimesliceReader.hpp"

void read_timeslice_archive(const std::string& filename)
{
    fles::TimesliceInputArchive ar {filename};
    spadic::TimesliceReader r;

    while (auto p = ar.get()) {
        r.add_timeslice(*p);
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
                     "\" as Timeslice archive." << std::endl;
        return 1;
    }
}
