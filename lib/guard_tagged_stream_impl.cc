/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "guard_tagged_stream_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace sprobe {

template<class IN_T>
typename guard_tagged_stream<IN_T>::sptr guard_tagged_stream<IN_T>::make(const std::string& length_tag_key)
{
    return gnuradio::make_block_sptr<guard_tagged_stream_impl<IN_T>>(length_tag_key);
}


/*
 * The private constructor
 */
template<class IN_T>
guard_tagged_stream_impl<IN_T>::guard_tagged_stream_impl(const std::string& length_tag_key):
    gr::tagged_stream_block("guard_tagged_stream",
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        length_tag_key)
{
    
}

/*
 * Our virtual destructor.
 */
template<class IN_T>
guard_tagged_stream_impl<IN_T>::~guard_tagged_stream_impl() {}

template<class IN_T>
int guard_tagged_stream_impl<IN_T>::calculate_output_stream_length(
    const gr_vector_int& ninput_items)
{
    return ninput_items[0]+1;
}

template<class IN_T>
int guard_tagged_stream_impl<IN_T>::work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    auto in = static_cast<const IN_T*>(input_items[0]);
    auto out = static_cast<IN_T*>(output_items[0]);
    int nin = ninput_items[0];

    if(noutput_items < nin+1) return 0;

    memcpy(out, in, nin*sizeof(IN_T));
    out[nin] = static_cast<IN_T>(0);
    this->add_item_tag(0,
        this->nitems_written(0)+nin,
        pmt::intern("end"),
        pmt::from_long(1),
        pmt::PMT_F);
    return nin+1;
}

template class guard_tagged_stream<gr_complex>;
template class guard_tagged_stream<float>;
template class guard_tagged_stream<std::uint8_t>;
template class guard_tagged_stream<std::int16_t>;
template class guard_tagged_stream<std::int32_t>;

} /* namespace sprobe */
} /* namespace gr */
