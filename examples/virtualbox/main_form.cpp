#include "stdafx.h"
#include "main_form.h"
#include "provider.h"

const CUiString MainForm::kClassName = _T("VirtualBoxDemo");


MainForm::MainForm()
= default;


MainForm::~MainForm()
= default;

CUiString MainForm::GetSkinFolder()
{
	return _T("virtualbox");
}

CUiString MainForm::GetSkinFile()
{
	return _T("main.xml");
}

CUiString MainForm::GetWindowClassName() const
{
	return kClassName;
}

void MainForm::InitWindow()
{

	m_EditColumn = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_column")));
	m_CheckBoxItemCenter = dynamic_cast<ui::CheckBox*>(FindControl(_T("checkbox_item_center")));
	m_EditTotal = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_total")));
	m_pTileList = dynamic_cast<VirtualTileBox*>(FindControl(_T("list")));
	m_OptionColumnFix = dynamic_cast<ui::Option*>(FindControl(_T("option_column_fix")));
	m_EditUpdate = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_update")));
	m_EditTaskName = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_task_name")));
	m_EditDelete = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_delete")));
	m_EditChildMargin = dynamic_cast<ui::RichEdit*>(FindControl(_T("edit_child_margin")));

	m_pRoot->AttachBubbledEvent(ui::kEventClick, ui::Bind(&MainForm::OnClicked, this, std::placeholders::_1));

	// 设置提供者
	m_DataProvider = new Provider;
	m_pTileList->SetDataProvider(m_DataProvider);



}

LRESULT MainForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}


bool MainForm::OnClicked(ui::EventArgs* args)
{
	auto sName = args->pSender->GetName();
	if (sName == _T("btn_set_total"))
	{
		if (!m_EditChildMargin->GetText().IsEmpty())
		{
			m_pTileList->SetAttribute(_T("childmargin"), m_EditChildMargin->GetText());
		}
		if (m_OptionColumnFix->IsSelected())
		{
			m_pTileList->SetAttribute(_T("column"), m_EditColumn->GetText());
			if (m_CheckBoxItemCenter->IsSelected())
			{
				m_pTileList->SetAttribute(_T("width"), _T("auto"));
				m_pTileList->SetAttribute(_T("halign"), _T("center"));
			}
			else {
				m_pTileList->SetAttribute(_T("width"), _T("stretch"));

			}		
		}
		else {
			m_pTileList->SetAttribute(_T("width"), _T("stretch"));
			m_pTileList->SetAttribute(_T("column"), _T("-1"));

		}


		int nTotal = _ttoi(m_EditTotal->GetText());
		if (nTotal > 0) {
			m_DataProvider->SetTotal(nTotal);
		}
	}
	else if (sName == _T("btn_update"))
	{
		m_DataProvider->ChangeTaskName(_ttoi(m_EditUpdate->GetText())-1, 
			m_EditTaskName->GetText());
	}
	else if (sName == _T("btn_delete"))
	{
		m_DataProvider->RemoveTask(_ttoi(m_EditDelete->GetText()) - 1); 
	}

	return true;
}
