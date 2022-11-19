#include <iostream>
#include "../Triangle/Triangle.hpp"
#include "../ReadWriter/ReadWriter.cpp"


//----------------------------------------------------------------
//						ReadWriter Class Testing
//----------------------------------------------------------------

//Author: Matthew Haywood

// Testing the Functions of the Read and Writer Class

using namespace std;

int main() {

	int passedCases = 0;
	int totalCases = 0;

	cout << "\n\n";

	ReadWriter objReader = ReadWriter();

	std::vector<Vertex> vertices;
	// std::vector<Triangle> triangles;

	// Triangle t1 = Triangle(1, v1,v2,v3);

	objReader.readObjFile("testObjFile.obj", vertices);

	for(int i = 0; i < vertices.size(); i++){
		std::cout << vertices[i].get_Id() << " " << vertices[i].get('x') << " " << vertices[i].get('y') << " " << vertices[i].get('z') << "\n";
	}

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

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
