#ifndef UI_CORE_RENDER_H_
#define UI_CORE_RENDER_H_

#pragma once

namespace ui 
{

class UILIB_API RenderContext_GdiPlus : public IRenderContext
{
public:
	RenderContext_GdiPlus();
	virtual ~RenderContext_GdiPlus();

	virtual HDC GetDC() override;
	virtual bool Resize(int width, int height, bool flipBItmap = true) override;
	virtual void Clear() override;
	virtual std::unique_ptr<IRenderContext> Clone() override;

	virtual HBITMAP DetachBitmap() override;
	virtual BYTE* GetBits() override;
	virtual int	GetWidth() override;
	virtual int GetHeight() override;
	virtual void ClearAlpha(const CUiRect& rcDirty, int alpha = 0) override;
	virtual void RestoreAlpha(const CUiRect& rcDirty, const CUiRect& rcShadowPadding = CUiRect(), int alpha = 0) override;

	virtual bool IsRenderTransparent() const override;
	virtual bool SetRenderTransparent(bool bTransparent) override;

	virtual void Save() override;
	virtual void Restore() override;

	virtual CUiPoint OffsetWindowOrg(CUiPoint ptOffset) override;
	virtual CUiPoint SetWindowOrg(CUiPoint ptOffset) override;
	virtual CUiPoint GetWindowOrg() const override;

	virtual void SetClip(const CUiRect& rc) override;
	virtual void SetRoundClip(const CUiRect& rc, int width, int height) override;
	virtual void ClearClip() override;

	virtual HRESULT BitBlt(int x, int y, int cx, int cy, HDC hdcSrc, int xSrc = 0, int yScr = 0, DWORD rop = SRCCOPY) override;
	virtual bool AlphaBlend(int xDest, int yDest, int widthDest, int heightDest, HDC hdcSrc, int xSrc, int yScr, int widthSrc, int heightSrc, BYTE uFade = 255) override;

	virtual void DrawImage(const CUiRect& rcPaint, HBITMAP hBitmap, bool bAlphaChannel,
		const CUiRect& rcImageDest, const CUiRect& rcImageSource, const CUiRect& rcCorners, BYTE uFade = 255, bool xtiled = false, bool ytiled = false) override;

	virtual void DrawColor(const CUiRect& rc, DWORD dwColor, BYTE uFade = 255) override;
	virtual void DrawColor(const CUiRect& rc, const CUiString& colorStr, BYTE uFade = 255) override;

	virtual void DrawLine(const CUiRect& rc, int nSize, DWORD dwPenColor) override;
	virtual void DrawLine(const IPen* pen, int x1, int y1, int x2, int y2) override;
	virtual void DrawBezier(const IPen* pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) override;
	virtual void DrawRect(const CUiRect& rc, int nSize, DWORD dwPenColor) override;
	virtual void DrawRoundRect(const CUiRect& rc, const CUiSize& roundSize, int nSize, DWORD dwPenColor) override;
	virtual void DrawText(const CUiRect& rc, const CUiString& strText, DWORD dwTextColor, const CUiString& strFontId, UINT uStyle, BYTE uFade = 255, bool bLineLimit = false) override;

	virtual void DrawEllipse(const CUiRect& rc, int nSize, DWORD dwColor) override;
	virtual void FillEllipse(const CUiRect& rc, DWORD dwColor) override;

	virtual CUiRect MeasureText(const CUiString& strText, const CUiString& strFontId, UINT uStyle, int width = DUI_NOSET_VALUE) override;

	virtual void DrawPath(const IPath* path, const IPen* pen) override;
	virtual void FillPath(const IPath* path, const IBrush* brush) override;

private:
	HDC			m_hDC;
	int			m_saveDC;
	HBITMAP		m_hOldBitmap;

	bool		m_bTransparent;
	GdiClip		m_clip;
	GdiBitmap	m_bitmap;
};

} // namespace ui

#endif // UI_CORE_RENDER_H_
