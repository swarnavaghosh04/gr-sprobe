/* -*- c++ -*- */
/*
 * Copyright 2024 Swarnava Ghosh.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 */

#ifndef INCLUDED_SPROBE_SAMPLE_COUNTER_IMPL_H
#define INCLUDED_SPROBE_SAMPLE_COUNTER_IMPL_H

#include <gnuradio/sprobe/sample_counter.h>

namespace gr {
namespace sprobe {

template<class IN_T>
class sample_counter_impl : public sample_counter<IN_T>
{
private:
    std::uint64_t d_samples_passed;
    std::string d_msg;

public:
    sample_counter_impl(const std::string& msg = "some comment");
    ~sample_counter_impl();

    int work(int noutput_items,
             gr_vector_const_void_star& input_items,
             gr_vector_void_star& output_items);
    
    bool start() override;
    bool stop() override;

    const std::string& msg() const override;
    void set_msg(const std::string& msg) override;
    std::uint64_t samples_passed() const override;
};

} // namespace sprobe
} // namespace gr

#endif /* INCLUDED_SPROBE_SAMPLE_COUNTER_IMPL_H */
