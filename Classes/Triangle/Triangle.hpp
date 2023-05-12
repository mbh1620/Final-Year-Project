#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "../Vertex/Vertex.cpp"
#include "../Vector3D/Vector3D.hpp"
#include "../Material/Material.cpp"
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

	std::vector<int> vertexIndices;

	std::vector<int> neighbouringTrianglesIndices;

	Material triangleMaterial; 

	Vector3D triangleNormal;

	std::vector<Vector3D> edgeLengths; 

public:

	Triangle(int id, int v1, int v2, int v3, std::vector<Vertex> &globalVertices);

	~Triangle();

	Triangle(const Triangle& a);

	Triangle& operator=(const Triangle& a);

	int getId();

	std::vector<int> getVertexIndices();

	std::vector<Vertex> getVertices(std::vector<Vertex> &globalVertices);

	Vector3D& getTriangleNormal();

	void setVertexIndices(int v1, int v2, int v3);

<<<<<<< HEAD
	void setNeighbouringTriangleIndex(int neighbouringTriangleIndex);

	std::vector<int> getNeighbouringTriangles();
=======
	void setNeighbouringTriangles(std::vector<Triangle> &_neighbouringTriangles);

	void setNeighbouringTriangle(Triangle &neighbouringTriangle);

	std::vector<Triangle> getNeighbouringTriangles();
>>>>>>> main

	void displayNeighbouringTriangles();

	void setTriangleMaterial(Material _triangleMaterial);

	Material getTriangleMaterial();

	bool compareTriangleMaterial(const Triangle& a);

	void calculateNormal(std::vector<Vertex> &globalVertices);

	void calculateEdgeLengths(std::vector<Vertex> &globalVertices);

	void displayEdgeLengths();

	Vector3D getEdgeLength(int edgeIndex);

};

#endif