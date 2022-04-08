#ifndef UI_CONTROL_ACTIVEX_H__
#define UI_CONTROL_ACTIVEX_H__

#pragma once

struct IOleObject;


namespace ui {
/////////////////////////////////////////////////////////////////////////////////////
//

class ActiveXCtrl;

template< class T >
class CSafeRelease
{
public:
    CSafeRelease(T* p) : m_p(p) { };
    ~CSafeRelease() { if( m_p != NULL ) m_p->Release(); };
    T* Detach() { T* t = m_p; m_p = NULL; return t; };
    T* m_p;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API ActiveXUI :public Control
{
    friend class ActiveXCtrl;
public:
    ActiveXUI();
    virtual ~ActiveXUI();

    LPCTSTR GetClass() const;
	LPVOID GetInterface(LPCTSTR pstrName);
	UINT GetControlFlags() const;
	HWND GetNativeWindow() const;

    bool IsDelayCreate() const;
    void SetDelayCreate(bool bDelayCreate = true);

    bool CreateControl(const CLSID clsid);
    bool CreateControl(LPCTSTR pstrCLSID);
    HRESULT GetControl(const IID iid, LPVOID* ppRet);
	CLSID GetClisd() const;
    CUiString GetModuleName() const;
    void SetModuleName(LPCTSTR pstrText);

    void SetVisible(bool bVisible = true);
    void SetInternVisible(bool bVisible = true);
	void SetPos(RECT rc, bool bNeedInvalidate = true);
	void Move(SIZE szOffset, bool bNeedInvalidate = true);
    bool DoPaint(HDC hDC, const RECT& rcPaint, Box* pStopControl);

    void SetAttribute(LPCTSTR pstrName, LPCTSTR pstrValue);

    LRESULT MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled);

protected:
    virtual void ReleaseControl();
    virtual bool DoCreateControl();

protected:
    CLSID m_clsid;
    CUiString m_sModuleName;
    bool m_bCreated;
    bool m_bDelayCreate;
    IOleObject* m_pUnk;
    ActiveXCtrl* m_pControl;
    HWND m_hwndHost;
};

} // namespace ui

#endif // UI_CONTROL_ACTIVEX_H__
