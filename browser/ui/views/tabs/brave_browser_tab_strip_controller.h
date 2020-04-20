/* Copyright (c) 2019 The Brave Authors. All rights reserved.
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

#ifndef BRAVE_BROWSER_UI_VIEWS_TABS_BRAVE_BROWSER_TAB_STRIP_CONTROLLER_H_
#define BRAVE_BROWSER_UI_VIEWS_TABS_BRAVE_BROWSER_TAB_STRIP_CONTROLLER_H_

#include <memory>

#include "brave/browser/ui/tabs/brave_tab_strip_model.h"
#include "chrome/browser/ui/views/tabs/browser_tab_strip_controller.h"

class BraveTabContextMenuContents;

class BraveBrowserTabStripController : public BrowserTabStripController {
 public:
  BraveBrowserTabStripController(TabStripModel* model,
                                 BrowserView* browser_view);
  ~BraveBrowserTabStripController() override;

  // BrowserTabStripController overrides:
  void ShowContextMenuForTab(Tab* tab,
                             const gfx::Point& p,
                             ui::MenuSourceType source_type) override;

  void StartMRUCycling(BraveTabStripModel* brave_tab_strip_model) override;

 private:
  // To capture the release of the Ctrl key when doing a MRU cycling with
  // Ctrl-tab
  class CtrlReleaseHandler : public ui::EventHandler {
   public:
    explicit CtrlReleaseHandler(BraveTabStripModel* model,
                                BrowserView* browser_view);
    ~CtrlReleaseHandler() override;

   private:
    void OnKeyEvent(ui::KeyEvent* event) override;
    BraveTabStripModel* model_;
    BrowserView* browser_view_;
    DISALLOW_COPY_AND_ASSIGN(CtrlReleaseHandler);
  };

  // If non-NULL it means we're showing a menu for the tab.
  std::unique_ptr<BraveTabContextMenuContents> context_menu_contents_;

  std::unique_ptr<CtrlReleaseHandler> ctrl_released_event_handler_;

  DISALLOW_COPY_AND_ASSIGN(BraveBrowserTabStripController);
};

#endif  // BRAVE_BROWSER_UI_VIEWS_TABS_BRAVE_BROWSER_TAB_STRIP_CONTROLLER_H_
