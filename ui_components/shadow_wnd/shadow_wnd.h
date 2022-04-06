#ifndef __SHADOW_WND_H__
#define __SHADOW_WND_H__

#pragma once

#include "windows_manager/window_ex.h"

namespace uic {

using namespace ui;

/** @class ShadowWnd
 * @brief һ�����ӵ�����������Χ�Ĵ��ڣ����� WS_EX_LAYERED ������ʵ����Ӱ
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @date 2019-03-22
 */
class ShadowWnd : public WindowImplBase
{
public:
	ShadowWnd();

	virtual CUiString GetSkinFolder() override;
	virtual CUiString GetSkinFile() override;
	virtual CUiString GetWindowClassName() const override;
	virtual LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled) override;
	
	virtual HWND Create(Window* window);
private:
	Window*	window_ = nullptr;
};

/** @class ShadowWnd
 * @brief ʹ�ø�����Ӱ���ڵĻ��࣬ʵ���˴������ڲ����ӵĹ��ܣ��ṩû�� WS_EX_LAYERED ���ԵĴ��ڼ̳�
 * @copyright (c) 2016, NetEase Inc. All rights reserved
 * @date 2019-03-22
 */
class ShadowWndBase : public WindowImplBase
{
public:
	ShadowWndBase();

	virtual HWND Create(HWND hwndParent, LPCTSTR pstrName, DWORD dwStyle, DWORD dwExStyle, 
		bool isLayeredWindow = false, const ui::CUiRect& rc = ui::CUiRect(0, 0, 0, 0)) override;

private:
	ShadowWnd* shadow_wnd_;
};
} // namespace uic

#endif // __SHADOW_WND_H__
