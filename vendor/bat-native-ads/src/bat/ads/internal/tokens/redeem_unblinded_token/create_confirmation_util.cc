/* Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#include "bat/ads/internal/tokens/redeem_unblinded_token/create_confirmation_util.h"

#include <utility>

#include "base/base64url.h"
#include "base/json/json_writer.h"
#include "base/optional.h"
#include "base/strings/string_number_conversions.h"
#include "base/values.h"
#include "bat/ads/ads.h"
#include "bat/ads/internal/account/confirmations/confirmation_info.h"
#include "bat/ads/internal/features/features.h"
#include "bat/ads/internal/locale/country_code_util.h"
#include "bat/ads/internal/platform/platform_helper.h"
#include "bat/ads/internal/privacy/challenge_bypass_ristretto_util.h"
#include "bat/ads/internal/privacy/unblinded_tokens/unblinded_token_info.h"
#include "brave/components/l10n/browser/locale_helper.h"
#include "brave/components/l10n/common/locale_util.h"
#include "wrapper.hpp"

namespace ads {

using challenge_bypass_ristretto::TokenPreimage;
using challenge_bypass_ristretto::VerificationKey;
using challenge_bypass_ristretto::VerificationSignature;

std::string CreateConfirmationRequestDTO(const ConfirmationInfo& confirmation) {
  base::Value dto(base::Value::Type::DICTIONARY);

  dto.SetKey("creativeInstanceId",
             base::Value(confirmation.creative_instance_id));

  dto.SetKey("payload", base::Value(base::Value::Type::DICTIONARY));

  const std::string blinded_payment_token_base64 =
      confirmation.blinded_payment_token.encode_base64();
  dto.SetKey("blindedPaymentToken", base::Value(blinded_payment_token_base64));

  const std::string type = std::string(confirmation.type);
  dto.SetKey("type", base::Value(type));

  DCHECK(!g_build_channel.name.empty());
  dto.SetKey("buildChannel", base::Value(g_build_channel.name));

  if (g_build_channel.is_release) {
    const std::string locale =
        brave_l10n::LocaleHelper::GetInstance()->GetLocale();

    if (locale::IsMemberOfAnonymitySet(locale)) {
      const std::string country_code = brave_l10n::GetCountryCode(locale);
      dto.SetKey("countryCode", base::Value(country_code));
    } else {
      if (locale::ShouldClassifyAsOther(locale)) {
        dto.SetKey("countryCode", base::Value("??"));
      }
    }
  }

  if (!features::HasActiveStudy()) {
    dto.SetKey("experiment", base::Value(base::Value::Type::DICTIONARY));
  } else {
    base::Value dictionary(base::Value::Type::DICTIONARY);
    const base::Optional<std::string> study = features::GetStudy();
    if (study.has_value() && !study->empty()) {
      dictionary.SetKey("name", base::Value(study.value()));
    }

    const base::Optional<std::string> group = features::GetGroup();
    if (group.has_value() && !group->empty()) {
      dictionary.SetKey("group", base::Value(group.value()));
    }

    dto.SetKey("experiment", std::move(dictionary));
  }

  const std::string platform = PlatformHelper::GetInstance()->GetPlatformName();
  dto.SetKey("platform", base::Value(platform));

  std::string json;
  base::JSONWriter::Write(dto, &json);

  return json;
}

std::string CreateCredential(const privacy::UnblindedTokenInfo& unblinded_token,
                             const std::string& payload) {
  DCHECK(!payload.empty());

  VerificationKey verification_key =
      unblinded_token.value.derive_verification_key();
  if (privacy::ExceptionOccurred()) {
    NOTREACHED();
    return "";
  }

  VerificationSignature verification_signature = verification_key.sign(payload);
  if (privacy::ExceptionOccurred()) {
    NOTREACHED();
    return "";
  }

  const std::string verification_signature_base64 =
      verification_signature.encode_base64();
  if (privacy::ExceptionOccurred()) {
    NOTREACHED();
    return "";
  }

  TokenPreimage token_preimage = unblinded_token.value.preimage();
  if (privacy::ExceptionOccurred()) {
    NOTREACHED();
    return "";
  }

  const std::string token_preimage_base64 = token_preimage.encode_base64();
  if (privacy::ExceptionOccurred()) {
    NOTREACHED();
    return "";
  }

  base::Value dictionary(base::Value::Type::DICTIONARY);

  dictionary.SetKey("payload", base::Value(payload));
  dictionary.SetKey("signature", base::Value(verification_signature_base64));
  dictionary.SetKey("t", base::Value(token_preimage_base64));

  std::string json;
  base::JSONWriter::Write(dictionary, &json);

  std::string credential_base64url;
  base::Base64UrlEncode(json, base::Base64UrlEncodePolicy::INCLUDE_PADDING,
                        &credential_base64url);

  return credential_base64url;
}

}  // namespace ads
