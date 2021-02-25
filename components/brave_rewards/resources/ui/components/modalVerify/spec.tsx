/* global jest, expect, describe, it, afterEach */
import * as React from 'react'
import { shallow } from 'enzyme'
import { create } from 'react-test-renderer'
import PanelVerify from './index'
import { TestThemeProvider } from 'brave-ui/theme'

describe('PanelVerify tests', () => {
  const baseComponent = (props?: object) => <TestThemeProvider><PanelVerify id='panel-verify' {...props} /></TestThemeProvider>

  describe('basic tests', () => {
    it('matches the snapshot', () => {
      const component = baseComponent()
      const tree = create(component).toJSON()
      expect(tree).toMatchSnapshot()
    })

    it('renders the component', () => {
      const wrapper = shallow(baseComponent())
      const assertion = wrapper.find('#panel-verify').length
      expect(assertion).toBe(1)
    })
  })
})
