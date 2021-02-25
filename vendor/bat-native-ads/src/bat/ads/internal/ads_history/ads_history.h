/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_HISTORY_ADS_HISTORY_H_
#define BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_HISTORY_ADS_HISTORY_H_

#include <stdint.h>

#include "bat/ads/ads_history_info.h"
#include "bat/ads/internal/frequency_capping/permission_rules/ads_per_day_frequency_cap.h"
#include "bat/ads/internal/frequency_capping/permission_rules/new_tab_page_ads_per_day_frequency_cap.h"
#include "bat/ads/internal/frequency_capping/permission_rules/promoted_content_ads_per_day_frequency_cap.h"

namespace ads {

class ConfirmationType;
struct AdNotificationInfo;
struct NewTabPageAdInfo;
struct PromotedContentAdInfo;

namespace history {

// Maximum entries based upon 7 days of ad history for
// |kAdNotificationsPerDayFrequencyCap| ad notifications per day with 2
// confirmation types (viewed and either clicked or dismissed) and
// |kNewTabPageAdsPerDayFrequencyCap| new tab page ads per day with 2
// confirmation types (viewed and clicked)
// |kPromotedContentAdsPerDayFrequencyCap| promoted content ads per day with 2
// confirmation types (viewed and clicked)
const size_t kMaximumEntries =
    7 * ((kAdNotificationsPerDayFrequencyCap * 2) +
         (kNewTabPageAdsPerDayFrequencyCap * 2) +
         (kPromotedContentAdsPerDayFrequencyCap * 2));

AdsHistoryInfo Get(const AdsHistoryInfo::FilterType filter_type,
                   const AdsHistoryInfo::SortType sort_type,
                   const uint64_t from_timestamp,
                   const uint64_t to_timestamp);

void AddAdNotification(const AdNotificationInfo& ad,
                       const ConfirmationType& confirmation_type);

void AddNewTabPageAd(const NewTabPageAdInfo& ad,
                     const ConfirmationType& confirmation_type);

void AddPromotedContentAd(const PromotedContentAdInfo& ad,
                          const ConfirmationType& confirmation_type);

}  // namespace history
}  // namespace ads

#endif  // BRAVE_VENDOR_BAT_NATIVE_ADS_SRC_BAT_ADS_INTERNAL_ADS_HISTORY_ADS_HISTORY_H_
