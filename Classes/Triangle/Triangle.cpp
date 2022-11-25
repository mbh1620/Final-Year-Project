#include "Triangle.hpp"

//----------------------------------------------------------------
//						Triangle Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A class used to store information about a triangle.

*/

Triangle::Triangle(int _id, int v1, int v2, int v3, std::vector<Vertex> &vertices){

	id = _id;
	vertexIndices.push_back(v1);
	vertexIndices.push_back(v2);
	vertexIndices.push_back(v3);

	Material defaultMaterial = Material("default");

	defaultMaterial.setKdParameter(Vector3D(1, 0.8, 0.8, 0.8));

	triangleMaterial = defaultMaterial;

	calculateNormal(vertices);

}

Triangle::~Triangle(){

}

Triangle::Triangle(const Triangle& a){

	id = a.id;
	vertexIndices = a.vertexIndices;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;
	triangleMaterial = a.triangleMaterial;

}

Triangle& Triangle:: operator=(const Triangle& a){
	
	id = a.id;
	vertexIndices = a.vertexIndices;
	neighbouringTriangles = a.neighbouringTriangles;
	triangleNormal = a.triangleNormal;
	triangleMaterial = a.triangleMaterial;

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

Vector3D& Triangle::getTriangleNormal(){

	return this->triangleNormal;

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

void Triangle::displayNeighbouringTriangles(){

	for(int i = 0; i < neighbouringTriangles.size(); i++){
		std::cout << neighbouringTriangles[i].getId() << " ";
	}

	std::cout << "\n";

}

void Triangle::setNeighbouringTriangle(Triangle &neighbouringTriangle){

	if(neighbouringTriangles.size() < 3){
		neighbouringTriangles.push_back(neighbouringTriangle);
	} else {
		std::cout << "Error: Maximum number of neighbouring Triangles Reached!";
		throw;
	}

}

std::vector<Triangle> Triangle::getNeighbouringTriangles(){

	return neighbouringTriangles;

}

void Triangle::setTriangleMaterial(Material _triangleMaterial){

	triangleMaterial = _triangleMaterial;

}

Material Triangle::getTriangleMaterial(){

	return triangleMaterial;

}

bool Triangle::compareTriangleMaterial(const Triangle& a){

	if(triangleMaterial == a.triangleMaterial){
		return true;
	} else {
		return false;
	}

}

void Triangle::calculateNormal(std::vector<Vertex> &vertices){

	Vector3D f1 = Vector3D(1, vertices[vertexIndices[0]].get('x'), vertices[vertexIndices[0]].get('y'), vertices[vertexIndices[0]].get('z'));
	Vector3D f2 = Vector3D(1, vertices[vertexIndices[1]].get('x'), vertices[vertexIndices[1]].get('y'), vertices[vertexIndices[1]].get('z'));
	Vector3D f3 = Vector3D(1, vertices[vertexIndices[2]].get('x'), vertices[vertexIndices[2]].get('y'), vertices[vertexIndices[2]].get('z'));

	Vector3D vectorU = f2 - f1;
	Vector3D vectorV = f3 - f1;

	triangleNormal = vectorU.crossProduct(vectorV);
	 
}
