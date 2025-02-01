/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_PACKET_EXTRACTOR_H
#define INCLUDED_SPROBE_PACKET_EXTRACTOR_H

#include <gnuradio/block.h>
#include <gnuradio/sprobe/api.h>

namespace gr {
namespace sprobe {

/*!
 * \brief <+description of block+>
 * \ingroup sprobe
 *
 */
template<class IN_T>
class SPROBE_API packet_extractor : virtual public gr::block
{
public:
    typedef std::shared_ptr<packet_extractor<IN_T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of sprobe::packet_extractor.
     *
     * To avoid accidental use of raw pointers, sprobe::packet_extractor's
     * constructor is in a private implementation
     * class. sprobe::packet_extractor::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& start_tag_name = "packet_len", const std::string& end_tag_name = "packet_end");

    virtual const std::string& start_tag_name() const = 0;
    virtual const std::string& end_tag_name() const = 0;
    virtual void set_start_tag_name(const std::string& start_tag_name) = 0;
    virtual void set_end_tag_name(const std::string& end_tag_name) = 0;
};

typedef packet_extractor<gr_complex> packet_extractor_c;
typedef packet_extractor<float> packet_extractor_f;
typedef packet_extractor<std::uint8_t> packet_extractor_b;
typedef packet_extractor<std::int16_t> packet_extractor_s;
typedef packet_extractor<std::int32_t> packet_extractor_i;

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_PACKET_EXTRACTOR_H */
