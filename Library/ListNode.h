#ifndef _LISTNODE_H_
#define _LISTNODE_H_

//template <class T> class LinkedList;

template<class T>
class ListNode
{
public:
	inline ListNode();
	inline ListNode(const T& data);
	inline ~ListNode();
	inline
	inline T& 			GetData();
	inline ListNode*	GetNext() const;
	inline ListNode*	GetPrevious() const;
	inline
	inline void			SetNext(ListNode* next);
	inline void			SetPrevious(ListNode* previous);

private:
	T					m_this;
	ListNode*			m_next;
	ListNode*			m_previous;
};

#include "ListNode.inl"

#endif _LISTNODE_H_