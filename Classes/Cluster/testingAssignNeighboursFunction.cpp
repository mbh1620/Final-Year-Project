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

	clock_t start = clock();

	objReader.readObjFile("sphere-18.obj", vertices, triangles);
	// objReader.readObjFile("protrudingTestCube.obj", vertices, triangles);
	// objReader.readObjFile("testCubeMoreDetailOneSide.obj", vertices, triangles);

	std::cout << "Number of vertices: " << vertices.size() << "\n";
	std::cout << "Number of triangles: " << triangles.size() << "\n";

	clock_t end = clock();

	std::cout << "Time Taken For ReadObjFile function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";

	start = clock();

	// assignNeighbouringTriangles(triangles);

	assignNeighbouringTriangles(triangles);

	end = clock();

	std::cout << "Time Taken For assignNeighbouringTriangles function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";
}