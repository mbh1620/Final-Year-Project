#include <iostream>
#include "../Cluster/Cluster.cpp"
#include "../ReadWriter/ReadWriter.cpp"
#include "../../Functions/assignNeighbouringTriangles.hpp"

int main(){


	ReadWriter objReader = ReadWriter();

	//Set up vertices, triangles and materials vectors

	std::vector<Vertex> vertices;
	Vertex dummyVertex = Vertex(0, 1.0, 1.0, 1.0);
	vertices.push_back(dummyVertex); 

	std::vector<Triangle> triangles;
	Triangle dummyTriangle = Triangle(-1,0,0,0, vertices);
	triangles.push_back(dummyTriangle);

	std::vector<Material> materials;
	Material material2 = Material("default");
	material2.setKdParameter(0.3,0.5,0.6);
	materials.push_back(material2);

	objReader.readObjFile("protrudingTestCube.obj", vertices, triangles);

	assignNeighbouringTrianglesParallel(triangles); //Parallel

	Cluster cluster1 = Cluster(1, triangles[9], 70);

	std::unordered_map<int, Triangle> globalUsedTriangles;

	cluster1.createCluster(triangles, globalUsedTriangles, vertices);

	cluster1.iterativelyEdgeCollapse(vertices);

	std::vector<Edge> edges;

	edges.push_back(Edge(1, 0, 0, vertices));

	for(int i = 0; i < cluster1.getClusterEdges().size(); i++){
		edges.push_back(cluster1.getClusterEdges()[i]);
	}

	std::vector<Triangle> producedTriangles;

	producedTriangles.push_back(dummyTriangle);

	for(int i = 0; i < cluster1.generateOutputTriangles(vertices).size(); i++){
		producedTriangles.push_back(cluster1.generateOutputTriangles(vertices)[i]);
	}

	cluster1.generateOutputTriangles(vertices);

	objReader.writeObjFile("outputCube", vertices, producedTriangles, materials, edges, true, true);


}