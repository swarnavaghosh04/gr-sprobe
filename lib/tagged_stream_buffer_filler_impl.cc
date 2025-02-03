/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "tagged_stream_buffer_filler_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace sprobe {

template<class IN_T>
typename tagged_stream_buffer_filler<IN_T>::sptr tagged_stream_buffer_filler<IN_T>::make(int buffer_len, const std::string& length_tag_key)
{
    return gnuradio::make_block_sptr<tagged_stream_buffer_filler_impl<IN_T>>(buffer_len, length_tag_key);
}


/*
 * The private constructor
 */
template<class IN_T>
tagged_stream_buffer_filler_impl<IN_T>::tagged_stream_buffer_filler_impl(int buffer_len, const std::string& length_tag_key):
    gr::tagged_stream_block("tagged_stream_buffer_filler",
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        length_tag_key),
    d_buffer_len(buffer_len)
{
    if(d_buffer_len < 1) throw std::runtime_error("buffer length must be at least 1!");
    this->set_tag_propagation_policy(gr::block::TPP_DONT);
}

/*
 * Our virtual destructor.
 */
template<class IN_T>
tagged_stream_buffer_filler_impl<IN_T>::~tagged_stream_buffer_filler_impl() {}

template<class IN_T>
int tagged_stream_buffer_filler_impl<IN_T>::calculate_output_stream_length(
    const gr_vector_int& ninput_items)
{
    return ninput_items[0] + (d_buffer_len- (ninput_items[0]%d_buffer_len) );
}

template<class IN_T>
int tagged_stream_buffer_filler_impl<IN_T>::buffer_len() const { return d_buffer_len; }
template<class IN_T>
void tagged_stream_buffer_filler_impl<IN_T>::set_buffer_len(int buffer_len){
    if(buffer_len >= 1) d_buffer_len = buffer_len;
}

template<class IN_T>
int tagged_stream_buffer_filler_impl<IN_T>::work(int noutput_items,
                                           gr_vector_int& ninput_items,
                                           gr_vector_const_void_star& input_items,
                                           gr_vector_void_star& output_items)
{
    auto in = static_cast<const IN_T*>(input_items[0]);
    auto out = static_cast<IN_T*>(output_items[0]);
    int nin = ninput_items[0];
    
    std::copy(in, in+nin, out);
    std::fill(out+nin, out+nin+(d_buffer_len-(nin%d_buffer_len)), static_cast<IN_T>(0));

    std::vector<tag_t> tags;
    this->get_tags_in_window(tags, 0, 0, nin);
    std::for_each(tags.begin(), tags.end(), [&](tag_t& tag){
        tag.offset -= this->nitems_read(0);
        tag.offset += this->nitems_written(0);
        this->add_item_tag(0, tag);
    });

    return nin+(d_buffer_len- (nin%d_buffer_len));
}

template class tagged_stream_buffer_filler<gr_complex>;
template class tagged_stream_buffer_filler<float>;
template class tagged_stream_buffer_filler<std::uint8_t>;
template class tagged_stream_buffer_filler<std::int16_t>;
template class tagged_stream_buffer_filler<std::int32_t>;

} /* namespace sprobe */
} /* namespace gr */
