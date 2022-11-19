#include "Triangle.hpp"

//----------------------------------------------------------------
//						Triangle Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A class used to store information about a triangle.

*/

Triangle::Triangle(int _id, Vertex v1, Vertex v2, Vertex v3){

	id = _id;
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

}

Triangle::~Triangle(){

}

Triangle::Triangle(const Triangle& a){

	id = a.id;
	vertices = a.vertices;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;

}

Triangle& Triangle:: operator=(const Triangle& a){
	
	id = a.id;
	vertices = a.vertices;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;

	return *this;
}

int Triangle::getId(){
	
	return id;

}

std::vector<Vertex> Triangle::getVertices(){

	return vertices;
}

void Triangle::setVertices(Vertex v1, Vertex v2, Vertex v3){

	vertices.clear();
	vertices.push_back(v1);
	vertices.push_back(v2);
	vertices.push_back(v3);

}

void Triangle::setNeighbouringTriangles(std::vector<Triangle> _neighbouringTriangles){

	neighbouringTriangles = _neighbouringTriangles;
	
}
