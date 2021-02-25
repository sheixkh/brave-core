/* This Source Code Form is subject to the terms of the Mozilla Public
 * License. v. 2.0. If a copy of the MPL was not distributed with this file.
 * You can obtain one at http://mozilla.org/MPL/2.0/. */

import styled from 'brave-ui/theme'
import { Props } from './index'

export const StyledWrapper = styled<Partial<Props>, 'button'>('button')`
  user-select: none;
  font-family: ${p => p.theme.fontFamily.body};
  border: none;
  background: none;
  padding: 0;
  cursor: pointer;
  display: flex;
  align-items: center;
  margin: 0 0 8px 0;
`

export const StyledAmount = styled<Partial<Props>, 'div'>('div')`
  opacity: 1;
  border-radius: 20px;
  color: #fff;
  border: 1px solid rgba(255, 255, 255, 0.35);
  background: ${p => p.selected ? 'rgba(255, 255, 255, 0.35)' : 'transparent'};
  vertical-align: baseline;
  padding: ${p => p.type === 'big' ? '0 16px' : '0 12px'};
  min-height: ${p => p.type === 'big' ? 40 : 32}px;
  min-width: ${p => p.type === 'big' ? '118px' : '82px'};
  margin-right: 12px;
  display: flex;
  align-items: center;
  justify-content: center;
`

export const StyledTokens = styled<{}, 'div'>('div')`
  margin-left: 5px;
`

export const StyledNumber = styled.span`
  display: flex;
`

export const StyledLogo = styled<Partial<Props>, 'div'>('div')`
  margin-right: 6px;
  width: 23px;
`

export const StyledConverted = styled<Partial<Props>, 'div'>('div')`
  vertical-align: baseline;
  opacity: ${p => p.selected ? 1 : 0.4};
  font-size: ${p => p.type === 'big' ? '12px' : '10px'};
  color: #ffffff;
  display: inline-block;
  font-weight: 500;
`
