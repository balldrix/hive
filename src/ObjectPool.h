#pragma once

#include <list>

template <class T>
class ObjectPool
{
public:
	ObjectPool() = default;
	virtual ~ObjectPool();

	virtual T* Get() = 0;
	void ReturnObject(T* obj);
protected:
	std::list<T*> m_pool;
};

template <class T>
ObjectPool<T>::~ObjectPool()
{
	for(T* obj : m_pool)
	{
		delete obj;
		obj = nullptr;
	}

	m_pool.clear();
}

template<class T>
void ObjectPool<T>::ReturnObject(T* obj)
{
	m_pool.push_back(obj);
}
