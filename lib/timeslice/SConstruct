# ex: syntax=python

import os

env = Environment(CXX='clang++', CCFLAGS=['-std=c++11'])
env.Append(ENV={'TERM': os.environ['TERM']}) # clang color output

try:
    env.Append(FLES_DIR=os.environ['FLES_DIR'],
               CPPPATH=['$FLES_DIR/lib/fles_ipc'])
except KeyError:
    raise SystemExit("Please set the FLES_DIR environment variable "
                     "to the root of the flesnet source tree.")

fles_ipc = env.Library(env.Glob('$FLES_DIR/lib/fles_ipc/*.cpp'))

env.Program('tsreader',
            source=['timeslice_reader.cpp'],
            LIBS=[fles_ipc, 'boost_serialization'])
