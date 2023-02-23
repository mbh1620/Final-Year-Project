//Main file

#include <iostream>
#include "../Cluster/Cluster.cpp"
#include "../ReadWriter/ReadWriter.cpp"
#include "../../Functions/assignNeighbouringTriangles.hpp"
#include "../../Functions/createMultipleClusters.hpp"

//----------------------------------------------------------------
//			Main file for all of the high level functions
//----------------------------------------------------------------

//Author: Matthew Haywood

// Write Testing Detail Here

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

	//Read object into the vertices and triangles vectors

	objReader.readObjFile("protrudingTestCube.obj", vertices, triangles);

	//Assign neighbouring triangles

	assignNeighbouringTriangles(triangles);

	std::vector<Edge> edges;

	edges.push_back(Edge(1, 0, 0, vertices));

	std::vector<Triangle> outputTriangles = createMultipleClusters(vertices, triangles, materials, edges,8, 80);

	objReader.writeObjFile("outputCube", vertices, outputTriangles, materials, edges, true, true);

}


