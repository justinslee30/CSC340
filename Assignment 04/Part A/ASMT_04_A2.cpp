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

void kickSport(const unique_ptr<SportName> uPtr_SportName)
{
	cout << "Bye Bye " << uPtr_SportName->getName() << endl;
}

int main()
{
	unique_ptr<SportName> SportName_uPtr_1{ make_unique<SportName>("Soccer") };
	unique_ptr<SportName> SportName_uPtr_2{ make_unique<SportName>("Baseball") };
	kickSport(move(SportName_uPtr_1));
	cout << "SportName_uPtr_1: " << SportName_uPtr_1 << endl;

	cout << "END OF PROGRAM" << endl;
	return 0;
}