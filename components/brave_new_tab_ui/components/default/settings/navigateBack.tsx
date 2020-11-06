// Copyright (c) 2020 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import * as React from 'react'
import styled from 'brave-ui/theme'
import { ArrowLeftIcon } from 'brave-ui/components/icons'

type Props = {
  onBack: () => {}
}

const Back = styled('button')`
  appearance: none;
  margin-bottom: 14px;
  outline: none;
  border: none;
  background: none;
  display: flex;
  flex-direction: row;
  gap: 10px;
  cursor: pointer;
  color: inherit;
  font-weight: 800;

  &:focus-visible {
    outline: solid 1px ${p => p.theme.color.brandBrave};
  }

  &:active {
    font-weight: 900;
  }
`

const Icon = styled('div')`
  width: 16px;
  height: 16px;
`

export default function NavigateBack (props: Props) {
  const onClick = React.useCallback(() => {
    props.onBack()
  }, [props.onBack])
  return (
    <Back onClick={onClick}>
      <Icon><ArrowLeftIcon /></Icon>
      <span>Back</span>
    </Back>
  )
}
