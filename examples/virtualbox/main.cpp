// VirtualBox.cpp : 定义应用程序的入口点。
//

#include "stdafx.h"
#include "main.h"
#include "main_form.h"
#include "VirtualTileBox.h"


ui::Control* MyCreateControlCallback(const ui::CUiString& sName)
{
	if (sName == _T("VirtualTileBox"))
	{
		return new VirtualTileBox();
	}
	return nullptr;
}

int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
	_In_opt_ HINSTANCE hPrevInstance,
	_In_ LPWSTR    lpCmdLine,
	_In_ int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);


	// 获取资源路径，初始化全局参数
	ui::CUiString theme_dir = ui::PathUtil::GetCurrentModuleDir();
	ui::GlobalManager::Startup(theme_dir + _T("resources\\"), MyCreateControlCallback, false);

	// 创建一个默认带有阴影的居中窗口
	MainForm* window = new MainForm();
	window->Create(NULL, MainForm::kClassName, WS_OVERLAPPEDWINDOW & ~WS_MAXIMIZEBOX, 0);
	window->CenterWindow();
	window->ShowModal();
	ui::GlobalManager::Shutdown();

	return 0;
}




