/* -*- c++ -*- */
/*
 * Copyright 2025 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_H
#define INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_H

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
class SPROBE_API tagged_stream_buffer_filler : virtual public gr::tagged_stream_block
{
public:
    typedef std::shared_ptr<tagged_stream_buffer_filler<IN_T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of
     * sprobe::tagged_stream_buffer_filler.
     *
     * To avoid accidental use of raw pointers, sprobe::tagged_stream_buffer_filler's
     * constructor is in a private implementation
     * class. sprobe::tagged_stream_buffer_filler::make is the public interface for
     * creating new instances.
     */
    static sptr make(int buffer_len, const std::string& length_tag_key = "packet_len");

    virtual int buffer_len() const = 0;
    virtual void set_buffer_len(int buffer_len) = 0;
};

typedef tagged_stream_buffer_filler<gr_complex> tagged_stream_buffer_filler_c;
typedef tagged_stream_buffer_filler<float> tagged_stream_buffer_filler_f;
typedef tagged_stream_buffer_filler<std::uint8_t> tagged_stream_buffer_filler_b;
typedef tagged_stream_buffer_filler<std::int16_t> tagged_stream_buffer_filler_s;
typedef tagged_stream_buffer_filler<std::int32_t> tagged_stream_buffer_filler_i;

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_TAGGED_STREAM_BUFFER_FILLER_H */
