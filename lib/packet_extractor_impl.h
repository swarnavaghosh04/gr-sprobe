/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_PACKET_EXTRACTOR_IMPL_H
#define INCLUDED_SPROBE_PACKET_EXTRACTOR_IMPL_H

#include <gnuradio/sprobe/packet_extractor.h>

namespace gr {
namespace sprobe {

template<class IN_T>
class packet_extractor_impl : public packet_extractor<IN_T>
{
private:
    std::string d_start_tag_name;
    std::string d_end_tag_name;
    int d_remaining;

public:
    packet_extractor_impl(const std::string& start_tag_name, const std::string& end_tag_name);
    ~packet_extractor_impl();

    const std::string& start_tag_name() const override;
    const std::string& end_tag_name() const override;
    void set_start_tag_name(const std::string& start_tag_name) override;
    void set_end_tag_name(const std::string& end_tag_name) override;

    // Where all the action really happens
    void forecast(int noutput_items, gr_vector_int& ninput_items_required);

    int general_work(int noutput_items,
                     gr_vector_int& ninput_items,
                     gr_vector_const_void_star& input_items,
                     gr_vector_void_star& output_items);
    
};

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_PACKET_EXTRACTOR_IMPL_H */
