// Copyright (c) 2021 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import styled from 'brave-ui/theme'
import Button, { Props as ButtonProps } from 'brave-ui/components/buttonsIndicators/button'

const isDarkTheme = (p: any) => {
  return p.theme.name === 'Brave Dark'
}

interface StyledDialogWrapperProps {
  textDirection: string
}

export const StyledDialogWrapper = styled<StyledDialogWrapperProps, 'div'>('div')`
  position: fixed;
  top: 0;
  left: 0;
  width: 100%;
  height: 100%;
  z-index: 5;
  display: flex;
  justify-content: center;
  align-items: center;
`

interface StyledDialogProps {
  textDirection: string
}

export const StyledDialog = styled<StyledDialogProps, 'div'>('div')`
  position: relative;
  width: 437px;
  top: -50px;
  background-color: ${p => p.theme.color.contextMenuBackground};
  border-radius: 4px;
  padding: 32px 24px 24px 24px;
  display: flex;
  flex-direction: column;

  box-shadow: 0px 4px 12px 0px rgba(0, 0, 0, 0.2);
`

export const DialogTitle = styled<{}, 'div'>('div')`
  font-weight: 600;
  font-size: 15px;
  line-height: 20px;
  color: ${p => isDarkTheme(p) ? '#F0F2FF' : '#212529'};
`

export const CloseButton = styled('button')`
  appearance: none;
  background: none;
  border: none;
  position: absolute;
  padding: 4px;
  box-sizing: content-box;
  margin: 0;
  right: 16px;
  top: 16px;
  width: 16px;
  height: 16px;
  cursor: pointer;
  border-radius: 100%;
  outline: none;
  transition: background .12s ease-in-out, box-shadow .12s ease-in-out;
  [dir=rtl] & {
    right: unset;
    left: 16px;
  }
  :hover, :focus-visible {
    background: rgba(255, 255, 255, .3);
  }
  :active {
    box-shadow: 0 0 0 4px rgba(255, 255, 255, .6);
  }

  color: ${p => isDarkTheme(p) ? '#C2C4CF' : '#495057'};
`

export const StyledInputLabel = styled<{}, 'div'>('div')`
  margin-top: 18px;
  font-weight: 500;
  font-size: 13px;
  line-height: 16px;
  color: ${p => isDarkTheme(p) ? '#C2C4CF' : '#495057'};
`

export const StyledInput = styled<{}, 'input'>('input')`
  outline: none;
  margin-top: 6px;
  width: 389px;
  height: 40px;
  background: ${p => isDarkTheme(p) ? '#1E2029' : 'white'};
  padding: 10px 18px;
  border-radius: 4px;
  border: 1px solid ${p => isDarkTheme(p) ? '#5E6175' : '#AEB1C2'};
  color: ${p => isDarkTheme(p) ? '#C2C4CF' : '#495057'};
  font-family: Poppins;
  font-size: 13px;
  font-style: normal;
  font-weight: 400;
  line-height: 20px;
  letter-spacing: 0.01em;
  text-align: left;

  &:focus, :hover {
    border: 4px solid #A0A5EB;
    padding: 7px 15px;
  }

  &::placeholder {
    color: #84889C;
  }
`

export const StyledButtonsContainer = styled<{}, 'div'>('div')`
  box-sizing: border-box;
  display: flex;
  flex-direction: row;
  flex-wrap: wrap;
  justify-content: flex-end;
  margin-top: 24px;
  gap: 10px;
`

export const StyledButton = styled(Button as React.ComponentType<ButtonProps>)`
  &:focus {
    outline-offset: 2px;
    outline-color: ${p => p.theme.color.brandBrave};
    outline-width: 2px;
  }

  &:active {
    outline: none;
  }
`
