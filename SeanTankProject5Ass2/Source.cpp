#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 

using namespace std;
#define STUDENTDATAFILE "StudentData.txt"
#define STUDENTEMAILFILE "StudentData_Emails.txt"

struct STUDENT_DATA {
private:
	string firstName;
	string lastName;
public:
	STUDENT_DATA(string firstName, string lastName) {
		this->firstName = firstName;
		this->lastName = lastName;
	}
	friend ostream& operator<< (std::ostream& cout, STUDENT_DATA sd) {
		return cout << sd.firstName << " " << sd.lastName << endl;
	}
};

/*
* Take a string of [Last name], [First name]
* Split it by comma, then return a STUDENT_DATA object
*/
STUDENT_DATA ParseStringToStudentData(string line) {
	vector<string> names;
	string name;
	stringstream ssLine(line);
	while (getline(ssLine, name, ',')) {
		names.push_back(name);
	}
	return STUDENT_DATA(names.back(), names.front());
}

/*
* Take an open file and a vector of STUDENT_DATA
* Read the file line by line
* Fill the vector with a STUDENT_DATA object
*/
void PopulateVectorFromFile(ifstream file, vector <STUDENT_DATA> &classList) {
	string line;
	while (getline(file, line)) {
		classList.push_back(ParseStringToStudentData(line));
	}
}

/*
* Take a vector and print to cout every element.
* Iterator can be found from C++ reference Docs: https://cplusplus.com/reference/vector/vector/end/
*/
void PrintClassList(vector <STUDENT_DATA> classList) {
	for (vector<STUDENT_DATA>::iterator it = classList.begin(); it != classList.end(); ++it)
		cout << *it;
}

int main() {
	vector <STUDENT_DATA> classList;
	PopulateVectorFromFile(ifstream (STUDENTDATAFILE), classList);
#ifdef _DEBUG
	PrintClassList(classList);
#endif
	return 1;
}