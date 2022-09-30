//	LinkedBag340.cpp
//	Created by: CSC340

#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <algorithm>
#include "Node.h"
#include "LinkedBag.h"
using namespace std;

template<typename ItemType>
bool LinkedBag<ItemType>::removeSecondNode340()
{
	Node<ItemType>* headPtrCopy = headPtr.get();
	Node<ItemType>* nodeToDeletePtr = headPtr->getNext();
	Node<ItemType>* nodeToConnectPtr = nodeToDeletePtr->getNext();
	bool actionSuccessful;

	if (headPtr != nullptr && nodeToDeletePtr != nullptr && nodeToConnectPtr != nullptr)
	{
		actionSuccessful = true;
		headPtrCopy->setNext(nodeToDeletePtr->getNextUnique());
		itemCount--;
	}
	else
	{
		actionSuccessful = false;
		cout << "\nCannot perform removeSecondNode340()!";
	}
	return actionSuccessful;
}

template<typename ItemType> 
bool LinkedBag<ItemType>::addEnd340(const ItemType &newEntry)
{
	bool actionSuccessful;
	unique_ptr<Node<ItemType>> newEndNode{ make_unique < Node<ItemType>>(newEntry) };
	Node<ItemType>* iter = headPtr.get();
	while (iter->getNext())
	{
		iter = iter->getNext();
	}
	iter->setNext(newEndNode);
	itemCount++;
	actionSuccessful = true;
	return actionSuccessful;
}

template<typename ItemType> 
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
	int size = 0;
	Node<ItemType>* iter = headPtr.get();
	while (iter)
	{
		iter = iter->getNext();
		size++;
	}
	return size;
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340Recursive() const
{
	Node<ItemType>* iter = headPtr.get();
	return getCurrentSize340RecursiveHelper(iter);
}

template<typename ItemType>
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const
{
	static Node<ItemType>* size_iter = headPtr.get();
	if (size_iter == nullptr)
	{
		size_iter = headPtr.get();
		return 0;
	}
	else
	{
		size_iter = size_iter->getNext();
		return getCurrentSize340RecursiveNoHelper() + 1;
	}
}

template<typename ItemType>
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType &anEntry) const
{
	Node<ItemType>* iter = headPtr.get();
	return getFrequencyOf340RecursiveHelper(iter, anEntry);
}

template<typename ItemType> //DONE - MAYBE
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType &anEntry) const
{
	static Node<ItemType>* freq_iter = headPtr.get();
	if (freq_iter == nullptr)
	{
		freq_iter = headPtr.get();
		return 0;
	}
	else
	{
		if (freq_iter->getItem() == anEntry)
		{
			freq_iter = freq_iter->getNext();
			return getFrequencyOf340RecursiveNoHelper(anEntry) + 1;
		}
		else
		{
			freq_iter = freq_iter->getNext();
			return getFrequencyOf340RecursiveNoHelper(anEntry);
		}
	}
}

template<typename ItemType> 
ItemType LinkedBag<ItemType>::removeRandom340()
{
	srand((unsigned int)time(NULL));
	int indexRemoved = rand() % itemCount;
	ItemType returnResult;
	Node<ItemType>* nodeToDeletePtr = headPtr.get();
	Node<ItemType>* nodeBeforeDeletePtr = headPtr.get();
	Node<ItemType>* nodeAfterDeletePtr = headPtr.get();
	//if the index is the beginning one - GOOD
	if (indexRemoved == 0)
	{
		returnResult = nodeToDeletePtr->getItem();
		unique_ptr<Node<ItemType>>& newHead = headPtr->getNextUnique();
		swap(headPtr, newHead);
		cout << "\nBye Bye first node: " << newHead << " with value " << newHead->getItem();
		itemCount--;
	}
	//if the index is in between the beginning and ending - GOOD
	else if (indexRemoved > 0 && indexRemoved < (itemCount-1))
	{

		for (int i = 0; i < indexRemoved; i++)
		{
			if (i == 0)
			{
				nodeToDeletePtr = nodeToDeletePtr->getNext();
				nodeAfterDeletePtr = nodeAfterDeletePtr->getNext();
				nodeAfterDeletePtr = nodeAfterDeletePtr->getNext();
			}
			else
			{
				nodeBeforeDeletePtr = nodeBeforeDeletePtr->getNext();
				nodeToDeletePtr = nodeToDeletePtr->getNext();
				nodeAfterDeletePtr = nodeAfterDeletePtr->getNext();
			}
		}
		returnResult = nodeToDeletePtr->getItem();
		itemCount--;
		nodeBeforeDeletePtr->setNext(nodeToDeletePtr->getNextUnique());
	}
	//if the index is at the end
	else
	{
		nodeToDeletePtr = nodeToDeletePtr->getNext();
		while (nodeToDeletePtr->getNext() != nullptr)
		{
			nodeBeforeDeletePtr = nodeBeforeDeletePtr->getNext();
			nodeToDeletePtr = nodeToDeletePtr->getNext();
		}
		itemCount--;
		returnResult = nodeToDeletePtr->getItem();
		nodeBeforeDeletePtr->setNext(nodeToDeletePtr->getNextUnique());
	}
	return returnResult;
}

template<typename ItemType>
unique_ptr<LinkedBag<ItemType>> LinkedBag<ItemType>::getSortedLB(unique_ptr<Node<ItemType>>& begin_node, unique_ptr<Node<ItemType>>& end_node)
{
	vector<ItemType> bag_vector = this->toVector();
	unique_ptr<LinkedBag<ItemType>> sorted_bag{ make_unique <LinkedBag<ItemType>>() };
	sort(bag_vector.begin(), bag_vector.end());
	typename vector<ItemType>::reverse_iterator rItr;
	for (rItr = bag_vector.rbegin(); rItr != bag_vector.rend(); rItr++)
	{
		string before_dash_str = rItr->substr(0,rItr->find("-"));
		if (before_dash_str.find_first_not_of("0123456789") == string::npos)
		{
			bool success = sorted_bag->add(*rItr);
			if (!success) {
				cout << "\n !add() FAILED: " << *rItr;
			}
		}
		else
		{
			cout << "\ninvalid entry removed " << *rItr;
		}
	}
	sorted_bag->itemCount++;
	sorted_bag->itemCount++;
	begin_node->setNext(sorted_bag->headPtr);
	swap(begin_node, sorted_bag->headPtr);
	Node<ItemType>* iter = sorted_bag->headPtr.get();
	while (iter->getNext())
	{
		iter = iter->getNext();
	}
	iter->setNext(end_node);
	return sorted_bag;
}

template<typename ItemType> 
int LinkedBag<ItemType>::getCurrentSize340RecursiveHelper(Node<ItemType>* helper_iter) const
{
	if (helper_iter == nullptr)
	{
		return 0;
	}
	else
	{
		return getCurrentSize340RecursiveHelper(helper_iter->getNext()) + 1;
	}
}

template<typename ItemType> 
int LinkedBag<ItemType>::getFrequencyOf340RecursiveHelper(Node<ItemType>*helper_iter, const ItemType &anEntry) const
{
	if (helper_iter == nullptr)
	{
		return 0;
	}
	else
	{
		if (helper_iter->getItem() == anEntry)
		{
			return getFrequencyOf340RecursiveHelper(helper_iter->getNext(), anEntry) + 1;
		}
		else
		{
			return getFrequencyOf340RecursiveHelper(helper_iter->getNext(), anEntry);
		}
	}
	return 0;
}