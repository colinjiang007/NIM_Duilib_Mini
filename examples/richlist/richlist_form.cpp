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
		title.Format(_T("下载任务 [%02d]"), i + 1);

		item->InitSubControls(img, title);
		list_->Add(item);
	}

	// 监听列表中点击选择子项的事件
	list_->AttachSelect(ui::Bind(&RichlistForm::OnSelected, this, std::placeholders::_1));
}


bool RichlistForm::OnSelected(ui::EventArgs* args)
{
	int current = args->wParam;
	int old = args->lParam;


	CUiString message;
	message.Format(_T("您选择了索引为 %d 的子项，上一次选择子项索引为 %d"), current, old);
	MessageBox(GetHWND(), message, _T("提示"), MB_OK);

	return true;
}

LRESULT RichlistForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}