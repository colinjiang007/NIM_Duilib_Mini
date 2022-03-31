#ifndef UI_UTILS_UTILS_H_
#define UI_UTILS_UTILS_H_

#pragma once

#include <oaidl.h> // for VARIANT

namespace ui
{

/////////////////////////////////////////////////////////////////////////////////////
//

class STRINGorID
{
public:
	STRINGorID(LPCTSTR lpString) : m_lpstr(lpString)
	{
	
	}

	STRINGorID(UINT nID) : m_lpstr(MAKEINTRESOURCE(nID))
	{
	
	}

	LPCTSTR m_lpstr;
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CUiPoint : public tagPOINT
{
public:
	CUiPoint()
	{
		x = y = 0;
	}

	CUiPoint(const POINT& src)
	{
		x = src.x;
		y = src.y;
	}

	CUiPoint(int _x, int _y)
	{
		x = _x;
		y = _y;
	}

	CUiPoint(LPARAM lParam)
	{
		x = GET_X_LPARAM(lParam);
		y = GET_Y_LPARAM(lParam);
	}

	void Offset(int offsetX, int offsetY)
	{
		x += offsetX;
		y += offsetY;
	}

	void Offset(CUiPoint offsetPoint)
	{
		x += offsetPoint.x;
		y += offsetPoint.y;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CUiSize : public tagSIZE
{
public:
	CUiSize()
	{
		cx = cy = 0;
	}

	CUiSize(const CUiSize& src)
	{
		cx = src.cx;
		cy = src.cy;
	}

	CUiSize(int _cx, int _cy)
	{
		cx = _cx;
		cy = _cy;
	}

	void Offset(int offsetCX, int offsetCY)
	{
		cx += offsetCX;
		cy += offsetCY;
	}

	void Offset(CUiSize offsetPoint)
	{
		cx += offsetPoint.cx;
		cy += offsetPoint.cy;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CUiRect : public tagRECT
{
public:
	CUiRect()
	{
		left = top = right = bottom = 0;
	}

	CUiRect(const RECT& src)
	{
		left = src.left;
		top = src.top;
		right = src.right;
		bottom = src.bottom;
	}

	CUiRect(int iLeft, int iTop, int iRight, int iBottom)
	{
		left = iLeft;
		top = iTop;
		right = iRight;
		bottom = iBottom;
	}

	int GetWidth() const
	{
		return right - left;
	}

	int GetHeight() const
	{
		return bottom - top;
	}

	void Clear()
	{
		left = top = right = bottom = 0;
	}

	bool IsRectEmpty() const
	{
		return ::IsRectEmpty(this) == TRUE; 
	}

	void ResetOffset()
	{
		::OffsetRect(this, -left, -top);
	}

	void Normalize()
	{
		if( left > right ) { int iTemp = left; left = right; right = iTemp; }
		if( top > bottom ) { int iTemp = top; top = bottom; bottom = iTemp; }
	}

	void Offset(int cx, int cy)
	{
		::OffsetRect(this, cx, cy);
	}

	void Offset(const CUiPoint& offset)
	{
		::OffsetRect(this, offset.x, offset.y);
	}

	void Inflate(int cx, int cy)
	{
		::InflateRect(this, cx, cy);
	}

	void Inflate(const CUiRect& rect)
	{
		this->left -= rect.left;
		this->top -= rect.top;
		this->right += rect.right;
		this->bottom += rect.bottom;
	}

	void Deflate(int cx, int cy)
	{
		::InflateRect(this, -cx, -cy);
	}

	void Deflate(const CUiRect& rect)
	{
		this->left += rect.left;
		this->top += rect.top;
		this->right -= rect.right;
		this->bottom -= rect.bottom;
	}

	void Union(const CUiRect& rc)
	{
		::UnionRect(this, this, &rc);
	}

	void Intersect(const CUiRect& rc)
	{
		::IntersectRect(this, this, &rc);
	}

	void Subtract(const CUiRect& rc)
	{
		::SubtractRect(this, this, &rc);
	}

	bool IsPointIn(const CUiPoint& point) const
	{
		return ::PtInRect(this, point) == TRUE;
	}

	bool Equal(const CUiRect& rect) const
	{
		return this->left == rect.left && this->top == rect.top 
			&& this->right == rect.right && this->bottom == rect.bottom;
	}
};

/////////////////////////////////////////////////////////////////////////////////////
//

class UILIB_API CUiString
{
public:
	enum { MAX_LOCAL_STRING_LEN = 127 };

	CUiString();
	CUiString(const TCHAR ch);
	CUiString(const CUiString& src);
	CUiString(LPCTSTR lpsz, int nLen = -1);
	~CUiString();
	CUiString ToString();

	void Empty();
	int GetLength() const;
	bool IsEmpty() const;
	TCHAR GetAt(int nIndex) const;
	void Append(LPCTSTR pstr);
	void Assign(LPCTSTR pstr, int nLength = -1);
	LPCTSTR GetData() const;

	void SetAt(int nIndex, TCHAR ch);
	operator LPCTSTR() const;

	TCHAR operator[] (int nIndex) const;
	const CUiString& operator=(const CUiString& src);
	const CUiString& operator=(const TCHAR ch);
	const CUiString& operator=(LPCTSTR pstr);
#ifdef _UNICODE
	const CUiString& CUiString::operator=(LPCSTR lpStr);
	const CUiString& CUiString::operator+=(LPCSTR lpStr);
#else
	const CUiString& CUiString::operator=(LPCWSTR lpwStr);
	const CUiString& CUiString::operator+=(LPCWSTR lpwStr);
#endif
	CUiString operator+(const CUiString& src) const;
	CUiString operator+(LPCTSTR pstr) const;
	const CUiString& operator+=(const CUiString& src);
	const CUiString& operator+=(LPCTSTR pstr);
	const CUiString& operator+=(const TCHAR ch);

	bool operator == (LPCTSTR str) const;
	bool operator != (LPCTSTR str) const;
	bool operator <= (LPCTSTR str) const;
	bool operator <  (LPCTSTR str) const;
	bool operator >= (LPCTSTR str) const;
	bool operator >  (LPCTSTR str) const;

	int Compare(LPCTSTR pstr) const;
	int CompareNoCase(LPCTSTR pstr) const;

	void MakeUpper();
	void MakeLower();

	CUiString Left(int nLength) const;
	CUiString Mid(int iPos, int nLength = -1) const;
	CUiString Right(int nLength) const;

	void Trim();
	void TrimLeft();
	void TrimRight();

	int Find(TCHAR ch, int iPos = 0) const;
	int Find(LPCTSTR pstr, int iPos = 0) const;
	int ReverseFind(TCHAR ch) const;
	int Replace(LPCTSTR pstrFrom, LPCTSTR pstrTo);

	int __cdecl Format(LPCTSTR pstrFormat, ...);
	int __cdecl SmallFormat(LPCTSTR pstrFormat, ...);

protected:
	LPTSTR m_pstr;
	TCHAR m_szBuffer[MAX_LOCAL_STRING_LEN + 1];
};
/////////////////////////////////////////////////////////////////////////////////////
//

class CUiVariant : public VARIANT
{
public:
	CUiVariant() 
	{ 
		VariantInit(this); 
	}

	CUiVariant(int i)
	{
		VariantInit(this);
		this->vt = VT_I4;
		this->intVal = i;
	}

	CUiVariant(float f)
	{
		VariantInit(this);
		this->vt = VT_R4;
		this->fltVal = f;
	}

	CUiVariant(LPOLESTR s)
	{
		VariantInit(this);
		this->vt = VT_BSTR;
		this->bstrVal = s;
	}

	CUiVariant(IDispatch *disp)
	{
		VariantInit(this);
		this->vt = VT_DISPATCH;
		this->pdispVal = disp;
	}

	~CUiVariant() 
	{ 
		VariantClear(this); 
	}
};

class PathUtil
{
public:
	static CUiString GetCurrentModuleDir()
	{
		TCHAR tszModule[MAX_PATH + 1] = { 0 };
		::GetModuleFileName(NULL, tszModule, MAX_PATH);
		CUiString sInstancePath = tszModule;
		int pos = sInstancePath.ReverseFind(_T('\\'));
		if (pos >= 0) {
			sInstancePath = sInstancePath.Left(pos + 1);
		}
		return sInstancePath;
	}
};

}// namespace ui

#endif // UI_UTILS_UTILS_H_