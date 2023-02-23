#include "Edge.hpp"
#include <iostream>

//----------------------------------------------------------------
//						Edge Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A class used to store information about an Edge.

*/

Edge::Edge(){

}

Edge::Edge(int _id, int _vertexIndex1, int _vertexIndex2, Vector3D _edgeLength){

	id = _id;
	vertexIndex1 = _vertexIndex1;
	vertexIndex2 = _vertexIndex2;

	edgeLength = _edgeLength;

}

Edge::Edge(int _id, int _vertexIndex1, int _vertexIndex2, std::vector<Vertex> &globalVertices){

	id = _id;

	Vector3D f1 = Vector3D(1, globalVertices[_vertexIndex1].get('x'), globalVertices[_vertexIndex1].get('y'), globalVertices[_vertexIndex1].get('z'));
	Vector3D f2 = Vector3D(1, globalVertices[_vertexIndex2].get('x'), globalVertices[_vertexIndex2].get('y'), globalVertices[_vertexIndex2].get('z'));

	vertexIndex1 = _vertexIndex1;
	vertexIndex2 = _vertexIndex2;

	edgeLength = f2.distancePositive(f1);
}

Edge::~Edge(){

}

Edge::Edge(const Edge& a){

	id = a.id;
	
	vertexIndex1 = a.vertexIndex1;
	vertexIndex2 = a.vertexIndex2;

	edgeLength = a.edgeLength;

}

Edge& Edge:: operator=(const Edge& a){

	id = a.id;
	
	vertexIndex1 = a.vertexIndex1;
	vertexIndex2 = a.vertexIndex2;

	edgeLength = a.edgeLength;

	return *this;
}

bool Edge:: operator==(const Edge& a){

	if((vertexIndex1 == a.vertexIndex1 && vertexIndex2 == a.vertexIndex2) || (vertexIndex1 == a.vertexIndex2 && vertexIndex2 == a.vertexIndex1)){
		return true;
	} else {
		return false;
	}

}

bool Edge:: operator!=(const Edge& a){

	if((vertexIndex1 != a.vertexIndex1 && vertexIndex2 != a.vertexIndex2) || (vertexIndex1 != a.vertexIndex2 && vertexIndex2 != a.vertexIndex1)){
		return true;
	} else {
		return false;
	}

}

int Edge::getId(){

	return id;

}

void Edge::setId(int _id){

	id = _id;

}

int Edge::getVertexIndex1(){

	return vertexIndex1;

}

int Edge::getVertexIndex2(){

	return vertexIndex2;

}

void Edge::setVertexIndex1(int _vertexIndex1){

	vertexIndex1 = _vertexIndex1;

}

void Edge::setVertexIndex2(int _vertexIndex2){

	vertexIndex2 = _vertexIndex2;

}

void Edge::displayVertexIndices(){

	std::cout << vertexIndex1 << " " << vertexIndex2 << "\n";

}

void Edge::reCalculateEdgeLength(std::vector<Vertex> &globalVertices){

	Vector3D f1 = Vector3D(1, globalVertices[vertexIndex1].get('x'), globalVertices[vertexIndex1].get('y'), globalVertices[vertexIndex1].get('z'));
	Vector3D f2 = Vector3D(1, globalVertices[vertexIndex2].get('x'), globalVertices[vertexIndex2].get('y'), globalVertices[vertexIndex2].get('z'));

	edgeLength = f2.distancePositive(f1);

	std::cout <<  "edge length: " << edgeLength.getMagnitude() << "\n";

}

Vector3D Edge::getEdgeLength(){

	return edgeLength;
	
}


