/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_SQL_STORE_H_
#define BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_SQL_STORE_H_

#include <string>
#include <utility>
#include <vector>

#include "bat/ledger/internal/core/async_result.h"
#include "bat/ledger/internal/core/bat_ledger_context.h"
#include "bat/ledger/public/interfaces/ledger.mojom.h"

namespace ledger {

class SQLStore : public BATLedgerContext::Component {
 public:
  static const size_t kComponentKey;

  explicit SQLStore(BATLedgerContext* context);
  ~SQLStore() override;

  template <typename... Args>
  static auto BindValues(Args&&... args) {
    std::vector<mojom::DBCommandBindingPtr> bindings;
    BindingHelper::AddBindings(&bindings, std::forward<Args>(args)...);
    return bindings;
  }

  using CommandResult = AsyncResult<mojom::DBCommandResponsePtr>;

  CommandResult RunTransaction(mojom::DBTransactionPtr transaction);

  CommandResult Execute(const std::string& sql);

  CommandResult Execute(const std::string& sql,
                        std::vector<mojom::DBCommandBindingPtr>&& bindings);

  CommandResult Query(
      const std::string& sql,
      const std::vector<mojom::DBCommand::RecordBindingType>& columns);

  CommandResult Query(
      const std::string& sql,
      const std::vector<mojom::DBCommand::RecordBindingType>& columns,
      std::vector<mojom::DBCommandBindingPtr>&& bindings);

 protected:
  virtual CommandResult RunTransactionImpl(mojom::DBTransactionPtr transaction);

 private:
  struct BindingHelper {
    template <typename T>
    static void SetValue(T* binding, double value) {
      binding->value->set_double_value(value);
    }

    template <typename T>
    static void SetValue(T* binding, int64_t value) {
      binding->value->set_int64_value(value);
    }

    template <typename T>
    static void SetValue(T* binding, int32_t value) {
      binding->value->set_int_value(value);
    }

    template <typename T>
    static void SetValue(T* binding, const char* value) {
      binding->value->set_string_value(std::string(value));
    }

    template <typename T>
    static void SetValue(T* binding, const std::string& value) {
      binding->value->set_string_value(value);
    }

    template <typename T>
    static void SetValue(T* binding, bool value) {
      binding->value->set_bool_value(value);
    }

    template <typename T>
    static void SetValue(T* binding, std::nullptr_t) {
      binding->value->set_null_value(0);
    }

    template <typename T>
    static void AddBindings(T* bindings) {}

    template <typename T, typename U, typename... Args>
    static void AddBindings(T* bindings, U&& value, Args&&... args) {
      auto binding = mojom::DBCommandBinding::New();
      binding->value = mojom::DBValue::New();
      SetValue(binding.get(), std::forward<U>(value));
      binding->index = bindings->size();
      bindings->push_back(std::move(binding));
      AddBindings(bindings, std::forward<Args>(args)...);
    }
  };
};

}  // namespace ledger

#endif  // BRAVE_VENDOR_BAT_NATIVE_LEDGER_SRC_BAT_LEDGER_INTERNAL_CORE_SQL_STORE_H_
