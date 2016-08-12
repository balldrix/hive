#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

#include "ListNode.h"

template<class T>
class LinkedList
{
public:
	inline LinkedList();
	inline ~LinkedList();

	inline void 	Insert(const T& Data);
	inline void		Clear();
	inline void 	Remove(const T& Data);
	inline void 	Remove(ListNode<T>* node);
	inline ListNode<T>*	GetFirst() const;
	inline ListNode<T>*	GetLast() const;
	inline bool		IsEmpty() const;

private:

	// do i really need a copy constructor??
	//LinkedList(const LinkedList<T>& otherList){};

	ListNode<T>* m_head;
	ListNode<T>* m_tail;
};

#include "LinkedList.inl"

#endif //_LINKEDLIST_H_