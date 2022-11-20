
#include <cmath>
#include "../Vector3D/Vector3D.hpp"

//----------------------------------------------------------------
//					Vector3D Class Implementation
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A 3D Vector Class used to store the information and functions associated
with 3D Vectors.

*/

Vector3D::Vector3D(int _id, float _x, float _y, float _z){

	//Constructor for an unormalized vector

	directionComponents.push_back(_x);
	directionComponents.push_back(_y);
	directionComponents.push_back(_z);

	calculateMagnitude();

	normaliseVector();

}

Vector3D::Vector3D(int _id, float _magnitude, float _x, float _y, float _z){

	//Constructor for a normalised 3D Vector

	magnitude = _magnitude;
	directionComponentsNormalised.push_back(_x);
	directionComponentsNormalised.push_back(_y);
	directionComponentsNormalised.push_back(_z);

}

Vector3D::~Vector3D(){

}

Vector3D::Vector3D(const Vector3D& a){

	id = a.id;
	magnitude = a.magnitude;
	directionComponents = a.directionComponents;
	directionComponentsNormalised= a.directionComponentsNormalised;

}

Vector3D& Vector3D:: operator=(const Vector3D& a){

	id = a.id;
	magnitude = a.magnitude;
	directionComponents = a.directionComponents;
	directionComponentsNormalised = a.directionComponentsNormalised;

	return *this;
}

Vector3D& Vector3D:: operator+(const Vector3D& a){

	float xComponent = directionComponents[0] + a.directionComponents[0];
	float yComponent = directionComponents[1] + a.directionComponents[1];
	float zComponent = directionComponents[2] + a.directionComponents[2];

	Vector3D *outputVector = new Vector3D(0, xComponent, yComponent, zComponent);

	return *outputVector;

}

Vector3D& Vector3D:: operator-(const Vector3D& a){

	float xComponent = directionComponents[0] - a.directionComponents[0];
	float yComponent = directionComponents[1] - a.directionComponents[1];
	float zComponent = directionComponents[2] - a.directionComponents[2];

	Vector3D *outputVector = new Vector3D(0, xComponent, yComponent, zComponent);

	return *outputVector;
}

int Vector3D::getId(){

	return id;

}

float Vector3D::getMagnitude(){

	return magnitude;

}

std::vector<float> Vector3D::getNormalisedDirectionComponents(){

	return directionComponentsNormalised;

}

std::vector<float> Vector3D::getDirectionComponents(){

	return directionComponents;

}

void Vector3D::normaliseVector(){

	directionComponentsNormalised.push_back(directionComponents[0]/magnitude);
	directionComponentsNormalised.push_back(directionComponents[1]/magnitude);
	directionComponentsNormalised.push_back(directionComponents[2]/magnitude);

}

void Vector3D::calculateMagnitude(){

	magnitude = sqrt(pow(directionComponents[0],2)+pow(directionComponents[1],2)+pow(directionComponents[2],2));

}

float Vector3D::dotProduct(Vector3D& a){

	return (a.directionComponents[0] * directionComponents[0]) + (a.directionComponents[1] * directionComponents[1]) + (a.directionComponents[2] * directionComponents[2]);

}

Vector3D Vector3D::crossProduct(Vector3D& a){

	float xComponent = (directionComponents[1] * a.directionComponents[2]) - (directionComponents[2] * a.directionComponents[1]);
	float yComponent = (directionComponents[2] * a.directionComponents[0]) - (directionComponents[0] * a.directionComponents[2]);
	float zComponent = (directionComponents[0] * a.directionComponents[1]) - (directionComponents[1] * a.directionComponents[0]);
	
	Vector3D outputVector = Vector3D(0, xComponent, yComponent, zComponent);

	return outputVector;
}



