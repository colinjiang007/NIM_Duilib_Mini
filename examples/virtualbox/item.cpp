#include "stdafx.h"
#include "item.h"
#include "VirtualTileBox.h"
#include "provider.h"

Item::Item()
:control_img_(nullptr)
{
}


Item::~Item()
= default;

void Item::InitSubControls(const CUiString& img, const CUiString& title, int nDataIndex)
{
	// 查找 Item 下的控件
	if (control_img_ == nullptr)
	{
		control_img_ = dynamic_cast<ui::Control*>(FindSubControl(_T("control_img")));
		label_title_ = dynamic_cast<ui::Label*>(FindSubControl(_T("label_title")));
		progress_ = dynamic_cast<ui::Progress*>(FindSubControl(_T("progress")));
		btn_del_ = dynamic_cast<ui::Button*>(FindSubControl(_T("btn_del")));
		// 模拟进度条进度
		progress_->SetValue((double)(GetTickCount() % 100));
		// 设置图标和任务名称
		control_img_->SetBkImage(img);
		// 绑定删除任务处理函数
		btn_del_->AttachClick(ui::Bind(&Item::OnRemove, this, std::placeholders::_1));
	}

	CUiString showText;
	showText.Format(_T("%s %d%%"), title.GetData(), GetTickCount() % 100);
	label_title_->SetText(showText);
	m_nDataIndex = nDataIndex;

}


bool Item::OnRemove(ui::EventArgs* args)
{
	// 删除时，只需删除数据就可以了，不要删除界面上的元素
	VirtualTileBox* pTileBox = dynamic_cast<VirtualTileBox*>(m_pOwner);
	Provider* pProvider = dynamic_cast<Provider*>(pTileBox->GetDataProvider());
	pProvider->RemoveTask(m_nDataIndex);
	return true;
}
