/* -*- c++ -*- */
/*
 * Copyright 2024 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_SAMPLE_COUNTER_H
#define INCLUDED_SPROBE_SAMPLE_COUNTER_H

#include <gnuradio/sprobe/api.h>
#include <gnuradio/sync_block.h>

namespace gr {
namespace sprobe {

/*!
 * \brief counts the number of samples passed and prints it out
 * \ingroup sprobe
 *
 */
template<class IN_T>
class SPROBE_API sample_counter : virtual public gr::sync_block
{
public:
    typedef std::shared_ptr<sample_counter<IN_T>> sptr;

    /*!
     * \brief Return a shared_ptr to a new instance of sprobe::sample_counter.
     *
     * To avoid accidental use of raw pointers, sprobe::sample_counter's
     * constructor is in a private implementation
     * class. sprobe::sample_counter::make is the public interface for
     * creating new instances.
     */
    static sptr make(const std::string& msg = "some comment");

    virtual const std::string& msg() const = 0;
    virtual void set_msg(const std::string& msg) = 0;
    virtual std::uint64_t samples_passed() const = 0;
    
};

typedef sample_counter<gr_complex> sample_counter_c;
typedef sample_counter<float> sample_counter_f;
typedef sample_counter<std::uint8_t> sample_counter_b;
typedef sample_counter<std::int16_t> sample_counter_s;
typedef sample_counter<std::int32_t> sample_counter_i;

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_SAMPLE_COUNTER_H */
