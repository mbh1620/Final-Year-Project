#ifndef CLUSTER_H
#define CLUSTER_H

#include "../Triangle/Triangle.cpp"
//----------------------------------------------------------------
//						Cluster Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Cluster Class used to store data and functions associated with a cluster.

A Cluster is a group of triangles that face in roughly the same direction. A new triangle is

added by checking against an average of the cluster.  

*/

//Class Variables

//Class Functions

class Cluster{

private:

	int id;

	std::vector<Triangle> clusterTriangles;

	Vector3D averageClusterNormal;

	Vector3D sumOfNormals;

	int countOfTriangles;

public:

	Cluster(int id, Triangle initialTriangle);

	~Cluster();

	Cluster(const Cluster& a);

	Cluster& operator=(const Cluster& a);

	void updateAverageClusterNormal();

	void createCluster();

};

#endif