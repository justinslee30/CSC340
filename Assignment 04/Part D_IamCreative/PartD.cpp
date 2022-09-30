//	LinkedBagClient340.cpp
//	Created by: Duc Ta

#include "Include.h"

//
//
// PLEASE DO NOT CHANGE THIS FILE
//
//

void displayBag(const unique_ptr<LinkedBag<string>>&);

int main() {

	cout << "----- LINKED BAG 340 C++-----" << endl << endl;

	// 1. Create a bag and add initial nodes
	cout << "--->>>>> Test 1 --->>>>>" << endl;
	unique_ptr<LinkedBag<string>> bag { make_unique <LinkedBag<string>>() };
	
	// A small vector of small objects to test the bag
	vector<string> items { "#-END", "5-FIVE", "4-FOUR", "4-FOUR", "3-THREE", "2-TWO", "1-ONE", "0-ZERO", "#-BEGIN" };
	cout << " \n!add()...     ";
	vector<string>::const_iterator cItr;
	for (cItr = items.begin(); cItr  != items.end(); cItr++) {
		cout << "\n"<< *cItr << " ";
		bool success = bag->add(*cItr);
		if ( !success) {
			cout << " !add() FAILED: " << *cItr << endl;
		}
	}
	displayBag(bag);

	// 2. Remove the second node
	cout << "\n--->>>>> Test 2 --->>>>>";
	cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	displayBag(bag);
	cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	cout << "\n !removeSecondNode340()... ";
	bag->removeSecondNode340();
	displayBag(bag);
	
	// 3. Add a node to the end of the linked list
	cout << "\n--->>>>> Test 3 --->>>>>";
	cout << "\n !addEnd340()... ";
	bag->addEnd340("9-NINE");
	cout << "\n !addEnd340()... ";
	bag->addEnd340("4-FOUR"); 
	displayBag(bag);
	cout << "\n !addEnd340()... ";
	bag->addEnd340("9-NINE");
	cout << "\n !addEnd340()... ";
	bag->addEnd340("0-ZERO");
	displayBag(bag);

	unique_ptr<Node<string>> n0{ make_unique<Node<string>>("LB START") };
	unique_ptr<Node<string>> n1{ make_unique<Node<string>>("LB END") };
	unique_ptr<LinkedBag<string>> sorted_bag{ bag->getSortedLB(n0, n1) };
	cout << "\n------Distinct Sorted Bag-------";
	displayBag(sorted_bag);

	return 0;
}

// Display the current contents in the bag
void displayBag(const unique_ptr<LinkedBag<string>>& bag) {
	cout << "\n !Display bag: ";
	auto bagItems = make_unique<vector<string>>(bag->toVector());

	vector<string>::const_iterator cItr;
	for (cItr = bagItems->begin(); cItr  != bagItems->end(); cItr++) {
		cout << *cItr << " ";
	}
	
	cout << "\n  -----------> " << bagItems->size() << " item(s) total";
	cout << endl;
}