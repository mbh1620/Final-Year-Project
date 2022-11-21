#include "Cluster.hpp"

//----------------------------------------------------------------
//						Cluster Class Implementation
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class Description

*/

Cluster::Cluster(int _id, Triangle initialTriangle) {

	id = _id;

	clusterTriangles.push_back(initialTriangle);

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

	//Add final triangleNormal to average cluster normal and divide by number of triangles in cluster

	sumOfNormals = sumOfNormals + clusterTriangles.back().getTriangleNormal();

	averageClusterNormal = sumOfNormals / countOfTriangles;

}

void Cluster::createCluster(){

}
