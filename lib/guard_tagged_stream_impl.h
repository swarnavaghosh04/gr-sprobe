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
    std::string d_length_tag_key;
    std::string d_end_tag_key;
    int d_tail_len;
    int d_packet_remaining;
    int d_tail_remaining;

public:
    guard_tagged_stream_impl(const std::string& length_tag_key, const std::string& end_tag_key, int tail_len);
    ~guard_tagged_stream_impl();

    const std::string& length_tag_key() const override;
    const std::string& end_tag_key() const override;
    int tail_len() const override;
    void set_length_tag_key(const std::string& length_tag_key) override;
    void set_end_tag_key(const std::string& end_tag_key) override;
    void set_tail_len(int tail_len) override;

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
             gr_vector_int& ninput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
};

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_GUARD_TAGGED_STREAM_IMPL_H */
