# Copyright 2020 Free Software Foundation, Inc.
#
# This file is part of GNU Radio
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

########################################################################
# Check if there is C++ code at all
########################################################################
if(NOT sprobe_sources)
    message(STATUS "No C++ sources... skipping python bindings")
    return()
endif(NOT sprobe_sources)

########################################################################
# Check for pygccxml
########################################################################
gr_python_check_module_raw("pygccxml" "import pygccxml" PYGCCXML_FOUND)

include(GrPybind)

########################################################################
# Python Bindings
########################################################################

list(APPEND sprobe_python_files
    sample_counter_python.cc
    unguard_tagged_stream_python.cc
    guard_tagged_stream_python.cc
    tagged_stream_buffer_filler_python.cc python_bindings.cc)

gr_pybind_make_oot(sprobe ../../.. gr::sprobe "${sprobe_python_files}")

# copy bindings extension for use in QA test module
add_custom_command(
    TARGET sprobe_python
    POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:sprobe_python>
            ${PROJECT_BINARY_DIR}/test_modules/gnuradio/sprobe/)

install(
    TARGETS sprobe_python
    DESTINATION ${GR_PYTHON_DIR}/gnuradio/sprobe
    COMPONENT pythonapi)
