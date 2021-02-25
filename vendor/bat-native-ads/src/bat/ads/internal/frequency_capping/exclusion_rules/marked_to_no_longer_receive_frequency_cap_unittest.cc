/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/exclusion_rules/marked_to_no_longer_receive_frequency_cap.h"

#include "bat/ads/internal/unittest_base.h"
#include "bat/ads/internal/unittest_util.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

namespace {
const char kCreativeSetId[] = "654f10df-fbc4-4a92-8d43-2edf73734a60";
}  // namespace

class BatAdsMarkedToNoLongerReceiveFrequencyCapTest : public UnitTestBase {
 protected:
  BatAdsMarkedToNoLongerReceiveFrequencyCapTest() = default;

  ~BatAdsMarkedToNoLongerReceiveFrequencyCapTest() override = default;
};

TEST_F(BatAdsMarkedToNoLongerReceiveFrequencyCapTest,
       AllowAdIfNotMarkedToNoLongerReceive) {
  // Arrange
  CreativeAdInfo ad;
  ad.creative_set_id = kCreativeSetId;

  // Act
  MarkedToNoLongerReceiveFrequencyCap frequency_cap;
  const bool should_exclude = frequency_cap.ShouldExclude(ad);

  // Assert
  EXPECT_FALSE(should_exclude);
}

TEST_F(BatAdsMarkedToNoLongerReceiveFrequencyCapTest,
       DoNotAllowAdIfMarkedToNoLongerReceive) {
  // Arrange
  CreativeAdInfo ad;
  ad.creative_set_id = kCreativeSetId;

  Client::Get()->ToggleAdThumbDown(ad.creative_instance_id, ad.creative_set_id,
                                   AdContentInfo::LikeAction::kThumbsUp);

  // Act
  MarkedToNoLongerReceiveFrequencyCap frequency_cap;
  const bool should_exclude = frequency_cap.ShouldExclude(ad);

  // Assert
  EXPECT_TRUE(should_exclude);
}

}  // namespace ads
