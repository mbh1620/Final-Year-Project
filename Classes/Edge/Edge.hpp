#ifndef EDGE_H
#define EDGE_H

#include "../Vector3D/Vector3D.hpp"
#include "../Vertex/Vertex.hpp"

//----------------------------------------------------------------
//							Edge Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Edge Class

*/

/* Variables

	int vertexIndex1
	int vertexIndex2
	Vector3D edgeLength

*/

/* Functions

	Add

	Subtract


*/

class Edge{

private:

	int id;										//Edge Id

	int vertexIndex1;							//Edge Vertex 1

	int vertexIndex2;							//Edge Vertex 2

	Vector3D edgeLength;						//Edge length contained in Vector magnitude

public:

	Edge();

	Edge(int id, int vertexIndex1, int vertexIndex2, Vector3D edgeLength);

	Edge(int id, int vertexIndex1, int vertexIndex2, std::vector<Vertex> &globalVertices);

	~Edge();

	Edge(const Edge& a);

	Edge& operator=(const Edge& a);

	bool operator==(const Edge& a);

	bool operator!=(const Edge& a);

	int getId();

	void setId(int id);

	int getVertexIndex1();

	int getVertexIndex2();

	void setVertexIndex1(int _vertexIndex1);

	void setVertexIndex2(int _vertexIndex2);

	void displayVertexIndices();

	void reCalculateEdgeLength(std::vector<Vertex> &globalVertices);

	Vector3D getEdgeLength();

};

#endif