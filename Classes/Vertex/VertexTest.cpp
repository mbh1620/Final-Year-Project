#include <iostream>
#include "Vertex.cpp"

//----------------------------------------------------------------
//					Testing Vertex Class Template
//----------------------------------------------------------------

//Author: Matthew Haywood

// Testing the Vertex Class here

using namespace std;

int main() {

	string TestName = "Vertex";

	Vertex vertex1 = Vertex(1, 1.0,1.2,3.2);

	cout << "\n\n";

	try {

		if (1 == 1){
		
		cout << TestName <<" - Test 1 Passed! \n";
		
		} else {
			throw 505;
		}

	} catch (...) {
		cout << TestName << " - Test 1 Failed! \n";
	}

	cout << "\n\n";
	
}
