#include <iostream>
#include "Vertex.cpp"

//----------------------------------------------------------------
//					Testing Vertex Class
//----------------------------------------------------------------

//Author: Matthew Haywood

// Testing the Vertex Class here

using namespace std;

int main() {

	Vertex vertex1 = Vertex(1, 1.0,1.2,3.2);

	string TestName = "Vertex - Test 1 get x";

	int passedCases = 0;

	int totalCases = 0;

	cout << "\n\n";

	totalCases += 1;

	if (vertex1.get('x') == float(1.0)){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Vertex - Test 2 get y";
	totalCases += 1;

	if (vertex1.get('y') == float(1.2)){
		
		passedCases += 1;
		
	} else {

		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Vertex - Test 3 get z";
	totalCases += 1;

	if (vertex1.get('z') == float(3.2)){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Vertex - Test 4 getId";
	totalCases += 1;

	if (vertex1.get_Id() == 1){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Vertex - Test 5 Add two Vertices together";
	totalCases += 1;

	Vertex vertex2 = Vertex(2, 3.4, 4.2, 5.6);

	vertex1 = vertex1 + vertex2;

	if (vertex1.get('x') == float(4.4)){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Vertex - Test 6 Subtract two Vertices together";
	totalCases += 1;

	vertex1 = vertex1 - vertex2;

	if (vertex1.get('x') == float(1.0)){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	
	cout << "\n\n";
}
