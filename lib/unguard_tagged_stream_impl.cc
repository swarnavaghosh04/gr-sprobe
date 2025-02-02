/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#include "unguard_tagged_stream_impl.h"
#include <gnuradio/io_signature.h>

namespace gr {
namespace sprobe {

template<class IN_T>
typename unguard_tagged_stream<IN_T>::sptr unguard_tagged_stream<IN_T>::make(const std::string& start_tag_name, const std::string& end_tag_name)
{
    return gnuradio::make_block_sptr<unguard_tagged_stream_impl<IN_T>>(start_tag_name, end_tag_name);
}


/*
 * The private constructor
 */
template<class IN_T>
unguard_tagged_stream_impl<IN_T>::unguard_tagged_stream_impl(const std::string& start_tag_name, const std::string& end_tag_name):
    gr::block("unguard_tagged_stream",
        gr::io_signature::make(1, 1, sizeof(IN_T)),
        gr::io_signature::make(1, 1, sizeof(IN_T))),
    d_start_tag_name(start_tag_name),
    d_end_tag_name(end_tag_name),
    d_remaining(0)
{
    this->set_tag_propagation_policy(gr::block::TPP_DONT);
}

/*
 * Our virtual destructor.
 */
template<class IN_T>
unguard_tagged_stream_impl<IN_T>::~unguard_tagged_stream_impl() {}

template<class IN_T>
const std::string& unguard_tagged_stream_impl<IN_T>::start_tag_name() const{ return d_start_tag_name; }
template<class IN_T>
const std::string& unguard_tagged_stream_impl<IN_T>::end_tag_name() const{ return d_end_tag_name; }
template<class IN_T>
void unguard_tagged_stream_impl<IN_T>::set_start_tag_name(const std::string& start_tag_name){ d_start_tag_name = start_tag_name; }
template<class IN_T>
void unguard_tagged_stream_impl<IN_T>::set_end_tag_name(const std::string& end_tag_name){ d_end_tag_name = end_tag_name; }

template<class IN_T>
void unguard_tagged_stream_impl<IN_T>::forecast(int noutput_items, gr_vector_int& ninput_items_required)
{
    ninput_items_required[0] = noutput_items;
}

template<class IN_T>
int unguard_tagged_stream_impl<IN_T>::general_work(int noutput_items,
                                   gr_vector_int& ninput_items,
                                   gr_vector_const_void_star& input_items,
                                   gr_vector_void_star& output_items)
{
    auto in = static_cast<const IN_T*>(input_items[0]);
    auto nin = static_cast<int>(ninput_items[0]);
    auto out = static_cast<IN_T*>(output_items[0]);

    std::vector<tag_t> tags;

    if(d_remaining > 0){
        int nproc = noutput_items < d_remaining ? noutput_items : d_remaining;
        this->get_tags_in_window(tags, 0, 0, nproc);
        std::sort(tags.begin(), tags.end(), [](const tag_t& a, const tag_t& b){return a.offset < b.offset;});
        memcpy(out, in, nproc*sizeof(IN_T));
        for(tag_t& tag: tags){
            tag.offset -= this->nitems_read(0);
            tag.offset += this->nitems_written(0);
            this->add_item_tag(0, tag);
        }
        d_remaining -= nproc;
        if(d_remaining == 0) this->consume_each(nproc+1);
        else this->consume_each(nproc);
        return nproc;
    }

    this->get_tags_in_window(tags, 0, 0, nin);

    const tag_t *start_tag = nullptr, *end_tag = nullptr;

    for(const tag_t& tag : tags){
        if(start_tag == nullptr){
            if(pmt::eqv(tag.key, pmt::intern(d_start_tag_name))){
                start_tag = &tag;
            }
        }else if(pmt::eqv(tag.key, pmt::intern(d_end_tag_name))){
            end_tag = &tag;
            break;
        }
    }

    if(start_tag == nullptr){
        this->consume_each(nin);
        return 0;
    }else{
        unsigned long drop = start_tag->offset - this->nitems_read(0);
        if(end_tag == nullptr){
            this->consume_each(drop);
            return 0;
        }
        d_remaining = end_tag->offset - start_tag->offset;
        int nproc = noutput_items < d_remaining ? noutput_items : d_remaining;
        this->get_tags_in_window(tags, 0, drop, drop+nproc);
        memcpy(out, in+drop, nproc*sizeof(IN_T));
        for(tag_t& tag: tags){
            if(tag.offset == this->nitems_read(0)+drop){
                tag.value = pmt::from_long(d_remaining);
            }
            tag.offset -= this->nitems_read(0)+drop;
            tag.offset += this->nitems_written(0);
            this->add_item_tag(0, tag);
        }
        d_remaining -= nproc;
        if(d_remaining == 0) this->consume_each(drop+nproc+1);
        else this->consume_each(drop+nproc);
        return nproc;
    }
}

template class unguard_tagged_stream<gr_complex>;
template class unguard_tagged_stream<float>;
template class unguard_tagged_stream<std::uint8_t>;
template class unguard_tagged_stream<std::int16_t>;
template class unguard_tagged_stream<std::int32_t>;

} /* namespace sprobe */
} /* namespace gr */
