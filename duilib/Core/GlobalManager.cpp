#include "StdAfx.h"
#include <zmouse.h>
#include <shlwapi.h>
#include "Utils/UnZip.h"

namespace ui
{

CUiString GlobalManager::m_pStrResourcePath;
std::vector<Window*> GlobalManager::m_aPreMessages;
std::map<CUiString, std::unique_ptr<WindowBuilder>> GlobalManager::m_builderMap;
CreateControlCallback GlobalManager::m_createControlCallback;

GlobalManager::MapStringToImagePtr GlobalManager::m_mImageHash;
std::map<CUiString, DWORD> GlobalManager::m_mapTextColor;
std::map<CUiString, CUiString> GlobalManager::m_mGlobalClass;
std::map<CUiString, TFontInfo*> GlobalManager::m_mCustomFonts;
CUiString GlobalManager::m_sDefaultFontId;

short GlobalManager::m_H = 180;
short GlobalManager::m_S = 100;
short GlobalManager::m_L = 100;

CUiString GlobalManager::m_strDefaultFontName;
CUiString GlobalManager::m_strDefaultDisabledColor = _T("textdefaultdisablecolor");
CUiString GlobalManager::m_strDefaultFontColor = _T("textdefaultcolor");
DWORD GlobalManager::m_dwDefaultLinkFontColor = 0xFF0000FF;
DWORD GlobalManager::m_dwDefaultLinkHoverFontColor = 0xFFD3215F;
DWORD GlobalManager::m_dwDefaultSelectedBkColor = 0xFFBAE4FF;

std::unique_ptr<IRenderFactory> GlobalManager::m_renderFactory;

static ULONG_PTR g_gdiplusToken;
static Gdiplus::GdiplusStartupInput g_gdiplusStartupInput;
static HZIP g_hzip = NULL;

void GlobalManager::Startup(LPCTSTR strResourcePath, const CreateControlCallback& callback, bool bAdaptDpi, LPCTSTR theme, LPCTSTR language)
{
	m_renderFactory = std::make_unique<RenderFactory_GdiPlus>();
	CUiString combinePath(strResourcePath);
	combinePath += theme;
	GlobalManager::SetResourcePath(combinePath);
	m_createControlCallback = callback;

	// 适配DPI
	if (bAdaptDpi) {
		DpiManager::GetInstance()->SetAdaptDPI();
		DpiManager::GetInstance()->SetScale(DpiManager::GetMainMonitorDPI());
	}

	// 解析全局资源信息
	LoadGlobalResource();

	// 加载多语言文件，如果使用了资源压缩包则从内存中加载语言文件
	CUiString lanPath(strResourcePath);
	lanPath += language;
	lanPath += _T("\\gdstrings.ini");
	if (g_hzip) {

		HGLOBAL hGlobal = GetData(lanPath);
		if (hGlobal) {
			MutiLanSupport::GetInstance()->LoadStringTable(hGlobal);
			GlobalFree(hGlobal);
		}
	}
	else {
		MutiLanSupport::GetInstance()->LoadStringTable(lanPath);
	}

	GdiplusStartup(&g_gdiplusToken, &g_gdiplusStartupInput, NULL);
	// Boot Windows Common Controls (for the ToolTip control)
	::InitCommonControls();
}

void GlobalManager::Shutdown()
{
	if (g_hzip)
	{
		CloseZip(g_hzip);
		g_hzip = NULL;
	}
	m_renderFactory.reset();
	RemoveAllFonts();
	Gdiplus::GdiplusShutdown(g_gdiplusToken);
}

CUiString GlobalManager::GetCurrentPath()
{
	TCHAR tszModule[MAX_PATH + 1] = { 0 };
	::GetCurrentDirectory(MAX_PATH, tszModule);
	return tszModule;
}

CUiString GlobalManager::GetResourcePath()
{
	return m_pStrResourcePath;
}

void GlobalManager::SetCurrentPath(LPCTSTR strPath)
{
	::SetCurrentDirectory(strPath);
}

void GlobalManager::SetResourcePath(LPCTSTR strPath)
{
	m_pStrResourcePath = strPath;
	if (m_pStrResourcePath.IsEmpty()) return;
	TCHAR cEnd = m_pStrResourcePath.GetAt(m_pStrResourcePath.GetLength() - 1);
	if (cEnd != _T('\\') && cEnd != _T('/')) m_pStrResourcePath += _T('\\');
}

void GlobalManager::LoadGlobalResource()
{
	ui::WindowBuilder dialog_builder;
	ui::Window paint_manager;
	dialog_builder.Create(_T("global.xml"), CreateControlCallback(), &paint_manager);
}

void GlobalManager::ReloadSkin(LPCTSTR resourcePath)
{
	RemoveAllFonts();
	RemoveAllTextColors();
	RemoveAllClasss();
	RemoveAllImages();

	SetResourcePath(resourcePath);
	LoadGlobalResource();

	for (auto it = m_aPreMessages.begin(); it != m_aPreMessages.end(); it++) {
		(*it)->GetRoot()->Invalidate();
	}
}

ui::IRenderFactory* GlobalManager::GetRenderFactory()
{
	return m_renderFactory.get();
}

std::unique_ptr<ui::IRenderContext> GlobalManager::CreateRenderContext()
{
	std::unique_ptr<ui::IRenderContext> p;
	p.reset(m_renderFactory->CreateRenderContext());
	return p;
}

std::unique_ptr<ui::IPen> GlobalManager::CreatePen(DWORD color, int width /*= 1*/)
{
	std::unique_ptr<ui::IPen> p;
	p.reset(m_renderFactory->CreatePen(color, width));
	return p;
}

std::unique_ptr<ui::IBrush> GlobalManager::CreateBrush(DWORD color)
{
	std::unique_ptr<ui::IBrush> p;
	p.reset(m_renderFactory->CreateBrush(color));
	return p;
}

std::unique_ptr<ui::IMatrix> GlobalManager::CreateMatrix()
{
	std::unique_ptr<ui::IMatrix> p;
	p.reset(m_renderFactory->CreateMatrix());
	return p;
}

std::unique_ptr<ui::IPath> GlobalManager::CreatePath()
{
	std::unique_ptr<ui::IPath> p;
	p.reset(m_renderFactory->CreatePath());
	return p;
}

void GlobalManager::AddClass(LPCTSTR strClassName, LPCTSTR strControlAttrList)
{
	ASSERT(!StringHelper::IsEmpty(strClassName));
	ASSERT(!StringHelper::IsEmpty(strControlAttrList));
	m_mGlobalClass[strClassName] = strControlAttrList;
}

CUiString GlobalManager::GetClassAttributes(LPCTSTR strClassName)
{
	auto it = m_mGlobalClass.find(strClassName);
	if (it != m_mGlobalClass.end()) {
		return it->second;
	}

	return _T("");
}

void GlobalManager::RemoveAllClasss()
{
	m_mGlobalClass.clear();
}

void GlobalManager::AddTextColor(LPCTSTR strName, LPCTSTR strValue)
{

	CUiString strColor = CUiString(strValue).Mid(1);
	LPTSTR pstr = NULL;
	DWORD dwBackColor = _tcstoul(strColor, &pstr, 16);

	m_mapTextColor[strName] = dwBackColor;
}

DWORD GlobalManager::GetTextColor(LPCTSTR strName)
{
	// 必须在global.xml中提前定义到颜色值
	ASSERT(m_mapTextColor[strName] != 0);
	return m_mapTextColor[strName];
}

void GlobalManager::RemoveAllTextColors()
{
	m_mapTextColor.clear();
}

std::shared_ptr<ImageInfo> GlobalManager::IsImageCached(LPCTSTR strImagePath)
{
	CUiString imageFullPath = StringHelper::ReparsePath(strImagePath);
	std::shared_ptr<ImageInfo> sharedImage;
	auto it = m_mImageHash.find(imageFullPath);
	if (it != m_mImageHash.end()) {
		sharedImage = it->second.lock();
	}

	return sharedImage;
}

std::shared_ptr<ImageInfo> GlobalManager::AddImageCached(const std::shared_ptr<ImageInfo>& sharedImage)
{
	ASSERT(m_mImageHash[sharedImage->sImageFullPath].expired() == true);
	m_mImageHash[sharedImage->sImageFullPath] = sharedImage;
	sharedImage->SetCached(true);
	return sharedImage;
}

void GlobalManager::RemoveFromImageCache(LPCTSTR imageFullPath)
{
	auto it = m_mImageHash.find(imageFullPath);
	if (it != m_mImageHash.end()) {
		m_mImageHash.erase(it);
	}
	else {
		ASSERT(FALSE);
	}
}

void GlobalManager::OnImageInfoDestroy(ImageInfo* pImageInfo)
{
	ASSERT(pImageInfo);
	if (pImageInfo && pImageInfo->IsCached()) {
		if (!pImageInfo->sImageFullPath.IsEmpty()) {
			GlobalManager::RemoveFromImageCache(pImageInfo->sImageFullPath);
		}
	}
	delete pImageInfo;
}

std::shared_ptr<ImageInfo> GlobalManager::GetImage(LPCTSTR bitmap)
{
	CUiString imageFullPath = StringHelper::ReparsePath(bitmap);
	if (IsUseZip())
	{
		imageFullPath = GetZipFilePath(imageFullPath);
	}
	std::shared_ptr<ImageInfo> sharedImage;
	auto it = m_mImageHash.find(imageFullPath);
	if (it == m_mImageHash.end()) {
		std::unique_ptr<ImageInfo> data;
		if (IsUseZip())
		{
			data = ImageInfo::LoadImage(GetData(imageFullPath), imageFullPath);
		}
		if (!data)
		{
			data = ImageInfo::LoadImage(imageFullPath);
		}
		if (!data) return sharedImage;
		sharedImage.reset(data.release(), &OnImageInfoDestroy);
		m_mImageHash[imageFullPath] = sharedImage;
		sharedImage->SetCached(true);
	}
	else {
		sharedImage = it->second.lock();
	}

	return sharedImage;
}

CUiString GlobalManager::GetDefaultFontName()
{
	return m_strDefaultFontName;
}

void GlobalManager::RemoveAllImages()
{
	for (auto it = m_aPreMessages.begin(); it != m_aPreMessages.end(); it++) {
		(*it)->GetRoot()->ClearImageCache();
	}

	m_mImageHash.clear();
}

HFONT GlobalManager::AddFont(LPCTSTR strFontId, LPCTSTR strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bDefault)
{
	CUiString strNewFontId = strFontId;
	if (strNewFontId.IsEmpty())
	{
#ifdef _UNICODE
		strNewFontId = std::to_wstring(m_mCustomFonts.size()).c_str();
#else
		strNewFontId = std::to_string(m_mCustomFonts.size()).c_str();
#endif // _UNICODE
	}

	auto iter = m_mCustomFonts.find(strNewFontId);
	ASSERT(iter == m_mCustomFonts.end());

	static bool bOsOverXp = IsWindowsVistaOrGreater();
	CUiString fontName = strFontName;
	if (fontName == _T("system")) {
		fontName = bOsOverXp ? _T("微软雅黑") : _T("新宋体");
	}

	LOGFONT lf = { 0 };
	::GetObject(::GetStockObject(DEFAULT_GUI_FONT), sizeof(LOGFONT), &lf);
	_tcscpy(lf.lfFaceName, fontName.GetData());
	lf.lfCharSet = DEFAULT_CHARSET;
	lf.lfHeight = -DpiManager::GetInstance()->ScaleInt(nSize);
	if (bBold) lf.lfWeight += FW_BOLD;
	if (bUnderline) lf.lfUnderline = TRUE;
	if (bItalic) lf.lfItalic = TRUE;
	HFONT hFont = ::CreateFontIndirect(&lf);
	if (hFont == NULL) return NULL;

	TFontInfo* pFontInfo = new TFontInfo;
	if (!pFontInfo) return false;
	pFontInfo->hFont = hFont;
	pFontInfo->sFontName = fontName;
	pFontInfo->iSize = nSize;
	pFontInfo->bBold = bBold;
	pFontInfo->bUnderline = bUnderline;
	pFontInfo->bItalic = bItalic;
	::ZeroMemory(&pFontInfo->tm, sizeof(pFontInfo->tm));

	m_mCustomFonts.insert(std::make_pair(strNewFontId, pFontInfo));

	if (bDefault) m_sDefaultFontId = strNewFontId;

	return hFont;
}

TFontInfo* GlobalManager::GetTFontInfo(LPCTSTR strFontId)
{
	CUiString strFindId = strFontId;
	if (strFindId.IsEmpty())
	{
		ASSERT(!m_sDefaultFontId.IsEmpty());
		strFindId = m_sDefaultFontId;
	}

	auto iter = m_mCustomFonts.find(strFindId);
	ASSERT(iter != m_mCustomFonts.end());

	TFontInfo* pFontInfo = static_cast<TFontInfo*>(iter->second);
	return pFontInfo;
}

HFONT GlobalManager::GetFont(LPCTSTR strFontId)
{
	TFontInfo* pFontInfo = GetTFontInfo(strFontId);
	if (pFontInfo)
		return pFontInfo->hFont;
	return nullptr;
}

HFONT GlobalManager::GetFont(LPCTSTR strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	for (auto it = m_mCustomFonts.begin(); it != m_mCustomFonts.end(); it++) {
		auto pFontInfo = it->second;
		if (pFontInfo->sFontName == strFontName && pFontInfo->iSize == nSize &&
			pFontInfo->bBold == bBold && pFontInfo->bUnderline == bUnderline && pFontInfo->bItalic == bItalic)
			return pFontInfo->hFont;
	}
	return NULL;
}

TFontInfo* GlobalManager::GetFontInfo(LPCTSTR strFontId, HDC hDcPaint)
{
	TFontInfo* pFontInfo = GetTFontInfo(strFontId);
	if (pFontInfo->tm.tmHeight == 0) {
		HFONT hOldFont = (HFONT) ::SelectObject(hDcPaint, pFontInfo->hFont);
		::GetTextMetrics(hDcPaint, &pFontInfo->tm);
		::SelectObject(hDcPaint, hOldFont);
	}
	return pFontInfo;
}

TFontInfo* GlobalManager::GetFontInfo(HFONT hFont, HDC hDcPaint)
{
	for (auto it = m_mCustomFonts.begin(); it != m_mCustomFonts.end(); it++) {
		auto pFontInfo = it->second;
		if (pFontInfo->hFont == hFont) {
			if (pFontInfo->tm.tmHeight == 0) {
				HFONT hOldFont = (HFONT) ::SelectObject(hDcPaint, pFontInfo->hFont);
				::GetTextMetrics(hDcPaint, &pFontInfo->tm);
				::SelectObject(hDcPaint, hOldFont);
			}
			return pFontInfo;
		}
	}

	ASSERT(FALSE);
	return NULL;
}

bool GlobalManager::FindFont(HFONT hFont)
{
	for (auto it = m_mCustomFonts.begin(); it != m_mCustomFonts.end(); it++) {
		auto pFontInfo = it->second;
		if (pFontInfo->hFont == hFont)
			return true;
	}
	return false;
}

bool GlobalManager::FindFont(LPCTSTR strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic)
{
	for (auto it = m_mCustomFonts.begin(); it != m_mCustomFonts.end(); it++) {
		auto pFontInfo = it->second;
		if (pFontInfo->sFontName == strFontName && pFontInfo->iSize == nSize &&
			pFontInfo->bBold == bBold && pFontInfo->bUnderline == bUnderline && pFontInfo->bItalic == bItalic)
			return true;
	}
	return false;
}

bool GlobalManager::RemoveFontAt(LPCTSTR strFontId)
{
	auto iter = m_mCustomFonts.find(strFontId);
	if (iter == m_mCustomFonts.end()) return false;

	TFontInfo* pFontInfo = static_cast<TFontInfo*>(iter->second);
	::DeleteObject(pFontInfo->hFont);
	delete pFontInfo;

	m_mCustomFonts.erase(iter);

	return true;
}

void GlobalManager::RemoveAllFonts()
{
	for (auto it = m_mCustomFonts.begin(); it != m_mCustomFonts.end(); it++) {
		auto pFontInfo = it->second;
		::DeleteObject(pFontInfo->hFont);
		delete pFontInfo;
	}
	m_mCustomFonts.clear();
}

CUiString GlobalManager::GetDefaultDisabledTextColor()
{
	return m_strDefaultDisabledColor;
}

void GlobalManager::SetDefaultDisabledTextColor(LPCTSTR strColor)
{
	m_strDefaultDisabledColor = strColor;
}

CUiString GlobalManager::GetDefaultTextColor()
{
	return m_strDefaultFontColor;
}

void GlobalManager::SetDefaultTextColor(LPCTSTR strColor)
{
	m_strDefaultFontColor = strColor;
}

DWORD GlobalManager::GetDefaultLinkFontColor()
{
	return m_dwDefaultLinkFontColor;
}

void GlobalManager::SetDefaultLinkFontColor(DWORD strColor)
{
	m_dwDefaultLinkFontColor = strColor;
}

DWORD GlobalManager::GetDefaultLinkHoverFontColor()
{
	return m_dwDefaultLinkHoverFontColor;
}

void GlobalManager::SetDefaultLinkHoverFontColor(DWORD dwColor)
{
	m_dwDefaultLinkHoverFontColor = dwColor;
}

DWORD GlobalManager::GetDefaultSelectedBkColor()
{
	return m_dwDefaultSelectedBkColor;
}

void GlobalManager::SetDefaultSelectedBkColor(DWORD dwColor)
{
	m_dwDefaultSelectedBkColor = dwColor;
}

Box* GlobalManager::CreateBox(const CUiString& strXmlPath, CreateControlCallback callback)
{
	WindowBuilder builder;
	Box* box = builder.Create(strXmlPath.GetData(), callback);
	ASSERT(box);

	return box;
}

Box* GlobalManager::CreateBoxWithCache(const CUiString& strXmlPath, CreateControlCallback callback)
{
	Box* box = nullptr;
	auto it = m_builderMap.find(strXmlPath);
	if (it == m_builderMap.end()) {
		WindowBuilder* builder = new WindowBuilder();
		box = builder->Create(strXmlPath.GetData(), callback);
		if (box) {
			m_builderMap[strXmlPath].reset(builder);
		}
		else {
			ASSERT(FALSE);
		}
	}
	else {
		box = it->second->Create(callback);
	}

	return box;
}

void GlobalManager::FillBox(Box* pUserDefinedBox, const CUiString& strXmlPath, CreateControlCallback callback)
{
	WindowBuilder winBuilder;
	Box* box = winBuilder.Create(strXmlPath.GetData(), callback, pUserDefinedBox->GetWindow(), nullptr, pUserDefinedBox);
	ASSERT(box);

	return;
}

void GlobalManager::FillBoxWithCache(Box* pUserDefinedBox, const CUiString& strXmlPath, CreateControlCallback callback)
{
	Box* box = nullptr;
	auto it = m_builderMap.find(strXmlPath);
	if (it == m_builderMap.end()) {
		WindowBuilder* winBuilder = new WindowBuilder();
		box = winBuilder->Create(strXmlPath.GetData(), callback, pUserDefinedBox->GetWindow(), nullptr, pUserDefinedBox);
		if (box) {
			m_builderMap[strXmlPath].reset(winBuilder);
		}
		else {
			ASSERT(FALSE);
		}
	}
	else {
		box = it->second->Create(callback, pUserDefinedBox->GetWindow(), nullptr, pUserDefinedBox);
	}

	return;
}

Control* GlobalManager::CreateControl(LPCTSTR strControlName)
{
	if (m_createControlCallback) {
		return m_createControlCallback(strControlName);
	}

	return nullptr;
}

bool GlobalManager::IsUseZip()
{
	return g_hzip != NULL;
}

bool GlobalManager::OpenResZip(LPCTSTR  resource_name, LPCTSTR  resource_type, const std::string& password)
{
	HRSRC   rsc = FindResource(NULL, resource_name, resource_type);
	HGLOBAL resource = LoadResource(NULL, rsc);
	DWORD   size = SizeofResource(NULL, rsc);
	if (resource && size > 0)
	{

	}

	if (g_hzip)
	{
		CloseZip(g_hzip);
		g_hzip = NULL;
	}
	g_hzip = OpenZip(resource, size, password.c_str());
	return g_hzip != NULL;
}

bool GlobalManager::OpenResZip(LPCTSTR path, const std::string& password)
{
	if (g_hzip)
	{
		CloseZip(g_hzip);
		g_hzip = NULL;
	}
	g_hzip = OpenZip(path, password.c_str());
	return g_hzip != NULL;
}

HGLOBAL GlobalManager::GetData(LPCTSTR path)
{
	HGLOBAL hGlobal = NULL;
	CUiString file_path = GetZipFilePath(path);
	if (g_hzip && !file_path.IsEmpty())
	{
		ZIPENTRY ze;
		int i = 0;
		if (FindZipItem(g_hzip, file_path, true, &i, &ze) == ZR_OK)
		{
			if (ze.index >= 0)
			{
				hGlobal = GlobalAlloc(GMEM_MOVEABLE | GMEM_NODISCARD, ze.unc_size);
				if (hGlobal)
				{
					TCHAR *pData = (TCHAR*)GlobalLock(hGlobal);
					if (pData)
					{
						ZRESULT res = UnzipItem(g_hzip, ze.index, pData, ze.unc_size);
						GlobalUnlock(hGlobal);
						if (res != ZR_OK)
						{
							GlobalFree(hGlobal);
							hGlobal = NULL;
						}
					}
					else
					{
						GlobalFree(hGlobal);
						hGlobal = NULL;
					}
				}
			}
		}
	}

	return hGlobal;
}

CUiString GlobalManager::GetZipFilePath(LPCTSTR path)
{
	return ui::PathUtil::SimplifyFilePath(path);
	/*
	CUiString file_path = path;
	file_path.Replace(_T("\\"), _T("/"));
	file_path.Replace(_T("//"), _T("/"));
	for (unsigned int i = 0; i < file_path.GetLength();)
	{
		bool start_node = false;
		if (i == 0 || file_path.GetAt(i - 1) == _T('/'))
		{
			start_node = true;
		}
		TCHAR wch = file_path.GetAt(i);
		if (start_node && wch == _T('/'))//"//"
		{
			file_path.erase(i, 1);
			continue;
		}
		if (start_node && wch == L'.')
		{
			if (i + 1 < file_path.size() && file_path.at(i + 1) == L'/')// "./"
			{
				file_path.erase(i, 2);
				continue;
			}
			else if (i + 2 < file_path.size() && file_path.at(i + 1) == L'.' && file_path.at(i + 2) == L'/')// "../"
			{
				file_path.erase(i, 2);
				int i_erase = i - 2;
				if (i_erase < 0)
				{
					ASSERT(0);
				}
				while (i_erase > 0 && file_path.at(i_erase) != L'/')
					i_erase--;
				file_path.erase(i_erase, i - i_erase);
				i = i_erase;
				continue;
			}
		}
		i++;
	}
	return file_path;
	*/
}

bool GlobalManager::ImageCacheKeyCompare::operator()(const CUiString& key1, const CUiString& key2) const
{
	int nLen1 = (int)key1.GetLength();
	int nLen2 = (int)key2.GetLength();
	if (nLen1 != nLen2)
		return nLen1 < nLen2;

	LPCTSTR pStr1Begin = key1;
	LPCTSTR pStr2Begin = key2;
	LPCTSTR pStr1End = pStr1Begin + nLen1;
	LPCTSTR pStr2End = pStr2Begin + nLen2;

	// 逆向比较
	while (--pStr1End >= pStr1Begin && --pStr2End >= pStr2Begin && *pStr1End == *pStr2End);

	// 两个串都已经比光了，那么肯定相等，返回false
	if (pStr1End < pStr1Begin) {
		return false;
	}
	return *pStr1End < *pStr2End;
}

} // namespace ui
