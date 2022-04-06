#pragma once
#include "duilib/UIlib.h"

namespace uic {
	using ui::CUiString;
enum MsgBoxRet
{
	MB_YES,
	MB_NO
};

typedef std::function<void(MsgBoxRet)> MsgboxCallback;

void ShowMsgBox(HWND hwnd, MsgboxCallback cb,
    const CUiString &content = _T(""), bool content_is_id = true,
    const CUiString &title = _T("STRING_TIPS"), bool title_is_id = true,
    const CUiString &yes = _T("STRING_OK"), bool btn_yes_is_id = true,
    const CUiString &no = _T(""), bool btn_no_is_id = false);

class MsgBox : public ui::WindowImplBase
{
public:
	friend void ShowMsgBox(HWND hwnd,
        const CUiString &content, bool content_is_id,
        const CUiString &title, bool title_is_id,
        const CUiString &yes, bool btn_yes_is_id,
        const CUiString &no, bool btn_no_is_id);
public:
	MsgBox();
	virtual ~MsgBox();

	virtual CUiString GetSkinFolder() override;
	virtual CUiString GetSkinFile() override;
	virtual CUiString GetZIPFileName() const;
	virtual LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam) override;
	virtual void OnEsc(BOOL &bHandled);
	virtual void Close(UINT nRet = IDOK) override;

	virtual CUiString GetWindowClassName() const override;
	virtual CUiString GetWindowId() const /*override*/;
	virtual UINT GetClassStyle() const override;
	virtual void InitWindow() override;
private:
	bool OnClicked(ui::EventArgs* msg);

	void SetTitle(const CUiString &str);
	void SetContent(const CUiString &str);
	void SetButton(const CUiString &yes, const CUiString &no);
	void Show(HWND hwnd);

	void EndMsgBox(MsgBoxRet ret);
public:
	static const LPCTSTR kClassName;
private:
	ui::Label*		title_;
	ui::RichEdit*	content_;
	ui::Button*		btn_yes_;
	ui::Button*		btn_no_;

};

}
