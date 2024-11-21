#!/usr/bin/env python
# -*- coding: utf-8 -*-
#
# Copyright 2024 Swarnava Ghosh.
#
# SPDX-License-Identifier: GPL-3.0-or-later
#

from gnuradio import gr, gr_unittest
from gnuradio import blocks
try:
    from gnuradio import sprobe
except ImportError:
    import os
    import sys
    dirname, filename = os.path.split(os.path.abspath(__file__))
    sys.path.append(os.path.join(dirname, "bindings"))
    from gnuradio import sprobe

class qa_sample_counter(gr_unittest.TestCase):

    def setUp(self):
        self.tb = gr.top_block()

    def tearDown(self):
        self.tb = None

    def test_instance(self):

        instc1 = sprobe.sample_counter_c()
        instc2 = sprobe.sample_counter_c("hello")
        self.assertNotEqual(instc1.msg(), instc2.msg())

        instf1 = sprobe.sample_counter_f()
        instf2 = sprobe.sample_counter_f("hello")
        self.assertNotEqual(instf1.msg(), instf2.msg())

        instb1 = sprobe.sample_counter_b()
        instb2 = sprobe.sample_counter_b("hello")
        self.assertNotEqual(instb1.msg(), instb2.msg())

        insts1 = sprobe.sample_counter_s()
        insts2 = sprobe.sample_counter_s("hello")
        self.assertNotEqual(insts1.msg(), insts2.msg())

        insti1 = sprobe.sample_counter_i()
        insti2 = sprobe.sample_counter_i("hello")
        self.assertNotEqual(insti1.msg(), insti2.msg())


    def test_001_basic(self):
        test_input = (0xAA, 0xBB, 0xCC, 0xDD)
        expected_test_output = len(test_input)

        src = blocks.vector_source_b(test_input, False, 1, [])
        counter = sprobe.sample_counter_b()

        self.tb.connect(src, counter)
        self.tb.run()
        test_output = counter.samples_passed()
        
        self.assertEqual(test_output, expected_test_output)


if __name__ == '__main__':
    gr_unittest.run(qa_sample_counter)
