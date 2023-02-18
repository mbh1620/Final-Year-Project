#include <iostream>
#include "Material.cpp"

//----------------------------------------------------------------
//						Testing Template
//----------------------------------------------------------------

//Author: Matthew Haywood

// Write Testing Detail Here

using namespace std;

int main() {

	int passedCases = 0;
	int totalCases = 0;

	cout << "\n\n";

	/*Copy per test case

	string TestName = "[TestName]";
	totalCases += 1;

	if (passing testing conditions here){
		passedCases += 1
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	*/

	Material material1 = Material("Wood");

	material1.setKdParameter(0.8, 0.8, 0.8);

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
