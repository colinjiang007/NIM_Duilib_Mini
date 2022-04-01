#include "stdafx.h"
#include "ChildBox.h"

namespace ui
{

ChildBox::ChildBox()
{

}

void ChildBox::Init()
{
	if (!m_strXMLFile.IsEmpty())
	{
		Box* pChildWindow = static_cast<Box*>(GlobalManager::CreateBoxWithCache(m_strXMLFile, CreateControlCallback()));
		if (pChildWindow) {
			this->Add(pChildWindow);
		}
		else {
			ASSERT(FALSE);
			this->RemoveAll();
		}
	}
}

void ChildBox::SetAttribute( const CUiString& strName, const CUiString& strValue )
{
	if( strName == _T("xmlfile") )
		SetChildLayoutXML(strValue);
	else
		Box::SetAttribute(strName,strValue);
}

void ChildBox::SetChildLayoutXML(const CUiString& strXML )
{
	m_strXMLFile = strXML;
}

CUiString ChildBox::GetChildLayoutXML()
{
	return m_strXMLFile;
}

} // namespace ui
