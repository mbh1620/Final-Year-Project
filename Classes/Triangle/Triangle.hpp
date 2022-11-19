#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Vertex/Vertex.cpp"
#include <vector>

//----------------------------------------------------------------
//						Triangle Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A Class used to store information about Triangles.

*/

/* Class Variables

 An Array of 3 Vertex Objects.

 An Array of 3 Neighbouring Triangles.

 An Array of 3 floats for the Triangle Normal.

 An Id.

*/

/* Class Functions

	- A Function used to work out the Face Normal

	- A Function for working out the difference between two Face Normals

sub-functions required for Face Normal:

	- calculateSign for calculating the direction of the points

*/

class Triangle{

private:

	int id;

	std::vector<Vertex> vertices;

	std::vector<Triangle> neighbouringTriangles;

	std::vector<float> triangleNormal;

public:

	Triangle(int id, Vertex v1, Vertex v2, Vertex v3);

	~Triangle();

	Triangle(const Triangle& a);

	Triangle& operator=(const Triangle& a);

	int getId();

	std::vector<Vertex> getVertices();

	void setVertices(Vertex v1, Vertex v2, Vertex v3);

	void setNeighbouringTriangles(std::vector<Triangle> _neighbouringTriangles);

	// Vertex& getVertex(int vertexNumber);
};

#endif