//	LinkedBag340.cpp
//	Created by: CSC340

#include <cstddef>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include "Node.h"
#include "LinkedBag.h"
using namespace std;

template<typename ItemType> //DONE
bool LinkedBag<ItemType>::removeSecondNode340()
{
	Node<ItemType>* headPtrCopy = headPtr;
	Node<ItemType>* nodeToDeletePtr = headPtr->getNext();
	Node<ItemType>* nodeToConnectPtr = nodeToDeletePtr->getNext();
	bool actionSuccessful;

	if (headPtr != nullptr && nodeToDeletePtr != nullptr && nodeToConnectPtr != nullptr)
	{
		actionSuccessful = true;
		delete nodeToDeletePtr;
		headPtrCopy->setNext(nodeToConnectPtr);
		itemCount--;
	}
	else
	{
		actionSuccessful = false;
		cout << "Cannot perform removeSecondNode340()!" << endl;
	}
	return actionSuccessful;
}

template<typename ItemType> //DONE
bool LinkedBag<ItemType>::addEnd340(const ItemType &newEntry)
{
	bool actionSuccessful;
	Node<ItemType>* newEndNode = new Node<ItemType>();
	newEndNode->setItem(newEntry);
	newEndNode->setNext(nullptr);
	Node<ItemType>* iter = headPtr;
	while (iter->getNext() != nullptr)
	{
		iter = iter->getNext();
	}
	iter->setNext(newEndNode);
	itemCount++;
	actionSuccessful = true;
	return actionSuccessful;

}

template<typename ItemType> //DONE
int LinkedBag<ItemType>::getCurrentSize340Iterative() const
{
	int size = 0;
	Node<ItemType>* iter = headPtr;
	while (iter != nullptr)
	{
		iter = iter->getNext();
		size++;
	}
	return size;
}

template<typename ItemType> //DONE
int LinkedBag<ItemType>::getCurrentSize340Recursive() const
{
	Node<ItemType>* iter = headPtr;
	return getCurrentSize340RecursiveHelper(iter);
}

template<typename ItemType> //DONE - MAYBE
int LinkedBag<ItemType>::getCurrentSize340RecursiveNoHelper() const
{
	static Node<ItemType>* size_iter = headPtr;
	if (size_iter == nullptr)
	{
		size_iter = headPtr;
		return 0;
	}
	else
	{
		size_iter = size_iter->getNext();
		return getCurrentSize340RecursiveNoHelper() + 1;
	}
}

template<typename ItemType> //DONE
int LinkedBag<ItemType>::getFrequencyOf340Recursive(const ItemType &anEntry) const
{
	Node<ItemType>* iter = headPtr;
	return getFrequencyOf340RecursiveHelper(iter, anEntry);
}

template<typename ItemType> //DONE - MAYBE
int LinkedBag<ItemType>::getFrequencyOf340RecursiveNoHelper(const ItemType &anEntry) const
{
	static Node<ItemType>* freq_iter = headPtr;
	if (freq_iter == nullptr)
	{
		freq_iter = headPtr;
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

template<typename ItemType> //DONE
ItemType LinkedBag<ItemType>::removeRandom340()
{
	srand((unsigned int)time(NULL));
	int indexRemoved = rand() % itemCount;
	ItemType returnResult;
	Node<ItemType>* nodeToDeletePtr = headPtr;
	Node<ItemType>* nodeBeforeDeletePtr = headPtr;
	Node<ItemType>* nodeAfterDeletePtr = headPtr;
	//if the index is the beginning one
	if (indexRemoved == 0)
	{
		Node<ItemType>* newHead = headPtr->getNext();
		returnResult = nodeToDeletePtr->getItem();
		delete nodeToDeletePtr;
		itemCount--;
		headPtr = newHead;
	}
	//if the index is in between the beginning and ending
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
		delete nodeToDeletePtr;
		itemCount--;
		nodeBeforeDeletePtr->setNext(nodeAfterDeletePtr);
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
		returnResult = nodeToDeletePtr->getItem();
		delete nodeToDeletePtr;
		itemCount--;
		nodeBeforeDeletePtr->setNext(nullptr);
	}
	return returnResult;
}

template<typename ItemType> //DONE
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

template<typename ItemType> //DONE
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
