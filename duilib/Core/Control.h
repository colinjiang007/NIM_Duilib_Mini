#ifndef UI_CORE_CONTROL_H_
#define UI_CORE_CONTROL_H_

#pragma once

namespace ui 
{

typedef Control* (CALLBACK* FINDCONTROLPROC)(Control*, LPVOID);

class UILIB_API UserDataBase
{
public:
	virtual ~UserDataBase()
	{

	}
};

class UILIB_API Control : public PlaceHolder
{
	typedef std::map<int, CEventSource> GifEventMap;
public:
	Control();
	Control(const Control& r);
	Control& operator=(const Control& r) = delete;
    virtual ~Control();

    /// ͼ�����
	/**
	 * @brief ��ȡ������ɫ
	 * @return ���ر�����ɫ���ַ�������ֵ�� global.xml �ж���
	 */
	CUiString GetBkColor() const;

	/**
	 * @brief ���ñ�����ɫ
	 * @param[in] strColor Ҫ���õı�����ɫֵ����ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetBkColor(LPCTSTR strColor);

	/**
	 * @brief ��ȡĳ��״̬�µ�������ɫ
	 * @param[in] stateType Ҫ��ȡ����״̬�µ���ɫֵ���ο� ControlStateType ö��
	 * @return ָ��״̬���趨����ɫ�ַ�������Ӧ global.xml ��ָ��ɫֵ
	 */
	CUiString GetStateColor(ControlStateType stateType);

	/**
	 * @brief ����ĳ��״̬�µ�������ɫ
	 * @param[in] stateType Ҫ���ú���״̬�µ���ɫֵ���ο� ControlStateType ö��
	 * @param[in] strColor Ҫ���õ���ɫֵ����ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetStateColor(ControlStateType stateType, LPCTSTR strColor);

	/**
	 * @brief ��ȡ����ͼƬλ��
	 * @return ����ͼƬλ��  
	 */
    CUiString GetBkImage() const;


	/**
	 * @brief ���ñ���ͼƬ
	 * @param[in] strImage Ҫ���õ�ͼƬ·��
	 * @return ��
	 */
    void SetBkImage(LPCTSTR strImage);

	

	/**
	 * @brief ��ȡָ��״̬�µ�ͼƬλ��
	 * @param[in] Ҫ��ȡ����״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @return ָ��״̬�µ�ͼƬλ��
	 */
	CUiString GetStateImage(ControlStateType stateType);

	/**
	 * @brief ����ĳ��״̬�µ�ͼƬ
	 * @param[in] stateType Ҫ���ú���״̬�µ�ͼƬ���ο� ControlStateType ö��
	 * @param[in] strImage Ҫ���õ�ͼƬ·��
	 * @return ��
	 */
	void SetStateImage(ControlStateType stateType, LPCTSTR strImage);

	/**
	 * @brief ��ȡָ��״̬�µ�ǰ��ͼƬ
	 * @param[in] Ҫ��ȡ����״̬�µ�ͼƬ���ο� `ControlStateType` ö��
	 * @return ָ��״̬��ǰ��ͼƬλ��
	 */
	CUiString GetForeStateImage(ControlStateType stateType);

	/**
	 * @brief ����ĳ��״̬��ǰ��ͼƬ
	 * @param[in] stateType Ҫ���ú���״̬�µ�ͼƬ���ο� `ControlStateType` ö��
	 * @param[in] strImage Ҫ���õ�ǰ��ͼƬ·��
	 * @return ��
	 */
	void SetForeStateImage(ControlStateType stateType, LPCTSTR strImage);

	/**
	 * @brief ��ȡ�ؼ�״̬
	 * @return �ؼ���״̬����ο� `ControlStateType` ö��
	 */
	ControlStateType GetState() const;

	/**
	 * @brief ���ÿؼ�״̬
	 * @param[in] pStrState Ҫ���õĿؼ�״̬����ο� `ControlStateType` ö��
	 * @return ��
	 */
	void SetState(ControlStateType pStrState);

	/**
	 * @brief ��ȡ�ؼ�ͼƬָ��
	 * @return ����ͼƬ����ָ��
	 */
	virtual Image* GetEstimateImage();

	/// �߿����
	/**
	 * @brief ��ȡ�߿��С
	 * @return ���ر߿�Ĵ�С
	 */
	int GetBorderSize() const;

	/**
	 * @brief ���ñ߿��С
	 * @param[in] nSize Ҫ���õı߿��С
	 * @return ��
	 */
	void SetBorderSize(int nSize);

	/**
	 * @brief ��ȡ�߿���ɫ
	 * @return �߿����ɫ�ַ�������Ӧ global.xml �еľ�����ɫֵ
	 */
	CUiString GetBorderColor() const;

	/**
	 * @brief ���ñ߿���ɫ
	 * @param[in] strBorderColor ���ñ߿����ɫ�ַ���ֵ����ֵ������ global.xml �д���
	 * @return ��
	 */
	void SetBorderColor(LPCTSTR strBorderColor);

	/**
	 * @brief ���ñ߿�Ĵ�С
	 * @param[in] rc һ�� `UiRect` �ṹ�ı߿��С����
	 * @return ��
	 */
	void SetBorderSize(CUiRect rc);

	/**
	 * @brief ��ȡ���߿��С
	 * @return ���߿�Ĵ�С  
	 */
	int GetLeftBorderSize() const;

	/**
	 * @brief �������߿��С
	 * @param[in] nSize Ҫ���õ����߿��С
	 * @return ��
	 */
	void SetLeftBorderSize(int nSize);

	/**
	 * @brief ��ȡ�����߿��С
	 * @return �����߿��С
	 */
	int GetTopBorderSize() const;

	/**
	 * @brief ���ö����߿��С
	 * @param[in] nSize Ҫ���õ��Ϸ��߿��С
	 * @return ��
	 */
	void SetTopBorderSize(int nSize);

	/**
	 * @brief ��ȡ�Ҳ�߿��С
	 * @return �Ҳ�ı߿��С
	 */
	int GetRightBorderSize() const;

	/**
	 * @brief �����Ҳ�߿��С
	 * @param[in] nSize Ҫ���õ��Ҳ�߿��С
	 * @return ��
	 */
	void SetRightBorderSize(int nSize);

	/**
	 * @brief ��ȡ�·��߿��С
	 * @return �·��߿��С
	 */
	int GetBottomBorderSize() const;

	/**
	 * @brief �����·��߿��С
	 * @param[in] nSize Ҫ���õ��·��߿��С
	 * @return ��
	 */
	void SetBottomBorderSize(int nSize);

	/**
	 * @brief ��ȡ�߿��С
	 * @return �ĸ�����ı߿��С
	 */
	CUiSize GetBorderRound() const;

	/**
	 * @brief ���ñ߿��С
	 * @param[in] cxyRound һ�� CSize �ṹ��ʾ���ĸ�����߿�Ĵ�С
	 * @return ��
	 */
	void SetBorderRound(CUiSize cxyRound);

    /// ������
	/**
	 * @brief ��ȡ���ָ������
	 * @return ��ǰ�������
	 */
	virtual CursorType GetCursorType() const;

	/**
	 * @brief ���õ�ǰ���ָ������
	 * @param[in] flag Ҫ���õ�������ͣ��ο� CursorType ö��
	 * @return ��
	 */
	void SetCursorType(CursorType flag);

	/**
	 * @brief ��ȡ�ؼ����������״̬�µ���ʾ�ı�
	 * @return ���ص�ǰ�������״̬��ʾ���ı�
	 */
    virtual CUiString GetToolTipText() const;



	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı�
	 * @param[in] strText Ҫ���õ��ı�
	 * @return ��
	 */
	virtual void SetToolTipText(LPCTSTR strText);

	
	/**
	 * @brief ��������������ؼ���ʾ����ʾ�ı��������ļ��ж�Ӧ������
	 * @param[in] strTextId �������ļ��ж�Ӧ����ʾ���� ID
	 * @return ��
	 */
	virtual void SetToolTipTextId(LPCTSTR strTextId);

	/**
	 * @brief ��������������ؼ�����ʾ���ı����������
	 * @param[in] nWidth Ҫ���õĿ��ֵ
	 * @return ��
	 */
	virtual void SetToolTipWidth(int nWidth);

	/**
	 * @brief ��ȡ����������ؼ�����ʾ���ı����������
	 * @return ��ǰ��ʾ�ı������
	 */
	virtual int GetToolTipWidth(void) const;

    /// �˵�
	/**
	 * @brief �ؼ��Ƿ���Ӧ�Ҽ��˵���Ϣ
	 * @return ���ؽ����ʾ���Ƿ���Ӧ�Ҽ��˵���Ϣ��true ��Ӧ�Ҽ��˵���Ϣ��false ����Ӧ�Ҽ��˵���Ϣ
	 */
    virtual bool IsContextMenuUsed() const;

	/**
	 * @brief ���ÿؼ���Ӧ�Ҽ��˵���Ϣ
	 * @param[in] bMenuUsed �Ƿ���Ӧ�Ҽ��˵���Ϣ��true Ϊ�ǣ�false Ϊ��
	 * @return ��
	 */
    virtual void SetContextMenuUsed(bool bMenuUsed);

    /// �û����ݣ��������������û�ʹ��
	/**
	 * @brief ��ȡ�û��󶨵��ؼ��������ַ���
	 * @return ���ؾ��������ַ���
	 */
    virtual CUiString GetDataID() const;
				

	/**
	 * @brief ��һ���ַ������ݵ��ؼ�
	 * @param[in] strText Ҫ�󶨵��ַ�������
	 * @return ��
	 */
    virtual void SetDataID(LPCTSTR strText);

	
	/**
	 * @brief ��ȡ�û��󶨵��Զ������ݽṹ
	 * @return �û��󶨵��Զ���ṹ����ָ��
	 */
	virtual UserDataBase* GetUserDataBase() const;

	/**
	 * @brief ���Զ������ݵ��ؼ����û��ɼ̳� UserDataBase ��������Ҫ�󶨵�����
	 * @param[in] pUserDataBase ����ָ��
	 * @return ��
	 */
	virtual void SetUserDataBase(UserDataBase* pUserDataBase);

    /// һЩ��Ҫ������
	/**
	 * @brief ���ÿؼ��Ƿ�ɼ�
	 * @param[in] bVisible Ϊ true ʱ�ؼ��ɼ���Ϊ false ʱ�ؼ�������
	 * @return ��
	 */
    virtual void SetVisible(bool bVisible = true);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
    virtual void SetInternVisible(bool bVisible = true); // �����ڲ����ã���Щuiӵ�д��ھ������Ҫ��д�˺���

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual void SetVisible_(bool bVisible);

	/**
	 * @brief ���ؼ��Ƿ����
	 * @return �ؼ�����״̬������ true �ؼ����ã�����Ϊ false
	 */
    virtual bool IsEnabled() const;

	/**
	 * @brief ���ÿؼ�����״̬
	 * @param[in] bEnable Ϊ true ʱ�ؼ����ã�Ϊ false ʱ�ؼ�Ϊ����״̬�򲻿���
	 * @return ��
	 */
    virtual void SetEnabled(bool bEnable = true);

	/**
	 * @brief ���ؼ��Ƿ���Ӧ����¼�
	 * @return ���ؿؼ��Ƿ���Ӧ����¼������� true ��Ӧ����¼���false Ϊ����Ӧ
	 */
    virtual bool IsMouseEnabled() const;

	/**
	 * @brief ���ÿؼ��Ƿ���Ӧ����¼�
	 * @param[in] bEnable Ϊ true ��Ӧ����¼���Ϊ false ʱ����Ӧ����¼�
	 * @return ��
	 */
    virtual void SetMouseEnabled(bool bEnable = true);

	/**
	 * @brief ���ؼ��Ƿ���Ӧ�����¼�
	 * @return ���ؿؼ��Ƿ���Ӧ�����¼������� true ��Ӧ�����¼���false ����Ӧ�����¼�
	 */
    virtual bool IsKeyboardEnabled() const;

	/**
	 * @brief ���ÿؼ��Ƿ���Ӧ�����¼�
	 * @param[in] bEnable Ϊ true ��Ӧ�����¼���Ϊ false ʱ����Ӧ�����¼�
	 * @return ��
	 */
    virtual void SetKeyboardEnabled(bool bEnable = true);

	/**
	 * @brief ���ؼ��Ƿ���н���
	 * @return ���ؿؼ��Ƿ���м�㣬Ϊ true ʱ�ǵ�ǰ���н��㣬Ϊ false ʱ�ؼ�û�н���
	 */
    virtual bool IsFocused() const;

	/**
	 * @brief �ÿؼ���ȡ����
	 * @return ��
	 */
    virtual void SetFocus();

	/**
	 * @brief ���ؿؼ��ı�ʶ�������ж��Ƿ������Ӧ TAB �л��¼�
	 * @return ���ؿؼ��ı�ʶ����
	 */
	virtual UINT GetControlFlags() const;

	/**
	 * @brief �ÿؼ�������Զ��ȡ��������
	 * @return ��
	 */
	void SetNoFocus(); // �ؼ���Զ��Ҫ���㣬��KillFocus��һ��

	/**
	 * @brief �жϵ�ǰ��꽹���Ƿ��ڿؼ���
	 * @return ������꽹���Ƿ��ڿؼ��ϣ�true ��꽹���ڿؼ��ϣ�false ��꽹�㲻�ڿؼ���
	 */
	virtual bool IsMouseFocused() const { return m_bMouseFocused;}

	/**
	 * @brief �����Ƿ���꽹�㵽�ؼ���
	 * @param[in] bMouseFocused Ϊ true ʱ������꽹�㵽�ؼ��ϣ�Ϊ false ʱ�ÿؼ�ʧȥ��꽹��
	 * @return ��
	 */
	virtual void SetMouseFocused(bool bMouseFocused) { m_bMouseFocused = bMouseFocused; }

	/**
	 * @brief �жϿؼ���ǰ�Ƿ��Ǽ���״̬
	 * @return ���ؿؼ�״̬��true �ؼ���ǰ�Ǽ���״̬���ɼ������ã�false �ؼ���ǰ�Ǽ���״̬�����ܲ��ɼ��򱻽���
	 */
	virtual bool IsActivatable() const;

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual void Activate();

	/// �ؼ�����
	/**
	 * @brief �����������ָ���ؼ�
	 * @param[in] Proc
	 * @param[in] pData
	 * @param[in] uFlags
	 * @param[in] scrollPos
	 * @return ���ؿؼ���ָ��
	 */
    virtual Control* FindControl(FINDCONTROLPROC Proc, LPVOID pData, UINT uFlags, CUiPoint scrollPos = CUiPoint());

	/// λ�����
	/**
	 * @brief ��ȡ�ؼ�λ��
	 * @param[in] bContainShadow �Ƿ������Ӱ��Ĭ��Ϊ true �������Ӱ��Χ������ false Ϊ������
	 * @return ���ؿؼ���λ����Ϣ
	 */
	virtual	CUiRect GetPos(bool bContainShadow = true) const override;

	/**
	 * @brief ���ÿؼ�λ��
	 * @param[in] rc �ؼ�λ�õ�������Ϣ
	 * @return ��
	 */
	virtual void SetPos(CUiRect rc) override;

	/**
	 * @brief ��ȡ�ؼ�����߾�
	 * @return ���ؿؼ�����߾�
	 */
	virtual CUiRect GetMargin() const;

	/**
	 * @brief ���ÿؼ�����߾�
	 * @param[in] rcMargin �ؼ�����߾���Ϣ
	 * @param[in] bNeedDpiScale �Ƿ�����߾���� DPI ���䣬Ĭ��Ϊ true��false ������ DPI
	 * @return ��
	 */
	virtual void SetMargin(CUiRect rcMargin, bool bNeedDpiScale = true);

	/**
	 * @brief ����ؼ���С
	 * @param[in] szAvailable ��������
	 * @return szAvailable �ؼ�ʵ�ʴ�С�����������ͼƬ������ width �� height ����һ��Ϊ auto��������ͼƬ���������մ�С��
	 */
	virtual CUiSize EstimateSize(CUiSize szAvailable);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual CUiSize EstimateText(CUiSize szAvailable, bool& bReEstimateSize);

	/**
	 * @brief ���ָ�������Ƿ��ڹ�������ǰ����λ�õķ�Χ��
	 * @param[in] point ��������
	 * @return �����Ƿ��ڷ�Χ�ڣ�true �ڹ�������ǰ����λ�÷�Χ�ڣ�false ���ڹ�������ǰ����λ�÷�Χ��
	 */
	virtual bool IsPointInWithScrollOffset(const CUiPoint& point) const;

	// ��Ϣ����
	/**
	 * @brief �ؼ�ͳһ����Ϣ������ڣ�����ͳ Windows ��Ϣת��Ϊ�Զ����ʽ����Ϣ
	 * @param[in] eventType	��Ϣ����
	 * @param[in] wParam	��Ϣ��������
	 * @param[in] lParam	��Ϣ��������
	 * @param[in] tChar		������Ϣ
	 * @param[in] mousePos	�����Ϣ
	 * @return ��
	 */
	void HandleMessageTemplate(EventType eventType, WPARAM wParam = 0, LPARAM lParam = 0, TCHAR tChar = 0, CUiPoint mousePos = CUiPoint(), FLOAT pressure = 0.0f);

	/**
	 * @brief ��ת�������Ϣ�ɷ�����Ϣ������
	 * @param[in] msg ��Ϣ����
	 * @return ��
	 */
    virtual void HandleMessageTemplate(EventArgs& msg);

	/**
	 * @brief �жϿؼ��Ƿ��� HOT ״̬
	 * @return ���� true �� HOT ״̬�� ����Ϊ false
	 */
	virtual bool HasHotState();

	/**
	 * @brief ���ÿؼ��Ƿ���Ӧ������Ϣ
	 * @param[in] bRecv ����Ϊ true ��ʾ��Ӧ������Ϣ��false Ϊ����Ӧ
	 * @return ��
	 */
	void SetReceivePointerMsg(bool bRecv) { m_bReceivePointerMsg = bRecv; };
	
	/**
	 * @brief �жϿؼ��Ƿ���Ӧ������Ϣ
	 * @return ���� true Ϊ��Ӧ������Ϊ false
	 */
	bool IsReceivePointerMsg() const { return m_bReceivePointerMsg; };

	/**
	 * @brief ���ÿؼ�ʧȥ����ʱ�Ƿ�����굯����Ϣ
	 * @param[in] bNeed ����Ϊ true ��ʾ��Ӧ������Ϣ��false Ϊ����Ӧ
	 * @return ��
	 */
	void SetNeedButtonUpWhenKillFocus(bool bNeed) { m_bNeedButtonUpWhenKillFocus = bNeed; };

	/**
	 * @brief �жϿؼ�ʧȥ����ʱ�Ƿ�����굯����Ϣ
	 * @return ���� true Ϊ��Ҫ��false Ϊ����Ҫ
	 */
	bool IsNeedButtonUpWhenKillFocus() const { return m_bNeedButtonUpWhenKillFocus; };

	// ��������
	/**
	 * @brief ���ÿؼ�ָ������
	 * @param[in] szName Ҫ���õ��������ƣ��� width��
	 * @param[in] szValue Ҫ���õ�����ֵ���� 100��
	 * @return ��
	 */
	virtual void SetAttribute(LPCTSTR szName, LPCTSTR szValue);

	/**
	 * @brief ���ÿؼ��� class ȫ������
	 * @param[in] strClass Ҫ���õ� class ���ƣ������Ʊ����� global.xml �д���
	 * @return ��
	 */
	void SetClass(LPCTSTR strClass);

	/**
	 * @brief Ӧ��һ�������б�
	 * @param[in] strList �����б���ַ�����ʾ���� `width="100" height="30"`
	 * @return ��
	 */
    void ApplyAttributeList(LPCTSTR strList);

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	bool OnApplyAttributeList(LPCTSTR strReceiver, LPCTSTR strList, EventArgs* eventArgs);

	/// ���Ʋ���
	/**
	 * @brief ����ͼƬ·������ͼƬ��Ϣ
	 * @param[in��out] duiImage ����ʱ��עͼƬ��·����Ϣ������ɹ���Ỻ��ͼƬ����¼���ò����ĳ�Ա��
	 * @return ��
	 */
	void GetImage(Image& duiImage) const;

	/**
	 * @brief ����ͼƬ
	 * @param[in] pRender ����������
	 * @param[in] duiImage ͼƬ����
	 * @param[in] strModify ͼƬ�ĸ�������
	 * @param[in] nFade �ؼ���͸���ȣ�������ö���Ч����ֵ�ڻ���ʱ�ǲ��ϱ仯��
	 * @return �ɹ����� true��ʧ�ܷ��� false
	 */
	bool DrawImage(IRenderContext* pRender, Image& duiImage, LPCTSTR strModify = _T(""), int nFade = DUI_NOSET_VALUE);

	/**
	* @brief ��ȡ���������Ķ���
	* @return ���ػ��������Ķ���
	*/
	IRenderContext* GetRenderContext();

	/**
	* @brief ������������Ķ���
	* @return ��
	*/
	void ClearRenderContext();

	/**
	 * @brief ������
	 * @param[in] ������
	 * @return ������
	 */
	virtual void AlphaPaint(IRenderContext* pRender, const CUiRect& rcPaint);
	
	/**
	* @brief ���ƿؼ�����ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void Paint(IRenderContext* pRender, const CUiRect& rcPaint);

	/**
	* @brief ���ƿؼ�������ں���
	* @param[in] pRender ָ����������
	* @param[in] rcPaint ָ����������
	* @return ��
	*/
	virtual void PaintChild(IRenderContext* pRender, const CUiRect& rcPaint) {};

	/**
	* @brief �����Ƿ�Ի��Ʒ�Χ����������
	* @param[in] clip ���� true Ϊ��Ҫ������Ϊ����Ҫ�������ƺ���
	* @return ��
	*/
	void SetClip(bool clip) { m_bClip = clip; };

	/**
	* @brief �ж��Ƿ�Ի��Ʒ�Χ����������
	* @return ���� true Ϊ��Ҫ��false Ϊ����Ҫ
	*/
	bool IsClip() const { return m_bClip; }

	/**
	 * @brief ���ÿؼ�͸����
	 * @param[in] alpha 0 ~ 255 ��͸����ֵ��255 Ϊ��͸��
	 * @return ��
	 */
	void SetAlpha(int alpha);

	/**
	 * @brief ��ȡ�ؼ�͸����
	 * @return ���ؿؼ���͸����
	 */
	int GetAlpha() const { return m_nAlpha;	}

	/**
	 * @brief ���ؼ��Ƿ���͸������
	 * @return ���ؿؼ��Ƿ�͸����true �ؼ���ǰ��͸�����ԣ�false �ؼ�û��͸������
	 */
	bool IsAlpha() const { return m_nAlpha != 255; }

	/**
	 * @brief ���ý���״̬͸����
	 * @param[in] alpha 0 ~ 255 ��͸����ֵ��255 Ϊ��͸��
	 * @return ��
	 */
	void SetHotAlpha(int nHotAlpha);

	/**
	 * @brief ��ȡ����״̬͸����
	 * @return ���ؿؼ�����״̬��͸����
	 */
	int GetHotAlpha() const { return m_nHotAlpha; }

	/**
	 * @brief ��ȡ�ؼ�����ƫ����
	 * @return ���ص�ǰ�ؼ��Ļ���ƫ����
	 */
	CUiPoint GetRenderOffset() const { return m_renderOffset;	}

	/**
	 * @brief ���ÿؼ�����ƫ����
	 * @param[in] renderOffset �ؼ�ƫ������
	 * @return ��
	 */
	void SetRenderOffset(CUiPoint renderOffset);

	/**
	 * @brief ���ÿؼ�ƫ�Ƶ� X ����
	 * @param[in] renderOffsetX X ����ֵ
	 * @return ��
	 */
	void SetRenderOffsetX(int renderOffsetX);

	/**
	 * @brief ���ÿؼ�ƫ�Ƶ� Y ����
	 * @param[in] renderOffsetY Y ����ֵ
	 * @return ��
	 */
	void SetRenderOffsetY(int renderOffsetY);

	/// GifͼƬ
	/**
	 * @brief ���� GIF
	 * @param[in] �������ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifStopType ö��
	 * @return ��
	 */
	void StartGifPlayForUI(GifStopType frame = kGifStopFirst,int playcount = -1);

	/**
	 * @brief ֹͣ���� GIF
	 * @param[in] transfer �Ƿ�ֹͣ�¼�֪ͨ�������ߣ��ο� AttachGifPlayStop ����
	 * @param[frame] frame ���Ž���ֹͣ����һ֡�������õ�һ֡����ǰ֡�����һ֡����ο� GifStopType ö��
	 * @return ��
	 */
	void StopGifPlayForUI(bool transfer = false, GifStopType frame = kGifStopCurrent);

	/**
	 * @brief ���� GIF �������֪ͨ
	 * @param[in] callback Ҫ���� GIF ֹͣ���ŵĻص�����
	 * @return ��
	 */
	void AttachGifPlayStop(const EventCallback& callback){ OnGifEvent[m_nVirtualEventGifStop] += callback; };

	/// ��������
	/**
	 * @brief ��ȡ����������ָ��
	 * @return ���ض���������ָ��
	 */
	AnimationManager& GetAnimationManager()	{ return m_animationManager; }

	/// ͼƬ����
	/**
	 * @brief ����ͼƬ
	 * @return ��
	 */
	virtual void InvokeLoadImageCache();

	/**
	 * @brief ȡ������ͼƬ����
	 * @return ��
	 */
	virtual void UnLoadImageCache();

	/**
	 * @brief ����ͼƬ����
	 * @return ��
	 */
	virtual void ClearImageCache();

	/**
	 * @brief �����ؼ������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachAllEvents(const EventCallback& callback)	{ OnEvent[kEventAll] += callback; }

	/**
	 * @brief �����������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachMouseEnter(const EventCallback& callback) { OnEvent[kEventMouseEnter] += callback; }

	/**
	 * @brief ��������뿪�¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachMouseLeave(const EventCallback& callback) { OnEvent[kEventMouseLeave] += callback; }

	/**
	 * @brief ������������¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachMouseHover(const EventCallback& callback) { OnEvent[kEventMouseHover] += callback; }

	/**
	 * @brief ������갴���¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachButtonDown(const EventCallback& callback) { OnEvent[kEventMouseButtonDown] += callback; }

	/**
	 * @brief ������굯���¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachButtonUp(const EventCallback& callback) { OnEvent[kEventMouseButtonUp] += callback; }

	/**
	 * @brief ������ý����¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachSetFocus(const EventCallback& callback) { OnEvent[kEventSetFocus] += callback; }

	/**
	 * @brief ����ʧȥ�����¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachKillFocus(const EventCallback& callback) { OnEvent[kEventKillFocus] += callback; }

	/**
	 * @brief �����Ҽ��˵��¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachMenu(const EventCallback& callback) { OnEvent[kEventMouseMenu] += callback; }

	/**
	 * @brief �����ؼ���С�ı��¼�
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void AttachResize(const EventCallback& callback) { OnEvent[kEventResize] += callback; }

	/**
	 * @brief ȡ������ָ���¼����� EventType ö��
	 * @param[in] callback �¼�����Ļص���������ο� EventCallback ����
	 * @return ��
	 */
	void DetachEvent(EventType type);

protected:
	friend WindowBuilder;
	void AttachXmlEvent(EventType eventType, const EventCallback& callback) { OnXmlEvent[eventType] += callback; }
	/// GifͼƬ
	void GifPlay();
	void StopGifPlay(GifStopType frame = kGifStopCurrent);

	
	/// ��Ϣ����ı�����Ա�������������ⲿֱ�ӵ���
	virtual void HandleMessage(EventArgs& msg);
	virtual bool MouseEnter(EventArgs& msg);
	virtual bool MouseLeave(EventArgs& msg);
	virtual bool ButtonDown(EventArgs& msg);
	virtual bool ButtonUp(EventArgs& msg);

	/// ������ر�����Ա�������������ⲿֱ�ӵ���
	virtual void PaintBkColor(IRenderContext* pRender);
	virtual void PaintBkImage(IRenderContext* pRender);
	virtual void PaintStatusColor(IRenderContext* pRender);
	virtual void PaintStatusImage(IRenderContext* pRender);
	virtual void PaintText(IRenderContext* pRender);
	virtual void PaintBorder(IRenderContext* pRender);
protected:
	/**
	* @brief ��ȡ UTF8 ��ʽ�ı���ͼƬλ��
	* @return ����ͼƬλ��
	*/
	std::string GetUTF8BkImage() const;
	/**
	* @brief ���ñ���ͼƬ��UTF8 ��ʽ�ַ�����
	* @param[in] strImage Ҫ���õ�ͼƬ·��
	* @return ��
	*/
	void SetUTF8BkImage(const std::string& strImage);

	/**
	* @brief ��ȡ�ؼ����������״̬�µ���ʾ�ı���UTF8 ��ʽ��
	* @return ���ص�ǰ�������״̬��ʾ���ı�
	*/
	virtual std::string GetUTF8ToolTipText() const;

	/**
	* @brief ��������������ؼ���ʾ����ʾ�ı���UTF8 ��ʽ��
	* @param[in] strText Ҫ���õ��ı�
	* @return ��
	*/
	virtual void SetUTF8ToolTipText(const std::string& strText);

	/**
	* @brief ��������������ؼ���ʾ����ʾ�ı��������ļ��ж�Ӧ�����֣�UTF8 ��ʽ��
	* @param[in] strTextId �������ļ��ж�Ӧ����ʾ���� ID
	* @return ��
	*/
	virtual void SetUTF8ToolTipTextId(const std::string& strTextId);

	/**
	* @brief ��ȡ�û��󶨵��ؼ��������ַ�����UTF8 ��ʽ��
	* @return ���ؾ��������ַ���
	*/
	virtual std::string GetUTF8DataID() const;

	/**
	* @brief ��һ���ַ������ݵ��ؼ���UTF8 ��ʽ��
	* @param[in] strText Ҫ�󶨵��ַ�������
	* @return ��
	*/
	virtual void SetUTF8DataID(const std::string& strText);
private:
	void BroadcastGifEvent(int nVirtualEvent);
	int GetGifFrameIndex(GifStopType frame);

protected:
	EventMap OnXmlEvent;
	EventMap OnEvent;
	GifEventMap OnGifEvent;
	std::unique_ptr<UserDataBase> m_pUserDataBase;
	bool m_bMenuUsed;
	bool m_bEnabled;
	bool m_bMouseEnabled;
	bool m_bKeyboardEnabled;
	bool m_bFocused;
	bool m_bMouseFocused;
	bool m_bSetPos;		// ��ֹSetPosѭ������
	bool m_bNoFocus;	//�ؼ�����Ҫ����
	bool m_bClip;
	bool m_bGifPlay;
	bool m_bReceivePointerMsg;
	bool m_bNeedButtonUpWhenKillFocus;
	int m_nBorderSize;
	int m_nTooltipWidth;
	int m_nAlpha;
	int m_nHotAlpha;
	CUiSize m_szEstimateSize;
	CUiPoint m_renderOffset;
	CUiSize m_cxyBorderRound;
	CUiRect m_rcMargin;
	CUiRect m_rcPaint;
	CUiRect m_rcBorderSize;
	CursorType m_cursorType;	//Ӱ��ؼ��������״
	ControlStateType m_uButtonState;
	CUiString m_sToolTipText;
	CUiString m_sToolTipTextId;
	CUiString m_sUserData;
	CUiString m_strBkColor;
	StateColorMap m_colorMap;
	Image m_bkImage;
	StateImageMap m_imageMap;
	CUiString m_strBorderColor;
	ui::WeakCallbackFlag m_gifWeakFlag;
	AnimationManager m_animationManager;
	ui::WeakCallbackFlag m_loadBkImageWeakFlag;
	static const int m_nVirtualEventGifStop;
};

} // namespace ui

#endif // UI_CORE_CONTROL_H_
