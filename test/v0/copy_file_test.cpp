// Copyright 2019 Lawrence Livermore National Security, LLC and other Metall Project Developers.
// See the top-level COPYRIGHT file for details.
//
// SPDX-License-Identifier: (Apache-2.0 OR MIT)


#include "gtest/gtest.h"

#include <metall/metall.hpp>

#include <metall/detail/utility/file.hpp>
#include "../test_utility.hpp"

namespace {

void open(const std::string& file_name) {
  metall::manager manager(metall::open_only, file_name.c_str());

  auto a = manager.find<uint32_t>("a").first;
  ASSERT_EQ(*a, 1);

  auto b = manager.find<uint64_t>("b").first;
  ASSERT_EQ(*b, 2);
}

const std::string& original_file_path() {
  const static std::string file_path(test_utility::test_file_path("CopyFileTest"));
  return file_path;
}

const std::string& copy_file_path() {
  const static std::string file_path(test_utility::test_file_path("CopyFileTest_copy"));
  return file_path;
}

TEST(CopyFileTest, SyncCopy) {
  metall::manager::remove_file(original_file_path().c_str());
  metall::manager::remove_file(copy_file_path().c_str());

  {
    metall::manager manager(metall::create_only, original_file_path().c_str(), metall::manager::chunk_size() * 2);

    manager.construct<uint32_t>("a")(1);

    manager.construct<uint64_t>("b")(2);

    manager.sync();

    ASSERT_TRUE(metall::manager::copy_file(original_file_path().c_str(), copy_file_path().c_str()));

    // Check sparse file copy
    EXPECT_EQ(metall::detail::utility::get_file_size(original_file_path() + "_segment"),
              metall::detail::utility::get_file_size(copy_file_path() + "_segment"));

    EXPECT_EQ(metall::detail::utility::get_actual_file_size(original_file_path() + "_segment"),
              metall::detail::utility::get_actual_file_size(copy_file_path() + "_segment"));
  }
  open(copy_file_path());
}

TEST(CopyFileTest, AsyncCopy) {
  metall::manager::remove_file(original_file_path().c_str());
  metall::manager::remove_file(copy_file_path().c_str());

  {
    metall::manager manager(metall::create_only, original_file_path().c_str(), metall::manager::chunk_size() * 2);

    manager.construct<uint32_t>("a")(1);

    manager.construct<uint64_t>("b")(2);

    manager.sync();

    auto handler = metall::manager::copy_file_async(original_file_path().c_str(), copy_file_path().c_str());
    ASSERT_TRUE(handler.get());

    // Check sparse file copy
    EXPECT_EQ(metall::detail::utility::get_file_size(original_file_path() + "_segment"),
              metall::detail::utility::get_file_size(copy_file_path() + "_segment"));

    EXPECT_EQ(metall::detail::utility::get_actual_file_size(original_file_path() + "_segment"),
              metall::detail::utility::get_actual_file_size(copy_file_path() + "_segment"));
  }
  open(copy_file_path());
}
}