/*************************************************************************
 * Copyright (C) coralbay.tv Ltd. - All Rights Reserved.
 * Unauthorized copying of this file via any medium is strictly prohibited
 * Proprietary and Confidential
 ************************************************************************/

#include <gtest/gtest.h>

#include <890toass.hpp>
#include <stltoass.hpp>

#include <fstream>

////////////////////////////////////////////////////////////////////////////////
class test_890_2_ass : public testing::Test
{
public:

    test_890_2_ass() = default;

    ~test_890_2_ass() override = default;
};

////////////////////////////////////////////////////////////////////////////////
TEST_F(test_890_2_ass, generic_test)
{
#if 0
    {
        std::ifstream ifs("/home/gavin/media/subs/GBNAT6003122.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/gavin/media/subs/GBNAT6003122_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r,cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 0
    {
        std::ifstream ifs("/home/gavin/media/subs/NE765178.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/gavin/media/subs/NE765178_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r,cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 0
    {
        std::ifstream ifs("/home/gavin/media/subs/TTY9001051RU.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/gavin/media/subs/TTY9001051RU_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r,cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 0
    {
        std::ifstream ifs("/home/gavin/media/subs/TTY9001051HB.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/gavin/media/subs/TTY9001051HB_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 0
    {
        std::ifstream ifs("/home/gavin/media/subs/TTY9001051HB.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/gavin/media/subs/TTY9001051HB_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 1
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples/TTY9001051HB.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/anatoliym/Desktop/890ToASS/sub_samples/TTY9001051HB_converted_plugin.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 1
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples/GBNAT6003122.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::probe(ifs);
        ASSERT_EQ(r, cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 1
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples/crash1.890", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/anatoliym/Desktop/890ToASS/sub_samples/crash1.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::L890::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::L890::result::RESULT_OK);
    }
#endif

#if 0
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples1/AM132765-RON.STL", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/anatoliym/Desktop/890ToASS/sub_samples1/AM132765-RON-test.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::EBU::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::EBU::result::RESULT_OK);
    }
#endif

#if 1
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples1/BB110159-NOR.STL", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/anatoliym/Desktop/890ToASS/sub_samples1/BB110159-NOR-test.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::EBU::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::EBU::result::RESULT_OK);
    }
#endif

#if 1
    {
        std::ifstream ifs("/home/anatoliym/Desktop/890ToASS/sub_samples1/MO_20180423_1879_ro.stl", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        std::ofstream ofs("/home/anatoliym/Desktop/890ToASS/sub_samples1/MO_20180423_1879_ro-test.ass", std::ifstream::binary);
        ASSERT_TRUE(!!ifs);

        auto r = cb::subtitle::EBU::convert(ifs, ofs);
        ASSERT_EQ(r, cb::subtitle::EBU::result::RESULT_OK);
    }
#endif

}
