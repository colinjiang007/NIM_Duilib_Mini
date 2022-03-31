﻿#include "StdAfx.h"

namespace ui
{

#define GG_VA_COPY(a, b) (a = b)
#define COUNT_OF(array)			(sizeof(array)/sizeof(array[0]))

namespace
{

template<typename CharType>
int StringTokenizeT(const std::basic_string<CharType> &input,
					const std::basic_string<CharType> &delimitor,
					std::list<std::basic_string<CharType> > &output)
{
	size_t token_begin;
	size_t token_end;

	output.clear();

	for (token_begin = token_end = 0; token_end != std::basic_string<CharType>::npos;)
	{
		token_begin = input.find_first_not_of(delimitor, token_begin);
		if (token_begin == std::basic_string<CharType>::npos)
			break;
		token_end = input.find_first_of(delimitor, token_begin + 1);
		output.push_back(input.substr(token_begin, token_end - token_begin));
		token_begin = token_end + 1;
	}

	return static_cast<int>(output.size());
}

template<typename CharType>
size_t StringReplaceAllT(const std::basic_string<CharType> &find,
					  const std::basic_string<CharType> &replace,
					  std::basic_string<CharType> &output)
{
	size_t find_length = find.size();
	size_t replace_length = replace.size();
	size_t offset = 0, endpos;
	size_t target = 0, found_pos;
	size_t replaced = 0;
	CharType *data_ptr;

	if (find.empty())
		return 0;

	/*
	 * to avoid extra memory reallocating,
	 * we use two passes to finish the task in the case that replace.size() is greater find.size()
	 */

	if (find_length < replace_length)
	{
		/* the first pass, count all available 'find' to be replaced  */
		for (;;)
		{
			offset = output.find(find, offset);
			if (offset == std::basic_string<CharType>::npos)
				break;
			replaced++;
			offset += find_length;
		}

		if (replaced == 0)
			return 0;

		size_t newsize = output.size() + replaced * (replace_length - find_length);

		/* we apply for more memory to hold the content to be replaced */
		endpos = newsize;
		offset = newsize - output.size();
		output.resize(newsize);
		data_ptr = &output[0];

		memmove((void*)(data_ptr + offset),
				(void*)data_ptr,
				(output.size() - offset) * sizeof(CharType));
	}
	else
	{
		endpos = output.size();
		offset = 0;
		data_ptr = const_cast<CharType *>(&output[0]);
	}

	/* the second pass,  the replacement */
	while (offset < endpos)
	{
		found_pos = output.find(find, offset);
		if (found_pos != std::basic_string<CharType>::npos)
		{
			/* move the content between two targets */
			if (target != found_pos)
				memmove((void*)(data_ptr + target),
						(void*)(data_ptr + offset),
						(found_pos - offset) * sizeof(CharType));

			target += found_pos - offset;

			/* replace */
			memcpy(data_ptr + target,
				   replace.data(),
				   replace_length * sizeof(CharType));

			target += replace_length;
			offset = find_length + found_pos;
			replaced++;
		}
		else
		{
			/* ending work  */
			if (target != offset)
				memcpy((void*)(data_ptr + target),
					   (void*)(data_ptr + offset),
					   (endpos - offset) * sizeof(CharType));
			break;
		}
	}

	if (replace_length < find_length)
		output.resize(output.size() - replaced * (find_length - replace_length));

	return replaced;
}

inline int vsnprintfT(char *dst, size_t count, const char *format, va_list ap)
{
	return vsnprintf(dst, count, format, ap);
}

inline int vsnprintfT(wchar_t *dst, size_t count, const wchar_t *format, va_list ap)
{
	return _vsnwprintf(dst, count, format, ap);
}

template<typename CharType>
void StringAppendVT(const CharType *format, va_list ap, std::basic_string<CharType> &output)
{
	CharType stack_buffer[1024];

	/* first, we try to finish the task using a fixed-size buffer in the stack */
	va_list ap_copy;
	GG_VA_COPY(ap_copy, ap);

	int result = vsnprintfT(stack_buffer, COUNT_OF(stack_buffer), format, ap_copy);
	va_end(ap_copy);
	if (result >= 0 && result < static_cast<int>(COUNT_OF(stack_buffer)))
	{
		/* It fits */
		output.append(stack_buffer, result);
		return;
	}

	/* then, we have to repeatedly increase buffer size until it fits. */
	int buffer_size = COUNT_OF(stack_buffer);
	std::basic_string<CharType> heap_buffer;
	for (;;)
	{
		if (result != -1)
		{
			assert(0);
			return; /* not expected, result should be -1 here */
		}
		buffer_size <<= 1; /* try doubling the buffer size */
		if (buffer_size > 32 * 1024 * 1024)
		{
			assert(0);
			return;	/* too long */
		}
		/* resize */
		heap_buffer.resize(buffer_size);
		/*
		 * NOTE: You can only use a va_list once.  Since we're in a while loop, we
		 * need to make a new copy each time so we don't use up the original.
		 */
		GG_VA_COPY(ap_copy, ap);
		result = vsnprintfT(&heap_buffer[0], buffer_size, format, ap_copy);
		va_end(ap_copy);

		if ((result >= 0) && (result < buffer_size)) {
			/* It fits */
			output.append(&heap_buffer[0], result);
			return;
		}
	}
}

#define NOT_SPACE(x) ((x) != 0x20 && ((x) < 0 || 0x1d < (x)))

template<typename CharType>
void StringTrimT(std::basic_string<CharType> &output)
{
	if (output.empty())
		return;
	size_t bound1 = 0;
	size_t bound2 = output.length();
	const CharType *src = output.data();

	for (; bound2 > 0; bound2--)
		if (NOT_SPACE(src[bound2-1]))
			break;

	for (; bound1 < bound2; bound1++)
		if (NOT_SPACE(src[bound1]))
			break;

	if (bound1 < bound2) {
		memmove((void *)src,
			src + bound1,
			sizeof(CharType) * (bound2 - bound1));
	}

	output.resize(bound2 - bound1);
}

template<typename CharType>
void StringTrimLeftT(std::basic_string<CharType> &output)
{
	size_t check = 0;
	size_t length = output.length();
	const CharType *src = output.data();

	for (; check < length; check++)
		if (NOT_SPACE(src[check]))
			break;

	output.erase(0, check);
}

template<typename CharType>
void StringTrimRightT(std::basic_string<CharType> &output)
{
	size_t length = output.length();
	const CharType *src = output.data();

	for (; length > 0; length--)
		if (NOT_SPACE(src[length-1]))
			break;

	output.resize(length);
}

} // anonymous namespace

std::wstring StringHelper::ReparsePath(const std::wstring& strFilePath)
{
	std::wstring tmp(strFilePath);
	ReplaceAll(L"/", L"\\", tmp);
	ReplaceAll(L"\\\\", L"\\", tmp);
	return tmp;
}

CUiString StringHelper::ReparsePath(const CUiString& strFilePath)
{
	CUiString tmp(strFilePath);
	tmp.Replace(_T("/"), _T("\\"));
	tmp.Replace(_T("\\\\"), _T("\\"));
	return tmp;
}

std::wstring StringHelper::Printf(const wchar_t *format, ...)
{
	va_list	args;
	va_start(args, format);
	std::wstring output;
	StringAppendVT<wchar_t>(format, args, output);
	va_end(args);

	return output;
}

size_t StringHelper::ReplaceAll(const std::wstring& find, const std::wstring& replace, std::wstring& output)
{
	if (output.empty())
	{
		return 0;
	}
	return StringReplaceAllT<wchar_t>(find, replace, output);
}


std::wstring StringHelper::MakeLowerString(const std::wstring &str)
{
	std::wstring resStr = str;
	if (resStr.empty())
		return L"";
	wchar_t *start = &resStr[0];
	wchar_t *end = start + resStr.length();
	for (; start < end; start++)
	{
		if (*start >= L'A' && *start <= L'Z')
			*start += L'a' - L'A';
	}
	
	return resStr;
}

std::wstring StringHelper::MakeUpperString(const std::wstring &str)
{
	std::wstring resStr = str;
	if (resStr.empty())
		return L"";
	wchar_t *start = &resStr[0];
	wchar_t *end = start + resStr.length();
	for (; start < end; start++)
	{
		if (*start >= L'a' && *start <= L'z')
			*start -= L'a' - L'A';
	}

	return resStr;
}


bool StringHelper::MBCSToUnicode(const char *input, std::wstring& output, int code_page)
{
	output.clear();
	int length = ::MultiByteToWideChar(code_page, 0, input, -1, NULL, 0);
	if (length <= 0)
		return false;
	output.resize(length-1);
	if (output.empty())
		return true;
	::MultiByteToWideChar(code_page,
		0,
		input,
		-1,
		&output[0],
		static_cast<int>(output.size()));
	return true;
}

bool StringHelper::MBCSToUnicode(const std::string &input, std::wstring& output, int code_page)
{
	output.clear();
	int length = ::MultiByteToWideChar(code_page, 0, input.c_str(), static_cast<int>(input.size()), NULL, 0);
	output.resize(length);
	if (output.empty())
		return true;
	::MultiByteToWideChar(code_page,
		0,
		input.c_str(),
		static_cast<int>(input.size()),
		&output[0],
		static_cast<int>(output.size()));
	return true;
}

bool StringHelper::UnicodeToMBCS(const wchar_t *input, std::string &output, int code_page)
{
	output.clear();
	int length = ::WideCharToMultiByte(code_page, 0, input, -1, NULL, 0, NULL, NULL);
	if (length <= 0)
		return false;
	output.resize(length-1);
	if (output.empty())
		return true;
	::WideCharToMultiByte(code_page,
		0,
		input,
		length-1,
		&output[0],
		static_cast<int>(output.size()),
		NULL,
		NULL);
	return true;
}

bool StringHelper::UnicodeToMBCS(const std::wstring& input, std::string &output, int code_page)
{
	output.clear();
	int length = ::WideCharToMultiByte(code_page, 0, input.c_str(), static_cast<int>(input.size()), NULL, 0, NULL, NULL);
	output.resize(length);
	if (output.empty())
		return true;
	::WideCharToMultiByte(code_page,
		0,
		input.c_str(),
		static_cast<int>(input.size()),
		&output[0],
		static_cast<int>(output.size()),
		NULL,
		NULL);
	return true;
}


int StringHelper::Utf8ToUnicode(const std::string& utf, std::wstring& unicode)
{

	int dwUnicodeLen = MultiByteToWideChar(CP_UTF8, 0, utf.c_str(), utf.size(), NULL, 0);
	unicode.resize(dwUnicodeLen);
	MultiByteToWideChar(CP_UTF8, 0, utf.c_str(), utf.size(), (LPWSTR)unicode.c_str(), dwUnicodeLen);
	return dwUnicodeLen;
}

int StringHelper::UnicodeToUtf8(const std::wstring& unicode, std::string& utf8)
{
	int len;
	len = WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), unicode.size(), NULL, 0, NULL, NULL);
	utf8.resize(len);
	WideCharToMultiByte(CP_UTF8, 0, unicode.c_str(), unicode.size(), (LPSTR)utf8.c_str(), len, NULL, NULL);
	return len;
}

int StringHelper::UnicodeToGB2312(const std::wstring& unicode, std::string& gb)
{
	int n = WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), unicode.size(), 0, 0, 0, 0);
	gb.resize(n);
	::WideCharToMultiByte(CP_ACP, 0, unicode.c_str(), unicode.size(), (char*)gb.c_str(), n, 0, 0);
	return n;
}

int StringHelper::Gb2312ToUnicode(const std::string& gb, std::wstring& unicode)
{
	int n = MultiByteToWideChar(CP_ACP, 0, gb.c_str(), gb.size(), NULL, 0);
	unicode.resize(n);
	::MultiByteToWideChar(CP_ACP, 0, gb.c_str(), gb.size(), (LPWSTR)unicode.c_str(), unicode.length());
	return n;
}


void StringHelper::CUiStringToUnicode(const CUiString& src, std::wstring& ret)
{
	ret.clear();
	if (src.IsEmpty()){
		return;
	}
#ifdef _UNICODE
	ret = (LPCTSTR)src;
#else
	Gb2312ToUnicode((LPCTSTR)src, ret);
#endif // _UNICODE

}

void StringHelper::CUiStringToGB2312(const CUiString& src, std::string& ret)
{
	ret.clear();
	if (src.IsEmpty()){
		return;
	}
#ifdef _UNICODE
	UnicodeToGB2312((LPCTSTR)src, ret);
#else
	ret = (LPCSTR)src;
#endif // _UNICODE

}

void StringHelper::CUiStringToUtf8(const CUiString& src, std::string& ret)
{
	ret.clear();
	if (src.IsEmpty()){
		return;
	}
#ifdef _UNICODE
	UnicodeToUtf8((LPCTSTR)src, ret);
#else
	wstring usrc;
	Gb2312ToUnicode((LPCTSTR)src, usrc);
	UnicodeToUtf8(usrc, ret);
#endif // _UNICODE
}

void StringHelper::UnicodeToCUiString(const std::wstring& src, CUiString& ret)
{
	ret.Empty();
	if (src.empty()){
		return;
	}
#ifdef _UNICODE
	ret = src.c_str();
#else
	string gbret;
	UnicodeToGB2312(src, gbret);
	ret = gbret.c_str();
#endif // _UNICODE
}

void StringHelper::GB2312ToCUiString(const std::string& src, CUiString& ret)
{
	ret.Empty();
	if (src.empty()){
		return;
	}
#ifdef _UNICODE
	std::wstring wret;
	Gb2312ToUnicode(src, wret);
	ret = wret.c_str();
#else
	ret = src.c_str();
#endif // _UNICODE
}

void StringHelper::Utf8ToCUiString(const std::string& src, CUiString& ret)
{
	ret.Empty();
	if (src.empty()){
		return;
	}
	std::wstring uret;
	Utf8ToUnicode(src, uret);
#ifdef _UNICODE
	ret = uret.c_str();
#else
	string gbret;
	UnicodeToGB2312(uret, gbret);
	ret = gbret.c_str();
#endif // _UNICODE
}

void StringHelper::SplitCUiString(const CUiString& strSource, const CUiString& token, std::vector<CUiString>& ret)
{
	ret.clear();
	TCHAR* nowtk = nullptr;
	TCHAR* nexttk = nullptr;

	nowtk = _tcstok_s((LPTSTR)(LPCTSTR)strSource, token, &nexttk);//(LPSTR)(LPCTSTR)将CString转char*
	CUiString strItem;
	do
	{
		if (nullptr == nowtk) {
			break;
		}
		strItem = nowtk;
		strItem.TrimLeft();
		ret.push_back(strItem);
		nowtk = _tcstok_s(NULL, token, &nexttk);//(LPSTR)(LPCTSTR)将CString转char*
	} while (true);
}

bool StringHelper::SplitCUiStringKeyValue(const CUiString& strSource, const CUiString& token, CUiString& key, CUiString& value)
{
	if (strSource.GetLength() <= token.GetLength()) {
		return false;
	}
	key.Empty();
	value.Empty();
	int pos = strSource.Find(token);
	if (pos <= 0) {
		return false;
	}
	key = strSource.Left(pos);
	value = strSource.Right(strSource.GetLength() - pos - token.GetLength());
	if (key.IsEmpty() || value.IsEmpty()) {
		return false;
	}
	return true;
}

std::string StringHelper::TrimLeft(const char *input)
{
	std::string output = input;
	TrimLeft(output);
	return output;
}

std::string StringHelper::TrimRight(const char *input)
{
	std::string output = input;
	TrimRight(output);
	return output;
}

std::string StringHelper::Trim(const char *input) /* both left and right */
{
	std::string output = input;
	Trim(output);
	return output;
}

std::string& StringHelper::TrimLeft(std::string &input)
{
	StringTrimLeftT<char>(input);
	return input;
}

std::string& StringHelper::TrimRight(std::string &input)
{
	StringTrimRightT<char>(input);
	return input;
}

std::string& StringHelper::Trim(std::string &input) /* both left and right */
{
	StringTrimT<char>(input);
	return input;
}

std::wstring StringHelper::TrimLeft(const wchar_t *input)
{
	std::wstring output = input;
	TrimLeft(output);
	return output;
}

std::wstring StringHelper::TrimRight(const wchar_t *input)
{
	std::wstring output = input;
	TrimRight(output);
	return output;
}

std::wstring StringHelper::Trim(const wchar_t *input) /* both left and right */
{
	std::wstring output = input;
	Trim(output);
	return output;
}

std::wstring& StringHelper::TrimLeft(std::wstring &input)
{
	StringTrimLeftT<wchar_t>(input);
	return input;
}

std::wstring& StringHelper::TrimRight(std::wstring &input)
{
	StringTrimRightT<wchar_t>(input);
	return input;
}

std::wstring& StringHelper::Trim(std::wstring &input) /* both left and right */
{
	StringTrimT<wchar_t>(input);
	return input;
}


std::list<std::string> StringHelper::Split(const std::string& input, const std::string& delimitor)
{
	std::list<std::string> output;
	std::string input2(input);

	if (input2.empty())
		return output;

	char *token = strtok(&input2[0], delimitor.c_str());
	while (token != NULL)
	{
		output.push_back(token);
		token = strtok(NULL, delimitor.c_str());
	}

	return output;
}

std::list<std::wstring> StringHelper::Split(const std::wstring& input, const std::wstring& delimitor)
{
	std::list<std::wstring> output;
	std::wstring input2(input);

	if (input2.empty())
		return output;

	wchar_t *token = wcstok(&input2[0], delimitor.c_str());
	while (token != NULL)
	{
		output.push_back(token);
		token = wcstok(NULL, delimitor.c_str());
	}


	return output;
}

} // namespace nbase
