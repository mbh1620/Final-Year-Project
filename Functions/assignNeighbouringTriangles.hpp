#include <omp.h>
//----------------------------------------------------------------
//						assignNeighbouringTriangles
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Function used to calculate the neighbouring triangles of all triangles in the model

*/

/* Function Input

 - globalTriangles

*/

/* Function Output

 will update the list of triangles so void

*/

bool faceNeighbouring(Triangle a, Triangle b){

	int count = 0;

	for(int i = 0; i < a.getVertexIndices().size(); i++){
		for(int j = 0; j < b.getVertexIndices().size(); j++){
			if(a.getVertexIndices()[i] == b.getVertexIndices()[j]){
				count += 1;
			}
		}
	}

	if(count >= 2){
		return true;
	} else {
		return false;
	}

}

void assignNeighbouringTriangles(std::vector<Triangle> &globalTriangles){

	// omp_set_num_threads(6);

	// #pragma omp parallel for collapse(2) shared(globalTriangles)

	for(int i = 1; i < globalTriangles.size(); i++){
		for(int j = 1; j < globalTriangles.size(); j++){
			if(i != j){
				if(faceNeighbouring(globalTriangles[i], globalTriangles[j])){

					globalTriangles[i].setNeighbouringTriangleIndex(j);

				}
			}
		}
	}

	// #pragma omp barrier
}

void assignNeighbouringTrianglesParallel(std::vector<Triangle> &globalTriangles){
	omp_set_num_threads(6);

	#pragma omp parallel for collapse(2) shared(globalTriangles)

	for(int i = 1; i < globalTriangles.size(); i++){
		for(int j = 1; j < globalTriangles.size(); j++){
			if(i != j){
				if(faceNeighbouring(globalTriangles[i], globalTriangles[j])){

					globalTriangles[i].setNeighbouringTriangleIndex(j);

				}
			}
		}
	}

	#pragma omp barrier
}




