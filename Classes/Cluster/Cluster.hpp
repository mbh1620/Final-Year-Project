#ifndef CLUSTER_H
#define CLUSTER_H

#include "../Triangle/Triangle.cpp"

#include <unordered_map>
#include <list>

//----------------------------------------------------------------
//						Cluster Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Cluster Class used to store data and functions associated with a cluster.

A Cluster is a group of triangles that face in roughly the same direction. A new triangle is

added by checking against an average normal of the cluster.  

*/

//Class Variables

//Class Functions

class Cluster{

private:

	int id;

	std::list<Triangle> candidateTriangles;

	std::unordered_map<int, Triangle> discardedTriangles;

	std::vector<Triangle> clusterTriangles;

	Vector3D averageClusterNormal;

	Vector3D tolerance;

	Vector3D sumOfNormals;

	int countOfTriangles;

public:

	Cluster(int id, Triangle &initialTriangle, float tolerance);

	~Cluster();

	Cluster(const Cluster& a);

	Cluster& operator=(const Cluster& a);

	void updateAverageClusterNormal();

	void colourCluster(std::vector<Material> &globalMaterials, std::vector<Triangle> &globalTriangles);

	void createCluster(std::vector<Triangle> &triangleVector);

	bool checkTriangleAgainstClusterNormal(Triangle triangle);

	void displayClusterTriangles();

	std::vector<Triangle> getClusterTriangles();

	bool checkIfTriangleIsInVector(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	void displayDiscardedTriangles();

	void addNeighbouringTriangles(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	bool checkIfTriangleIsInDiscardedTriangles(Triangle targetTriangle);

	bool checkIfTriangleIsInCluster(Triangle targetTriangle);

};

#endif