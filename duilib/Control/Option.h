#ifndef UI_CONTROL_OPTION_H_
#define UI_CONTROL_OPTION_H_

#pragma once

namespace ui
{

template<typename InheritType = Control>
class UILIB_API OptionTemplate : public CheckBoxTemplate<InheritType>
{
public:
	OptionTemplate();
	~OptionTemplate();
		
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual void SetWindow(Window* pManager, Box* pParent, bool bInit = true) override;
	virtual void SetAttribute(const CUiString& strName, const CUiString& strValue) override;
	virtual void Selected(bool bSelected, bool bTriggerEvent = false) override;
	virtual void Activate() override;

	/**
	 * @brief ��ȡ����������
	 * @return ����������
	 */
	virtual  CUiString GetGroup() const;

	/**
	 * @brief ����������
	 * @param[in] strGroupName ������
	 * @return ��
	 */
	virtual void SetGroup(const CUiString& strGroupName);

protected:
	CUiString	m_sGroupName;
};

template<typename InheritType>
OptionTemplate<InheritType>::OptionTemplate() :
	m_sGroupName()
{

}

template<typename InheritType>
OptionTemplate<InheritType>::~OptionTemplate()
{
	if (!m_sGroupName.IsEmpty() && this->m_pWindow) this->m_pWindow->RemoveOptionGroup(m_sGroupName, this);
}

template<typename InheritType>
void OptionTemplate<InheritType>::SetWindow(Window* pManager, Box* pParent, bool bInit)
{
	__super::SetWindow(pManager, pParent, bInit);
	if (bInit && !m_sGroupName.IsEmpty()) {
		if (this->m_pWindow) this->m_pWindow->AddOptionGroup(m_sGroupName, this);
	}
}

template<typename InheritType>
void OptionTemplate<InheritType>::SetAttribute(const CUiString& strName, const CUiString& strValue)
{
	if (strName == _T("group")) SetGroup(strValue);
	else __super::SetAttribute(strName, strValue);
}

template<typename InheritType>
void OptionTemplate<InheritType>::Selected(bool bSelected, bool bTriggerEvent)
{
	//if( m_bSelected == bSelected ) return;
	this->m_bSelected = bSelected;

	if (this->m_pWindow != NULL) {
		if (this->m_bSelected) {
			if (!m_sGroupName.IsEmpty()) {
				std::vector<Control*>* aOptionGroup = this->m_pWindow->GetOptionGroup(m_sGroupName);
				ASSERT(aOptionGroup);
				if (aOptionGroup) {
					for (auto it = aOptionGroup->begin(); it != aOptionGroup->end(); it++) {
						auto pControl = static_cast<OptionTemplate<InheritType>*>(*it);
						if (pControl != this) {
							pControl->Selected(false, bTriggerEvent);
						}
					}
				}
			}

			if (bTriggerEvent) {
				this->m_pWindow->SendNotify(this, kEventSelect);
			}
		}
		else {
			this->m_pWindow->SendNotify(this, kEventUnSelect);
		}
	}

	this->Invalidate();
}

template<typename InheritType>
void OptionTemplate<InheritType>::Activate()
{
	ButtonTemplate<InheritType>::Activate();
	if (!this->IsActivatable()) return;
	Selected(true, true);
}

template<typename InheritType>
CUiString OptionTemplate<InheritType>::GetGroup() const
{
	return m_sGroupName;
}

template<typename InheritType>
void OptionTemplate<InheritType>::SetGroup(const CUiString& strGroupName)
{
	if (strGroupName.IsEmpty()) {
		if (m_sGroupName.IsEmpty()) return;
		m_sGroupName.Empty();
	}
	else {
		if (m_sGroupName == strGroupName) return;
		if (!m_sGroupName.IsEmpty() && this->m_pWindow) this->m_pWindow->RemoveOptionGroup(m_sGroupName, this);
		m_sGroupName = strGroupName;
	}

	if (!m_sGroupName.IsEmpty()) {
		if (this->m_pWindow) this->m_pWindow->AddOptionGroup(m_sGroupName, this);
	}
	else {
		if (this->m_pWindow) this->m_pWindow->RemoveOptionGroup(m_sGroupName, this);
	}

	Selected(this->m_bSelected, true);
}

typedef OptionTemplate<Control> Option;
typedef OptionTemplate<Box> OptionBox;

}

#endif // UI_CONTROL_OPTION_H_
