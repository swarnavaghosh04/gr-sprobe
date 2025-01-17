/*
 * Copyright 2024 Free Software Foundation, Inc.
 *
 * This file is part of GNU Radio
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 *
 */

/***********************************************************************************/
/* This file is automatically generated using bindtool and can be manually edited  */
/* The following lines can be configured to regenerate this file during cmake      */
/* If manual edits are made, the following tags should be modified accordingly.    */
/* BINDTOOL_GEN_AUTOMATIC(0)                                                       */
/* BINDTOOL_USE_PYGCCXML(0)                                                        */
/* BINDTOOL_HEADER_FILE(sample_counter.h)                                        */
/* BINDTOOL_HEADER_FILE_HASH(f39b4ef381cab0e39b56c5b4733fd02f)                     */
/***********************************************************************************/

#include <pybind11/complex.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

#include <gnuradio/sprobe/sample_counter.h>
// pydoc.h is automatically generated in the build directory
#include <sample_counter_pydoc.h>

template<class IN_T>
void bind_sample_counter_template(py::module& m, const char* classname){

    using sample_counter = gr::sprobe::sample_counter<IN_T>;

    py::class_<
        sample_counter,
        gr::sync_block,
        gr::block,
        gr::basic_block,
        std::shared_ptr<sample_counter>>(m, classname)
        
        .def(
            py::init(&sample_counter::make),
            py::arg("msg") = "some comment")
            
        .def("msg", &sample_counter::msg)
        .def("set_msg", &sample_counter::set_msg, py::arg("msg"))
        .def("samples_passed", &sample_counter::samples_passed);
}

void bind_sample_counter(py::module& m){
    bind_sample_counter_template<gr_complex>(m, "sample_counter_c");
    bind_sample_counter_template<float>(m, "sample_counter_f");
    bind_sample_counter_template<std::uint8_t>(m, "sample_counter_b");
    bind_sample_counter_template<std::int16_t>(m, "sample_counter_s");
    bind_sample_counter_template<std::int32_t>(m, "sample_counter_i");
}
