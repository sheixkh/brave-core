/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at https://mozilla.org/MPL/2.0/. */

#include "brave/components/brave_wallet/buildflags/buildflags.h"

#if BUILDFLAG(BRAVE_WALLET_ENABLED)
#include "brave/components/brave_wallet/brave_wallet_constants.h"
#include "content/public/common/url_constants.h"
#include "extensions/common/constants.h"
#include "url/gurl.h"
#endif

#define ShouldTrackURLForRestore ShouldTrackURLForRestore_ChromiumImpl

#include "../../../../../chrome/browser/sessions/session_common_utils.cc"

#undef ShouldTrackURLForRestore

bool ShouldTrackURLForRestore(const GURL& url) {
#if BUILDFLAG(BRAVE_WALLET_ENABLED)
  if (url.SchemeIs(content::kChromeUIScheme) && url.host() == "wallet") {
    return false;
  } else if (url.SchemeIs("chrome-extension") &&
             url.host() == ethereum_remote_client_extension_id) {
    return false;
  }
#endif
  return ShouldTrackURLForRestore_ChromiumImpl(url);
}
