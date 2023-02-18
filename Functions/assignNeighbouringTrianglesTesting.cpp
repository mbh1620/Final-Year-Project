#include <iostream>
#include "assignNeighbouringTriangles.hpp"
// #include "../Classes/Triangle/Triangle.cpp"
#include "../Classes/ReadWriter/ReadWriter.cpp"

int main(){

	ReadWriter objReader = ReadWriter();

	std::vector<Vertex> vertices;
	
	Vertex dummyVertex = Vertex(0, 1.0, 1.0, 1.0);

	vertices.push_back(dummyVertex); // This is so the indexing starts from 1

	std::vector<Triangle> triangles;

	objReader.readObjFile("cube.obj", vertices, triangles);

	assignNeighbouringTriangles(triangles);

	for(int i = 1; i < triangles.size(); i++){

		// std::cout << triangles[i].getId() << "\n";

		std::cout<< triangles[i].getNeighbouringTriangles()[0].getId() << " " << triangles[i].getNeighbouringTriangles()[1].getId() << " " << triangles[i].getNeighbouringTriangles()[2].getId() << "\n";

	}

}