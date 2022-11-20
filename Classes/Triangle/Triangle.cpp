#include "Triangle.hpp"

//----------------------------------------------------------------
//						Triangle Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A class used to store information about a triangle.

*/

Triangle::Triangle(int _id, int v1, int v2, int v3){

	id = _id;
	vertexIndices.push_back(v1);
	vertexIndices.push_back(v2);
	vertexIndices.push_back(v3);

}

Triangle::~Triangle(){

}

Triangle::Triangle(const Triangle& a){

	id = a.id;
	vertexIndices = a.vertexIndices;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;

}

Triangle& Triangle:: operator=(const Triangle& a){
	
	id = a.id;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;

	return *this;
}

int Triangle::getId(){
	
	return id;

}

std::vector<int> Triangle::getVertexIndices(){

	return vertexIndices;
}

std::vector<Vertex> Triangle::getVertices(std::vector<Vertex> &vertices){

	std::vector<Vertex> outputVertices;

	outputVertices.push_back(vertices[vertexIndices[0]]);
	outputVertices.push_back(vertices[vertexIndices[1]]);
	outputVertices.push_back(vertices[vertexIndices[2]]);

	return outputVertices;

}

void Triangle::setVertices(int v1, int v2, int v3){

	vertexIndices.clear();
	vertexIndices.push_back(v1);
	vertexIndices.push_back(v2);
	vertexIndices.push_back(v3);

}

void Triangle::setNeighbouringTriangles(std::vector<Triangle> _neighbouringTriangles){

	neighbouringTriangles = _neighbouringTriangles;
	
}

void Triangle::calculateNormal(){
	
}
