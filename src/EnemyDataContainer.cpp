#include "EnemyDataContainer.h"

EnemyDataContainer::EnemyDataContainer()
{
}

EnemyDataContainer::~EnemyDataContainer()
{
	m_dataList.clear();
}

void EnemyDataContainer::Add(EnemyData& data)
{
	m_dataList.push_back(data);
}

EnemyData EnemyDataContainer::GetData(const std::string &type)
{
	for(size_t i = 0; i < m_dataList.size(); i++)
	{
		if(m_dataList[i].type == type)
		{
			return m_dataList[i];
		}
	}

	return EnemyData();
}
