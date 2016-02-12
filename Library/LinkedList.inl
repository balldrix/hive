template <class T>
inline
LinkedList<T>::LinkedList() :
m_head(NULL),
m_tail(NULL)
{
}

template <class T>
inline
LinkedList<T>::~LinkedList()
{
	Clear();
}

template <class T>
inline void
LinkedList<T>::Insert(const T& data)
{
	ListNode<T>* node = new ListNode<T>(data);

	if (m_tail != NULL)
	{
		m_tail->SetNext(node);
		node->SetPrevious(m_tail);
		m_tail = node;
	}
	else
	{
		m_head = node;
		m_tail = node;
	}
}

template <class T>
inline void
LinkedList<T>::Clear()
{
	ListNode<T>* node = m_head;

	while (node != NULL)
	{
		ListNode<T>* temp = node;
		node = node->GetNext();
		delete temp;
	}

	m_head = NULL;
	m_tail = NULL;
}

template <class T>
inline void
LinkedList<T>::Remove(const T& data)
{
	ListNode<T>* node = m_head;

	while (node != NULL)
	{
		if (node->GetData == data)
		{
			Remove(node);
			return;
		}
		node = node->GetNext();
	}
}

template <class T>
inline void
LinkedList<T>::Remove(ListNode<T>* node)
{
	ListNode<T>* previous = node->GetPrevious();
	ListNode<T>* next = node->GetNext();

	if (previous != NULL)
	{
		previous->SetNext(next);
	}
	else
	{
		m_head = next;
	}

	if (next != NULL)
	{
		next->SetPrevious(previous);
	}
	else
	{
		m_tail = previous;
	}

	delete node;
}

template <class T>
inline ListNode<T>*
LinkedList<T>::GetFirst() const
{
	return m_head;
}

template <class T>
inline ListNode<T>*
LinkedList<T>::GetLast() const
{
	return m_tail;
}

template <class T>
inline bool
LinkedList<T>::IsEmpty() const
{
	return (m_head == 0);
}