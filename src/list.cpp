#include "list.h"

List::List()
{
	head.next = &head;
}

void List::Insert(Node* curNode, Node* insNode)
{
	insNode->next=curNode->next;
	curNode->next=insNode;
}

Node* List::GetHead()
{
	return &head;
}

List::~List()
{
	Clear();
}

void List::DeleteNext(Node* curNode)
{
	Node* temp=curNode->next;
	curNode->next=curNode->next->next;
	delete temp;
}

List::List(const List& list)
{
	head.m = list.head.m;
	head.next = &head;

	Node* q = &head;
	Node* p = list.head.next;

	while(p != &list.head)
	{
		List::Insert(q, new Node(p->m));
		p = p->next;
		q = q->next;
	}
}

void List::Clear()
{
	while (head.next != &head)
	{
		DeleteNext(&head);
	}
}

List& List::operator=(const List& l)
{
	
	if (this==&l)
		return *this;

	else
	{
		this->Clear();

		head.m = l.head.m;
		head.next = &head;

		Node* q = &head;
		Node* p = l.head.next;
		while(p != &l.head)
		{
			List::Insert(q, new Node(p->m));
			p = p->next;
			q = q->next;
		}
	}
}