#include <iostream>
#include "../Vertex/Vertex.hpp"
#include "Triangle.cpp"
#include <vector>

//----------------------------------------------------------------
//					Triangle Class Testing
//----------------------------------------------------------------

//Author: Matthew Haywood

// Testing Used to test the Triangle Class
using namespace std;

int main() {

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

	int passedCases = 0;
	int totalCases = 0;

	Vertex vertex1 = Vertex(0, 1.2, 2.4, 3.5);
	Vertex vertex2 = Vertex(1, 2.0, 3.0, 4.0);
	Vertex vertex3 = Vertex(2, 3.0, 2.0, 1.0);

	std::vector<Vertex> globalVertices;

	globalVertices.push_back(vertex1);
	globalVertices.push_back(vertex2);
	globalVertices.push_back(vertex3);

	int TRIANGLE_ID = 1;

	Triangle triangle1 = Triangle(TRIANGLE_ID, 0,1,2);

	cout << triangle1.getVertices(globalVertices)[0].get('x') << triangle1.getVertices(globalVertices)[0].get('y');

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
