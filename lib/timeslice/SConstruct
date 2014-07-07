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

# build flib_dpb library
env.Append(CPPPATH=['$FLES_DIR/lib/flib_dpb'])
flib_dpb = env.Library(env.Glob('$FLES_DIR/lib/flib_dpb/*.cpp'))

# build SPADIC Message library
env.Replace(MSG_DIR='../message')
env.Append(CPPPATH=['$MSG_DIR', '$MSG_DIR/wrap/cpp'])
spadic_msg = env.Library([env.Glob('$MSG_DIR/*.c'),
                          '$MSG_DIR/wrap/cpp/Message.cpp'])

#---------------------------------------------------------------------

# build application
env.Program('tsreader', ['timeslice_reader.cpp', 'TimesliceReader.cpp'],
            LIBS=[fles_ipc, flib_dpb, spadic_msg, 'boost_serialization'])
