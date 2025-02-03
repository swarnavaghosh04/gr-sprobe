/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_IMPL_H
#define INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_IMPL_H

#include <gnuradio/sprobe/tagged_stream_buffer_filler.h>

namespace gr {
namespace sprobe {

template<class IN_T>
class tagged_stream_buffer_filler_impl : public tagged_stream_buffer_filler<IN_T>
{
private:
    int d_buffer_len;

protected:
    int calculate_output_stream_length(const gr_vector_int& ninput_items) override;

public:
    tagged_stream_buffer_filler_impl(int buffer_len, const std::string& length_tag_key);
    ~tagged_stream_buffer_filler_impl();

    int buffer_len() const override;
    void set_buffer_len(int buffer_len) override;

    // Where all the action really happens
    int work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_IMPL_H */
