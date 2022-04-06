#ifndef UI_RENDER_IRENDER_H_
#define UI_RENDER_IRENDER_H_

#pragma once

namespace ui 
{

class UILIB_API IClip : public ui::SupportWeakCallback
{
public:
	virtual void CreateClip(HDC hDC, CUiRect rc) = 0;
	virtual void CreateRoundClip(HDC hDC, CUiRect rc, int width, int height) = 0;
	virtual void ClearClip(HDC hDC) = 0;
};

class IRenderContext;
class UILIB_API AutoClip : public ui::SupportWeakCallback
{
public:
	AutoClip(IRenderContext* pRender, const CUiRect& rc, bool bClip = true);
	AutoClip(IRenderContext* pRender, const CUiRect& rcRound, int width, int height, bool bClip = true);
	~AutoClip();

private:
	IRenderContext *m_pRender;
	bool			m_bClip;
};

class UILIB_API IBitmap : public ui::SupportWeakCallback
{
	virtual bool Init(HDC hSrcDC, int width, int height, bool flipBItmap) = 0;
	virtual void Clear() = 0;
	virtual HBITMAP DetachBitmap() = 0;

	virtual HBITMAP GetBitmap() = 0;
	virtual BYTE* GetBits() = 0;
	virtual int	GetWidth() = 0;
	virtual int GetHeight() = 0;

	virtual void ClearAlpha(const CUiRect& rcDirty, int alpha) = 0;
	virtual void RestoreAlpha(const CUiRect& rcDirty, const CUiRect& rcShadowPadding, int alpha) = 0;
};

class UILIB_API IPen : public ui::SupportWeakCallback
{
public:
	IPen(DWORD color, int width = 1) : color_(color) {};
	IPen(const IPen& r) : color_(r.color_) {};
	IPen& operator=(const IPen& r) = delete;

	virtual IPen* Clone() = 0;

	virtual void SetWidth(int width) = 0;
	virtual int GetWidth() = 0;
	virtual void SetColor(DWORD color) = 0;
	virtual DWORD GetColor() { return color_; };

	enum LineCap
	{
		LineCapFlat = 0,
		LineCapSquare = 1,
		LineCapRound = 2,
		LineCapTriangle = 3
	};
	virtual void SetStartCap(LineCap cap) = 0;
	virtual void SetEndCap(LineCap cap) = 0;
	virtual void SetDashCap(LineCap cap) = 0;
	virtual LineCap GetStartCap() = 0;
	virtual LineCap GetEndCap() = 0;
	virtual LineCap GetDashCap() = 0;

	enum LineJoin
	{
		LineJoinMiter = 0,
		LineJoinBevel = 1,
		LineJoinRound = 2,
		LineJoinMiterClipped = 3
	};
	virtual void SetLineJoin(LineJoin join) = 0;
	virtual LineJoin GetLineJoin() = 0;

	enum DashStyle
	{
		DashStyleSolid,          // 0
		DashStyleDash,           // 1
		DashStyleDot,            // 2
		DashStyleDashDot,        // 3
		DashStyleDashDotDot,     // 4
		DashStyleCustom          // 5
	};
	virtual void SetDashStyle(DashStyle style) = 0;
	virtual DashStyle GetDashStyle() = 0;

protected:
	DWORD color_ = 0;
};

class UILIB_API IBrush : public ui::SupportWeakCallback
{
public:
	IBrush(DWORD color) : color_(color){};
	IBrush(HBITMAP bitmap) {};
	IBrush(const IBrush& r)	: color_(r.color_)	{};
	IBrush& operator=(const IBrush& r) = delete;

	virtual IBrush* Clone() = 0;

	virtual DWORD GetColor() { return color_; };
	virtual IBitmap* GetBitmap() { return bitmap_.get(); };

protected:
	DWORD color_ = 0;
	std::unique_ptr<IBitmap> bitmap_;
};

class UILIB_API IMatrix : public ui::SupportWeakCallback
{
public:
	virtual void Translate(int offsetX, int offsetY) = 0;
	virtual void Scale(int scaleX, int scaleY) = 0;
	virtual void Rotate(float angle) = 0;
	virtual void RotateAt(float angle, const CUiPoint& center) = 0;
};

class UILIB_API IPath : public ui::SupportWeakCallback
{
public:
	IPath(){};
	IPath(const IPath& r){};
	IPath& operator=(const IPath& r) = delete;

	virtual IPath* Clone() = 0;
	virtual void Reset() = 0;

	enum FillMode
	{
		FillModeAlternate,        // 0
		FillModeWinding           // 1
	};
	virtual void SetFillMode(FillMode mode) = 0;
	virtual FillMode GetFillMode() = 0;

	virtual void StartFigure() = 0;
	virtual void CloseFigure() = 0;

	virtual void AddLine(int x1, int y1, int x2, int y2) = 0;
	virtual void AddLines(const CUiPoint* points, int count) = 0;
	virtual void AddBezier(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) = 0;
	virtual void AddCurve(const CUiPoint* points, int count) = 0;
	virtual void AddRect(int left, int top, int right, int bottom) = 0;
	virtual void AddRect(const CUiRect& rect) = 0;
	virtual void AddEllipse(int left, int top, int right, int bottom) = 0;
	virtual void AddEllipse(const CUiRect& rect) = 0;
	virtual void AddArc(int x, int y, int width, int height, float startAngle, float sweepAngle) = 0;
	virtual void AddPie(int x, int y, int width, int height, float startAngle, float sweepAngle) = 0;
	virtual void AddPolygon(const CUiPoint* points, int count) = 0;

	virtual CUiRect GetBound(const IPen* pen) = 0;
	virtual bool IsContainsPoint(int x, int y) = 0;
	virtual bool IsStrokeContainsPoint(int x, int y, const IPen* pen) = 0;

	virtual void Transform(const IMatrix* matrix) = 0;
};

class UILIB_API IRenderContext : public ui::SupportWeakCallback
{
public:
	virtual HDC GetDC() = 0;
	virtual bool Resize(int width, int height, bool flipBItmap = true) = 0;
	virtual void Clear() = 0;
	virtual std::unique_ptr<IRenderContext> Clone() = 0;

	virtual HBITMAP DetachBitmap() = 0;
	virtual BYTE* GetBits() = 0;
	virtual int	GetWidth() = 0;
	virtual int GetHeight() = 0;
	virtual void ClearAlpha(const CUiRect& rcDirty, int alpha = 0) = 0;
	virtual void RestoreAlpha(const CUiRect& rcDirty, const CUiRect& rcShadowPadding = CUiRect(), int alpha = 0) = 0;

	virtual bool IsRenderTransparent() const = 0;
	virtual bool SetRenderTransparent(bool bTransparent) = 0;

	virtual void Save() = 0;
	virtual void Restore() = 0;
	virtual CUiPoint OffsetWindowOrg(CUiPoint ptOffset) = 0;
	virtual CUiPoint SetWindowOrg(CUiPoint ptOffset) = 0;
	virtual CUiPoint GetWindowOrg() const = 0;

	virtual void SetClip(const CUiRect& rc) = 0;
	virtual void SetRoundClip(const CUiRect& rcItem, int width, int height) = 0;
	virtual void ClearClip() = 0;

	virtual HRESULT BitBlt(int x, int y, int cx, int cy, HDC hdcSrc, int xSrc = 0, int yScr = 0, DWORD rop = SRCCOPY) = 0;
	virtual bool AlphaBlend(int xDest, int yDest, int widthDest, int heightDest, HDC hdcSrc, int xSrc, int yScr, int widthSrc, int heightSrc, BYTE uFade = 255) = 0;

	virtual void DrawImage(const CUiRect& rcPaint, HBITMAP hBitmap, bool bAlphaChannel,
		const CUiRect& rcImageDest, const CUiRect& rcImageSource, const CUiRect& rcCorners, BYTE uFade = 255, bool xtiled = false, bool ytiled = false) = 0;

	virtual void DrawColor(const CUiRect& rc, DWORD dwColor, BYTE uFade = 255) = 0;
	virtual void DrawColor(const CUiRect& rc, const CUiString& colorStr, BYTE uFade = 255) = 0;

	virtual void DrawLine(const CUiRect& rc, int nSize, DWORD dwPenColor) = 0;
	virtual void DrawLine(const IPen* pen, int x1, int y1, int x2, int y2) = 0;
	virtual void DrawBezier(const IPen* pen, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) = 0;
	virtual void DrawRect(const CUiRect& rc, int nSize, DWORD dwPenColor) = 0;
	virtual void DrawRoundRect(const CUiRect& rc, const CUiSize& roundSize, int nSize, DWORD dwPenColor) = 0;

	virtual void DrawText(const CUiRect& rc, const CUiString& strText, DWORD dwTextColor, const CUiString& strFontId, UINT uStyle, BYTE uFade = 255, bool bLineLimit = false) = 0;

	virtual void DrawEllipse(const CUiRect& rc, int nSize, DWORD dwColor) = 0;
	virtual void FillEllipse(const CUiRect& rc, DWORD dwColor) = 0;

	virtual CUiRect MeasureText(const CUiString& strText, const CUiString& strFontId, UINT uStyle, int width = DUI_NOSET_VALUE) = 0;

	virtual void DrawPath(const IPath* path, const IPen* pen) = 0;
	virtual void FillPath(const IPath* path, const IBrush* brush) = 0;
};

class UILIB_API IRenderFactory
{
public:
	virtual ui::IPen* CreatePen(DWORD color, int width = 1) = 0;
	virtual ui::IBrush* CreateBrush(DWORD corlor) = 0;
	virtual ui::IBrush* CreateBrush(HBITMAP bitmap) = 0;
	virtual ui::IMatrix* CreateMatrix() = 0;
	virtual ui::IPath* CreatePath() = 0;
	virtual ui::IBitmap* CreateBitmap() = 0;
	virtual ui::IRenderContext* CreateRenderContext() = 0;
};

} // namespace ui

#endif // UI_RENDER_IRENDER_H_
