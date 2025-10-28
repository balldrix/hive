#pragma once

#include <vector>

class Prop;

class PropManager
{
public:
	PropManager();
	~PropManager();
private:
	std::vector<Prop*> m_propList;
};