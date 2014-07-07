# ex: syntax=python

import os

use_clang = True

# basic compiler settings
env = Environment(CCFLAGS=['-std=c++11'])
if use_clang:
    env.Replace(CXX='clang++')
    env.Append(ENV={'TERM': os.environ['TERM']}) # for color output

# set paths to sources
requested = {'FLES_DIR': 'the root of the flesnet source tree',
             'SPADIC_DIR': 'the root of the SPADIC software source tree'}
for name in requested:
    try:
        env.Replace(**{name: os.environ[name]})
    except KeyError:
        raise SystemExit("Please set the %s environment variable to %s." %
                         (name, requested[name]))

# build fles_ipc library
env.Append(CPPPATH=['$FLES_DIR/lib/fles_ipc'])
fles_ipc = env.Library(env.Glob('$FLES_DIR/lib/fles_ipc/*.cpp'))

# build flib_dpb library
env.Append(CPPPATH=['$FLES_DIR/lib/flib_dpb'])
flib_dpb = env.Library(env.Glob('$FLES_DIR/lib/flib_dpb/*.cpp'))

# build SPADIC Message library
env.Append(CPPPATH=['$SPADIC_DIR/lib/message',
                    '$SPADIC_DIR/lib/message/wrap/cpp'])
spadic_msg = env.Library([env.Glob('$SPADIC_DIR/lib/message/*.c'),
                          '$SPADIC_DIR/lib/message/wrap/cpp/Message.cpp'])

#---------------------------------------------------------------------

# build application
env.Program('tsreader', ['timeslice_reader.cpp', 'TimesliceReader.cpp'],
            LIBS=[fles_ipc, flib_dpb, spadic_msg, 'boost_serialization'])
