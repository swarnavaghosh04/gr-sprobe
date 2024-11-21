/* -*- c++ -*- */
/*
 * Copyright 2024 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "sample_counter_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace sprobe {

template<class IN_T>
typename sample_counter<IN_T>::sptr sample_counter<IN_T>::make(const std::string& msg)
{
    return gnuradio::make_block_sptr<sample_counter_impl<IN_T>>(msg);
}

template<class IN_T>
sample_counter_impl<IN_T>::sample_counter_impl(const std::string& msg):
    gr::sync_block(
        "sample_counter",
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        gr::io_signature::make(0, 0, 0)),
    d_msg(msg)
{
}

template<class IN_T>
sample_counter_impl<IN_T>::~sample_counter_impl() {}

template<class IN_T>
int sample_counter_impl<IN_T>::work(int noutput_items,
                              gr_vector_const_void_star& input_items,
                              gr_vector_void_star& output_items)
{
    d_samples_passed += noutput_items;
    return noutput_items;
}

template<class IN_T>
bool sample_counter_impl<IN_T>::start()
{
    d_samples_passed = 0;
    return sync_block::start();
}

template<class IN_T>
bool sample_counter_impl<IN_T>::stop()
{
    sync_block::d_logger->info("{}: {}", d_msg, d_samples_passed);
    return sync_block::stop();
}

template<class IN_T>
const std::string& sample_counter_impl<IN_T>::msg() const{ return d_msg; }
template<class IN_T>
void sample_counter_impl<IN_T>::set_msg(const std::string& msg) { d_msg = msg; }
template<class IN_T>
std::uint64_t sample_counter_impl<IN_T>::samples_passed() const{ return d_samples_passed; }

template class sample_counter<gr_complex>;
template class sample_counter<float>;
template class sample_counter<std::uint8_t>;
template class sample_counter<std::int16_t>;
template class sample_counter<std::int32_t>;

} /* namespace sprobe */
} /* namespace gr */
