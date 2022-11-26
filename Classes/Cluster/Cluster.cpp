#include "Cluster.hpp"
#include <algorithm>

//----------------------------------------------------------------
//						Cluster Class Implementation
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class Description

*/

Cluster::Cluster(int _id, Triangle &initialTriangle, float _tolerance) {

	id = _id;

	tolerance = Vector3D(1, _tolerance, _tolerance, _tolerance);

	candidateTriangles.push_back(initialTriangle);

	averageClusterNormal = initialTriangle.getTriangleNormal();

	sumOfNormals = initialTriangle.getTriangleNormal();

	countOfTriangles = 1;

}

Cluster::~Cluster(){

}

Cluster::Cluster(const Cluster& a){

}

Cluster& Cluster:: operator=(const Cluster& a){

	return *this;
}

void Cluster::updateAverageClusterNormal(){

	sumOfNormals = sumOfNormals + clusterTriangles.back().getTriangleNormal();

	countOfTriangles = countOfTriangles + 1;

	averageClusterNormal = sumOfNormals / countOfTriangles;

}

void Cluster::colourCluster(std::vector<Material> &globalMaterials, std::vector<Triangle> &globalTriangles){

	std::string materialName = "material-" + std::to_string(globalMaterials.size());
	Material newMtl = Material(materialName);

	float r = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float g = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
	float b = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

	newMtl.setKdParameter(r, g, b);

	globalMaterials.push_back(newMtl);

	for(int i = 0; i < clusterTriangles.size(); i++){
		globalTriangles[clusterTriangles[i].getId()].setTriangleMaterial(newMtl);
	}

}

void Cluster::createCluster(std::vector<Triangle> &triangleVector, std::unordered_map<int, Triangle> &globalUsedTriangles){

	while(candidateTriangles.size() > 0){

		if(checkTriangleAgainstClusterNormal(candidateTriangles.front()) == true && 
			checkIfTriangleIsInCluster(candidateTriangles.front()) == false &&
			checkIfTriangleIsInDiscardedTriangles(candidateTriangles.front(), globalUsedTriangles) == false){

			clusterTriangles.push_back(candidateTriangles.front());

			updateAverageClusterNormal();

			std::pair<int, Triangle> discardedTriangle (candidateTriangles.front().getId(), candidateTriangles.front());

			globalUsedTriangles.insert(discardedTriangle);

			addNeighbouringTriangles(candidateTriangles.front(), triangleVector);

			candidateTriangles.pop_front();

		} else {

			// std::pair<int, Triangle> discardedTriangle (candidateTriangles.front().getId(), candidateTriangles.front());

			// discardedTriangles.insert(discardedTriangle);

			candidateTriangles.pop_front();

		}
	}
}

bool Cluster::checkTriangleAgainstClusterNormal(Triangle triangle){

	Vector3D difference = triangle.getTriangleNormal() - averageClusterNormal;

	if(difference < tolerance){
		return true;
	} else {
		return false;
	}
}

void Cluster::displayClusterTriangles(){

	for(int i = 0; i < clusterTriangles.size(); i++){

		std::cout << clusterTriangles[i].getId() << "\n";

	}

}

std::vector<Triangle> Cluster::getClusterTriangles(){

	return clusterTriangles;

}

void Cluster::addNeighbouringTriangles(Triangle &targetTriangle, std::vector<Triangle> triangleVector){

	for(int i = 0; i < triangleVector[targetTriangle.getId()].getNeighbouringTriangles().size(); i++){

		candidateTriangles.push_back(triangleVector[targetTriangle.getId()].getNeighbouringTriangles()[i]);
		
	}
}

bool Cluster::checkIfTriangleIsInDiscardedTriangles(Triangle targetTriangle, std::unordered_map<int, Triangle> &globalUsedTriangles){

	std::unordered_map<int, Triangle>::iterator it = globalUsedTriangles.find(targetTriangle.getId());

	if( globalUsedTriangles.end() != it){

		return true;

	} else {

		return false;

	}
}

bool Cluster::checkIfTriangleIsInCluster(Triangle targetTriangle){

	for(int i = 0; i < clusterTriangles.size(); i++){

		if(clusterTriangles[i].getId() == targetTriangle.getId()){
			
			return true;

		}
	}

	return false;
}










