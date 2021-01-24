/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/core/sql_store.h"

#include <string>
#include <utility>

#include "bat/ledger/internal/core/bat_ledger_test.h"

namespace ledger {

class SQLStoreTest : public BATLedgerTest {};

TEST_F(SQLStoreTest, BindValues) {
  auto bindings = SQLStore::BindValues(true, int32_t(2202), 0.008, nullptr,
                                       "hello", int64_t(64));

  ASSERT_EQ(bindings.size(), size_t(6));

  EXPECT_EQ(bindings[0]->index, 0);
  EXPECT_EQ(bindings[0]->value->get_bool_value(), true);

  EXPECT_EQ(bindings[1]->index, 1);
  EXPECT_EQ(bindings[1]->value->get_int_value(), 2202);

  EXPECT_EQ(bindings[2]->index, 2);
  EXPECT_EQ(bindings[2]->value->get_double_value(), 0.008);

  EXPECT_EQ(bindings[3]->index, 3);
  EXPECT_EQ(bindings[3]->value->get_null_value(), 0);

  EXPECT_EQ(bindings[4]->index, 4);
  EXPECT_EQ(bindings[4]->value->get_string_value(), "hello");

  EXPECT_EQ(bindings[5]->index, 5);
  EXPECT_EQ(bindings[5]->value->get_int64_value(), 64);
}

}  // namespace ledger
