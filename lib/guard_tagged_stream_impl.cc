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
typename guard_tagged_stream<IN_T>::sptr guard_tagged_stream<IN_T>::make(const std::string& length_tag_key, const std::string& end_tag_key, int tail_len)
{
    return gnuradio::make_block_sptr<guard_tagged_stream_impl<IN_T>>(length_tag_key, end_tag_key, tail_len);
}

/*
 * The private constructor
 */
template<class IN_T>
guard_tagged_stream_impl<IN_T>::guard_tagged_stream_impl(const std::string& length_tag_key, const std::string& end_tag_key, int tail_len):
    gr::block("guard_tagged_stream",
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        gr::io_signature::make(1, 1, sizeof(IN_T))),
    d_length_tag_key(length_tag_key),
    d_end_tag_key(end_tag_key),
    d_tail_len(tail_len < 1 ? 1 : tail_len),
    d_packet_remaining(0),
    d_tail_remaining(0)
{
    this->set_tag_propagation_policy(gr::block::TPP_CUSTOM);
}

/*
 * Our virtual destructor.
 */
template<class IN_T>
guard_tagged_stream_impl<IN_T>::~guard_tagged_stream_impl() {}

template<class IN_T>
const std::string& guard_tagged_stream_impl<IN_T>::length_tag_key() const { return d_length_tag_key; }
template<class IN_T>
const std::string& guard_tagged_stream_impl<IN_T>::end_tag_key() const { return d_end_tag_key; }
template<class IN_T>
int guard_tagged_stream_impl<IN_T>::tail_len() const { return d_tail_len; }
template<class IN_T>
void guard_tagged_stream_impl<IN_T>::set_length_tag_key(const std::string& length_tag_key){ d_length_tag_key = length_tag_key; }
template<class IN_T>
void guard_tagged_stream_impl<IN_T>::set_end_tag_key(const std::string& end_tag_key){ d_end_tag_key = end_tag_key; }
template<class IN_T>
void guard_tagged_stream_impl<IN_T>::set_tail_len(int tail_len){ d_tail_len = tail_len < 1 ? 1 : tail_len; }

template<class IN_T>
void guard_tagged_stream_impl<IN_T>::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    // int needed = noutput_items - d_tail_remaining;
    // ninput_items_required[0] = needed < 0 ? 0 : needed; // DOES NOT WORK WITH 0 OUTPUT!!!
    ninput_items_required[0] = noutput_items;
}

template<class IN_T>
int guard_tagged_stream_impl<IN_T>::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    auto in = static_cast<const IN_T*>(input_items[0]);
    auto out = static_cast<IN_T*>(output_items[0]);
    int nin = ninput_items[0];


    if(d_packet_remaining > 0){
        int nconsume = noutput_items < d_packet_remaining ? noutput_items : d_packet_remaining;
        d_packet_remaining -= nconsume;
        std::copy(in, in+nconsume, out);
        std::vector<tag_t> tags;
        this->get_tags_in_window(tags, 0, 0, nconsume);
        for(tag_t& tag : tags){
            tag.offset -= this->nitems_read(0);
            tag.offset += this->nitems_written(0);
            this->add_item_tag(0, tag);
        }
        this->consume_each(nconsume);
        // this->d_logger->info("handled packet secondary {}", nconsume);
        return nconsume;
    }
    else if(d_tail_remaining > 0){
        int produce = noutput_items < d_tail_remaining ? noutput_items : d_tail_remaining;
        std::fill(out, out+produce, static_cast<IN_T>(0));
        if(d_tail_remaining == d_tail_len) this->add_item_tag(0,
            this->nitems_written(0),
            pmt::intern(d_end_tag_key),
            pmt::from_long(d_tail_len),
            pmt::PMT_F);
        d_tail_remaining -= produce;
        this->consume_each(0);
        // this->d_logger->info("handled tail {}", produce);
        return produce;
    }
    else{
        std::vector<tag_t> tags;
        this->get_tags_in_window(tags, 0, 0, nin, pmt::intern(d_length_tag_key));
        // std::sort(tags.begin(), tags.end(), [](const tag_t& a, const tag_t& b){return a.offset < b.offset;});

        int nconsume;

        if(tags.size() != 0){
            d_tail_remaining = d_tail_len;
            d_packet_remaining = tags[0].offset - this->nitems_read(0) + pmt::to_long(tags[0].value);
            nconsume = noutput_items < d_packet_remaining ? noutput_items : d_packet_remaining;
            d_packet_remaining -= nconsume;
            // this->d_logger->info("handled packet {}", nconsume);
        }else{
            nconsume = noutput_items < nin ? noutput_items : nin;
            // this->d_logger->info("default copy {}", nconsume);
        }

        std::copy(in, in+nconsume, out);
        this->get_tags_in_window(tags, 0, 0, nconsume);
        for(tag_t& tag : tags){
            tag.offset -= this->nitems_read(0);
            tag.offset += this->nitems_written(0);
            this->add_item_tag(0, tag);
        }
        this->consume_each(nconsume);
        return nconsume;
    }                     
}

template class guard_tagged_stream<gr_complex>;
template class guard_tagged_stream<float>;
template class guard_tagged_stream<std::uint8_t>;
template class guard_tagged_stream<std::int16_t>;
template class guard_tagged_stream<std::int32_t>;

} /* namespace sprobe */
} /* namespace gr */
