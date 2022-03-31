#include "StdAfx.h"
#include "Utils.h"
namespace ui
{
	/////////////////////////////////////////////////////////////////////////////////////
	//
	//

	CUiString::CUiString() : m_pstr(m_szBuffer)
	{
		m_szBuffer[0] = _T('\0');
	}

	CUiString::CUiString(const TCHAR ch) : m_pstr(m_szBuffer)
	{
		m_szBuffer[0] = ch;
		m_szBuffer[1] = _T('\0');
	}

	CUiString::CUiString(LPCTSTR lpsz, int nLen) : m_pstr(m_szBuffer)
	{
		ASSERT(!::IsBadStringPtr(lpsz, -1) || lpsz == NULL);
		m_szBuffer[0] = _T('\0');
		Assign(lpsz, nLen);
	}

	CUiString::CUiString(const CUiString& src) : m_pstr(m_szBuffer)
	{
		m_szBuffer[0] = _T('\0');
		Assign(src.m_pstr);
	}

	CUiString::~CUiString()
	{
		if (m_pstr != m_szBuffer) free(m_pstr);
	}

	CUiString CUiString::ToString()
	{
		return m_pstr;
	}

	int CUiString::GetLength() const
	{
		return (int)_tcslen(m_pstr);
	}

	CUiString::operator LPCTSTR() const
	{
		return m_pstr;
	}

	void CUiString::Append(LPCTSTR pstr)
	{
		int nNewLength = GetLength() + (int)_tcslen(pstr);
		if (nNewLength >= MAX_LOCAL_STRING_LEN) {
			if (m_pstr == m_szBuffer) {
				m_pstr = static_cast<LPTSTR>(malloc((nNewLength + 1) * sizeof(TCHAR)));
				_tcscpy(m_pstr, m_szBuffer);
				_tcscat(m_pstr, pstr);
			}
			else {
				m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (nNewLength + 1) * sizeof(TCHAR)));
				_tcscat(m_pstr, pstr);
			}
		}
		else {
			if (m_pstr != m_szBuffer) {
				free(m_pstr);
				m_pstr = m_szBuffer;
			}
			_tcscat(m_szBuffer, pstr);
		}
	}

	void CUiString::Assign(LPCTSTR pstr, int cchMax)
	{
		if (pstr == NULL) pstr = _T("");
		cchMax = (cchMax < 0 ? (int)_tcslen(pstr) : cchMax);
		if (cchMax < MAX_LOCAL_STRING_LEN) {
			if (m_pstr != m_szBuffer) {
				free(m_pstr);
				m_pstr = m_szBuffer;
			}
		}
		else if (cchMax > GetLength() || m_pstr == m_szBuffer) {
			if (m_pstr == m_szBuffer) m_pstr = NULL;
			m_pstr = static_cast<LPTSTR>(realloc(m_pstr, (cchMax + 1) * sizeof(TCHAR)));
		}
		_tcsncpy(m_pstr, pstr, cchMax);
		m_pstr[cchMax] = _T('\0');
	}

	bool CUiString::IsEmpty() const
	{
		return m_pstr[0] == _T('\0');
	}

	void CUiString::Empty()
	{
		if (m_pstr != m_szBuffer) free(m_pstr);
		m_pstr = m_szBuffer;
		m_szBuffer[0] = _T('\0');
	}

	LPCTSTR CUiString::GetData() const
	{
		return m_pstr;
	}

	TCHAR CUiString::GetAt(int nIndex) const
	{
		return m_pstr[nIndex];
	}

	TCHAR CUiString::operator[] (int nIndex) const
	{
		return m_pstr[nIndex];
	}

	const CUiString& CUiString::operator=(const CUiString& src)
	{
		Assign(src);
		return *this;
	}

	const CUiString& CUiString::operator=(LPCTSTR lpStr)
	{
		if (lpStr)
		{
			ASSERT(!::IsBadStringPtr(lpStr, -1));
			Assign(lpStr);
		}
		else
		{
			Empty();
		}
		return *this;
	}

#ifdef _UNICODE

	const CUiString& CUiString::operator=(LPCSTR lpStr)
	{
		if (lpStr)
		{
			ASSERT(!::IsBadStringPtrA(lpStr, -1));
			int cchStr = (int)strlen(lpStr) + 1;
			LPWSTR pwstr = (LPWSTR)_alloca(cchStr);
			if (pwstr != NULL) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr);
			Assign(pwstr);
		}
		else
		{
			Empty();
		}
		return *this;
	}

	const CUiString& CUiString::operator+=(LPCSTR lpStr)
	{
		if (lpStr)
		{
			ASSERT(!::IsBadStringPtrA(lpStr, -1));
			int cchStr = (int)strlen(lpStr) + 1;
			LPWSTR pwstr = (LPWSTR)_alloca(cchStr);
			if (pwstr != NULL) ::MultiByteToWideChar(::GetACP(), 0, lpStr, -1, pwstr, cchStr);
			Append(pwstr);
		}

		return *this;
	}

#else

	const CUiString& CUiString::operator=(LPCWSTR lpwStr)
	{
		if (lpwStr)
		{
			ASSERT(!::IsBadStringPtrW(lpwStr, -1));
			int cchStr = ((int)wcslen(lpwStr) * 2) + 1;
			LPSTR pstr = (LPSTR)_alloca(cchStr);
			if (pstr != NULL) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
			Assign(pstr);
		}
		else
		{
			Empty();
		}

		return *this;
	}

	const CUiString& CUiString::operator+=(LPCWSTR lpwStr)
	{
		if (lpwStr)
		{
			ASSERT(!::IsBadStringPtrW(lpwStr, -1));
			int cchStr = ((int)wcslen(lpwStr) * 2) + 1;
			LPSTR pstr = (LPSTR)_alloca(cchStr);
			if (pstr != NULL) ::WideCharToMultiByte(::GetACP(), 0, lpwStr, -1, pstr, cchStr, NULL, NULL);
			Append(pstr);
		}

		return *this;
	}

#endif // _UNICODE

	const CUiString& CUiString::operator=(const TCHAR ch)
	{
		Empty();
		m_szBuffer[0] = ch;
		m_szBuffer[1] = _T('\0');
		return *this;
	}

	CUiString CUiString::operator+(const CUiString& src) const
	{
		CUiString sTemp = *this;
		sTemp.Append(src);
		return sTemp;
	}

	CUiString CUiString::operator+(LPCTSTR lpStr) const
	{
		if (lpStr)
		{
			ASSERT(!::IsBadStringPtr(lpStr, -1));
			CUiString sTemp = *this;
			sTemp.Append(lpStr);
			return sTemp;
		}

		return *this;
	}

	const CUiString& CUiString::operator+=(const CUiString& src)
	{
		Append(src);
		return *this;
	}

	const CUiString& CUiString::operator+=(LPCTSTR lpStr)
	{
		if (lpStr)
		{
			ASSERT(!::IsBadStringPtr(lpStr, -1));
			Append(lpStr);
		}

		return *this;
	}

	const CUiString& CUiString::operator+=(const TCHAR ch)
	{
		TCHAR str[] = { ch, _T('\0') };
		Append(str);
		return *this;
	}

	bool CUiString::operator == (LPCTSTR str) const { return (Compare(str) == 0); };
	bool CUiString::operator != (LPCTSTR str) const { return (Compare(str) != 0); };
	bool CUiString::operator <= (LPCTSTR str) const { return (Compare(str) <= 0); };
	bool CUiString::operator <  (LPCTSTR str) const { return (Compare(str) < 0); };
	bool CUiString::operator >= (LPCTSTR str) const { return (Compare(str) >= 0); };
	bool CUiString::operator >  (LPCTSTR str) const { return (Compare(str) > 0); };

	void CUiString::SetAt(int nIndex, TCHAR ch)
	{
		ASSERT(nIndex >= 0 && nIndex < GetLength());
		m_pstr[nIndex] = ch;
	}

	int CUiString::Compare(LPCTSTR lpsz) const
	{
		return _tcscmp(m_pstr, lpsz);
	}

	int CUiString::CompareNoCase(LPCTSTR lpsz) const
	{
		return _tcsicmp(m_pstr, lpsz);
	}

	void CUiString::MakeUpper()
	{
		_tcsupr(m_pstr);
	}

	void CUiString::MakeLower()
	{
		_tcslwr(m_pstr);
	}

	CUiString CUiString::Left(int iLength) const
	{
		if (iLength < 0) iLength = 0;
		if (iLength > GetLength()) iLength = GetLength();
		return CUiString(m_pstr, iLength);
	}

	CUiString CUiString::Mid(int iPos, int iLength) const
	{
		if (iLength < 0) iLength = GetLength() - iPos;
		if (iPos + iLength > GetLength()) iLength = GetLength() - iPos;
		if (iLength <= 0) return CUiString();
		return CUiString(m_pstr + iPos, iLength);
	}

	CUiString CUiString::Right(int iLength) const
	{
		int iPos = GetLength() - iLength;
		if (iPos < 0) {
			iPos = 0;
			iLength = GetLength();
		}
		return CUiString(m_pstr + iPos, iLength);
	}

	int CUiString::Find(TCHAR ch, int iPos /*= 0*/) const
	{
		ASSERT(iPos >= 0 && iPos <= GetLength());
		if (iPos != 0 && (iPos < 0 || iPos >= GetLength())) return -1;
		LPCTSTR p = _tcschr(m_pstr + iPos, ch);
		if (p == NULL) return -1;
		return (int)(p - m_pstr);
	}

	int CUiString::Find(LPCTSTR pstrSub, int iPos /*= 0*/) const
	{
		ASSERT(!::IsBadStringPtr(pstrSub, -1));
		ASSERT(iPos >= 0 && iPos <= GetLength());
		if (iPos != 0 && (iPos < 0 || iPos > GetLength())) return -1;
		LPCTSTR p = _tcsstr(m_pstr + iPos, pstrSub);
		if (p == NULL) return -1;
		return (int)(p - m_pstr);
	}

	int CUiString::ReverseFind(TCHAR ch) const
	{
		LPCTSTR p = _tcsrchr(m_pstr, ch);
		if (p == NULL) return -1;
		return (int)(p - m_pstr);
	}

	int CUiString::Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo)
	{
		CUiString sTemp;
		int nCount = 0;
		int iPos = Find(pstrFrom);
		if (iPos < 0) return 0;
		int cchFrom = (int)_tcslen(pstrFrom);
		int cchTo = (int)_tcslen(pstrTo);
		while (iPos >= 0) {
			sTemp = Left(iPos);
			sTemp += pstrTo;
			sTemp += Mid(iPos + cchFrom);
			Assign(sTemp);
			iPos = Find(pstrFrom, iPos + cchTo);
			nCount++;
		}
		return nCount;
	}

	int CUiString::Format(LPCTSTR pstrFormat, ...)
	{
		LPTSTR szSprintf = NULL;
		va_list argList;
		int nLen;
		va_start(argList, pstrFormat);
		nLen = _vsntprintf(NULL, 0, pstrFormat, argList);
		szSprintf = (TCHAR*)malloc((nLen + 1) * sizeof(TCHAR));
		ZeroMemory(szSprintf, (nLen + 1) * sizeof(TCHAR));
		int iRet = _vsntprintf(szSprintf, nLen + 1, pstrFormat, argList);
		va_end(argList);
		Assign(szSprintf);
		free(szSprintf);
		return iRet;
	}

	int CUiString::SmallFormat(LPCTSTR pstrFormat, ...)
	{
		CUiString sFormat = pstrFormat;
		TCHAR szBuffer[64] = { 0 };
		va_list argList;
		va_start(argList, pstrFormat);
		int iRet = ::wvsprintf(szBuffer, sFormat, argList);
		va_end(argList);
		Assign(szBuffer);
		return iRet;
	}


}// namespace ui
