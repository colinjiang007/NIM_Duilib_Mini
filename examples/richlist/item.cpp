#include "stdafx.h"
#include "item.h"


Item::Item()
{
}


Item::~Item()
{
}

void Item::InitSubControls(const CUiString& img, const CUiString& title)
{
	// 查找 Item 下的控件
	control_img_	= dynamic_cast<ui::Control*>(FindSubControl(_T("control_img")));
	label_title_	= dynamic_cast<ui::Label*>(FindSubControl(_T("label_title")));
	progress_		= dynamic_cast<ui::Progress*>(FindSubControl(_T("progress")));
	btn_del_		= dynamic_cast<ui::Button*>(FindSubControl(_T("btn_del")));

	// 模拟进度条进度
	progress_->SetValue((double)(GetTickCount() % 100));

	// 设置图标和任务名称
	control_img_->SetBkImage(img);
	CUiString showText;
	int dd = GetTickCount() % 100U;
	showText.Format(_T("%s %d%%"), title.GetData(), dd);
	label_title_->SetText(showText);

	// 绑定删除任务处理函数
	btn_del_->AttachClick(ui::Bind(&Item::OnRemove, this, std::placeholders::_1));
}

bool Item::OnRemove(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent->Remove(this);
}
