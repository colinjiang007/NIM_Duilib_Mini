#ifndef UI_CORE_VBOX_H_
#define UI_CORE_VBOX_H_

#pragma once

namespace ui
{

class UILIB_API VLayout : public Layout
{
public:
	VLayout();
	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual CUiSize ArrangeChild(const std::vector<Control*>& items, CUiRect rc) override;
	virtual CUiSize AjustSizeByChild(const std::vector<Control*>& items, CUiSize szAvailable) override;
};

class UILIB_API VBox : public Box
{
public:
	VBox();
};

}
#endif // UI_CORE_VBOX_H_
