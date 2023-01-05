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

	objReader.readObjFile("protrudingTestCube.obj", vertices, triangles);

	assignNeighbouringTriangles(triangles);

	Cluster cluster1 = Cluster(1, triangles[11], 0.8);

	std::unordered_map<int, Triangle> globalUsedTriangles;

	cluster1.createCluster(triangles, globalUsedTriangles, vertices);

	// cluster1.displayClusterTriangles();

	cluster1.displayEdges();

	cluster1.colourCluster(materials, triangles);

	int smallestIndex = cluster1.getSmallestEdgeIndex();

	std::cout << "smallest index "<< smallestIndex;

	// cluster1.edgeCollapse(1, vertices);
	cluster1.edgeCollapse(17, false, vertices);
	cluster1.edgeCollapse(8, true, vertices);
	cluster1.edgeCollapse(7, false, vertices);
	cluster1.edgeCollapse(1, true, vertices);
	cluster1.edgeCollapse(5, false, vertices);

	cluster1.displayEdges();
	// cluster1.edgeCollapse(1, true, vertices);
	// cluster1.edgeCollapse(7, false, vertices);
	// cluster1.edgeCollapse(8, true, vertices);
	// cluster1.edgeCollapse(1, true, vertices);
	
	std::vector<Triangle> outputTriangles;

	outputTriangles.push_back(dummyTriangle);

	std::vector<Triangle> producedTriangles = cluster1.generateOutputTriangles(vertices);

	for(int i = 0; i < producedTriangles.size(); i++){
		outputTriangles.push_back(producedTriangles[i]);
	}

	std::vector<Edge> edges;

	edges.push_back(Edge(1, 0,0, vertices));

	for(int i = 0; i < cluster1.getClusterEdges().size(); i++){
		edges.push_back(cluster1.getClusterEdges()[i]);
	}


	objReader.writeObjFile("outputCube", vertices, outputTriangles, materials, edges, true, true);

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


