/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/ad_targeting/ad_targeting_segment_util.h"

#include <string>

#include "bat/ads/internal/client/client.h"
#include "testing/gtest/include/gtest/gtest.h"

// npm run test -- brave_unit_tests --filter=BatAds*

namespace ads {
namespace ad_targeting {

TEST(BatAdsAdTargetingSegmentUtilTest, SplitParentChildSegment) {
  // Arrange
  const std::string segment = "parent-child";

  // Act
  const SegmentList segments = SplitSegment(segment);

  // Assert
  const SegmentList expected_segments = {"parent", "child"};

  EXPECT_EQ(expected_segments, segments);
}

TEST(BatAdsAdTargetingSegmentUtilTest, SplitParentSegment) {
  // Arrange
  const std::string segment = "parent";

  // Act
  const SegmentList segments = SplitSegment(segment);

  // Assert
  const SegmentList expected_segments = {"parent"};

  EXPECT_EQ(expected_segments, segments);
}

TEST(BatAdsAdTargetingSegmentUtilTest, SplitEmptySegment) {
  // Arrange
  const std::string segment = "";

  // Act
  const SegmentList segments = SplitSegment(segment);

  // Assert
  const SegmentList expected_segments = {};

  EXPECT_EQ(expected_segments, segments);
}

TEST(BatAdsAdTargetingSegmentUtilTest, GetParentSegment) {
  // Arrange
  const std::string segment = "technology & computing-software";

  // Act
  const std::string parent_segment = GetParentSegment(segment);

  // Assert
  const std::string expected_parent_segment = "technology & computing";

  EXPECT_EQ(expected_parent_segment, parent_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, GetParentSegmentFromParentSegment) {
  // Arrange
  const std::string segment = "technology & computing";

  // Act
  const std::string parent_segment = GetParentSegment(segment);

  // Assert
  const std::string expected_parent_segment = "technology & computing";

  EXPECT_EQ(expected_parent_segment, parent_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, GetParentSegmentFromEmptyString) {
  // Arrange
  const std::string segment = "";

  // Act
  const std::string parent_segment = GetParentSegment(segment);

  // Assert
  const std::string expected_parent_segment = "";

  EXPECT_EQ(expected_parent_segment, parent_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, GetParentSegments) {
  // Arrange
  const SegmentList segments = {"technology & computing-software",
                                "personal finance-personal finance",
                                "automobiles"};

  // Act
  const SegmentList parent_segments = GetParentSegments(segments);

  // Assert
  const SegmentList expected_parent_segments = {
      "technology & computing", "personal finance", "automobiles"};

  EXPECT_EQ(expected_parent_segments, parent_segments);
}

TEST(BatAdsAdTargetingSegmentUtilTest, GetParentSegmentsForEmptyList) {
  // Arrange
  const SegmentList segments;

  // Act
  const SegmentList parent_segments = GetParentSegments(segments);

  // Assert
  const SegmentList expected_parent_segments = {};

  EXPECT_EQ(expected_parent_segments, parent_segments);
}

TEST(BatAdsAdTargetingSegmentUtilTest, ShouldFilterParentChildSegment) {
  // Arrange
  Client client;

  Client::Get()->ToggleAdOptOutAction("parent-child",
                                      CategoryContentInfo::OptAction::kNone);

  // Act
  const bool should_filter_segment = ShouldFilterSegment("parent-child");

  // Assert
  EXPECT_TRUE(should_filter_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, ShouldFilterParentSegment) {
  // Arrange
  Client client;

  Client::Get()->ToggleAdOptOutAction("parent",
                                      CategoryContentInfo::OptAction::kNone);

  // Act
  const bool should_filter_segment = ShouldFilterSegment("parent");

  // Assert
  EXPECT_TRUE(should_filter_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, ShouldNotFilterParentChildSegment) {
  // Arrange
  Client client;

  Client::Get()->ToggleAdOptOutAction("parent-child",
                                      CategoryContentInfo::OptAction::kNone);

  // Act
  const bool should_filter_segment = ShouldFilterSegment("foo-bar");

  // Assert
  EXPECT_FALSE(should_filter_segment);
}

TEST(BatAdsAdTargetingSegmentUtilTest, ShouldNotFilterParentSegment) {
  // Arrange
  Client client;

  Client::Get()->ToggleAdOptOutAction("parent",
                                      CategoryContentInfo::OptAction::kNone);

  // Act
  const bool should_filter_segment = ShouldFilterSegment("foo");

  // Assert
  EXPECT_FALSE(should_filter_segment);
}

}  // namespace ad_targeting
}  // namespace ads
