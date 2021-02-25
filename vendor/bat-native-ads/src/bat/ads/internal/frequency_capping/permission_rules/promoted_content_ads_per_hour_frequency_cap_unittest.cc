/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/frequency_capping/permission_rules/promoted_content_ads_per_hour_frequency_cap.h"

#include "bat/ads/internal/frequency_capping/frequency_capping_unittest_util.h"
#include "bat/ads/internal/unittest_base.h"
#include "bat/ads/internal/unittest_util.h"
#include "bat/ads/pref_names.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {

namespace {
const char kCreativeInstanceId[] = "9aea9a47-c6a0-4718-a0fa-706338bb2156";
}  // namespace

class BatAdsPromotedContentAdsPerHourFrequencyCapTest : public UnitTestBase {
 protected:
  BatAdsPromotedContentAdsPerHourFrequencyCapTest() = default;

  ~BatAdsPromotedContentAdsPerHourFrequencyCapTest() override = default;
};

TEST_F(BatAdsPromotedContentAdsPerHourFrequencyCapTest,
       AllowAdIfThereIsNoAdsHistory) {
  // Arrange
  const AdEventList ad_events;

  // Act
  PromotedContentAdsPerHourFrequencyCap frequency_cap(ad_events);
  const bool is_allowed = frequency_cap.ShouldAllow();

  // Assert
  EXPECT_TRUE(is_allowed);
}

TEST_F(BatAdsPromotedContentAdsPerHourFrequencyCapTest,
       AllowAdIfDoesNotExceedCap) {
  // Arrange
  CreativeAdInfo ad;
  ad.creative_instance_id = kCreativeInstanceId;

  const AdEventInfo ad_event = GenerateAdEvent(AdType::kPromotedContentAd, ad,
                                               ConfirmationType::kViewed);

  const AdEventList ad_events(kPromotedContentAdsPerHourFrequencyCap - 1,
                              ad_event);

  // Act
  PromotedContentAdsPerHourFrequencyCap frequency_cap(ad_events);
  const bool is_allowed = frequency_cap.ShouldAllow();

  // Assert
  EXPECT_TRUE(is_allowed);
}

TEST_F(BatAdsPromotedContentAdsPerHourFrequencyCapTest,
       AllowAdIfDoesNotExceedCapAfter1Hour) {
  // Arrange
  CreativeAdInfo ad;
  ad.creative_instance_id = kCreativeInstanceId;

  const AdEventInfo ad_event = GenerateAdEvent(AdType::kPromotedContentAd, ad,
                                               ConfirmationType::kViewed);

  const AdEventList ad_events(kPromotedContentAdsPerHourFrequencyCap, ad_event);

  FastForwardClockBy(base::TimeDelta::FromHours(1));

  // Act
  PromotedContentAdsPerHourFrequencyCap frequency_cap(ad_events);
  const bool is_allowed = frequency_cap.ShouldAllow();

  // Assert
  EXPECT_TRUE(is_allowed);
}

TEST_F(BatAdsPromotedContentAdsPerHourFrequencyCapTest,
       DoNotAllowAdIfExceedsCapWithin1Hour) {
  // Arrange
  CreativeAdInfo ad;
  ad.creative_instance_id = kCreativeInstanceId;

  const AdEventInfo ad_event = GenerateAdEvent(AdType::kPromotedContentAd, ad,
                                               ConfirmationType::kViewed);

  const AdEventList ad_events(kPromotedContentAdsPerHourFrequencyCap, ad_event);

  FastForwardClockBy(base::TimeDelta::FromMinutes(59));

  // Act
  PromotedContentAdsPerHourFrequencyCap frequency_cap(ad_events);
  const bool is_allowed = frequency_cap.ShouldAllow();

  // Assert
  EXPECT_FALSE(is_allowed);
}

TEST_F(BatAdsPromotedContentAdsPerHourFrequencyCapTest, AdsPerHour) {
  // Arrange

  // Act

  // Assert
  EXPECT_EQ(4UL, kPromotedContentAdsPerHourFrequencyCap);
}

}  // namespace ads
