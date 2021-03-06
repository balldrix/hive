#pragma once

#include "EnemyData.h"

class EnemyDataContainer
{
public:
	EnemyDataContainer();
	~EnemyDataContainer();

	void Add(EnemyData& data);
	EnemyData GetData(const std::string &type);

private:
	std::vector<EnemyData> m_dataList;
};