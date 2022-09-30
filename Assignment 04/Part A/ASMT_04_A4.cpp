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
	unique_ptr<SportName> football_unique{ make_unique<SportName>("Football") };
	cout << "addressof(), football_unique: " << addressof(*football_unique) << endl;
	cout << "Converting..." << endl;
	shared_ptr<SportName> football_shared_1{ move(football_unique) };
	cout << "addressof(), football_unique: " << addressof(*football_unique) << endl;
	cout << "addressof(), football_shared_1: " << addressof(*football_shared_1) << endl;
	shared_ptr<SportName> football_shared_2{ football_shared_1 };
	cout << "addressof(), football_shared_2: " << addressof(*football_shared_2) << endl;
	cout << "use_count(), football_shared: " << football_shared_1.use_count() << endl;
	football_shared_2.reset();
	cout << "addressof(), football_shared_1: " << addressof(*football_shared_1) << endl;
	cout << "addressof(), football_shared_2: " << addressof(*football_shared_2) << endl;
	cout << "use_count(), football_shared: " << football_shared_1.use_count() << endl;
}