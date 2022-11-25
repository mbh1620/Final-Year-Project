#include <iostream>
#include "../Triangle/Triangle.hpp"
#include "../../Functions/assignNeighbouringTriangles.hpp"
#include "../ReadWriter/ReadWriter.cpp"
#include "../Cluster/Cluster.cpp"
#include "../../Functions/createMultipleClusters.hpp"


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
	Vertex dummyVertex = Vertex(-100, -10.0, -11.0, -11.0);
	vertices.push_back(dummyVertex); // This is so the indexing starts from 1

	std::vector<Triangle> triangles;
	Triangle dummyTriangle = Triangle(-100,1,1,1, vertices);
	triangles.push_back(dummyTriangle); //This is so that triangles start from 1 and does not conflict with obj file
 
	std::vector<Cluster> clusters;

	std::vector<Material> materials;

	Material material2 = Material("default");

	material2.setKdParameter(0.3,0.5,0.6);

	materials.push_back(material2);

	objReader.readObjFile("cube.obj", vertices, triangles);

	assignNeighbouringTriangles(triangles);

	// createMultipleClusters(vertices, triangles, materials);
	Cluster cluster1 = Cluster(1, triangles[1], 0.05);

	cluster1.createCluster(triangles);

	cluster1.colourCluster(materials, triangles);

	cluster1.displayClusterTriangles();

	Cluster cluster2 = Cluster(1, triangles[3], 0.05);

	cluster2.createCluster(triangles);

	cluster2.colourCluster(materials, triangles);

	cluster2.displayClusterTriangles();

	Cluster cluster3 = Cluster(1, triangles[5], 0.05);

	cluster3.createCluster(triangles);

	cluster3.colourCluster(materials, triangles);

	cluster3.displayClusterTriangles();

	Cluster cluster4 = Cluster(1, triangles[7], 0.25);

	cluster4.createCluster(triangles);

	cluster4.colourCluster(materials, triangles);

	cluster4.displayClusterTriangles();

	objReader.writeObjFile("outputCube", vertices, triangles, materials, true, true);
	/*Copy per test cases

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

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
