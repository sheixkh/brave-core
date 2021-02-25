/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'

// Components
import {
  Box,
  DisabledContent,
  List,
  ModalContribute,
  TableContribute,
  Tokens
} from '../../components'
import { Column, Grid, Select, ControlWrapper, Checkbox } from 'brave-ui/components'
import { DetailRow as ContributeDetailRow } from '../../components/tableContribute'
import NextContribution from '../../components/nextContribution'

// Utils
import locale from './fakeLocale'

// Assets
const favicon = require('../img/brave-favicon.png')
const buzz = require('../img/buzz.jpg')
const ddgo = require('../img/ddgo.jpg')
const guardian = require('../img/guardian.jpg')
const wiki = require('../img/wiki.jpg')

const doNothing = () => {
  console.log('nothing')
}

interface State {
  contributeToggle: boolean
  modalContribute: boolean
  settings: boolean
}

class ContributeBox extends React.Component<{}, State> {
  constructor (props: {}) {
    super(props)
    this.state = {
      contributeToggle: true,
      modalContribute: false,
      settings: false
    }
  }

  contributeSettingsChild = () => {
    return (
      <>
        <Grid columns={1} customStyle={{ margin: '0 auto' }}>
          <Column size={1} customStyle={{ justifyContent: 'center', flexWrap: 'wrap' }}>
            <ControlWrapper text={locale.contributionMonthly}>
              <Select>
                <div data-value='10'><Tokens value={'10.0'} converted={'4.00'} /></div>
                <div data-value='20'><Tokens value={'20.0'} converted={'6.00'} /></div>
                <div data-value='40'><Tokens value={'40.0'} converted={'12.00'} /></div>
                <div data-value='100'><Tokens value={'100.0'} converted={'40.00'} /></div>
              </Select>
            </ControlWrapper>
            <ControlWrapper text={locale.contributionMinTime}>
              <Select>
                <div data-value='5'>{locale.contributionTime5}</div>
                <div data-value='8'>{locale.contributionTime8}</div>
                <div data-value='60'>{locale.contributionTime60}</div>
              </Select>
            </ControlWrapper>
            <ControlWrapper text={locale.contributionMinVisits}>
              <Select>
                <div data-value='5'>{locale.contributionVisit1}</div>
                <div data-value='8'>{locale.contributionVisit5}</div>
                <div data-value='60'>{locale.contributionVisit10}</div>
              </Select>
            </ControlWrapper>
            <ControlWrapper text={locale.contributionOther}>
              <Checkbox
                value={{
                  contributionNonVerified: true,
                  contributionVideos: true
                }}
                multiple={true}
              >
                <div data-key='contributionNonVerified'>{locale.contributionNonVerified}</div>
                <div data-key='contributionVideos'>{locale.contributionVideos}</div>
              </Checkbox>
            </ControlWrapper>
          </Column>
        </Grid>
      </>
    )
  }

  get contributeRows (): ContributeDetailRow[] {
    return [
      {
        profile: {
          name: 'Jonathon Doe',
          verified: true,
          provider: 'youtube',
          src: favicon
        },
        url: 'https://brave.com',
        attention: 40,
        onRemove: doNothing
      },
      {
        profile: {
          name: 'duckduckgo.com',
          verified: true,
          src: ddgo
        },
        url: 'https://brave.com',
        attention: 20,
        onRemove: doNothing
      },
      {
        profile: {
          name: 'buzzfeed.com',
          verified: false,
          src: buzz
        },
        url: 'https://brave.com',
        attention: 10,
        onRemove: doNothing
      },
      {
        profile: {
          name: 'theguardian.com',
          verified: true,
          src: guardian
        },
        url: 'https://brave.com',
        attention: 5,
        onRemove: doNothing
      },
      {
        profile: {
          name: 'wikipedia.org',
          verified: false,
          src: wiki
        },
        url: 'https://brave.com',
        attention: 4,
        onRemove: doNothing
      }
    ]
  }

  contributeDisabled () {
    return (
      <DisabledContent
        type={'contribute'}
      >
        Pay directly for the content you love. <br />
        Your <b>monthly allowance</b> gets divided based on your attention metric.
      </DisabledContent>
    )
  }

  onContributeToggle = () => {
    this.setState({ contributeToggle: !this.state.contributeToggle })
  }

  onContributeModalClose = () => {
    this.setState({ modalContribute: false })
  }

  onContributeModalOpen = () => {
    this.setState({ modalContribute: true })
  }

  onSettingsToggle = () => {
    this.setState({ settings: !this.state.settings })
  }

  render () {
    return (
      <Box
        title={locale.contributionTitle}
        type={'contribute'}
        description={locale.contributionDesc}
        toggle={true}
        checked={this.state.contributeToggle}
        settingsChild={this.contributeSettingsChild()}
        disabledContent={this.contributeDisabled()}
        onToggle={this.onContributeToggle}
        settingsOpened={this.state.settings}
        onSettingsClick={this.onSettingsToggle}
      >
        {
          this.state.modalContribute
            ? <ModalContribute
              onRestore={doNothing}
              excludedRows={this.contributeRows}
              rows={this.contributeRows}
              onClose={this.onContributeModalClose.bind(self)}
            />
            : null
        }
        <List title={locale.contributionMonthly}>
          <Select floating={true}>
            <div data-value='10'><Tokens value={'10.0'} converted={'4.00'} /></div>
            <div data-value='20'><Tokens value={'20.0'} converted={'6.00'} /></div>
            <div data-value='40'><Tokens value={'40.0'} converted={'12.00'} /></div>
            <div data-value='100'><Tokens value={'100.0'} converted={'40.00'} /></div>
          </Select>
        </List>
        <List
          title={locale.contributionNextDate}
        >
          <NextContribution>July 25th</NextContribution>
        </List>
        <List title={locale.contributionSites}>
          Total &nbsp;<Tokens value={'55'} hideText={true} />
        </List>
        <TableContribute
          header={[
            'Site',
            'Attention'
          ]}
          rows={this.contributeRows}
          allSites={false}
          numSites={55}
          showRemove={true}
          numExcludedSites={100}
          onShowAll={this.onContributeModalOpen.bind(self)}
          headerColor={true}
        >
          Please visit some sites
        </TableContribute>
      </Box>
    )
  }
}

export default ContributeBox
