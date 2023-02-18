
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

Vector3D::Vector3D(){
	
}

Vector3D::Vector3D(int _id, float _x, float _y, float _z){

	//Constructor for an unormalized vector

	directionComponents.push_back(_x);
	directionComponents.push_back(_y);
	directionComponents.push_back(_z);

	if(_x == 0.0 && _y == 0.0 && _z == 0.0){

		directionComponentsNormalised.push_back(0.0);
		directionComponentsNormalised.push_back(0.0);
		directionComponentsNormalised.push_back(0.0);
		magnitude = 0.0;

	} else{

		calculateMagnitude();

		normaliseVector();

	}

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

Vector3D& Vector3D:: operator/(const int a){

	float xComponent = directionComponents[0] / a;
	float yComponent = directionComponents[1] / a;
	float zComponent = directionComponents[2] / a;

	Vector3D *outputVector = new Vector3D(0, xComponent, yComponent, zComponent);

	return *outputVector;

}

bool Vector3D:: operator<(const Vector3D& a){

	//By using abs we could have 1,1,1 and -1,-1,-1 which would return true even though they are completely oppisite

	//however if we had 

	if(abs(directionComponents[0]) < abs(a.directionComponents[0])
		&& abs(directionComponents[1]) < abs(a.directionComponents[1])
		&& abs(directionComponents[2]) < abs(a.directionComponents[2])){
		return true;
	} else {
		return false;
	}

}

bool Vector3D:: operator<=(const Vector3D& a){

	if(directionComponents[0] <= a.directionComponents[0]
		&& directionComponents[1] <= a.directionComponents[1]
		&& directionComponents[2] <= a.directionComponents[2]){
		return true;
	} else {
		return false;
	}

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

void Vector3D::displayNormalisedDirectionComponents(){

	std::cout << directionComponentsNormalised[0] << " " << directionComponentsNormalised[1] << " " << directionComponentsNormalised[2] << "\n";

}

std::vector<float> Vector3D::getDirectionComponents(){

	return directionComponents;

}

void Vector3D::displayDirectionComponents(){

	// std::cout << directionComponents[0] << " " << directionComponents[1] << " " << directionComponents[2] << "\n";

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

float Vector3D::angleBetweenVectors(Vector3D& a){

	float angle = acos(dotProduct(a)/(magnitude * a.magnitude));
		
	angle = angle * (180/M_PI);

	return angle;
}

Vector3D& Vector3D::distancePositive(Vector3D& a){

	float xComponent = directionComponents[0] - a.directionComponents[0];
	float yComponent = directionComponents[1] - a.directionComponents[1];
	float zComponent = directionComponents[2] - a.directionComponents[2];

	Vector3D *outputVector = new Vector3D(0, abs(xComponent), abs(yComponent), abs(zComponent));

	return *outputVector;


}



