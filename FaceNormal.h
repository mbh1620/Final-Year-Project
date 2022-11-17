#include <vector>

//----------------------------------------------------------------
//						Face Normal Function
//----------------------------------------------------------------

//Author: Matthew Haywood

//Function for working out the normal of a face

std::vector<float> faceNormal(float vertex1[3], float vertex2[3], float vertex3[3]){

	std::vector<float> faceNormal;

		
	
	return faceNormal;
}

float signFunction(float vertex1[3], float vertex2[3], float vertex3[3]){

	//works out the direction of triangle depending on order of points input

	return (vertex1[0] - vertex3[0]) * (vertex2[1] - vertex3[1]) - (vertex2[0] - vertex3[0]) * (vertex1[1] - vertex3[1]);

}