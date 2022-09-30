#pragma once
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include <algorithm>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <string.h>
#include <unordered_map>
#include <utility>
#include <vector>
using namespace std;

class Dictionary
{
private:
	unordered_map<string, vector<pair<string,string>>> mDictData;
	vector<string> mPos;
	vector<string> mActionWords;
public:
	//default constructor - DONE
	Dictionary();
	//constructor - would just copy data over to dictData - DONE
	Dictionary(vector<string>, vector<string>);
	//loading into dictData member variable given an fstream - DONE
	void load();
	//set mPos - DONE
	void setPos(vector<string> pos);
	//set mActionWords - DONE
	void setActionWords(vector<string> actionWords);
	//help function - DONE
	void help();
	//invalid entry function - DONE
	void invalidEntry();
	//invalid action function (includes invalid entry function) - DONE
	void invalidAction(string invalid_action, int n);
	//keyword function  - DONE
	unordered_map<string, vector<pair<string, string>>> keyword(string keyword);
	//distinct function - DONE
	void distinct(unordered_map<string, vector<pair<string, string>>> &data);
	//reverse function - DONE
	void reverse(unordered_map<string, vector<pair<string, string>>> &data);
	//part of speech function - DONE
	void pos(unordered_map<string, vector<pair<string, string>>> &data, string pos);
	//removing whitespace
	void formatQuery(string &query);
	//checks for valid input - DONE
	queue<string> validInputCheck(unordered_map<string, vector<pair<string, string>>> data, string query);
	//analyzes a valid input - NEED TO TEST
	void inputHandling(unordered_map<string, vector<pair<string, string>>> data, queue<string> query);
	//prints out result - DONE
	void print(unordered_map<string, vector<pair<string, string>>> const data);
	//TODO: run function that does everything
	void run();
};
#endif // !DICTIONARY_H
