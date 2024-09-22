#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream> 

using namespace std;
#define STUDENTDATAFILE "StudentData.txt"
#define STUDENTDATANUMARGS 2
#define STUDENTEMAILFILE "StudentData_Emails.txt"
#define STUDENTEMAILNUMARGS 3
#define PreRelease

struct STUDENT_DATA {
private:
	string firstName;
	string lastName;
	string email;
public:
	STUDENT_DATA(string firstName, string lastName, string email = "None") {
		this->firstName = firstName;
		this->lastName = lastName;
		this->email = email;
	}
	friend ostream& operator<< (std::ostream& cout, STUDENT_DATA sd) {
#ifdef PreRelease
		return cout << sd.firstName << " " << sd.lastName << " " << sd.email << endl;
#else
		return cout << sd.firstName << " " << sd.lastName << endl;
#endif
	}
};

/*
* Take a string of [Last name], [First name]
* Split it by comma, then return a STUDENT_DATA object
* If there is an issue with the number of lines in the text file I am throwing an error
*/
STUDENT_DATA ParseStringToStudentData(string line) {
	vector<string> names;
	string name;
	stringstream ssLine(line);
	
	while (getline(ssLine, name, ',')) {
		names.push_back(name);
	}
#ifdef PreRelease
	return (names.size() == STUDENTEMAILNUMARGS) ?  STUDENT_DATA(names[0], names[1], names[2]) : throw invalid_argument("Expected three values in txt file.");
#else
	return (names.size() == STUDENTDATANUMARGS) ? STUDENT_DATA(names[0], names[1]) : throw invalid_argument("Expected two values in txt file.");
#endif // PreRelease
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
* Vector.begin() gives the ref to the first element
* Since vectors are contiguous you can just increment your address to access each element
*/
void PrintClassList(vector <STUDENT_DATA> classList) {
	for (vector<STUDENT_DATA>::iterator it = classList.begin(); it != classList.end(); ++it)
		cout << *it;
}

int main() {
	vector <STUDENT_DATA> classList;
#ifdef PreRelease
	cout << "Running in PreRelease" << endl;
	PopulateVectorFromFile(ifstream(STUDENTEMAILFILE), classList);
#else
	cout << "Running in Standard" << endl;
	PopulateVectorFromFile(ifstream(STUDENTDATAFILE), classList);
#endif

#ifdef _DEBUG
	PrintClassList(classList);
#endif
	return 1;
}