#include "StdAfx.h"

namespace ui 
{

MutiLanSupport* MutiLanSupport::GetInstance()
{
	static MutiLanSupport mutiLanSupport;
	return &mutiLanSupport;
}

bool MutiLanSupport::LoadStringTable(LPCTSTR strFilePath)
{
	ClearAll();

	FILE *hFile;
	_tfopen_s(&hFile, strFilePath, _T("r"));
	if (hFile == NULL) {
		return false;
	}

	char strRead[4096];
	std::vector<CUiString> stringList;
	CUiString strResource;

	while (fgets(strRead, 4096, hFile) != NULL)
	{
		std::string src = strRead;
		StringHelper::Utf8ToCUiString(src.c_str(), strResource);
		strResource.Trim();
		if (!strResource.IsEmpty()) {
			stringList.push_back(strResource);
		}
	}
	fclose(hFile);

	AnalyzeStringTable(stringList);
	return true;
}

bool MutiLanSupport::LoadStringTable(const HGLOBAL& hGlobal)
{
	std::vector<CUiString> string_list;
	std::string fragment((LPSTR)GlobalLock(hGlobal), GlobalSize(hGlobal));
	fragment.append("\n");
	std::string src;
	CUiString string_resourse;
	for (auto& it : fragment)
	{
		if (it == '\0' || it == '\n')
		{
			StringHelper::Utf8ToCUiString(src, string_resourse);
			string_resourse.Trim();
			if (!string_resourse.IsEmpty())
			{
				string_list.push_back(string_resourse);
			}
			src.clear();
			continue;
		}
		src.push_back(it);
	}

	GlobalUnlock(hGlobal);
	AnalyzeStringTable(string_list);

	return true;
}

CUiString MutiLanSupport::GetStringViaID(LPCTSTR id)
{
	CUiString text;
	if(StringHelper::IsEmpty(id))
		return text;

	auto it = m_stringTable.find(id);
	if (it == m_stringTable.end()) {
		ASSERT(FALSE);
		return text;
	}
	else {
		text = it->second;
	}

	return text;
}

bool MutiLanSupport::AnalyzeStringTable(const std::vector<CUiString> &list)
{
	int	nCount = (int)list.size();
	if (nCount <= 0)
		return false;
	
	CUiString key, value;
	for(int i = 0; i < nCount; i++)
	{
		const CUiString& strSrc = list[i];
		bool isValid = StringHelper::SplitCUiStringKeyValue(strSrc, _T("="), key,value);
		if (!isValid) {
			continue;
		}
		key.Trim();
		value.Trim();
		if (key.Find(_T(";")) == -1) {
			value.Replace(_T("\\r"), _T("\r"));
			value.Replace(_T("\\n"), _T("\n"));
			m_stringTable[key] = value;
		}
	}

	return true;
}

void MutiLanSupport::ClearAll()
{
	m_stringTable.clear();
}

}