/* Copyright (c) 2021 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ledger/internal/core/sql_store.h"

#include <string>
#include <utility>
#include <vector>

namespace ledger {

const size_t SQLStore::kComponentKey = BATLedgerContext::ReserveComponentKey();

SQLStore::SQLStore(BATLedgerContext* context) : Component(context) {}

SQLStore::~SQLStore() = default;

SQLStore::CommandResult SQLStore::RunTransaction(
    mojom::DBTransactionPtr transaction) {
  return RunTransactionImpl(std::move(transaction));
}

SQLStore::CommandResult SQLStore::Execute(const std::string& sql) {
  return Execute(sql, {});
}

SQLStore::CommandResult SQLStore::Execute(
    const std::string& sql,
    std::vector<mojom::DBCommandBindingPtr>&& bindings) {
  auto command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::RUN;
  command->command = sql;
  command->bindings = std::move(bindings);

  auto transaction = mojom::DBTransaction::New();
  transaction->commands.push_back(std::move(command));

  return RunTransaction(std::move(transaction));
}

SQLStore::CommandResult SQLStore::Query(
    const std::string& sql,
    const std::vector<mojom::DBCommand::RecordBindingType>& columns) {
  return Query(sql, columns, {});
}

SQLStore::CommandResult SQLStore::Query(
    const std::string& sql,
    const std::vector<mojom::DBCommand::RecordBindingType>& columns,
    std::vector<mojom::DBCommandBindingPtr>&& bindings) {
  auto command = mojom::DBCommand::New();
  command->type = mojom::DBCommand::Type::READ;
  command->command = sql;
  command->bindings = std::move(bindings);
  command->record_bindings = columns;

  auto transaction = mojom::DBTransaction::New();
  transaction->commands.push_back(std::move(command));

  return RunTransaction(std::move(transaction));
}

SQLStore::CommandResult SQLStore::RunTransactionImpl(
    mojom::DBTransactionPtr transaction) {
  DCHECK(transaction);

  CommandResult::Resolver resolver;
  context()->GetLedgerClient()->RunDBTransaction(
      std::move(transaction),
      [resolver](mojom::DBCommandResponsePtr response) mutable {
        DCHECK(response);
        resolver.Complete(std::move(response));
      });

  return resolver.result();
}

}  // namespace ledger
