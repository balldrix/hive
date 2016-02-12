template <class T>
inline
ListNode<T>::ListNode() :
m_this(NULL),
m_next(NULL),
m_previous(NULL)
{
}

template <class T>
inline
ListNode<T>::ListNode(const T& data) :
m_this(data),
m_next(NULL),
m_previous(NULL)
{
}

template <class T>
inline
ListNode<T>::~ListNode()
{
}

template<class T>
inline ListNode<T>*
ListNode<T>::GetPrevious() const
{
	return m_previous;
}

template<class T>
inline ListNode<T>*
ListNode<T>::GetNext() const
{
	return m_next;
}

template<class T>
inline T&
ListNode<T>::GetData()
{
	return m_this;
}

template<class T>
inline void
ListNode<T>::SetNext(ListNode* next)
{
	m_next = next;
}

template<class T>
inline void
ListNode<T>::SetPrevious(ListNode* previous)
{
	m_previous = previous;
}
