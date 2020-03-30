#pragma once

template <class T>
struct TNode {
	T val;
	TNode<T>* pNext;
};

template <class T>
class TList {

protected:
	TNode <T>* pFirst, * pLast, * pCurr, * pPrev, * pStop;
	int size;
	int pos;

public:

	TList() {
		pFirst = NULL;
		pLast = NULL;
		pCurr = NULL;
		pPrev = NULL;
		pStop = NULL;
		size = 0;
		pos = 0;
	}

	~TList() {
		TNode<T>* tmp = pFirst;
		while (pFirst != pStop) {
			pFirst = pFirst->pNext;
			delete tmp;
			tmp = pFirst;
		}
	}

	void InsFirst(const T& a)
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

	void InsLast(const T& a) {
		if (pFirst == pStop)
			InsFirst(a);
		else {
			TNode<T>* p = pFirst;
			while (p->pNext != pStop)
				p = p->pNext;
			TNode<T>* tmp;
			tmp = new TNode<T>;
			tmp->val = a;
			tmp->pNext = pStop;
			p->pNext = tmp;
			pLast = tmp;
		}
	}

	TNode<T>* GetNext() {
		return pCurr->pNext;
	}

	void DelFirst() {
		if (pFirst == pStop)
			return;
		if (pCurr == pFirst)
			pCurr = pFirst->pNext;
		T res = pFirst->val;
		TNode<T>* tmp;
		tmp = pFirst;
		pFirst = pFirst->pNext;
		delete tmp;
		size--;
	}

	void InsCurr(const T& a) {
		if (pCurr == pFirst) {
			InsFirst(a);
			pCurr = pFirst;
		}
		else {
			TNode<T>* tmp;
			tmp = new TNode<T>;
			tmp->val = a;
			pPrev->pNext = tmp;
			tmp->pNext = pCurr;
			pCurr = tmp;
			size++;
		}
	}

	void DelCurr()
	{
		if (pCurr == pStop) throw "Error DelCurr";
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

	T GetCurrEl() {
		if (pCurr == NULL) {
			throw "Error: no element";
		}
		return pCurr->val;
	}

	void Reset() {
		pCurr = pFirst;
		pPrev = pStop;
		pos = 0;
	}

	void GoNext() {
		pPrev = pCurr;
		pCurr = pCurr->pNext;
		pos++;
	}

	bool IsEnd() {
		return (pCurr == pStop);
	}

	bool IsNextLast() {
		return (pCurr->pNext == pStop);
	}

	void InsOnOrder(const T& el) {
		if ((pFirst == pStop) || (el > pFirst->val))
			InsFirst(el);
		else
			if (pLast->val > el)
				InsLast(el);
			else
				for (Reset(); !IsEnd(); GoNext()) {
					if (el > pCurr->val) {
						InsCurr(el);
						break;
					}
				}
	}

	void DelList() {
		for (Reset(); !IsEnd(); GoNext()) {
			DelCurr();
		}
		DelCurr();
	}
};


template <class T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
public:

	THeadList() : TList<T>() {
		pHead = new TNode<T>;
		this->pStop = pHead;
		pHead->pNext = pHead;
		this->pFirst = pHead;
	}

	void InsFirst(T el) {
		TList<T>::InsFirst(el);
		this->pHead->pNext = this->pFirst;
	}

	void InsLast(T el) {
		TList<T>::InsLast(el);
	}

	void InsCurr(T el) {
		TList<T>::InsCurr(el);
	}

	void DelFirst() {
		TList::DelFirst();
		this->pHead->pNext = this->pFirst;
	}

	~THeadList() {
		delete pHead;
	}
};
