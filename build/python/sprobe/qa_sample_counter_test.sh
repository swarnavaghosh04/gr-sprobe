#!/usr/bin/sh
export VOLK_GENERIC=1
export GR_DONT_LOAD_PREFS=1
export srcdir=/home/swarnava/devel/gr-sprobe/python/sprobe
export GR_CONF_CONTROLPORT_ON=False
export PATH="/home/swarnava/devel/gr-sprobe/build/python/sprobe":"$PATH"
export LD_LIBRARY_PATH="":$LD_LIBRARY_PATH
export PYTHONPATH=/home/swarnava/devel/gr-sprobe/build/test_modules:$PYTHONPATH
/usr/bin/python3 /home/swarnava/devel/gr-sprobe/python/sprobe/qa_sample_counter.py 
