#include <iostream>
#include "../Cluster/Cluster.cpp"
#include "../ReadWriter/ReadWriter.cpp"
#include "../../Functions/assignNeighbouringTriangles.hpp"


//----------------------------------------------------------------
//							Cluster Testing 
//----------------------------------------------------------------

//Author: Matthew Haywood

// Write Testing Detail Here

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
	Triangle dummyTriangle = Triangle(-1,0,0,0, vertices);
	triangles.push_back(dummyTriangle); //This is so that triangles start from 1 and does not conflict with obj file

	std::vector<Material> materials;

	Material material2 = Material("default");

	material2.setKdParameter(0.3,0.5,0.6);

	materials.push_back(material2);

	objReader.readObjFile("cube.obj", vertices, triangles);

	assignNeighbouringTriangles(triangles);

	Cluster cluster1 = Cluster(1, triangles[1], 0.05);

	cluster1.createCluster(triangles);

	cluster1.colourCluster(materials, triangles);

	cluster1.displayClusterTriangles();

	objReader.writeObjFile("outputCube", vertices, triangles, materials, true, true);


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
