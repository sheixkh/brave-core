/**
 * Copyright (c) 2020 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/.
 */

package org.chromium.chrome.browser.widget.crypto.binance;

import android.net.Uri;
import android.os.Bundle;
import android.text.TextUtils;

import androidx.appcompat.app.AppCompatActivity;

import org.chromium.base.Log;
import org.chromium.chrome.browser.util.TabUtils;
import org.chromium.chrome.browser.widget.crypto.binance.BinanceNativeWorker;
import org.chromium.components.embedder_support.util.UrlConstants;

import java.util.List;

public class BinanceActivity extends AppCompatActivity {
    private static final String REDIRECT_URI_ROOT = "com.brave.binance";
    private static final String CODE = "code";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);

        Uri data = getIntent().getData();
        if (data != null && !TextUtils.isEmpty(data.getScheme())) {
            if (REDIRECT_URI_ROOT.equals(data.getScheme())) {
                String code = data.getQueryParameter(CODE);
                if (!TextUtils.isEmpty(code)) {
                    TabUtils.openUrlInSameTab(UrlConstants.NTP_URL);
                    BinanceNativeWorker.getInstance().setAuthToken(code);
                    BinanceNativeWorker.getInstance().getAccessToken();
                    finish();
                }
            }
        }
    }
}