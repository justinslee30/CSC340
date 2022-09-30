#include "Dictionary.h"

Dictionary::Dictionary()
{
	//default constructor
}

Dictionary::Dictionary(vector<string> pos, vector<string> actionWords)
{
	mPos = pos;
	mActionWords = actionWords;
}

void Dictionary::load()
{
	//making sure the path of the file name is correct
	fstream rawData;
	string fileName;
	string termOrDef;
	string term;
	string pos;
	string def;
	int numTerm = 0;
	int totalNumDefs = 0;
	cout << "! Opening data file... ";
	cin >> fileName;
	rawData.open(fileName);
	while (rawData.fail())
	{
		cout << "<!>ERROR<!> ====> File could not be opened." << endl;
		cout << "<!>ERROR<!> ====> Provided file path: " << fileName << endl;
		cout << "Enter the CORRECT data file path: ";
		cin >> fileName;
		rawData.open(fileName);
	}
	cout << "! Loading data..." << endl;
	//opening the file name given the path and placing it into our unordered map
	while (rawData)
	{
		string line;
		if (!getline(rawData, line)) break;
		istringstream ssLine(line);
		while (getline(ssLine, termOrDef, '|'))
		{
			if (numTerm == 0)
			{
				term = termOrDef;
			}
			else
			{
				pos = termOrDef.substr(0, termOrDef.find("-=>>")- 1);
				def = termOrDef.substr(termOrDef.find("-=>>") + 5);
				def = string(1,char(toupper(def[0]))) + def.substr(1,def.size());
				mDictData[term].push_back(make_pair(pos, def));
				totalNumDefs++;
			}
			numTerm++;
		}
		sort(mDictData[term].begin(), mDictData[term].end());
		numTerm = 0;
	}
	//text to show it is closed
	cout << "! Loading completed..." << endl;
	cout << "! Closing data file... " << fileName << endl;
	rawData.close();
	cout << endl;
	cout << "====== DICTIONARY 340 C++ =====" << endl;
	cout << "------ Keywords: " << mDictData.size() << endl;
	cout << "------ Definitions: " << totalNumDefs << endl;
	cout << "\n";
}

void Dictionary::setPos(vector<string> pos)
{
	mPos = pos;
}

void Dictionary::setActionWords(vector<string> actionWords)
{
	mActionWords = actionWords;
}

void Dictionary::help()
{
	cout <<
		"|\n"
		"PARAMETER HOW-TO, please enter:\n"
		"1. A search key -then 2. An optional part of speech - then\n"
		"3. An optional 'distinct' -then 4. An optional 'reverse' \n"
		"|\n";
}

void Dictionary::invalidEntry()
{
	cout <<
		"|\n"
		"<NOT FOUND> To be considered for the next release. Thank you.\n"
		"|\n";
	help();
}

void Dictionary::invalidAction(string invalid_action, int n)
{
	switch (n)
	{
	case 1: 
		invalidEntry();
		break;
	case 2:
		cout <<
			"\n|\n"
			"<The entered 2nd parameter '" + invalid_action + "' is NOT a part of speech.>\n"
			"<The entered 2nd parameter '" + invalid_action + "' is NOT 'distinct'.>\n"
			"<The entered 2nd parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
			"<The entered 2nd parameter '" + invalid_action + "' was disregarded.>\n"
			"<The " + to_string(n) + "nd parameter should be a part of speech or 'distinct' or 'reverse'.>\n"
			"|\n";
		break;
	case 3:
		cout <<
			"|\n"
			"<The entered 3rd parameter '" + invalid_action + "' is NOT 'distinct'.>\n"
			"<The entered 3rd parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
			"<The entered 3rd parameter '" + invalid_action + "' was disregarded.>\n"
			"<The 3rd parameter should be 'distinct' or 'reverse'.>\n"
			"|\n";
		break;
	default:
		cout <<
			"|\n"
			"<The entered 4th parameter '" + invalid_action + "' is NOT 'reverse'.>\n"
			"<The entered 4th parameter '" + invalid_action + "' was disregarded.>\n"
			"<The 4th parameter should be 'distinct' or 'reverse'.>\n"
			"|\n";
		break;
	}
}

unordered_map<string, vector<pair<string, string>>> Dictionary::keyword(string keyword)
{
	unordered_map<string, vector<pair<string, string>>> output;
	unordered_map<string, vector<pair<string, string>>>::const_iterator entry = mDictData.find(keyword);
	output.insert({ entry->first,entry->second });
	return output;
}

void Dictionary::distinct(unordered_map<string, vector<pair<string, string>>> &data)
{
	data.begin()->second.erase(unique(data.begin()->second.begin(), data.begin()->second.end()), data.begin()->second.end());
}

void Dictionary::reverse(unordered_map<string, vector<pair<string, string>>> &data)
{
	vector<pair<string, string>> reverseData(data.begin()->second.rbegin(), data.begin()->second.rend());
	data.begin()->second.swap(reverseData);
}

void Dictionary::pos(unordered_map<string, vector<pair<string, string>>> &data, string pos)
{
	vector<pair<string, string>> newData;
	for (auto itD = data.begin()->second.begin(); itD != data.begin()->second.end(); itD++)
	{
		if (itD->first == pos)
		{
			newData.push_back(*itD);
		}
	}
	data.begin()->second = newData;
}

void Dictionary::formatQuery(string &query)
{
	//trim off leading and trailing whitespace first
	string whitespace = " ";
	int queryBegins = query.find_first_not_of(whitespace);
	int queryEnds = query.find_last_not_of(whitespace);
	if (queryBegins == queryEnds)
	{
		query = "";
	}
	else
	{
		query = query.substr(queryBegins, queryEnds - queryBegins + 1);
	}
	//now get rid of whitespace in between words
	int spaceBegins = query.find_first_of(whitespace);
	string fill = " ";
	while (spaceBegins != string::npos)
	{
		int spaceEnds = query.find_first_not_of(whitespace, spaceBegins);
		int range = spaceEnds - spaceBegins;
		query.replace(spaceBegins, range, fill);

		int newSpace = spaceBegins + fill.length();
		spaceBegins = query.find_first_of(whitespace, newSpace);
	}
	//lowercase it all
	transform(query.begin(), query.end(), query.begin(), ::tolower);
}

queue<string> Dictionary::validInputCheck(unordered_map<string, vector<pair<string, string>>> data, string query)
{
	istringstream ssQuery(query);
	string intermediate;
	queue<string> intermediateQuery;
	queue<string> validQuery;
	int queryCounter = 1;
	while (getline(ssQuery,intermediate,' '))
	{
		intermediateQuery.push(intermediate);
	}
	if (intermediateQuery.size() > 4)
	{
		return validQuery;
	}
	//takes care of an empty input
	if (intermediateQuery.size() == 0)
	{
		intermediateQuery.push("");
	}
	while (!intermediateQuery.empty())
	{
		switch (queryCounter)
		{
		case 1:
		{
			bool isValid = false;
			string term1 = intermediateQuery.front();
			unordered_map<string, vector<pair<string, string>>>::const_iterator findKeyword = data.find(term1);
			if (findKeyword != data.end() || term1 == mActionWords[0] || term1 == mActionWords[1] || term1 == "")
			{
				validQuery.push(term1);
				isValid = true;
			}
			if (!isValid)
			{
				return validQuery;
			}
			queryCounter++;
			intermediateQuery.pop();
			break;
		}
		case 2:
		{
			bool isValid = false;
			string term2 = intermediateQuery.front();
			vector<string>::iterator it = find(mPos.begin(), mPos.end(), term2);
			if (it != mPos.end() || term2 == mActionWords[2] || term2 == mActionWords[3])
			{
				validQuery.push(term2);
				isValid = true;
			}
			if (!isValid)
			{
				invalidAction(term2, queryCounter);
			}
			intermediateQuery.pop();
			queryCounter++;
			break;
		}
		case 3:
		{
			bool isValid = false;
			string term3 = intermediateQuery.front();
			if (term3 == mActionWords[2] || term3 == mActionWords[3])
			{
				validQuery.push(term3);
				isValid = true;
			}
			if (!isValid)
			{
				invalidAction(term3, queryCounter);
			}
			intermediateQuery.pop();
			queryCounter++;
			break;
		}
		case 4:
		{
			bool isValid = false;
			string term4 = intermediateQuery.front();
			if (term4 == mActionWords[3])
			{
				validQuery.push(term4);
				isValid = true;
			}
			if (!isValid)
			{
				invalidAction(term4, queryCounter);
			}
			intermediateQuery.pop();
			queryCounter++;
			break;
		}
		default:
		{
			intermediateQuery.pop();
			queue<string> empty;
			swap(validQuery, empty);
			break;
		}
		}
	}
	return validQuery;
}

void Dictionary::inputHandling(unordered_map<string, vector<pair<string, string>>> data, queue<string> query)
{
	unordered_map<string, vector<pair<string, string>>> output;
	bool isHelp = false;
	bool isKeyword = true;
	while (!query.empty())
	{
		string current = query.front();
		unordered_map<string, vector<pair<string, string>>>::const_iterator findKeyword = data.find(current);
		if (current == "")
		{
			isHelp = true;
		}
		else if (findKeyword != data.end() && isKeyword)
		{
			output = keyword(current);
			isKeyword = false;
		}
		else if (current == mActionWords[0])
		{
			isHelp = true;
		}
		else if (current == mActionWords[2])
		{
			distinct(output);
		}
		else if (current == mActionWords[3])
		{
			reverse(output);
		}
		else
		{
			pos(output, current);
		}
		query.pop();
	}
	if (output.empty() && isHelp)
	{
		help();
	}
	else if ((output.empty() || output.begin()->second.size() == 0) && !isHelp)
	{
		invalidEntry();
	}
	else
	{
		print(output);
	}
}

void Dictionary::print(unordered_map<string, vector<pair<string, string>>> const data)
{
	string newKeyword;
	for (unsigned int i = 0; i < data.begin()->first.length(); i++)
	{
		if (i == 0 || data.begin()->first.find("csc") != string::npos)
		{
			newKeyword.push_back(toupper(data.begin()->first[i]));
		}
		else
		{
			newKeyword.push_back(data.begin()->first[i]);
		}
	}
	cout << "|\n";
	for (auto itD = data.begin()->second.begin(); itD != data.begin()->second.end(); itD++)
	{
		cout << newKeyword << " [" << itD->first << "] : " << itD->second << endl;
	}
	cout << "|\n";
}

void Dictionary::run()
{
	int numInputs = 1;
	string query;
	string dummy;
	cout << "Search [" << numInputs << "]: ";
	getline(cin, dummy);
	getline(cin, query);
	formatQuery(query);
	while (query != mActionWords[1])
	{
		queue<string> validQuery = validInputCheck(mDictData, query);
		inputHandling(mDictData, validQuery);
		numInputs++;
		cout << "Search [" << numInputs << "]: ";
		getline(cin, query);
		formatQuery(query);
	}
	cout << "-----THANK YOU-----";
}
