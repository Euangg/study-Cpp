#include<string>
class Person {
public:
	Person(const std::string& name, const Date& birthday, const Address& addr);
	std::string name()const;
	std::string birthDate()const;
	std::string address()const;
private:
	std::string theName;
	Date theBirthDate;
	Address theAddress;
};