#include <iostream>
#include <string>
using namespace std;

class SportName {
public:
	SportName() {}
	explicit SportName(string name) {
		this->name = make_unique<string>(name);
	}
	~SportName() {
		cout << *this->name << ": Destructed." << endl;
	}
	const string& getName() const {
		return *this->name;
	}
private:
	unique_ptr<string> name{ nullptr };
};

int main()
{
	shared_ptr<SportName> basketball_shared_1{ make_shared<SportName>("Basketball") };
	weak_ptr<SportName> basketball_weak_1{ basketball_shared_1 };
	shared_ptr<SportName> basketball_shared_2{ basketball_weak_1.lock() };
	cout << "basketball_weak_1, expired() : " << basketball_weak_1.expired() << endl;
	basketball_shared_1.reset();
	cout << "SHARED 1 RESET..." << endl;
	cout << "basketball_weak_1, expired() : " << basketball_weak_1.expired() << endl;
	basketball_shared_2.reset();
	cout << "SHARED 2 RESET..." << endl;
	cout << "basketball_weak_1, expired() : " << basketball_weak_1.expired() << endl;

	shared_ptr<SportName> water_polo_shared_1{ make_shared<SportName>("Water Polo") };
	weak_ptr<SportName> water_polo_weak_1{ water_polo_shared_1 };
	cout << "water_polo_weak_1, expired(): " << water_polo_weak_1.expired() << endl;
	water_polo_weak_1.reset();
	cout << "WEAK 1 RESET..." << endl;
	cout << "water_polo_weak_1, expired(): " << water_polo_weak_1.expired() << endl;

	return 0;
}