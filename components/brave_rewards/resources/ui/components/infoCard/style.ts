/* This Source Code Form is subject to the terms of the Mozilla Public
 * License. v. 2.0. If a copy of the MPL was not distributed with this file.
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'styled-components'

export const StyledInfoCard = styled<{}, 'div'>('div')`
  height: 290px;
  border-radius: 4px;
  text-align: center;
  padding: 31px 15px 15px;
  background: #fff;
  max-width: 275px;
  margin: 0 auto;
  box-shadow: 0 2 4px  rgba(0,0,0,.2);
`

export const StyledTitle = styled<{}, 'strong'>('strong')`
  color: #222326;
  font-size: 18px;
  font-weight: 500;
  line-height: 28px;
`

export const StyledDesc = styled<{}, 'p'>('p')`
  color: #686978;
  font-size: 16px;
  line-height: 22px;
  font-family: Muli, sans-serif;
  letter-spacing: 0.16px;
  margin: 10px 0 8px;
  font-weight: 400;
`

export const StyledFigure = styled<{}, 'figure'>('figure')`
  box-sizing: border-box;
  display: block;
  max-width: 100%;
  margin: 10px auto 20px;
  height: 80px;
`

export const StyledGrid = styled<{}, 'div'>('div')`
  display: grid;
  grid-gap: 0px;
  grid-template-columns: 1fr 1fr 1fr;
  align-items: center;
  justify-content: center;

  @media (max-width: 640px) {
    grid-gap: 20px;
    grid-template-columns: 1fr;
  }
`

export const StyledColumn = styled<{}, 'div'>('div')`
  padding: 0 10px;
`
