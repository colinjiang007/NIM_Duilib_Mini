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
	// ���� Item �µĿؼ�
	control_img_	= dynamic_cast<ui::Control*>(FindSubControl(_T("control_img")));
	label_title_	= dynamic_cast<ui::Label*>(FindSubControl(_T("label_title")));
	progress_		= dynamic_cast<ui::Progress*>(FindSubControl(_T("progress")));
	btn_del_		= dynamic_cast<ui::Button*>(FindSubControl(_T("btn_del")));

	// ģ�����������
	progress_->SetValue((double)(GetTickCount() % 100));

	// ����ͼ�����������
	control_img_->SetBkImage(img);
	CUiString showText;
	int dd = GetTickCount() % 100U;
	showText.Format(_T("%s %d%%"), title.GetData(), dd);
	label_title_->SetText(showText);

	// ��ɾ����������
	btn_del_->AttachClick(ui::Bind(&Item::OnRemove, this, std::placeholders::_1));
}

bool Item::OnRemove(ui::EventArgs* args)
{
	ui::ListBox* parent = dynamic_cast<ui::ListBox*>(this->GetParent());
	return parent->Remove(this);
}
