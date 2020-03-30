#pragma once
#include<iostream>

using namespace std;

template <class T>
struct TNode
{
	T val;
	TNode<T>* pNext;
};

template <class T>
class TList {
protected:
	TNode<T>* pFirst, * pLast, * pCurr, * pPrev, * pStop;
	int pos, size;
public:
	TList();
	~TList();
	TList(const TList<T>& l);

	T GetCurrEl();

	void InsFirst(const T& a);

	void DelFirst();
	void DelCurr();
	void InsLast(const T& a);
	void InsCurr(const T& a);

	void Reset();
	void GoNext();
	bool IsEnd();

	void InsInOrder(const T& a);
};

template <class T>
TList<T>::TList()
{
	pFirst =
	pLast = NULL;
	pCurr = NULL;
	pPrev = NULL;
	pStop = NULL;
	size = 0;
	pos = -1;
}

template <class T>
TList<T>::~TList()
{
	TNode<T>* tmp = pFirst;
	while (pFirst != pStop)
	{
		pFirst = pFirst->pNext;
		delete tmp;
		tmp = pFirst;
	}
}

template <class T>
T TList<T>::GetCurrEl()
{
	if (pCurr == NULL) {
		throw "Current element is Null";
	}
	return pCurr->val;
}

template <class T>
TList<T>::TList(const TList<T>& l)
{
	TNode<T>* tmp = l.pFirst;
	if (tmp == pStop)
	{
		pFirst = tmp;
	}
	while (tmp != pStop)
	{
		Push(tmp->val);
		tmp = tmp->pNext;
	}
	delete tmp;
}

template <class T>
void TList<T>::InsFirst(const T& a)
{
	TNode<T>* tmp;
	tmp = new TNode<T>;
	tmp->pNext = pFirst;
	tmp->val = a;
	if (pFirst == pStop) {
		pLast = pFirst = tmp;
	}
	else {
		pFirst = tmp;
	}
	size++;
}

template <class type>
void TList<type>::InsFirst(const type& _val)
{
	if (pFirst == nullptr)
	{
		pFirst = new TNode;
		pFirst->pos = 0;
		pFirst->val = _val;
		pFirst->pNext = pFirst->pPrev = nullptr;
		++len;
		return;
	}
	TNode* p = new TNode;
	if (p == 0) throw ("Bad mem alloc on create");
	TNode* prev = pFirst;
	p->val = _val;
	p->pNext = pFirst;
	p->pPrev = nullptr;
	pCurr = pFirst = p;
	TNode* next = pFirst->pNext;
	next->pPrev = pFirst;
	++len;
	FullRePos();
};

template <class T>
void TList<T>::DelFirst()
{
	if (pFirst == pStop) {
		throw "Error DelFirst: List is empty";
	}
	TNode<T>* tmp = pFirst;
	pFirst = pFirst->pNext;
	pCurr = pFirst;
	delete tmp;
	size--;
}

template <class T>
void TList<T>::InsLast(const T& a)
{
	TNode<T>* tmp;
	tmp = new TNode<T>;
	tmp->pNext = pStop;
	tmp->val = a;
	if (pLast != pStop) {
		pLast->pNext = tmp;
		pLast = tmp;
	}
	else
	{
		pFirst = pLast = tmp;
	}
	size++;
}


template <class T>
void TList<T>::InsCurr(const T& a)
{
	if (pCurr == pFirst) {
		InsFirst(a);
	}
	else if (pCurr == NULL) {
		throw "Error InsCurr: Stop";
	}
	else {
		TNode<T>* tmp = new TNode<T>;
		tmp->val = a;
		pPrev->pNext = tmp;
		tmp->pNext = pCurr;
		pCurr = tmp;
		size++;
	}
}

template <class T>
void TList<T>::DelCurr()
{
	if (pCurr == pStop) throw "Error DelCurr: Stop";
	if (pCurr == pFirst) {
		DelFirst();
	}
	else {
		TNode<T>* tmp = pCurr;
		pPrev->pNext = pCurr->pNext;
		pCurr = pCurr->pNext;
		delete tmp;
		size--;
	}
}

template <class T>
void TList<T>::Reset() {
	pCurr = pFirst;
	pPrev = pStop;
	pos = 0;
}

template <class T>
void TList<T>::GoNext() {
	pPrev = pCurr;
	pCurr = pCurr->pNext;
	pos++;
}

template <class T>
bool TList<T>::IsEnd() {
	return pCurr == pStop;
}

template <class T>
void TList<T>::InsInOrder(const T& a) {
	if (pFirst == pStop) InsFirst(a);
	else if (pFirst->val < a) InsFirst(a);
	else if (pLast->val > a) InsLast(a);
	else {
		for (Reset(); !IsEnd(); GoNext()) {
			if (a > pCurr->val) {
				InsCurr(a);
				break;
			}
		}
	}
}


template <class T>
class THeadList :public TList<T> {

protected:
	TNode<T>* pHead;
public:
	THeadList() :TList<T>() {
		pHead = new TNode<T>;
		pHead->pNext = pHead;
		pStop = pFirst = pLast = pHead;
	}

	~THeadList() {
		delete pHead;
	}

	void InsFirst(T val) {
		TList::InsFirst(val);
		pHead->pNext = pFirst;
	}

	void DelFirst() {
		TList::DelFirst();
		pHead->pNext = pFirst;
	}
};