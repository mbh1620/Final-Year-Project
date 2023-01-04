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
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	*/

	int passedCases = 0;
	int totalCases = 0;

	Vertex vertex1 = Vertex(0, 1.0, 2.4, 3.5);
	Vertex vertex2 = Vertex(1, 1.0, 3.0, 4.0);
	Vertex vertex3 = Vertex(2, 1.0, 2.0, 1.0);

	std::vector<Vertex> globalVertices;

	globalVertices.push_back(vertex1);
	globalVertices.push_back(vertex2);
	globalVertices.push_back(vertex3);

	int TRIANGLE_ID = 1;

	Triangle triangle1 = Triangle(TRIANGLE_ID, 0,1,2, globalVertices);

	string TestName = "\nTriangle - Test 1 Construction";
	totalCases += 1;

	if (string(typeid(triangle1).name()) == "8Triangle"){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "\nTriangle - Test 2 Copy Constructor";
	totalCases += 1;

	Triangle triangle2 = triangle1;

	if (triangle2.getId() == 1){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "\nTriangle - Test 3 Assignment Operator";
	totalCases += 1;

	Triangle triangle3 = Triangle(2, 0, 1, 2, globalVertices);

	triangle3 = triangle1;

	if (triangle2.getId() == TRIANGLE_ID){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "\nTriangle - Test 4 getId()";
	totalCases += 1;

	int id = triangle1.getId();

	if (id == TRIANGLE_ID){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "\nTriangle - Test 5 getVertexIndices()";
	totalCases += 1;

	std::vector<int> returnedIndices = triangle1.getVertexIndices();

	if (returnedIndices[0] == 0 && returnedIndices[1] == 1 && returnedIndices[2] == 2){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}


	TestName = "\nTriangle - Test 6 getVertices()";
	totalCases += 1;

	std::vector<Vertex> returnedVertices = triangle1.getVertices(globalVertices);

	if (returnedVertices.size() == 3 && returnedVertices[0].getId() == 0 && returnedVertices[1].getId() == 1 && returnedVertices[2].getId() == 2){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 7 getTriangleNormal()";
	totalCases += 1;

	Vector3D triangleNormal = triangle1.getTriangleNormal();

	if (triangleNormal.getNormalisedDirectionComponents()[0] == -1 && triangleNormal.getNormalisedDirectionComponents()[1] == 0 && triangleNormal.getNormalisedDirectionComponents()[2] == 0){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 8 setVertexIndices()";
	totalCases += 1;

	triangle1.setVertexIndices(4,5,6);

	if (triangle1.getVertexIndices()[0] == 4 && triangle1.getVertexIndices()[1] == 5 && triangle1.getVertexIndices()[2] == 6){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 9 setNeighbouringTriangles()";
	totalCases += 1;

	Triangle triangle4 = triangle1;
	Triangle triangle5 = triangle1;
	Triangle triangle6 = triangle1;

	std::vector<Triangle> neighbouringTriangles;

	neighbouringTriangles.push_back(triangle4);
	neighbouringTriangles.push_back(triangle5);
	neighbouringTriangles.push_back(triangle6);

	triangle1.setNeighbouringTriangles(neighbouringTriangles);

	if (triangle1.getNeighbouringTriangles().size() == 3 && triangle1.getNeighbouringTriangles()[0].getId() == TRIANGLE_ID && triangle1.getNeighbouringTriangles()[1].getId() == TRIANGLE_ID && triangle1.getNeighbouringTriangles()[2].getId() == TRIANGLE_ID){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 10 setNeighbouringTriangle()";
	totalCases += 1;

	triangle2.setNeighbouringTriangle(triangle3);	

	if (triangle2.getNeighbouringTriangles().size() == 1 && triangle2.getNeighbouringTriangles()[0].getId() == TRIANGLE_ID ){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 11 setTriangleMaterial()";
	totalCases += 1;

	Material material1 = Material("Material1");

	material1.setKdParameter(232.0, 212.0, 146.0);

	triangle1.setTriangleMaterial(material1);

	if (triangle1.getTriangleMaterial().getKdParameter().getDirectionComponents()[0] == 232.0 && triangle1.getTriangleMaterial().getKdParameter().getDirectionComponents()[1] == 212.0 && triangle1.getTriangleMaterial().getKdParameter().getDirectionComponents()[2] == 146.0){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	TestName = "Triangle - Test 12 compareTriangleMaterial()";
	totalCases += 1;

	triangle2.setTriangleMaterial(material1);

	if (triangle1.compareTriangleMaterial(triangle2) == true && triangle1.compareTriangleMaterial(triangle3) == false){
		passedCases += 1;
	} else {
		cout << TestName << " FAILED! \n";
		cout << "\n\n";
	}

	cout << "\nTriangle - " << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
