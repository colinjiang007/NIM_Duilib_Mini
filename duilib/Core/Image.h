#ifndef UI_CORE_IMAGEDECODE_H_
#define UI_CORE_IMAGEDECODE_H_

#pragma once

#include <GdiPlus.h>

namespace ui 
{

class UILIB_API ImageInfo
{
public:
	ImageInfo();
	~ImageInfo();

	void SetAlpha(bool bAlphaChannel) {	m_bAlphaChannel = bAlphaChannel; }
	bool IsAlpha() { return m_bAlphaChannel; }
	bool IsCached()	{ return m_bCached; }
	void SetCached(bool bCached) { m_bCached = bCached; }

	void SetPropertyItem(Gdiplus::PropertyItem* pPropertyItem);

	void PushBackHBitmap(HBITMAP hBitmap);
	HBITMAP GetHBitmap(int nIndex);
	int GetFrameCount();
	bool IsGif();
	int GetInterval(int nIndex); //����Ϊ��λ 
	 
	static std::unique_ptr<ImageInfo> LoadImage(const CUiString& strImageFullPath);
	static std::unique_ptr<ImageInfo> LoadImage(HGLOBAL hGlobal, const CUiString& imageFullPath);

private:
	static std::unique_ptr<ImageInfo> LoadImageByBitmap(std::unique_ptr<Gdiplus::Bitmap>& pGdiplusBitmap, const CUiString& imageFullPath);

public:
	int nX;
	int nY;
	CUiString sImageFullPath;

private:
	bool m_bAlphaChannel;
	bool m_bCached;
	std::unique_ptr<Gdiplus::PropertyItem> m_propertyItem;
	std::vector<HBITMAP> m_vecBitmap;
};

struct UILIB_API ImageAttribute
{
public:
	ImageAttribute();

	void Init();
	void SetImageString(LPCTSTR strImageString);
	static void ModifyAttribute(ImageAttribute& imageAttribute, LPCTSTR strImageString);

	CUiString simageString;
	CUiString sImageName;
	CUiRect rcDest;
	CUiRect rcSource;
	CUiRect rcCorner;
	BYTE bFade;
	bool bTiledX;
	bool bTiledY;
	int nPlayCount;//�����GIF����ָ�����Ŵ��� -1 ��һֱ���ţ�ȱʡֵ��
};

class UILIB_API Image
{
public:
	Image();

	bool IsValid() { return (bool)imageCache; }
	bool IsPlaying() { return m_bPlaying; }
	void SetPlaying(bool bPlaying) { m_bPlaying = bPlaying; }

	void SetImageString(LPCTSTR strImageString);
	void ClearCache();

	bool IncrementCurrentFrame();
	void SetCurrentFrame(int nCurrentFrame);
	HBITMAP GetCurrentHBitmap();
	int GetCurrentInterval();
	int GetCurrentFrameIndex();
	int GetCycledCount();
	void ClearCycledCount();
	bool ContinuePlay();
	ImageAttribute imageAttribute;
	std::shared_ptr<ImageInfo> imageCache;

private:
	int m_nCurrentFrame;
	bool m_bPlaying;
	int m_nCycledCount;//���Ŵ���
};

class UILIB_API StateImage
{
public:
	StateImage();

	void SetControl(Control* control) {	m_pControl = control; }
	Image& operator[](ControlStateType stateType) {	return m_stateImageMap[stateType]; }

	bool HasHotImage();
	bool PaintStatusImage(IRenderContext* pRender, ControlStateType stateType, const CUiString& sImageModify = _T(""));
	Image* GetEstimateImage();
	void ClearCache();

private:
	Control* m_pControl;
	std::map<ControlStateType, Image> m_stateImageMap;
};

class UILIB_API StateImageMap
{
public:
	StateImageMap()	{ }

	void SetControl(Control* control);

	void SetImage(StateImageType stateImageType, ControlStateType stateType, const CUiString& strImagePath);
	CUiString GetImagePath(StateImageType stateImageType, ControlStateType stateType);

	bool HasHotImage();
	bool PaintStatusImage(IRenderContext* pRender, StateImageType stateImageType, ControlStateType stateType, const CUiString& sImageModify = _T(""));
	Image* GetEstimateImage(StateImageType stateImageType);

	void ClearCache();

private:
	std::map<StateImageType, StateImage> m_stateImageMap;
};

class UILIB_API StateColorMap
{
public:
	StateColorMap();

	void SetControl(Control* control);
	CUiString& operator[](ControlStateType stateType) { return m_stateColorMap[stateType]; }

	bool HasHotColor();
	void PaintStatusColor(IRenderContext* pRender, CUiRect rcPaint, ControlStateType stateType);

private:
	Control* m_pControl;
	std::map<ControlStateType, CUiString> m_stateColorMap;
};

} // namespace ui

#endif // UI_CORE_IMAGEDECODE_H_
