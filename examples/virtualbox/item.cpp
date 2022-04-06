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
	// ���� Item �µĿؼ�
	if (control_img_ == nullptr)
	{
		control_img_ = dynamic_cast<ui::Control*>(FindSubControl(_T("control_img")));
		label_title_ = dynamic_cast<ui::Label*>(FindSubControl(_T("label_title")));
		progress_ = dynamic_cast<ui::Progress*>(FindSubControl(_T("progress")));
		btn_del_ = dynamic_cast<ui::Button*>(FindSubControl(_T("btn_del")));
		// ģ�����������
		progress_->SetValue((double)(GetTickCount() % 100));
		// ����ͼ�����������
		control_img_->SetBkImage(img);
		// ��ɾ����������
		btn_del_->AttachClick(ui::Bind(&Item::OnRemove, this, std::placeholders::_1));
	}

	CUiString showText;
	showText.Format(_T("%s %d%%"), title.GetData(), GetTickCount() % 100);
	label_title_->SetText(showText);
	m_nDataIndex = nDataIndex;

}


bool Item::OnRemove(ui::EventArgs* args)
{
	// ɾ��ʱ��ֻ��ɾ�����ݾͿ����ˣ���Ҫɾ�������ϵ�Ԫ��
	VirtualTileBox* pTileBox = dynamic_cast<VirtualTileBox*>(m_pOwner);
	Provider* pProvider = dynamic_cast<Provider*>(pTileBox->GetDataProvider());
	pProvider->RemoveTask(m_nDataIndex);
	return true;
}
