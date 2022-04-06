#pragma once
using ui::CUiString;

class LayoutsForm : public ui::WindowImplBase
{
public:
	LayoutsForm(const CUiString& class_name, const CUiString& theme_directory, const CUiString& layout_xml);
	~LayoutsForm();

	/**
	 * һ�������ӿ��Ǳ���Ҫ��д�Ľӿڣ����������������ӿ�����������
	 * GetSkinFolder		�ӿ�������Ҫ���ƵĴ���Ƥ����Դ·��
	 * GetSkinFile			�ӿ�������Ҫ���ƵĴ��ڵ� xml �����ļ�
	 * GetWindowClassName	�ӿ����ô���Ψһ��������
	 */
	virtual CUiString GetSkinFolder() override;
	virtual CUiString GetSkinFile() override;
	virtual CUiString GetWindowClassName() const override;

	/**
	 * �յ� WM_CREATE ��Ϣʱ�ú����ᱻ���ã�ͨ����һЩ�ؼ���ʼ���Ĳ���
	 */
	virtual void InitWindow() override;

	/**
	 * �յ� WM_CLOSE ��Ϣʱ�ú����ᱻ����
	 */
	virtual LRESULT OnClose(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);


public:
	static void ShowCustomWindow(const CUiString& class_name, const CUiString& theme_directory, const CUiString& layout_xml);

private:
	CUiString class_name_;
	CUiString theme_directory_;
	CUiString layout_xml_;
};

