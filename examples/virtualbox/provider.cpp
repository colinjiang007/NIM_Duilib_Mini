#include "stdafx.h"
#include "provider.h"
#include "item.h"


int g_index = 1;

Provider::Provider()
:m_nTotal(0)
{

}


Provider::~Provider()
= default;

ui::Control* Provider::CreateElement()
{
	Item* item = new Item;
	ui::GlobalManager::FillBoxWithCache(item, _T("virtualbox/item.xml"));
	return item;
}

void Provider::FillElement(ui::Control *control, int index)
{
	Item* pItem = dynamic_cast<Item*>(control);

	
	CUiString img = _T("icon.png");
	CUiString title;
	title.Format(_T("%s [%02d]"), m_vTasks[index].sName.GetData(), m_vTasks[index].nId);
	pItem->InitSubControls(img, title, index);

}

int Provider::GetElementtCount()
{
	// 加锁
	std::lock_guard<std::mutex> auto_lock(lock_);
	return m_vTasks.size();
}

void Provider::SetTotal(int nTotal)
{
	if (nTotal == m_nTotal) return;
	if (nTotal <= 0) return;

	// 加锁
	lock_.lock();
	m_vTasks.clear();
	for (auto i=1; i <= nTotal; i++)
	{
		DownloadTask task;
		task.nId = i;
		task.sName = _T("任务名称");
		m_vTasks.emplace_back(task);
	}
	lock_.unlock();

	// 通知TileBox数据总数变动
	EmitCountChanged();
}

void Provider::RemoveTask(int nIndex)
{	
	lock_.lock();

	auto iter =	m_vTasks.begin() + nIndex;
	m_vTasks.erase(iter);

	lock_.unlock();

	// 通知TileBox数据总数变动
	EmitCountChanged();
}

void Provider::ChangeTaskName(int nIndex, const CUiString& sName)
{
	lock_.lock();

	if (nIndex > 0 && nIndex < (int)m_vTasks.size())
	{
		m_vTasks[nIndex].sName = sName;
	}
	lock_.unlock();

	// 发送数据变动通知
	EmitDataChanged(nIndex, nIndex);
}
