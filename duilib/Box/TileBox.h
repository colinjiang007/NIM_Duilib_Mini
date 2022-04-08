#ifndef UI_CORE_TILEBOX_H_
#define UI_CORE_TILEBOX_H_

#pragma once

namespace ui
{

class UILIB_API TileLayout : public Layout
{
public:
	TileLayout();

	/// 重写父类方法，提供个性化功能，请参考父类声明
	virtual CUiSize ArrangeChild(const std::vector<Control*>& items, const CUiRect& rc) override;
	virtual CUiSize AjustSizeByChild(const std::vector<Control*>& items, const CUiSize& szAvailable) override;
	virtual bool SetAttribute(LPCTSTR szName, LPCTSTR szValue) override;

	/**
	 * @brief 获取子项大小
	 * @return 返回子项大小
	 */
	CUiSize GetItemSize() const;

	/**
	 * @brief 设置子项大小
	 * @param[in] szItem 子项大小数据
	 * @return 无
	 */
	void SetItemSize(CUiSize szItem);

	/**
	 * @brief 获取列数量
	 * @return 返回列数量
	 */
	int GetColumns() const;

	/**
	 * @brief 设置显示几列数据
	 * @param[in] nCols 要设置显示几列的数值
	 * @return 无
	 */
	void SetColumns(int nCols);

protected:
	int m_nColumns;
	CUiSize m_szItem;
};

class UILIB_API TileBox : public Box
{
public:
	TileBox();
};

}
#endif // UI_CORE_TILEBOX_H_
