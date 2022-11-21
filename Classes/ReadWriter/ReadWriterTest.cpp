#include <iostream>
#include "../Triangle/Triangle.cpp"
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
	Vertex dummyVertex = Vertex(0, 1.0, 1.0, 1.0);
	vertices.push_back(dummyVertex); // This is so the indexing starts from 1

	std::vector<Triangle> triangles;

	objReader.readObjFile("cube.obj", vertices, triangles);

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

	// for(int i = 0; i < triangles.size(); i++){
	// 	cout << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[0] << " " << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[1] << " " << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[2] << "\n";
	// }

	Vector3D triangleDifference = triangles[0].getTriangleNormal() - triangles[1].getTriangleNormal();

	triangleDifference.displayNormalisedDirectionComponents();

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
