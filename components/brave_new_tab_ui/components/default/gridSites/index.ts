// Copyright (c) 2019 The Brave Authors. All rights reserved.
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this file,
// you can obtain one at http://mozilla.org/MPL/2.0/.

import styled, { css } from 'brave-ui/theme'

const isDarkTheme = (p: any) => {
  return p.theme.name === 'Brave Dark'
}

export const AddSiteTileImage = styled<{}, 'div'>('div')`
  background: rgba(255, 255, 255, 0.2);
  backdrop-filter: blur(8px);
  border-radius: 8px;
  width: 70px;
  height: 70px;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;

  &:hover {
    background: rgba(255, 255, 255, 0.4);
  }
`

export const AddSiteTile = styled<{}, 'button'>('button')`
  background: transparent;
  width: 78px;
  height: 110px;
  cursor: pointer;
  border: none;
  margin: 0;
  padding: 0;
  outline: unset;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  visibility: hidden;

  &:focus-visible, :focus {
    ${AddSiteTileImage} {
      width: 78px;
      height: 78px;
      background-clip: padding-box;
      border: 4px solid white;
    }
  }
`

export interface ListProps {
  blockNumber: number
  isDragging: boolean
}

export const List = styled<ListProps, 'div'>('div')`
  justify-self: start;
  align-items: normal;
  height: 100%;
  display: grid;
  grid-template-columns: repeat(${p => Math.min(p.blockNumber, 6).toString()}, 92px);
  justify-content: var(--ntp-item-justify, start);

  @media screen and (max-width: 700px) {
    grid-template-columns: repeat(${p => Math.min(p.blockNumber, 3).toString()}, 92px);
  }

  @media screen and (max-width: 390px) {
    grid-template-columns: repeat(${p => Math.min(p.blockNumber, 2).toString()}, 92px);
  }

  ${p => !p.isDragging && css`
    &:hover {
      ${AddSiteTile} {
        visibility: visible;
      }
    }
  `}
`

export const TileActionsContainer = styled<{}, 'nav'>('nav')`
  box-sizing: border-box;
  opacity: 0;
  visibility: hidden;
  transition: 0.15s opacity linear;
  position: absolute;
  width: 40px;
  height: 40px;
  z-index: 1;
  top: -12px;
  right: -12px;
  display: flex;
`

export const TileMenu = styled<{}, 'div'>('div')`
  position: absolute;
  top: 15px;
  left: 80px;
  min-width: 185px;
  height: 72px;
  padding: 8px 0;
  background: ${p => isDarkTheme(p) ? '#3B3E4F' : '#FFF'};
  display: flex;
  flex-direction: column;
  border-radius: 4px;
  box-shadow: 0px 0px 16px 0px rgba(0, 0, 0, 0.3);
  z-index: 2;
`

export const TileMenuItem = styled<{}, 'button'>('button')`
  width: 100%;
  height: 30px;
  font-family: Poppins;
  font-size: 13px;
  font-style: normal;
  font-weight: 500;
  line-height: 20px;
  letter-spacing: 0.01em;
  text-align: left;
  margin: 0;
  border: none;
  outline: unset;
  padding: 4px 13px;
  background: inherit;
  display: flex;
  flex-direction: row;
  align-items: center;
  gap: 11px;
  cursor: pointer;
  color: ${p => p.theme.color.contextMenuHoverForeground};

  &:hover, :focus-visible {
    background-color: ${p => p.theme.color.contextMenuHoverBackground};
    color: ${p => p.theme.color.contextMenuHoverForeground};
  }
`

export const TileAction = styled<{}, 'button'>('button')`
  -webkit-appearance: none;
  box-sizing: border-box;
  transition: color 0.1s linear;
  background: #DADCEB;
  width: 100%;
  border-radius: 50%;
  margin: 0;
  cursor: pointer;
  display: flex;
  align-items: center;
  justify-content: center;
  outline: unset;
  background-clip: padding-box;
  border: 4px solid transparent;

  &:focus-visible {
    border: 4px solid rgba(255, 255, 255, 0.6);
  }

  &:active {
    background: #AEB1C2;
    border: 4px solid transparent;
    background-clip: padding-box;
  }
`

export const TileFavicon = styled<{}, 'img'>('img')`
  background-color: #ffffff;
  display: block;
  padding: 16px;
  width: 70px;
  height: 70px;
  box-shadow: 0px 1px 4px 0px rgba(0, 0, 0, 0.3);
  border-radius: 8px;
  object-fit: contain;
`

export const TileTitle = styled<{}, 'p'>('p')`
  margin: 7px 0 0 0;
  font-family: Poppins;
  font-weight: 400;
  font-size: 11px;
  line-height: 17px;
  max-width: 100%;
  height: 17px;
  color: white;
  padding: 0 2px;
  overflow: hidden;
  white-space: nowrap;
  text-overflow: ellipsis;
`

interface TileProps {
  isDragging: boolean
  isMenuShowing: boolean
}

export const Tile = styled<TileProps, 'a'>('a')`
  position: relative;
  text-decoration: none;
  display: flex;
  flex-direction: column;
  justify-content: center;
  align-items: center;
  width: 78px;
  height: 110px;
  cursor: pointer;
  // Menu goes behind in other Tiles when tils has z-index.
  // Give z-index while dragging to make dragging tile moves over other tiles.
  z-index: ${p => p.isDragging ? 3 : 'unset' }
  outline: unset;

  &:focus-visible, :active {
    ${TileFavicon} {
      width: 78px;
      height: 78px;
      background-clip: padding-box;
      border: 4px solid rgba(255, 255, 255, 0.6) ;
    }
  }

  ${p => !p.isDragging && !p.isMenuShowing && css`
    &:hover {
      ${TileActionsContainer} {
        opacity: 1;
        visibility: visible;
      }
    }
  `}

  ${p => p.isMenuShowing && css`
    ${TileActionsContainer} {
      opacity: 1;
      visibility: visible;
    }
  `}
`
