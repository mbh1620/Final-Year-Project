#include <iostream>
#include "Vector3D.cpp"
//----------------------------------------------------------------
//							Vector3D Testing
//----------------------------------------------------------------

//Author: Matthew Haywood

// Write Testing Detail Here

using namespace std;

int main() {

	int passedCases = 0;
	int totalCases = 0;

	cout << "\n\n";

	Vector3D vector1 = Vector3D(1, 2, 3, 4);

	Vector3D vector2 = Vector3D(2, 5, 6, 7);

	float dotProduct = vector1.dotProduct(vector2);

	Vector3D crossProduct = vector1.crossProduct(vector2);

	Vector3D vector3 = vector1 + vector2;
	
	Vector3D vector4 = vector1 - vector2;

	cout << dotProduct << "\n";

	cout << crossProduct.getDirectionComponents()[0] << " " << crossProduct.getDirectionComponents()[1] << " " << crossProduct.getDirectionComponents()[2] << "\n";
		
	cout << vector3.getDirectionComponents()[0] << " " << vector3.getDirectionComponents()[1] << " " << vector3.getDirectionComponents()[2] << "\n";

	cout << vector4.getDirectionComponents()[0] << " " << vector4.getDirectionComponents()[1] << " " << vector4.getDirectionComponents()[2];

	cout << passedCases << " / " << totalCases << " TestCases Passed! \n";
	cout << "\n\n";

}
