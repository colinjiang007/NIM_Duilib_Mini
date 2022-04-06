#include "stdafx.h"
#include "toast.h"

using namespace ui;

namespace uic {

const LPCTSTR Toast::kClassName = _T("Toast");

Toast::Toast()
	:duration_(1000)
	, content_(nullptr)
	, close_button_(nullptr)
{
	duration_bgn_time_ = GetTickCount();
}

void Toast::ShowToast(const CUiString &content, int duration, HWND parent)
{
	Toast *toast = new Toast;
	HWND hWnd = toast->Create(parent, _T(""), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	if (hWnd == NULL)
		return;

	toast->SetContent(content);
	toast->SetDuration(duration);
	toast->CenterWindow();
	toast->ShowWindow(true);
}

CUiString Toast::GetSkinFolder()
{
	return _T("toast");
}

CUiString Toast::GetSkinFile()
{
	return _T("toast.xml");
}

CUiString Toast::GetWindowClassName() const
{
	return kClassName;
}

CUiString Toast::GetWindowId() const
{
	return kClassName;
}

UINT Toast::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

LRESULT Toast::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	if (uMsg == WM_KEYDOWN && wParam == VK_ESCAPE)
	{
		this->Close();
	}
	else if (uMsg == WM_TIMER) {
		if (wParam == UIC_DURATION_TIMER) {
			if (GetTickCount() >= duration_ + duration_bgn_time_) {
				this->Close();
			}
		}
	}
	// 整个toast界面都在标题栏，所以要处理WM_NC消息
	else if (uMsg == WM_NCLBUTTONDBLCLK || uMsg == WM_LBUTTONDBLCLK)
	{
		this->Close();
	}
	// duilib在WM_MOUSELEAVE消息中会发送一个lparam为-1的WM_MOUSEMOVE消息
	else if ((uMsg == WM_NCMOUSEMOVE || uMsg == WM_MOUSEMOVE) && lParam != -1)
	{
		if (NULL != close_button_ && !close_button_->IsVisible())
			close_button_->SetVisible(true);
	}
	else if (uMsg == WM_NCMOUSELEAVE || uMsg == WM_MOUSELEAVE)
	{
		POINT pt;
		GetCursorPos(&pt);
		ScreenToClient(m_hWnd, &pt);
		CUiRect client_rect;
		::GetClientRect(m_hWnd, &client_rect);
		// leave消息触发时，获取的鼠标坐标有可能还在client_rect范围内，会偏差1像素，这里缩减1像素
		client_rect.Deflate(CUiRect(1, 1, 1, 1));
		if (NULL != close_button_ && !client_rect.IsPointIn(pt))
			close_button_->SetVisible(false);
	}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void Toast::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&Toast::OnClicked, this, std::placeholders::_1));

	content_ = static_cast<RichEdit*>(FindControl(_T("content")));
	close_button_ = static_cast<Button*>(FindControl(_T("close_btn")));

	::SetTimer(GetHWND(), UIC_DURATION_TIMER, 500, NULL);

}

void Toast::SetDuration(int duration)
{
	if (duration <= 0)
		return;

	duration_ = duration;
	duration_bgn_time_ = GetTickCount();
}

bool Toast::OnClicked(ui::EventArgs* msg)
{
	CUiString name = msg->pSender->GetName();
	if (name == _T("close_btn"))
	{
		this->Close();
	}

	return true;
}

void Toast::SetContent(const CUiString &str)
{
	content_->SetText(str);

	int width = content_->GetFixedWidth();

	ui::CUiSize sz = content_->GetNaturalSize(width, 0);
	content_->SetFixedHeight(sz.cy);
}

LRESULT Toast::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(m_hWnd, UIC_DURATION_TIMER);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

}