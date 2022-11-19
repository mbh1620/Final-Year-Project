#include "Vertex.hpp"

//----------------------------------------------------------------
//							Vertex Main
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A Class used to store information about a 3D point in 3D space.

*/

Vertex::Vertex(int _id, float _x, float _y, float _z){

	id = _id;
	x = _x;
	y = _y;
	z = _z;

}

Vertex::~Vertex() {

}

Vertex::Vertex(const Vertex& a){

	id = a.id;
	x = a.x;
	y = a.y;
	z = a.z;

}

Vertex& Vertex:: operator=(const Vertex& a){

	id = a.id;
	x = a.x;
	y = a.y;
	z = a.z;

	return *this;
}

Vertex& Vertex:: operator+(const Vertex& a){

	x += a.x;
	y += a.y;
	z += a.z;

	return *this;
}

Vertex& Vertex:: operator-(const Vertex& a){

	x -= a.x;
	y -= a.y;
	z -= a.z;

	return *this;

}

float Vertex::get(char c){

	switch(c) {
		case 'x':
			return x;
			break;
		case 'y':
			return y;
			break;
		case 'z':
			return z;
			break;
		default:
			return 0;
	}
}

float Vertex::get_Id(){
	return id;
}

void Vertex::set(char c, float value){

	switch(c) {
		case 'x':
			x = value;
			break;
		case 'y':
			y = value;
			break;
		case 'z':
			z = value;
			break;
	}
}




