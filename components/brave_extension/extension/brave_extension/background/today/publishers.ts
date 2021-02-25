// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import { debounce } from '../../../../../common/debounce'
import Events from '../../../../../common/events'
import { fetchResource } from './privateCDN'
import { getPrefs as getPublisherPrefs, addPrefsChangedListener } from './publisher-user-prefs'
import { getSourcesUrl } from './urls'

let memoryData: BraveToday.Publishers | undefined
let readLock: Promise<void> | null
const publishersEvents = new Events()
const eventNameChanged = 'publishers-changed'
const storageKey = 'todayPublishers'
const STORAGE_SCHEMA_VERSION = 1

async function isValidStorageData (data: {[key: string]: any}) {
  return (
    data && data.todayPublishers &&
    data.todayPublishers.storageSchemaVersion === STORAGE_SCHEMA_VERSION &&
    data.todayPublishers.sourceUrl === (await getSourcesUrl()) &&
    data.todayPublishers.publishers
  )
}

async function setPublishersCache (publishers: BraveToday.Publishers) {
  chrome.storage.local.set({
    [storageKey]: {
      storageSchemaVersion: STORAGE_SCHEMA_VERSION,
      sourceUrl: (await getSourcesUrl()),
      publishers
    }
  })
}

function getPublishersFromCache () {
  return new Promise<void>(resolve => {
    chrome.storage.local.get(storageKey, async (data) => {
      if (await isValidStorageData(data)) {
        memoryData = data[storageKey].publishers
      }
      resolve()
    })
  })
}

const getLocalDataLock: Promise<void> = getPublishersFromCache()

async function convertToObject (publishers: BraveToday.Publisher[]): Promise<BraveToday.Publishers> {
  const prefs = await getPublisherPrefs()
  const data: BraveToday.Publishers = {}
  for (const publisher of publishers) {
    data[publisher.publisher_id] = {
      ...publisher,
      // TODO: read existing value
      user_enabled: prefs[publisher.publisher_id]
    }
  }
  return data
}

function performUpdate (notify: boolean = true) {
  // Sanity check
  if (readLock) {
    console.error('Asked to update feed but already waiting for another update!')
    return
  }
  // Only run this once at a time, otherwise wait for the update
  readLock = new Promise(async function (resolve, reject) {
    try {
      // TODO(petemill): Use If-None-Match so we don't re-download the exact
      // same publisher list. Save Etag in storage.
      const feedResponse = await fetchResource(await getSourcesUrl())
      if (feedResponse.ok) {
        const feedContents: BraveToday.Publisher[] = await feedResponse.json()
        console.debug('fetched today publishers', feedContents)
        memoryData = await convertToObject(feedContents)
        resolve()
        await setPublishersCache(memoryData)
        // Notify
        if (notify) {
          publishersEvents.dispatchEvent<BraveToday.Publishers>(eventNameChanged, memoryData)
        }
      } else {
        throw new Error(`Not ok when fetching publishers. Status ${feedResponse.status} (${feedResponse.statusText})`)
      }
    } catch (e) {
      console.error('Could not process Brave Today sources contents')
      reject(e)
    } finally {
      readLock = null
    }
  })
}

export async function getOrFetchData () {
  await getLocalDataLock
  if (memoryData) {
    return memoryData
  }
  // Don't notify about updated data if we're only getting new data
  // due to not having retrieved any data yet. Avoids double feed fetch since
  // requesting feed data also requests publishers data.
  return update(false, false)
}

export async function update (force: boolean = false, notify: boolean = true) {
  // Fetch but only once at a time, and wait.
  if (!readLock) {
    performUpdate(notify)
  } else if (force) {
    // If there was already an update in-progress, and we want
    // to make sure we use the latest data, we'll have to perform
    // another update to be sure.
    await readLock
    performUpdate(notify)
  }
  await readLock
  return memoryData
}

// Allow subscribers to observe when we have new data
type changeListener = (publishers: BraveToday.Publishers) => any
export function addPublishersChangedListener (listener: changeListener) {
  publishersEvents.addEventListener<BraveToday.Publishers>(eventNameChanged, listener)
}

const updateOnPrefsChanged = debounce(async () => {
  // TODO(petemill): only re-parse, don't re-fetch (as no indication that remote data
  // has changed).
  await update()
}, 2000)

// When publisher pref changes, update prefs data as we depend on it
addPrefsChangedListener(async function (prefs) {
  updateOnPrefsChanged()
})
