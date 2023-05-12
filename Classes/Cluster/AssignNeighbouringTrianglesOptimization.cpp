//Assign Neighbouring Triangles Optimization

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

	objReader.readObjFile("testSphere2.obj", vertices, triangles);

	std::cout << "Vertices: " << vertices.size() << " Triangles: " << triangles.size() << "\n";

	clock_t start1 = clock();

	assignNeighbouringTrianglesParallel(triangles); 

	clock_t end = clock();

	

}