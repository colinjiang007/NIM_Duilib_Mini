#include "StdAfx.h"

namespace ui
{

class ShadowBox : public Box
{
public:
	virtual void Paint(IRenderContext* pRender, const CUiRect& rcPaint) override
	{
		auto rcPos = GetPaddingPos();
		if (rcPaint.left >= rcPos.left && rcPaint.top >= rcPos.top && rcPaint.right <= rcPos.right && rcPaint.bottom <= rcPos.bottom) {
			return;
		}
		__super::Paint(pRender, rcPaint);
	};
};

Shadow::Shadow() :
	m_rcCurShadowCorner(14, 14, 14, 14),
	m_rcDefaultShadowCorner(14, 14, 14, 14),
	m_bShadowAttached(true),
	m_bUseDefaultImage(true),
	m_strImage(_T("file='../public/bk/bk_shadow.png' corner='30,30,30,30'")),
	m_pRoot(nullptr)
{
	DpiManager::GetInstance()->ScaleRect(m_rcCurShadowCorner);
	m_rcShadowCornerBackup = m_rcCurShadowCorner;
}

void Shadow::SetShadowImage(const CUiString &image)
{
	m_strImage = image;
	m_bUseDefaultImage = false;
}

CUiString Shadow::GetShadowImage() const
{
	return m_strImage;
}

void Shadow::SetShadowCorner(const CUiRect &rect)
{
	m_rcDefaultShadowCorner = m_rcCurShadowCorner = rect;
	DpiManager::GetInstance()->ScaleRect(m_rcCurShadowCorner);
	m_rcShadowCornerBackup = m_rcCurShadowCorner;
}

CUiRect Shadow::GetShadowCorner() const
{
	if (m_bShadowAttached) {
		return m_rcCurShadowCorner;
	}
	else {
		return CUiRect(0, 0, 0, 0);
	}
}

void Shadow::ResetShadowBox()
{
	if (m_bShadowAttached && m_pRoot) {
		auto rcTempShadowCorner = m_rcDefaultShadowCorner;
		DpiManager::GetInstance()->ScaleRect(rcTempShadowCorner);
		m_rcShadowCornerBackup = m_rcCurShadowCorner = rcTempShadowCorner;
		m_pRoot->GetLayout()->SetPadding(m_rcDefaultShadowCorner);
	}
}

Box*Shadow::AttachShadow(Box* pRoot)
{
	if (!m_bShadowAttached)
		return pRoot;

	m_pRoot = new ShadowBox();
	m_pRoot->GetLayout()->SetPadding(m_rcCurShadowCorner, false);

	int rootWidth = pRoot->GetFixedWidth();
	if (rootWidth > 0) {
		rootWidth += m_rcCurShadowCorner.left + m_rcCurShadowCorner.right;
	}
	m_pRoot->SetFixedWidth(rootWidth, true, false);

	int rootHeight = pRoot->GetFixedHeight();
	if (rootHeight > 0) {
		rootHeight += m_rcCurShadowCorner.top + m_rcCurShadowCorner.bottom;
	}
	m_pRoot->SetFixedHeight(rootHeight, false);

	if (m_bUseDefaultImage)
	{
		CUiSize size(3, 3);
		pRoot->SetBorderRound(size);
	}

	m_pRoot->Add(pRoot);
	m_pRoot->SetBkImage(m_strImage);

	return m_pRoot;
}

void Shadow::MaximizedOrRestored(bool isMaximized)
{
	if (!m_bShadowAttached)
		return;

	if (isMaximized && m_pRoot) {
		m_rcCurShadowCorner = CUiRect(0, 0, 0, 0);
		m_pRoot->GetLayout()->SetPadding(m_rcCurShadowCorner, false);

		if (m_bUseDefaultImage)
		{
			Control* control = m_pRoot->GetItemAt(0);
			CUiSize size(0, 0);
			control->SetBorderRound(size);
		}
	}
	else if (!isMaximized && m_pRoot) {
		m_rcCurShadowCorner = m_rcShadowCornerBackup;
		m_pRoot->GetLayout()->SetPadding(m_rcCurShadowCorner, false);

		if (m_bUseDefaultImage)
		{
			Control* control = m_pRoot->GetItemAt(0);
			CUiSize size(3, 3);
			control->SetBorderRound(size);
		}
	}
}

ui::Control* Shadow::GetRoot()
{
	return m_pRoot;
}

void Shadow::ClearImageCache()
{
	m_pRoot->ClearImageCache();
}

}
