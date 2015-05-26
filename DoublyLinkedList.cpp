#include <iostream>
#include <cassert>
#include "DoublyLinkedList.h"

using namespace std;

template <class T>
List<T>::List() : head(nullptr), tail(nullptr), current(nullptr), length(0)
{

}

template <class T>
List<T>::~List()
{
	deleteList();
}

template <class T>
List<T>::List(const List<T>& r)
{
	copyList(r);
}

template <class T>
List<T>& List<T>::operator=(const List<T>& right)
{
	if (this != &right)
	{
		deleteList();
		copyList(right);
	}
	return *this;
}

template <class T>
void List<T>::copyList(const List<T>& original)
{
	Node *ptr_new;
	Node *current;

	if (head != NULL)
	{
		deleteList();
	}

	if (original.head == NULL)
	{
		head = nullptr;
		tail = nullptr;
		current = nullptr;
		length = 0;
		return;
	}

	//Създаване(копиране) на първия възел
	current = original.head;
	head = new Node(current->m_data);
	tail = head;

	current = current->m_next;
	while (current != nullptr)
	{
		//Създава се нов възел
		ptr_new = new Node(current->m_data);
		tail->m_next = ptr_new; //Връзка на предходния с новия възел
		ptr_new->m_prev = tail; //Връзка на новия с предходния възел
		tail = ptr_new;

		current = current->m_next;
	}
	
	length = original.length;

}

template <class T>
void List<T>::deleteList()
{
	Node *p;

	while (head != nullptr)
	{
		p = head;
		head = head->m_next;
		delete p;
	}
	tail = nullptr;
	length = 0;
}

template <class T>
void List<T>::push_front(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		Node* ptr_head = head;
		head = new Node(value, head);
		ptr_head->m_prev = head;
	}

	length++;
}

template <class T>
void List<T>::pop_front()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->m_next == nullptr)
	{
		//Списъкът не е празен, но има само един възел
		head = nullptr; 
		tail = nullptr;
		delete head;
	}
	else
	{
		Node* ptr_node = head;
		head = head->m_next;
		delete ptr_node;
	}

	length--;
}

template <class T>
void List<T>::push_back(const T& value)
{
	if (head == nullptr)
	{
		head = new Node(value);
		tail = head;
	}
	else
	{
		//Добавяне на нов възел след текущия последен
		Node* tail_node = tail;
		tail_node->m_next = new Node(value, nullptr, tail);
		tail = tail_node->m_next;
	}
	length++;
}

template <class T>
void List<T>::pop_back()
{
	if (head == nullptr)
	{
		return;
	}
	else if (head->m_next == nullptr)
	{
		delete head;
		head = nullptr;
		tail = nullptr; //Списъкът не е празен, но има само един възел
	}
	else
	{
		Node* ptr_last = tail;
		Node* ptr_prev = tail->m_prev; //Адрес на предпоследния възел
		tail = ptr_prev;
		tail->m_next = nullptr;
		delete ptr_last;
	}
	length--;
}

template <class T>
T& List<T>::front()
{
	return head->m_data;
}

template <class T>
T& List<T>::back()
{
	return tail->m_data;
}

template <class T>
List<T>::iterator::iterator() : pNode(nullptr)
{

}

template <class T>
List<T>::iterator::iterator(Node* data) : pNode(data)
{

}

template <class T>
T& List<T>::iterator::operator*()
{
	return pNode->m_data;
}

template <class T>
bool List<T>::iterator::operator!=(iterator& secondIterator)
{
	return pNode != secondIterator.pNode;
}

template <class T>
bool List<T>::iterator::operator==(iterator& otherIterator)
{
	return pNode == otherIterator.pNode;
}

template <class T>
void List<T>::insert(iterator it, const T& value)
{
	if (it.pNode == nullptr)
	{
		push_back(value);
		length++;
		return;
	}
	else if (it.pNode == head)
	{
		Node *ptr_new = new Node(value);
		ptr_new->m_prev = nullptr;
		ptr_new->m_next = head;
		head->m_prev = ptr_new;
		head = ptr_new;
		length++;
		return;
	}
	else
	{
		Node* ptr_new = new Node(value);
		assert(it.pNode != nullptr);

		ptr_new->m_next = it.pNode;
		ptr_new->m_prev = it.pNode->m_prev;

		ptr_new->m_next->m_prev = ptr_new->m_prev;
		ptr_new->m_prev->m_next = ptr_new;

		length++;
	}
}

template <class T>
void List<T>::erase(iterator it)
{
	if (it.pNode == head)
	{
		head = head->m_next;
		head->m_prev = nullptr;
		delete it.pNode;
		length--;
		return;
	}
	else if (it.pNode == tail)
	{
		tail = tail->m_prev;
		tail->m_prev = nullptr;
		delete it.pNode;
		length--;
		return;
	}
	else
	{
		it.pNode->m_prev->m_next = it.pNode->m_next;
		it.pNode->m_next->m_prev = it.pNode->m_prev;
		delete it.pNode;
		length--;
	}
}

template <class T>
int List<T>::size()
{
	return length;
}

template <class T>
void List<T>::clear()
{
	deleteList();	
}

template <class T>
bool List<T>::empty()
{
	return length == 0;
}