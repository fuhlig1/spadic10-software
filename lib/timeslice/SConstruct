# ex: syntax=python

import os

use_clang = True

# basic compiler settings
env = Environment(CCFLAGS=['-std=c++11'])
if use_clang:
    env.Replace(CXX='clang++')
    env.Append(ENV={'TERM': os.environ['TERM']}) # for color output

# set path to flesnet sources
try:
    env.Replace(FLES_DIR=os.environ['FLES_DIR'])
except KeyError:
    raise SystemExit("Please set the FLES_DIR environment variable "
                     "to the root of the flesnet source tree.")

# build fles_ipc library
env.Append(CPPPATH=['$FLES_DIR/lib/fles_ipc'])
fles_ipc = env.Library(env.Glob('$FLES_DIR/lib/fles_ipc/*.cpp'))

# build timeslice debugger
env.Append(CPPPATH=['$FLES_DIR/app/tsclient'])
ts_debugger = env.Library('$FLES_DIR/app/tsclient/TimesliceDebugger.cpp')

#---------------------------------------------------------------------

# build application
env.Program('tsreader', ['timeslice_reader.cpp', 'TimesliceReader.cpp'],
            LIBS=[fles_ipc, ts_debugger, 'boost_serialization'])
