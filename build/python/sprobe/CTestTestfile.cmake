# CMake generated Testfile for 
# Source directory: /home/swarnava/devel/gr-sprobe/python/sprobe
# Build directory: /home/swarnava/devel/gr-sprobe/build/python/sprobe
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(qa_sample_counter "/usr/bin/sh" "qa_sample_counter_test.sh")
set_tests_properties(qa_sample_counter PROPERTIES  _BACKTRACE_TRIPLES "/usr/lib/cmake/gnuradio/GrTest.cmake;119;add_test;/home/swarnava/devel/gr-sprobe/python/sprobe/CMakeLists.txt;37;GR_ADD_TEST;/home/swarnava/devel/gr-sprobe/python/sprobe/CMakeLists.txt;0;")
subdirs("bindings")
