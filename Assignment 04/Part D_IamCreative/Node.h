//	Node.h
//  Created by Frank M. Carrano and Timothy M. Henry.
//	Updated by Duc Ta
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

#pragma once
#include <memory>
using namespace std;

template<typename ItemType>
class Node {
public:
	Node();
	Node(const ItemType&);
	Node(const ItemType&, unique_ptr<Node<ItemType>>&);
	~Node(); //added destructor
	void setItem(const ItemType&);
	void setNext(unique_ptr<Node<ItemType>>&);
	ItemType getItem() const;
	Node<ItemType>* getNext() const;
	unique_ptr<Node<ItemType>>& getNextUnique();

private:

	ItemType item{};			 // A data item
	unique_ptr<Node<ItemType>> next{ nullptr }; // Pointer to next node
};