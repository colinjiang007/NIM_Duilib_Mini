#ifndef UI_CORE_CHILDBOX_H_
#define UI_CORE_CHILDBOX_H_

#pragma once

namespace ui
{

class UILIB_API ChildBox : public Box
{
public:
	ChildBox();

	/// 重写父类方法，提供个性化功能，请参考父类声明
	virtual void Init() override;
	virtual void SetAttribute(LPCTSTR szName, LPCTSTR szValue) override;

	/**
	 * @brief 设置 ChildBox 关联的 XML 文件
	 * @param[in] strXML XML 文件路径
	 * @return 无
	 */
	void SetChildLayoutXML(LPCTSTR strXML);

	/**
	 * @brief 获取 ChildBox 关联的 XML 文件
	 * @return 返回 ChildBox 关联的 XML 文件
	 */
	CUiString GetChildLayoutXML();

private:
	CUiString m_strXMLFile;
};

} // namespace ui
#endif // UI_CORE_CHILDBOX_H_
