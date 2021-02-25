/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_RESOURCE_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_RESOURCE_H_

#include <stdint.h>

#include <string>

#include "bat/ads/internal/ad_targeting/data_types/behavioral/purchase_intent/purchase_intent_info.h"
#include "bat/ads/internal/ad_targeting/resources/resource.h"

namespace ads {
namespace ad_targeting {
namespace resource {

class PurchaseIntent : public Resource<PurchaseIntentInfo> {
 public:
  PurchaseIntent();
  ~PurchaseIntent() override;

  PurchaseIntent(const PurchaseIntent&) = delete;
  PurchaseIntent& operator=(const PurchaseIntent&) = delete;

  bool IsInitialized() const override;

  void LoadForLocale(const std::string& locale);

  void LoadForId(const std::string& locale);

  PurchaseIntentInfo get() const override;

 private:
  bool is_initialized_ = false;

  PurchaseIntentInfo purchase_intent_;

  bool FromJson(const std::string& json);
};

}  // namespace resource
}  // namespace ad_targeting
}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_AD_TARGETING_RESOURCES_BEHAVIORAL_PURCHASE_INTENT_PURCHASE_INTENT_RESOURCE_H_
