#include <iostream>
#include "../Vertex/Vertex.hpp"
#include "Triangle.cpp"
#include <vector>


int main() {

	Vertex dummyVertex = Vertex(0, 100.0, 10.0,100.0);

	Vertex vertex1 = Vertex(1, 1.0, 2.4, 3.5);
	Vertex vertex2 = Vertex(2, 1.0, 3.0, 4.0);
	Vertex vertex3 = Vertex(3, 1.0, 2.0, 1.0);

	std::vector<Vertex> globalVertices;

	globalVertices.push_back(dummyVertex);
	globalVertices.push_back(vertex1);
	globalVertices.push_back(vertex2);
	globalVertices.push_back(vertex3);

	Triangle triangle1 = Triangle(0, 1, 2, 3, globalVertices);

	triangle1.calculateEdgeLengths(globalVertices);

	triangle1.displayEdgeLengths();

	Vector3D v1 = triangle1.getEdgeLength(0);

	v1.displayDirectionComponents();

	Vector3D v2 = triangle1.getEdgeLength(1);

	v2.displayDirectionComponents();

	Vector3D v3 = triangle1.getEdgeLength(2);

	v3.displayDirectionComponents();

}