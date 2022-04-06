#pragma once

#include "VirtualTileBox.h"
#include <map>
#include <mutex>

struct DownloadTask
{
	int nId;
	CUiString sName;
};

class Provider : public VirtualTileInterface
{
public:
	Provider();
	~Provider();

	virtual ui::Control* CreateElement() override;

	/**
	* @brief ���ָ������
	* @param[in] control ����ؼ�ָ��
	* @param[in] index ����
	* @return ���ش����������ָ��
	*/
	virtual void FillElement(ui::Control *control, int index) override;

	/**
	* @brief ��ȡ��������
	* @return ������������
	*/
	virtual int GetElementtCount() override;

public:
	void SetTotal(int nTotal);
	void RemoveTask(int nIndex);
	void ChangeTaskName(int nIndex, const CUiString& sName);

private:
	int m_nTotal;
	std::vector<DownloadTask> m_vTasks;
	std::mutex  lock_;
};

