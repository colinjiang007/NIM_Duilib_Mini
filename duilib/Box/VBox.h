#ifndef UI_CORE_VBOX_H_
#define UI_CORE_VBOX_H_

#pragma once

namespace ui
{

class UILIB_API VLayout : public Layout
{
public:
	VLayout();
	/// 重写父类方法，提供个性化功能，请参考父类声明
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
