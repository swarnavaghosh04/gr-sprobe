/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_UNGUARD_TAGGED_STREAM_H
#define INCLUDED_SPROBE_UNGUARD_TAGGED_STREAM_H

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
class SPROBE_API unguard_tagged_stream : virtual public gr::block
{
public:
    typedef std::shared_ptr<unguard_tagged_stream<IN_T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of sprobe::unguard_tagged_stream.
     *
     * To avoid accidental use of raw pointers, sprobe::unguard_tagged_stream's
     * constructor is in a private implementation
     * class. sprobe::unguard_tagged_stream::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& start_tag_name = "packet_len", const std::string& end_tag_name = "packet_end");

    virtual const std::string& start_tag_name() const = 0;
    virtual const std::string& end_tag_name() const = 0;
    virtual void set_start_tag_name(const std::string& start_tag_name) = 0;
    virtual void set_end_tag_name(const std::string& end_tag_name) = 0;
};

typedef unguard_tagged_stream<gr_complex> unguard_tagged_stream_c;
typedef unguard_tagged_stream<float> unguard_tagged_stream_f;
typedef unguard_tagged_stream<std::uint8_t> unguard_tagged_stream_b;
typedef unguard_tagged_stream<std::int16_t> unguard_tagged_stream_s;
typedef unguard_tagged_stream<std::int32_t> unguard_tagged_stream_i;

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_UNGUARD_TAGGED_STREAM_H */
