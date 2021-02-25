/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/catalog/catalog_issuer_info.h"

namespace ads {

CatalogIssuerInfo::CatalogIssuerInfo() = default;

CatalogIssuerInfo::CatalogIssuerInfo(const CatalogIssuerInfo& info) = default;

CatalogIssuerInfo::~CatalogIssuerInfo() = default;

bool CatalogIssuerInfo::operator==(const CatalogIssuerInfo& rhs) const {
  return name == rhs.name && public_key == rhs.public_key;
}

bool CatalogIssuerInfo::operator!=(const CatalogIssuerInfo& rhs) const {
  return !(*this == rhs);
}

}  // namespace ads
