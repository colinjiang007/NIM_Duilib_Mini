#ifndef UI_CORE_TILEBOX_H_
#define UI_CORE_TILEBOX_H_

#pragma once

namespace ui
{

class UILIB_API TileLayout : public Layout
{
public:
	TileLayout();

	/// ��д���෽�����ṩ���Ի����ܣ���ο���������
	virtual CUiSize ArrangeChild(const std::vector<Control*>& items, CUiRect rc) override;
	virtual CUiSize AjustSizeByChild(const std::vector<Control*>& items, CUiSize szAvailable) override;
	virtual bool SetAttribute(const CUiString& strName, const CUiString& strValue) override;

	/**
	 * @brief ��ȡ�����С
	 * @return ���������С
	 */
	CUiSize GetItemSize() const;

	/**
	 * @brief ���������С
	 * @param[in] szItem �����С����
	 * @return ��
	 */
	void SetItemSize(CUiSize szItem);

	/**
	 * @brief ��ȡ������
	 * @return ����������
	 */
	int GetColumns() const;

	/**
	 * @brief ������ʾ��������
	 * @param[in] nCols Ҫ������ʾ���е���ֵ
	 * @return ��
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
