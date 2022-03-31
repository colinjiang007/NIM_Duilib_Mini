#ifndef UI_CORE_WINDOWHELPER_H_
#define UI_CORE_WINDOWHELPER_H_

#pragma once

#include "Image.h"
#include "Window.h"

namespace ui 
{
/**
* @brief ȫ�����Թ�������
* ���ڹ���һЩȫ�����ԵĹ����࣬����ȫ����ʽ��global.xml�����������õ�
*/
class UILIB_API GlobalManager
{
public:
	/**
	 * @brief ��ʼ��ȫ�����ú���
	 * @param[in] strResourcePath ��Դ·��λ��
	 * @param[in] callback �����Զ���ؼ�ʱ��ȫ�ֻص�����
	 * @param[in] bAdaptDpi �Ƿ����� DPI ����
	 * @param[in] theme ����Ŀ¼����Ĭ��Ϊ themes\\default
	 * @param[in] language ʹ�����ԣ�Ĭ��Ϊ lang\\zh_CN
	 * @return ��
	 */
	static void Startup(const CUiString& strResourcePath, const CreateControlCallback& callback, bool bAdaptDpi, const CUiString& theme = _T("themes\\default"), const CUiString& language = _T("lang\\zh_CN"));

	/**
	 * @brief �ͷ���Դ
	 * @return ��
	 */
	static void Shutdown();

	/**
	 * @brief ��ȡ��ǰ��������Ŀ¼
	 * @return ���ص�ǰ��������Ŀ¼
	 */
	static CUiString GetCurrentPath();

	/**
	 * @brief ��ȡ��ǰ��Դ����Ŀ¼
	 * @return ���ص�ǰ��Դ����Ŀ¼
	 */
	static CUiString GetResourcePath();

	/**
	 * @brief ���ó���ǰĿ¼
	 * @param[in] strPath Ҫ���õ�·��
	 * @return ��
	 */
	static void SetCurrentPath(const CUiString& strPath);

	/**
	 * @brief ����Ƥ����Դ����Ŀ¼
	 * @param[in] strPath Ҫ���õ�·��
	 * @return ��
	 */
	static void SetResourcePath(const CUiString& strPath);

	/**
	 * @brief ���¼���Ƥ����Դ
	 * @param[in] resourcePath ��Դ·��
	 * @return ��
	 */
	static void ReloadSkin(const CUiString& resourcePath);

	/**
	 * @brief ��ȡ���ƽӿ������
	 * @return ���ؽӿ������ָ��
	 */
	static IRenderFactory* GetRenderFactory();

	/**
	 * @brief ����ȫ�ֵĻ�������������
	 * @return ���ػ����������
	 */
	static std::unique_ptr<IRenderContext> CreateRenderContext();

	/**
	 * @brief ����һ������
	 * @param[in] color ������ɫ
	 * @param[in] width ���ʿ��
	 * @return ���ػ��ʶ���
	 */
	static std::unique_ptr<IPen> CreatePen(DWORD color, int width = 1);

	/**
	 * @brief ����һ����ˢ
	 * @param[in] color ��ˢ��ɫ
	 * @return ���ػ�ˢ����
	 */
	static std::unique_ptr<IBrush> CreateBrush(DWORD color);

	/**
	 * @brief ����һ������
	 * @return ���ؾ������
	 */
	static std::unique_ptr<IMatrix> CreateMatrix();

	/**
	 * @brief ����һ������·��
	 * @return ���ػ���·������
	 */
	static std::unique_ptr<IPath> CreatePath();

	/**
	 * @brief ���һ��ȫ�� class ����
	 * @param[in] strClassName ȫ�� class ����
	 * @param[in] strControlAttrList �����б���Ҫ�� XML ת��
	 * @return ��
	 */
	static void AddClass(const CUiString& strClassName, const CUiString& strControlAttrList);

	/**
	 * @brief ��ȡһ��ȫ�� class ���Ե�ֵ
	 * @param[in] strClassName ȫ�� class ����
	 * @return �����ַ�����ʽ�� class ����ֵ
	 */
	static CUiString GetClassAttributes(const CUiString& strClassName);

	/**
	 * @brief ��ȫ��������ɾ������ class ����
	 * @return ���ػ����������
	 */
	static void RemoveAllClasss();

	/**
	 * @brief ���һ��ȫ����ɫֵ�ṩ����ʹ��
	 * @param[in] strName ��ɫ���ƣ��� white��
	 * @param[in] strValue ��ɫ������ֵ���� #FFFFFFFF��
	 * @return ��
	 */
	static void AddTextColor(const CUiString& strName, const CUiString& strValue);

	/**
	 * @brief �������ƻ�ȡһ����ɫ�ľ�����ֵ
	 * @param[in] strName Ҫ��ȡ����ɫ����
	 * @return ���� DWORD ��ʽ����ɫ����ֵ
	 */
	static DWORD GetTextColor(const CUiString& strName);

	/**
	 * @brief ɾ������ȫ����ɫ����
	 * @return ��
	 */
	static void RemoveAllTextColors();

	/**
	 * @brief ���ָ��ͼƬ�Ƿ��Ѿ�������
	 * @param[in] bitmap ͼƬ·��
	 * @return ����Ѿ������棬�򷵻� ImageInfo ������ָ�����
	 */
	static std::shared_ptr<ImageInfo> IsImageCached(const CUiString& bitmap);

	/**
	 * @brief ���һ��ͼƬ��������
	 * @param[in] shared_image
	 * @return ���ر������ ImageInfo ����ָ�����
	 */
	static std::shared_ptr<ImageInfo> AddImageCached(const std::shared_ptr<ImageInfo>& shared_image);

	/**
	 * @brief �ӻ�����һ��һ��ͼƬ
	 * @param[in] imageFullPath ͼƬ·��
	 * @return ��
	 */
	static void RemoveFromImageCache(const CUiString& imageFullPath);

	/**
	 * @brief ͼƬ�����ٵĻص�
	 * @param[in] pImageInfo ͼƬ��Ӧ�� ImageInfo ����
	 * @return ��
	 */
	static void OnImageInfoDestroy(ImageInfo *pImageInfo);

	/**
	 * @brief ��ȡͼƬ ImageInfo ����
	 * @param[in] bitmap ͼƬ·��
	 * @return ����ͼƬ ImageInfo ���������ָ��
	 */
	static std::shared_ptr<ImageInfo> GetImage(const CUiString& bitmap);

	/**
	 * @brief �ӻ�����ɾ������ͼƬ
	 * @return ��
	 */
	static void RemoveAllImages();

	/**
	 * @brief ��ȡĬ����������
	 * @return ��������
	 */
	static CUiString GetDefaultFontName();

	/**
	 * @brief ���һ������
	 * @param[in] strFontId ָ�������ID���
	 * @param[in] strFontName ��������
	 * @param[in] nSize �����С
	 * @param[in] bBold �Ƿ����
	 * @param[in] bUnderline �Ƿ����»���
	 * @param[in] bItalic �Ƿ���б
	 * @param[in] bDefault �Ƿ�Ĭ��
	 * @return ��������� HFONT ���
	 */
	static HFONT AddFont(const CUiString& strFontId, const CUiString& strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic, bool bDefault);

	/**
	 * @brief ������������һ��������Ϣ
	 * @param[in] strFontId ����ID
	 * @return ��������� TFontInfo ��Ϣ
	 */
	static TFontInfo* GetTFontInfo(const CUiString& strFontId);

	/**
	 * @brief ��������ID����һ���������
	 * @param[in] strFontId ����ID
	 * @return ��������� HFONT ���
	 */
	static HFONT GetFont(const CUiString& strFontId);
	/**
	 * @brief �����������Ի�ȡ�������
	 * @param[in] strFontName ��������
	 * @param[in] nSize �����С
	 * @param[in] bBold �Ƿ����
	 * @param[in] bUnderline �Ƿ����»���
	 * @param[in] bItalic �Ƿ���б
	 * @return ��������� HFONT ���
	 */
	static HFONT GetFont(const CUiString& strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);

	/**
	 * @brief ��ȡ������Ϣ
	 * @param[in] strFontId ����ID
	 * @param[in] hDcPaint �豸���
	 * @return ��������� TFontInfo ��Ϣ
	 */
	static TFontInfo* GetFontInfo(const CUiString& strFontId, HDC hDcPaint);

	/**
	 * @brief ��ȡ������Ϣ
	 * @param[in] hFont ���������
	 * @param[in] hDcPaint �豸���
	 * @return ��������� TFontInfo ��Ϣ
	 */
	static TFontInfo* GetFontInfo(HFONT hFont, HDC hDcPaint);

	/**
	 * @brief ��������������ָ�������Ƿ����
	 * @param[in] hFont ���������
	 * @return �����Ƿ����
	 *     @retval true ����
	 *     @retval false ������
	 */
	static bool FindFont(HFONT hFont);

	/**
	 * @brief ����������Ϣ���������Ƿ����
	 * @param[in] strFontName ��������
	 * @param[in] nSize �����С
	 * @param[in] bBold �Ƿ����
	 * @param[in] bUnderline �Ƿ����»���
	 * @param[in] bItalic �Ƿ���б
	 * @return �����Ƿ����
	 *     @retval true ����
	 *     @retval false ������
	 */
	static bool FindFont(const CUiString& strFontName, int nSize, bool bBold, bool bUnderline, bool bItalic);

	/**
	 * @brief ������������ɾ������
	 * @param[in] strFontId ����ID
	 * @return �����Ƿ�ɾ���ɹ�
	 *     @retval true ɾ���ɹ�
	 *     @retval false ���岻���ڻ�ɾ��ʧ��
	 */
	static bool RemoveFontAt(const CUiString& strFontId);

	/**
	 * @brief ɾ����������
	 * @return ��
	 */
	static void RemoveAllFonts();

	/**
	 * @brief ��ȡĬ�Ͻ���״̬��������ɫ
	 * @return Ĭ�Ͻ���״̬��ɫ���ַ�����ʾ����Ӧ global.xml ��ָ����ɫֵ
	 */
	static CUiString GetDefaultDisabledTextColor();

	/**
	 * @brief ����Ĭ�Ͻ���״̬�µ�������ɫ
	 * @param[in] dwColor ������ɫ�ַ���ֵ���� white��
	 * @return ��
	 */
	static void SetDefaultDisabledTextColor(const CUiString& strColor);

	/**
	 * @brief ��ȡĬ��������ɫ
	 * @return Ĭ��������ɫ�ַ�����ʾ����Ӧ global.xml ��ָ����ɫֵ
	 */
	static CUiString GetDefaultTextColor();

	/**
	 * @brief ����Ĭ��������ɫ
	 * @param[in] ������ɫ���ַ���ֵ����Ӧ global.xml ��ָ����ɫֵ
	 * @return ��
	 */
	static void SetDefaultTextColor(const CUiString& strColor);

	/**
	 * @brief ��ȡĬ������������ɫ
	 * @return ����������ɫ DWORD ��ʽ��ɫֵ
	 */
	static DWORD GetDefaultLinkFontColor();

	/**
	 * @brief ����Ĭ������������ɫ
	 * @param[in] dwColor Ĭ������������ɫ
	 * @return ��
	 */
	static void SetDefaultLinkFontColor(DWORD dwColor);

	/**
	 * @brief ��ȡ�������ӵ�Ĭ��������ɫ
	 * @return ���ؽ������ӵ�Ĭ��������ɫ
	 */
	static DWORD GetDefaultLinkHoverFontColor();

	/**
	 * @brief ���ý������ӵ�Ĭ��������ɫ
	 * @param[in] dwColor �������ӵ�Ĭ��������ɫ
	 * @return ��
	 */
	static void SetDefaultLinkHoverFontColor(DWORD dwColor);

	/**
	 * @brief ��ȡĬ��ѡ��״̬������ɫ
	 * @return ����Ĭ��ѡ��״̬��������ɫ
	 */
	static DWORD GetDefaultSelectedBkColor();

	/**
	 * @brief ����Ĭ��ѡ��״̬��������ɫ
	 * @param[in] dwColor ������ɫֵ
	 * @return ��
	 */
	static void SetDefaultSelectedBkColor(DWORD dwColor);

	/**
	 * @brief ���� XML ����һ�� Box
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ָ������ģ��Ķ���ָ��
	 */
	static Box* CreateBox(const CUiString& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/**
	 * @brief ���� XML �ڻ����в���ָ�� Box�����û���򴴽�
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ָ������ģ��Ķ���ָ��
	 */
	static Box* CreateBoxWithCache(const CUiString& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/**
	 * @brief ʹ�� XML ���ָ�� Box
	 * @param[in] pUserDefinedBox Ҫ���� box ָ��
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ��
	 */
	static void FillBox(Box* pUserDefinedBox, const CUiString& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/**
	 * @brief ʹ�ù������Ļ������ָ�� Box�����û�������¹���
	 * @param[in] pUserDefinedBox Ҫ���� box ָ��
	 * @param[in] strXmlPath XML �ļ�·��
	 * @param[in] callback �Զ���ؼ��Ļص�������
	 * @return ��
	 */
	static void FillBoxWithCache(Box* pUserDefinedBox, const CUiString& strXmlPath, CreateControlCallback callback = CreateControlCallback());

	/**
	 * @brief �Զ���ؼ��������ȫ�ֻص�����
	 * @param[in] strControlName �Զ���ؼ�����
	 * @return ����һ���Զ���ؼ��Ķ���ָ��
	 */
	static Control* CreateControl(const CUiString& strControlName);

	/**
	 * @brief �жϵ�ǰ�Ƿ�ʹ���� zip ѹ����
	 * @return ���� true ��ʾʹ���� zip ѹ������Ϊ��Դ��false Ϊ��ͨĿ¼ģʽ
	 */
	static bool IsUseZip();

	/**
	 * @brief ��һ���ڴ�ѹ������Դ
	 * @param[in] resource_name ��Դ���ƣ��� MAKEINTRESOURCE ������
	 * @param[in] resource_type ��Դ���ͣ��Զ��嵼�����Դ��������
	 * @param[in] password ѹ��������
	 * @return ���� true �򿪳ɹ������� false Ϊ��ʧ��
	 */
	static bool OpenResZip(LPCTSTR  resource_name, LPCTSTR  resource_type, const std::string& password);

	/**
	 * @brief ��һ�������ļ�ѹ������Դ
	 * @param[in] path ѹ�����ļ�·��
	 * @param[in] password ѹ��������
	 * @return ���� true �򿪳ɹ������� false Ϊ��ʧ��
	 */
	static bool OpenResZip(const CUiString& path, const std::string& password);

	/**
	 * @brief ��ȡѹ�����е����ݵ��ڴ�
	 * @param[in] path Ҫ��ȡ���ļ���·��
	 * @return �����ļ����ڴ��ַ
	 */
	static HGLOBAL GetData(const CUiString& path);

	/**
	 * @brief ��ȡ�ļ���ѹ�����е�λ��
	 * @param[in] path Ҫ��ȡ���ļ�·��
	 * @return ������ѹ�����е��ļ�λ��
	 */
	static CUiString GetZipFilePath(const CUiString& path);

private:
	/**
	 * @brief ����ȫ����Դ
	 * @return ��
	 */
	static void LoadGlobalResource();

private:
	static std::unique_ptr<IRenderFactory> m_renderFactory;
	class ImageCacheKeyCompare
	{
	public:
		// ����ȽϺ������ǱȽ��ֵ���ģ����ǰ������·���
		// ���ȱȽϣ�����С�ĸ�С
		// ������Ƚϣ�������Ϊ�������ֵ���
		bool operator()(const CUiString& key1, const CUiString& key2) const;
	};
	typedef std::map<CUiString, std::weak_ptr<ImageInfo>, ImageCacheKeyCompare> MapStringToImagePtr;

	static CUiString m_pStrResourcePath; //ȫ�ֵ���Դ·����������ʱ���޸��������
	static std::vector<Window*> m_aPreMessages;
	static std::map<CUiString, std::unique_ptr<WindowBuilder>> m_builderMap;
	static CreateControlCallback m_createControlCallback;

	static MapStringToImagePtr m_mImageHash;
	static std::map<CUiString, DWORD> m_mapTextColor;
	static std::map<CUiString, CUiString> m_mGlobalClass;
	static std::map<CUiString, TFontInfo*> m_mCustomFonts;

	static CUiString m_sDefaultFontId;

	static short m_H;
	static short m_S;
	static short m_L;

	static CUiString m_strDefaultFontName;
	static CUiString m_strDefaultDisabledColor;
	static CUiString m_strDefaultFontColor;
	static DWORD m_dwDefaultLinkFontColor;
	static DWORD m_dwDefaultLinkHoverFontColor;
	static DWORD m_dwDefaultSelectedBkColor;
};

} // namespace ui

#endif // UI_CORE_WINDOWHELPER_H_
