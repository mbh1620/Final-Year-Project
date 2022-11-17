#include <iostream>
#include "../Functions/FaceNormal.h"

int main(){

	float a[3] = {0.5, 0.5, 0.5};
	float b[3] = {3.2, 4.4, 5.5};
	float c[3] = {6.4, 4.5, 3.4};

	std::vector<float> normal = faceNormal(a, b, c);

	if (normal[0] == 3 && normal[1] == 2 && normal[2] == 1){
		std::cout << "Face Normal - Test 1 Passed!";
	} else {
		std::cout << "Face Normal - Test 1 Failed!";
	}

}