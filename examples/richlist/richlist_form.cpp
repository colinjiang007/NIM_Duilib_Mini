#include "stdafx.h"
#include "richlist_form.h"
#include "item.h"

const CUiString RichlistForm::kClassName = _T("Basic");

RichlistForm::RichlistForm()
{
}


RichlistForm::~RichlistForm()
{
}

CUiString RichlistForm::GetSkinFolder()
{
	return _T("richlist");
}

CUiString RichlistForm::GetSkinFile()
{
	return _T("richlist.xml");
}

CUiString RichlistForm::GetWindowClassName() const
{
	return kClassName;
}

void RichlistForm::InitWindow()
{
	list_ = dynamic_cast<ui::ListBox*>(FindControl(_T("list")));

	for (auto i = 0; i < 100; i++)
	{
		Item* item = new Item;
		ui::GlobalManager::FillBoxWithCache(item, _T("richlist/item.xml"));

		CUiString img = _T("icon.png");
		CUiString title;
		title.Format(_T("�������� [%02d]"), i + 1);

		item->InitSubControls(img, title);
		list_->Add(item);
	}

	// �����б��е��ѡ��������¼�
	list_->AttachSelect(ui::Bind(&RichlistForm::OnSelected, this, std::placeholders::_1));
}


bool RichlistForm::OnSelected(ui::EventArgs* args)
{
	int current = args->wParam;
	int old = args->lParam;


	CUiString message;
	message.Format(_T("��ѡ��������Ϊ %d �������һ��ѡ����������Ϊ %d"), current, old);
	MessageBox(GetHWND(), message, _T("��ʾ"), MB_OK);

	return true;
}

LRESULT RichlistForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}