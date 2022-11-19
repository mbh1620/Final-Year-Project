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

	Vertex vertex1 = Vertex(1, 1.0, 2.0, 3.0);
	Vertex vertex2 = Vertex(2, 2.0, 3.0, 4.0);
	Vertex vertex3 = Vertex(3, 3.0, 2.0, 1.0);

	std::vector<Vertex> inputVertices;

	inputVertices.push_back(vertex1);
	inputVertices.push_back(vertex2);
	inputVertices.push_back(vertex3);

	int TRIANGLE_ID = 1;

	Triangle triangle1 = Triangle(TRIANGLE_ID, vertex1, vertex2, vertex3);

	int passedCases = 0;
	int totalCases = 0;

	cout << "\n\n";

	string TestName = "Triangle - Test 1 [Construct a Triangle]";
	totalCases += 1;

	if (string(typeid(triangle1).name()) == "8Triangle"){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 2 [Get Id Function]";
	totalCases += 1;

	if (triangle1.getId() == TRIANGLE_ID){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 3 [Get Vertices]";
	totalCases += 1;

	std::vector<Vertex> vertices = triangle1.getVertices();

	if (vertices[0].get('x') == inputVertices[0].get('x') && vertices[0].get('y') == inputVertices[0].get('y') && vertices[0].get('z') == inputVertices[0].get('z') &&
		vertices[1].get('x') == inputVertices[1].get('x') && vertices[1].get('y') == inputVertices[1].get('y') && vertices[1].get('z') == inputVertices[1].get('z') &&
		vertices[2].get('x') == inputVertices[2].get('x') && vertices[2].get('y') == inputVertices[2].get('y') && vertices[2].get('z') == inputVertices[2].get('z')){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 4 [set Vertices]";
	totalCases += 1;

	triangle1.setVertices(vertex1, vertex2, vertex3);

	if (vertices[0].get('x') == inputVertices[0].get('x') && vertices[0].get('y') == inputVertices[0].get('y') && vertices[0].get('z') == inputVertices[0].get('z') &&
		vertices[1].get('x') == inputVertices[1].get('x') && vertices[1].get('y') == inputVertices[1].get('y') && vertices[1].get('z') == inputVertices[1].get('z') &&
		vertices[2].get('x') == inputVertices[2].get('x') && vertices[2].get('y') == inputVertices[2].get('y') && vertices[2].get('z') == inputVertices[2].get('z')){
		
		passedCases += 1;
		
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	// TestName = "Triangle - Test 4 [set NeighbouringTriangles]";
	// totalCases += 1;

	// //Maybe change this to a model loader and load in points from a file 

	// Vertex vertex4 = Vertex(4, 3.2, 4.5, 6.5);
	// Vertex vertex5 = Vertex(5, 3.2, 3.4, 2.3);
	// Vertex vertex6 = Vertex(6, 5.6, 6.8, 3.2);

	// std::vector<Vertex> inputVertices2;

	// inputVertices2.push_back(vertex4);
	// inputVertices2.push_back(vertex5);
	// inputVertices2.push_back(vertex6);

	// Vertex vertex4 = Vertex(7, 3.6, 7.5, 8.5);
	// Vertex vertex5 = Vertex(8, 3.7, 4.4, 3.3);
	// Vertex vertex6 = Vertex(9, 6.6, 5.8, 4.2);

	// std::vector<Vertex> inputVertices3;

	// inputVertices3.push_back(vertex4);
	// inputVertices3.push_back(vertex5);
	// inputVertices3.push_back(vertex6);

	// Triangle triangle2 = Triangle(2, inputVertices2);
	// Triangle triangle3 = Triangle(3, inputVertices3);
	// Triangle triangle4 = Triangle(4, inputVertices4);

	// if (vertices[0].get('x') == inputVertices[0].get('x') && vertices[0].get('y') == inputVertices[0].get('y') && vertices[0].get('z') == inputVertices[0].get('z') &&
	// 	vertices[1].get('x') == inputVertices[1].get('x') && vertices[1].get('y') == inputVertices[1].get('y') && vertices[1].get('z') == inputVertices[1].get('z') &&
	// 	vertices[2].get('x') == inputVertices[2].get('x') && vertices[2].get('y') == inputVertices[2].get('y') && vertices[2].get('z') == inputVertices[2].get('z')){
		
	// 	passedCases += 1;
		
	// } else {
	// 	cout << TestName << " FAILED! \n";
	// 	cout << "\n\n";
	// }

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
