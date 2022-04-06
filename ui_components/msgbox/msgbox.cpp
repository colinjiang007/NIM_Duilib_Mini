#include "stdafx.h"
#include "msgbox.h"

namespace uic {

using namespace ui;

void ShowMsgBox(HWND hwnd,
	const CUiString &content, bool content_is_id,
	const CUiString &title, bool title_is_id,
	const CUiString &yes, bool btn_yes_is_id,
	const CUiString &no, bool btn_no_is_id)
{
	MsgBox* msgbox = new MsgBox;
	HWND hWnd = msgbox->Create(hwnd, _T(""), WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	if (hWnd == NULL)
		return;
	MutiLanSupport *multilan = MutiLanSupport::GetInstance();
	msgbox->SetTitle(title_is_id ? multilan->GetStringViaID(title) : title);
	msgbox->SetContent(content_is_id ? multilan->GetStringViaID(content) : content);
	msgbox->SetButton(btn_yes_is_id ? multilan->GetStringViaID(yes) : yes, btn_no_is_id ? multilan->GetStringViaID(no) : no);
	msgbox->Show(hwnd);
}

const LPCTSTR MsgBox::kClassName = _T("MsgBox");

MsgBox::MsgBox()
{
}

MsgBox::~MsgBox()
{
}

CUiString MsgBox::GetSkinFolder()
{
	return _T("msgbox");
}

CUiString MsgBox::GetSkinFile()
{
	return _T("msgbox.xml");
}

CUiString MsgBox::GetZIPFileName() const
{
	return _T("msgbox.zip");
}

CUiString MsgBox::GetWindowClassName() const
{
	return kClassName;
}

CUiString MsgBox::GetWindowId() const
{
	return kClassName;
}

UINT MsgBox::GetClassStyle() const
{
	return (UI_CLASSSTYLE_FRAME | CS_DBLCLKS);
}

LRESULT MsgBox::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//if(uMsg == WM_DESTROY)
	//{
	//	HWND hWndParent = GetWindowOwner(m_hWnd);
	//	if(hWndParent)
	//	{
	//		::EnableWindow(hWndParent, TRUE);
	//		::SetForegroundWindow(hWndParent);
	//		::SetFocus(hWndParent);
	//	}
	//}
	return __super::HandleMessage(uMsg, wParam, lParam);
}

void MsgBox::OnEsc(BOOL &bHandled)
{
	bHandled = TRUE;
	EndMsgBox(MB_NO);
}
void MsgBox::Close(UINT nRet)
{
	// 提示框关闭之前先Enable父窗口，防止父窗口隐到后面去。
	HWND hWndParent = GetWindowOwner(m_hWnd);
	if (hWndParent)
	{
		::EnableWindow(hWndParent, TRUE);
		::SetFocus(hWndParent);
	}

	__super::Close(nRet);
}

void MsgBox::InitWindow()
{
	m_pRoot->AttachBubbledEvent(ui::kEventClick, nbase::Bind(&MsgBox::OnClicked, this, std::placeholders::_1));

	title_ = (Label*)FindControl(_T("title"));
	content_ = (RichEdit*)FindControl(_T("content"));
	btn_yes_ = (Button*)FindControl(_T("btn_yes"));
	btn_no_ = (Button*)FindControl(_T("btn_no"));
}

bool MsgBox::OnClicked(ui::EventArgs* msg)
{
	CUiString name = msg->pSender->GetName();
	if (name == _T("btn_yes"))
	{
		EndMsgBox(MB_YES);
	}
	else if (name == _T("btn_no"))
	{
		EndMsgBox(MB_NO);
	}
	else if (name == _T("closebtn"))
	{
		EndMsgBox(MB_NO);
	}
	return true;
}

void MsgBox::SetTitle(const CUiString &str)
{
	title_->SetText(str);
}

void MsgBox::SetContent(const CUiString &str)
{
	content_->SetText(str);

	int width = content_->GetFixedWidth();

	ui::CUiSize sz = content_->GetNaturalSize(width, 0);
	content_->SetFixedHeight(sz.cy, false);
}

void MsgBox::SetButton(const CUiString &yes, const CUiString &no)
{
	if (!yes.IsEmpty())
	{
		btn_yes_->SetText(yes);
		btn_yes_->SetVisible(true);
		btn_yes_->SetFocus();
	}
	else
	{
		btn_yes_->SetVisible(false);
	}

	if (!no.IsEmpty())
	{
		btn_no_->SetText(no);
		btn_no_->SetVisible(true);
		if (yes.IsEmpty())
			btn_no_->SetFocus();
	}
	else
	{
		btn_no_->SetVisible(false);
	}
}

void MsgBox::Show(HWND hwnd)
{
	::EnableWindow(hwnd, FALSE);
	CenterWindow();
	ShowWindow(true);
}

void MsgBox::EndMsgBox(MsgBoxRet ret)
{
	this->Close(0);
}

}
