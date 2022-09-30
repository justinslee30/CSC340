#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Sport {
public:
	Sport() {}
	explicit Sport(string name, int ranking, vector<int> scores) {
		this->name = make_unique<string>(name);
		this->ranking = make_unique<int>(ranking);
		this->scores = make_unique<vector<int>>(scores);
		
	}
	~Sport() {
		cout << *this->name << " gone." << endl;
		cout << *this->ranking << " peace out." << endl;
	}
	const string& getName() const {
		return *this->name;
	}

	const int& getRanking() const
	{
		return *this->ranking;
	}

	const vector<int>& getScores() const
	{
		return *this->scores;
	}
private:
	unique_ptr<string> name{ nullptr };
	unique_ptr<int> ranking{ nullptr };
	unique_ptr<vector<int>> scores{ nullptr };
};

void kickSport(const unique_ptr<Sport> uPtr_Sport)
{
	cout << "Bye Bye " << uPtr_Sport->getName() << endl;
}

int main()
{
	vector<int> SoccerScores{ 2,1 };
	vector<int> BaseballScores{ 5,4 };
	unique_ptr<Sport> SportName_uPtr_1{ make_unique<Sport>("Soccer",3,SoccerScores) };
	unique_ptr<Sport> SportName_uPtr_2{ make_unique<Sport>("Baseball",2,BaseballScores) };
	kickSport(move(SportName_uPtr_1));
	cout << "SportName_uPtr_1: " << SportName_uPtr_1 << endl;

	cout << "END OF PROGRAM" << endl;
	return 0;
}