#include "stdafx.h"
#include "layouts_form.h"

LayoutsForm::LayoutsForm(const CUiString& class_name, const CUiString& theme_directory, const CUiString& layout_xml)
	: class_name_(class_name)
	, theme_directory_(theme_directory)
	, layout_xml_(layout_xml)
{
}


LayoutsForm::~LayoutsForm()
{
}

CUiString LayoutsForm::GetSkinFolder()
{
	return theme_directory_;
}

CUiString LayoutsForm::GetSkinFile()
{
	return layout_xml_;
}

CUiString LayoutsForm::GetWindowClassName() const
{
	return class_name_;
}

void LayoutsForm::InitWindow()
{

}

LRESULT LayoutsForm::OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	PostQuitMessage(0L);
	return __super::OnClose(uMsg, wParam, lParam, bHandled);
}

void LayoutsForm::ShowCustomWindow(const CUiString& class_name, const CUiString& theme_directory, const CUiString& layout_xml)
{
	LayoutsForm* window = new LayoutsForm(class_name, theme_directory, layout_xml);
	window->Create(NULL, class_name, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowModal();
}
