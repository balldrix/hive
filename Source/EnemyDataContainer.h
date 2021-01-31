// EnemyDataContainer.h
// Christopher Ball 2019-2021
// container of enemy data

#ifndef _ENEMYDATACONTAINER_H_
#define	_ENEMYDATACONTAINER_H_

#include "EnemyData.h"

class EnemyDataContainer
{
public:
	EnemyDataContainer();
	~EnemyDataContainer();

	void Add(EnemyData& data);
	EnemyData GetData(std::string type);

private:
	std::vector<EnemyData> m_dataList;
};

#endif // !_ENEMYDATACONTAINER_H_