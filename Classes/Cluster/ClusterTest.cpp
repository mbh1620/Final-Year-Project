#include <iostream>
#include "../Cluster/Cluster.cpp"
#include "../ReadWriter/ReadWriter.cpp"
#include "../../Functions/assignNeighbouringTriangles.hpp"


//----------------------------------------------------------------
//							Cluster Testing 
//----------------------------------------------------------------

//Author: Matthew Haywood

// Write Testing Detail Here


int main() {

	int passedCases = 0;
	int totalCases = 0;

	std::cout << "\n\n";

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

	objReader.readObjFile("sphere.obj", vertices, triangles);
	// objReader.readObjFile("protrudingTestCube.obj", vertices, triangles);
	// objReader.readObjFile("testCubeMoreDetailOneSide.obj", vertices, triangles);

	std::cout << "Number of vertices: " << vertices.size() << "\n";
	std::cout << "Number of triangles: " << triangles.size() << "\n";

	clock_t end = clock();

	std::cout << "Time Taken For ReadObjFile function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";

	start = clock();

	assignNeighbouringTriangles(triangles);

	assignNeighbouringTrianglesParallel(triangles);

	end = clock();

	std::cout << "Time Taken For assignNeighbouringTriangles function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";

	Cluster cluster1 = Cluster(1, triangles[4], 80);

	std::unordered_map<int, Triangle> globalUsedTriangles;

	start = clock();

	cluster1.createCluster(triangles, globalUsedTriangles, vertices);

	end = clock();

	std::cout << "Time Taken For createCluster function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";

	// // cluster1.displayClusterTriangles();

	// cluster1.displayEdges();

	// cluster1.colourCluster(materials, triangles);

	// int count = 0;
	// for(int i = 0; i < vertices.size(); i++){

	// 	std::cout << vertices[i].getEdgeOfCluster() << "\n";

	// 	count += vertices[i].getEdgeOfCluster();

	// }

	// std::cout << count;

	// start = clock();

	// cluster1.iterativelyEdgeCollapse(vertices, triangles);

	// end = clock();

	// std::cout << "Time Taken For iterativelyEdgeCollapse function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";
	
	// cluster1.displayEdges();
	
	// std::vector<Triangle> outputTriangles;

	// outputTriangles.push_back(dummyTriangle);

	// start = clock();

	// std::vector<Triangle> producedTriangles = cluster1.generateOutputTriangles(vertices);

	// end = clock();

	// std::cout << "Time Taken For generateOutputTriangles function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";	

	// for(int i = 0; i < producedTriangles.size(); i++){
	// 	outputTriangles.push_back(producedTriangles[i]);
	// }

	// std::vector<Edge> edges;

	// edges.push_back(Edge(1, 0, 0, vertices));

	// for(int i = 0; i < cluster1.getClusterEdges().size(); i++){
	// 	edges.push_back(cluster1.getClusterEdges()[i]);
	// }

	// start = clock();

	// objReader.writeObjFile("outputCube", vertices, outputTriangles, materials, edges, true, true);

	// end = clock();

	// std::cout << "Time Taken For writeObjFile function: " << (double)(clock()- start)/CLOCKS_PER_SEC << "s \n";	

	// /*Copy per test case

	// string TestName = "[TestName]";
	// totalCases += 1;

	// if (passing testing conditions here){
	// 	passedCases += 1
	// } else {
	// 	cout << TestName << " FAILED! \n";
	// 	cout << "\n\n";
	// }

	// */

	// cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	// cout << "\n\n";

}


