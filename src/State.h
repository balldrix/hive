#pragma once

#include <string>

template <typename T>
class State
{
public:
	virtual ~State() {}	
	virtual void OnEnter(T*) = 0;
	virtual void Execute(T*) = 0;
	virtual void OnExit(T*) = 0;
	std::string GetName() const { return m_name; }

protected:
	std::string m_name;
};