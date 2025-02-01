/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_GUARD_TAGGED_STREAM_H
#define INCLUDED_SPROBE_GUARD_TAGGED_STREAM_H

#include <gnuradio/sprobe/api.h>
#include <gnuradio/tagged_stream_block.h>

namespace gr {
namespace sprobe {

/*!
 * \brief <+description of block+>
 * \ingroup sprobe
 *
 */
template<class IN_T>
class SPROBE_API guard_tagged_stream : virtual public gr::tagged_stream_block
{
public:
    typedef std::shared_ptr<guard_tagged_stream<IN_T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of sprobe::guard_tagged_stream.
     *
     * To avoid accidental use of raw pointers, sprobe::guard_tagged_stream's
     * constructor is in a private implementation
     * class. sprobe::guard_tagged_stream::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& length_tag_key = "packet_len", const std::string& end_tag_key = "packet_end");

    virtual const std::string& end_tag_key() const = 0;
    virtual void set_end_tag_key(const std::string& end_tag_key) = 0;
};

typedef guard_tagged_stream<gr_complex> guard_tagged_stream_c;
typedef guard_tagged_stream<float> guard_tagged_stream_f;
typedef guard_tagged_stream<std::uint8_t> guard_tagged_stream_b;
typedef guard_tagged_stream<std::int16_t> guard_tagged_stream_s;
typedef guard_tagged_stream<std::int32_t> guard_tagged_stream_i;

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_GUARD_TAGGED_STREAM_H */
