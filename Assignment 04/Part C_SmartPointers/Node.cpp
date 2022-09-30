//  Node.cpp
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#include "Node.h"
#include <string>
#include <iostream>


template<typename ItemType>
Node<ItemType>::Node() : item(), next(nullptr) 
{
	cout << "\nMaking a new empty node";
}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem) : item(anItem), next(nullptr) 
{
	cout << "\nMaking a new node with value " << anItem << " and no next";
}

template<typename ItemType>
Node<ItemType>::Node(const ItemType& anItem, unique_ptr<Node<ItemType>>& nextNodePtr) :
	item(anItem), next(move(nextNodePtr)) 
{
	cout << "\nMaking a new node with value " << anItem << " and pointing to " << nextNodePtr;
}

template<typename ItemType>
Node<ItemType>::~Node()
{
	std::cout << "\nDestructing Node w/ @: " << this << " and item " << this->getItem();
}

template<typename ItemType>
void Node<ItemType>::setItem(const ItemType& anItem) {
	item = anItem;
}

template<typename ItemType>
void Node<ItemType>::setNext(unique_ptr<Node<ItemType>>& nextNodePtr) {
	next = move(nextNodePtr);
}

template<typename ItemType>
ItemType Node<ItemType>::getItem() const {
	return item;
}

template<typename ItemType>
Node<ItemType>* Node<ItemType>::getNext() const {
	Node <ItemType>* rawPtrToNext = next.get();
	return rawPtrToNext;
}

template<typename ItemType>
unique_ptr<Node<ItemType>>& Node<ItemType>::getNextUnique()
{
	return this->next;
}

