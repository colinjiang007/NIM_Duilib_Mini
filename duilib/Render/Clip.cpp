#include "StdAfx.h"

namespace ui {

GdiClip::GdiClip()
{

}

GdiClip::~GdiClip()
{

}

void GdiClip::CreateClip(HDC hDC, CUiRect rcItem)
{
	if (hDC != NULL) {
		CUiPoint ptWinOrg;
		GetWindowOrgEx(hDC, &ptWinOrg);
		rcItem.Offset(-ptWinOrg.x, -ptWinOrg.y);

		HRGN hRgn = ::CreateRectRgnIndirect(&rcItem);
		::SaveDC(hDC);
		::ExtSelectClipRgn(hDC, hRgn, RGN_AND);
		::DeleteObject(hRgn);
	}
}

void GdiClip::CreateRoundClip(HDC hDC, CUiRect rcItem, int width, int height)
{
	if (hDC != NULL) {
		CUiPoint ptWinOrg;
		GetWindowOrgEx(hDC, &ptWinOrg);
		rcItem.Offset(-ptWinOrg.x, -ptWinOrg.y);

		HRGN hRgn = ::CreateRoundRectRgn(rcItem.left, rcItem.top, rcItem.right + 1, rcItem.bottom + 1, width, height);
		::SaveDC(hDC);
		::ExtSelectClipRgn(hDC, hRgn, RGN_AND);
		::DeleteObject(hRgn);
	}
}

void GdiClip::ClearClip(HDC hDC)
{
	if (hDC != NULL) {
		ASSERT(::GetObjectType(hDC) == OBJ_DC || ::GetObjectType(hDC) == OBJ_MEMDC);
		::RestoreDC(hDC, -1);
	}
}

} // namespace ui
