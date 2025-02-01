/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_GUARD_TAGGED_STREAM_IMPL_H
#define INCLUDED_SPROBE_GUARD_TAGGED_STREAM_IMPL_H

#include <gnuradio/sprobe/guard_tagged_stream.h>

namespace gr {
namespace sprobe {

template<class IN_T>
class guard_tagged_stream_impl : public guard_tagged_stream<IN_T>
{
private:
    // Nothing to declare in this block.

protected:
    int calculate_output_stream_length(const gr_vector_int& ninput_items);

public:
    guard_tagged_stream_impl(const std::string& length_tag_key);
    ~guard_tagged_stream_impl();

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_GUARD_TAGGED_STREAM_IMPL_H */
