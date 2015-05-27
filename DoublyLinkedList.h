#include <iostream>
using namespace std;

#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H

template <class T>
class List
{
public:

	struct Node
	{
		T m_data;
		Node* m_next;
		Node* m_prev;

		Node(T data, Node *p_next = nullptr, Node *p_prev = nullptr) : m_data(data), m_next(p_next), m_prev(p_prev)
		{

		}
	};

	class iterator;

	//Канонично представяне
	List();
	~List();
	List(const List&);
	List& operator=(const List&);

	void push_front(const T&);
	void pop_front();
	void push_back(const T&);
	void pop_back();

	T& front();
	T& back();

	iterator begin()
	{
		iterator it(head);
		return it;
	}

	iterator end()
	{
		iterator it(tail->m_next);
		return it;
	}

	void insert(iterator, const T&);
	void erase(iterator);
	int size();
	void clear();
	bool empty();

	class iterator
	{
	public:
		iterator();
		iterator(Node*);
		T& operator*();

		iterator& operator++()
		{
			pNode = pNode->m_next;
			iterator temp(pNode);
			return temp;
		}

		iterator operator++(int)
		{
			iterator temp(pNode);
			pNode = pNode->m_next;
			return temp;
		}

		bool operator!=(iterator&);
		bool operator==(iterator&);

	private:
		Node* pNode;

	friend class List<T>;
	};


private:
	Node* head;
	Node* tail;
	Node* current;
	unsigned int length;

	//Помощни функции
	void copyList(const List<T>&);
	void deleteList();

};

#endif 