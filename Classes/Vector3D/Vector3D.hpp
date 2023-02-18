#ifndef VECTOR3D_H
#define VECTOR3D_H
#include <vector>

//----------------------------------------------------------------
//							Vector3D Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

A 3D Vector Class used to store the information and functions associated
with 3D Vectors.

*/

//Class Variables

//float magnitude

//std::vector <float> directionComponentsNormalized

//Class Functions

//Normalize Vector

// + - * / 

// Vector dot and cross products

// Difference between two vectors

class Vector3D{

private:

	int id;

	float magnitude;

	std::vector<float> directionComponents;

	std::vector<float> directionComponentsNormalised;

public:

	Vector3D();

	Vector3D(int _id, float _x, float _y, float _z);

	Vector3D(int _id, float _magnitude, float _x, float _y, float _z);

	~Vector3D();

	Vector3D(const Vector3D& a);

	Vector3D& operator=(const Vector3D& a);

	Vector3D& operator+(const Vector3D& a);
	
	Vector3D& operator-(const Vector3D& a);

	Vector3D& operator/(const int a);

	bool operator<(const Vector3D& a);

	bool operator<=(const Vector3D& a);

	int getId();

	float getMagnitude();

	std::vector<float> getNormalisedDirectionComponents();

	void displayNormalisedDirectionComponents();

	std::vector<float> getDirectionComponents();

	void displayDirectionComponents();

	void normaliseVector();

	void calculateMagnitude();

	//Mathematical Operators

	float dotProduct( Vector3D& a);

	Vector3D crossProduct( Vector3D& a);

	float angleBetweenVectors( Vector3D& a);

	Vector3D& distancePositive( Vector3D& a);

};

#endif