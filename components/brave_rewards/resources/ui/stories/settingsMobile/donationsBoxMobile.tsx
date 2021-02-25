/* This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this file,
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import * as React from 'react'

// Components
import { StyledListContent } from './style'
import { BoxMobile } from '../../components/mobile'
import { TableDonation, Tokens, List } from '../../components'
import { DetailRow as DonationDetailRow } from '../../components/tableDonation'
import { Column, Grid, Checkbox, ControlWrapper } from 'brave-ui/components'

// Utils
import locale from './fakeLocale'

// Assets
const favicon = require('../img/brave-favicon.png')
const eich = require('../img/eich.jpg')
const guardian = require('../img/guardian.jpg')

type Check = { yt: boolean, tw: boolean, inst: boolean }

interface Props {
  rewardsEnabled: boolean
}

interface State {
  check: Check
}

class DonationsBoxMobile extends React.Component<Props, State> {
  constructor (props: Props) {
    super(props)
    this.state = {
      check: {
        yt: true,
        tw: false,
        inst: false
      }
    }
  }

  doNothing = () => {
    console.log('nothing')
  }

  get donationRows (): DonationDetailRow[] {
    return [
      {
        profile: {
          name: 'Jonathon Doe',
          verified: true,
          provider: 'youtube',
          src: favicon
        },
        url: 'https://brave.com',
        type: 'recurring',
        contribute: {
          tokens: '2.0',
          converted: '0.20'
        },
        onRemove: this.doNothing
      },
      {
        profile: {
          verified: false,
          name: 'theguardian.com',
          src: guardian
        },
        url: 'https://brave.com',
        type: 'donation',
        contribute: {
          tokens: '12.0',
          converted: '6.20'
        },
        text: 'May 7'
      },
      {
        profile: {
          verified: false,
          name: 'BrendanEich',
          provider: 'twitter',
          src: eich
        },
        url: 'https://brave.com',
        type: 'tip',
        contribute: {
          tokens: '7.0',
          converted: '3.20'
        },
        text: 'May 2'
      }
    ]
  }

  onChange = (key: string, selected: boolean, child: React.ReactNode, all: { [key: string]: boolean }) => {
    this.setState({
      check: all as Check
    })
  }

  donationSettingsChild = () => {
    return (
      <>
        <Grid columns={1} customStyle={{ maxWidth: '270px', margin: '0 auto' }}>
          <Column size={1} customStyle={{ justifyContent: 'center', flexWrap: 'wrap' }}>
            <ControlWrapper text={'Enable ability to give tips on ‘Like’ posts'}>
              <Checkbox
                value={this.state.check}
                multiple={true}
                onChange={this.onChange}
              >
                <div data-key='yt'>YouTube</div>
                <div data-key='tw'>Twitter</div>
                <div data-key='rd'>Reddit</div>
                <div data-key='inst'>Instagram</div>
              </Checkbox>
            </ControlWrapper>
          </Column>
        </Grid>
      </>
    )
  }

  render () {
    return (
      <BoxMobile
        title={locale.donationTitle}
        type={'donation'}
        toggle={false}
        checked={this.props.rewardsEnabled}
        description={locale.donationDesc}
        settingsChild={this.donationSettingsChild()}
      >
        <List title={<StyledListContent>{locale.donationTotal}</StyledListContent>}>
          <StyledListContent>
            <Tokens value={'21.0'} converted={'7.00'} />
          </StyledListContent>
        </List>
        <StyledListContent>
          <TableDonation
            rows={this.donationRows}
            allItems={true}
            headerColor={true}
          >
            Please visit some sites
          </TableDonation>
        </StyledListContent>
      </BoxMobile>
    )
  }
}

export default DonationsBoxMobile
