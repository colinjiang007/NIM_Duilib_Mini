#include "stdafx.h"
#include "controls_form.h"

#include <fstream>

const CUiString ControlForm::kClassName = _T("Controls");

ControlForm::ControlForm()
{
}


ControlForm::~ControlForm()
{
}

CUiString ControlForm::GetSkinFolder()
{
	return _T("controls");
}

CUiString ControlForm::GetSkinFile()
{
	return _T("controls.xml");
}

CUiString ControlForm::GetWindowClassName() const
{
	return kClassName;
}

void ControlForm::InitWindow()
{
	/**
	 * 为了让代码看起来相对容易理解，不需要频繁跟进才能看明白示例代码
	 * 我们将一些控件储存为局部变量，正确的使用应该是将他们作为成员变量
	 * 不要在每次使用的时候都需要 FindControl，否则会影响性能代码不易读
	 */

	/* Initialize ListBox data */
	ui::ListBox* list = dynamic_cast<ui::ListBox*>(FindControl(_T("list")));
	CUiString fmtStr;
	for (auto i = 0; i < 30; i++)
	{
		ui::ListContainerElement* element = new ui::ListContainerElement;
		fmtStr.Format(_T("ListElement %d"), i);
		element->SetText(fmtStr);
		element->SetClass(_T("listitem"));
		element->SetFixedHeight(20);
		list->Add(element);
	}

	/* Initialize TreeView data */
	ui::TreeView* tree = dynamic_cast<ui::TreeView*>(FindControl(_T("tree")));
	ui::TreeNode* parent_node = nullptr;
	for (auto j = 0; j < 8; j++)
	{
		ui::TreeNode* node = new ui::TreeNode;
		node->SetClass(_T("listitem"));
		node->SetFixedHeight(20);
		if (parent_node)
		{
			fmtStr.Format(_T("Child node %d"), j);

			node->SetText(fmtStr);
			node->SetMargin({ 10, 0, 0, 0 });
			parent_node->AddChildNode(node);
		}
		else
		{
			fmtStr.Format(_T("Parent node"), j);
			node->SetText(fmtStr);
			tree->GetRootNode()->AddChildNode(node);
			parent_node = node;
		}
	}

	/* Initialize ComboBox data */
	ui::Combo* combo = dynamic_cast<ui::Combo*>(FindControl(_T("combo")));
	for (auto i = 0; i < 10; i++)
	{
		ui::ListContainerElement* element = new ui::ListContainerElement;
		element->SetClass(_T("listitem"));
		element->SetFixedHeight(30);
		element->SetBkColor(_T("white"));
		element->SetTextPadding({ 6,0,6,0 });
		fmtStr.Format(_T("Combo element %d"), i);
		element->SetText(fmtStr);
		combo->Add(element);
	}

	/* Load xml file content in global misc thread, and post update RichEdit task to UI thread */
	CUiString xml;
	CUiString controls_xml_path = ui::GlobalManager::GetResourcePath() + GetWindowResourcePath() + GetSkinFile();
	std::string utf8Xml = ReadFile2String(controls_xml_path);
	ui::StringHelper::Utf8ToCUiString(utf8Xml, xml);
	auto control_edit = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit")));
	control_edit->SetText(xml);
	control_edit->SetFocus();
	control_edit->HomeUp();

	/* Post repeat task to update progress value 900 milliseconds once */
	::SetTimer(GetHWND(), WM_ID_INTERVAL_TIMER, 900, NULL);

	/* Show settings menu */
	ui::Button* settings = dynamic_cast<ui::Button*>(FindControl(_T("settings")));
	settings->AttachClick([this](ui::EventArgs* args) {
		RECT rect = args->pSender->GetPos();
		ui::CUiPoint point;
		point.x = rect.left - 175;
		point.y = rect.top + 10;
		ClientToScreen(m_hWnd, &point);

		//todo
		//uic::CMenuWnd* pMenu = new nim_comp::CMenuWnd(NULL);
		//ui::STRINGorID xml(_T("settings_menu.xml"));
		//pMenu->Init(xml, _T("xml"), point);
		return true;
	});
}

LRESULT ControlForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	KillTimer(m_hWnd, WM_ID_INTERVAL_TIMER);
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void ControlForm::OnLoadedResourceFile(const CUiString& xml)
{
	
}

void ControlForm::OnProgressValueChagned(float value)
{
	auto progress = dynamic_cast<ui::Progress*>(FindControl(_T("progress")));
	progress->SetValue(value);
	auto circleprogress = dynamic_cast<ui::Progress*>(FindControl(_T("circleprogress")));
	circleprogress->SetValue(value);
	CUiString szBuffer;
	szBuffer.Format(_T("%.0f%%"), value);
	circleprogress->SetText(szBuffer);
}

std::string ControlForm::ReadFile2String(LPCTSTR sz_path)
{
	if (nullptr == sz_path) {
		return "";
	}
	HANDLE hFile = CreateFile(sz_path, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	if (hFile == INVALID_HANDLE_VALUE){
		return "";
	}
	int file_size = 0;
	file_size = GetFileSize(hFile, NULL);
	std::string file_str;
	file_str.resize(file_size);
	DWORD dwRead;
	if (!ReadFile(hFile, (void*)file_str.data(), file_size, &dwRead, NULL)){
		CloseHandle(hFile);
		return "";
	}
	CloseHandle(hFile);
	return std::move(file_str);
}

LRESULT ControlForm::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	switch (uMsg)
	{
	case WM_TIMER: {
		if (wParam == WM_ID_INTERVAL_TIMER) {
			OnProgressValueChagned((float)(GetTickCount()%100));
			break;
		}
		return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
	}
	default:
		{
			return WindowImplBase::HandleMessage(uMsg, wParam, lParam);
		}
	}
	return lRes;
}

