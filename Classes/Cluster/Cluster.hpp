#ifndef CLUSTER_H
#define CLUSTER_H

#include "../Triangle/Triangle.cpp"
#include "../Edge/Edge.cpp"

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

	std::vector<Triangle> clusterTriangles;

	std::vector<Triangle> outputTriangles;

	std::vector<Edge> clusterEdges;

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

	Vector3D getClusterNormal();

	void colourCluster(std::vector<Material> &globalMaterials, std::vector<Triangle> &globalTriangles);

	void createCluster(std::vector<Triangle> &triangleVector, std::unordered_map<int, Triangle> &globalUsedTriangles, std::vector<Vertex> &globalVertices);

	void inputEdges(Triangle triangle1, std::vector<Vertex> &globalVertices);

	bool checkEdgeInList(Edge edge1, std::vector<Edge> &edgeList);

	void displayEdges();

	std::vector<Edge> getClusterEdges();

	bool checkTriangleAgainstClusterNormal(Triangle triangle);

	bool checkTriangleAgainstClusterNormal(Triangle triangle, float tolerance);

	void displayClusterTriangles();

	std::vector<Triangle> getClusterTriangles();

	bool checkIfTriangleIsInVector(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	void addNeighbouringTriangles(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	bool checkIfTriangleIsInDiscardedTriangles(Triangle targetTriangle, std::unordered_map<int, Triangle> &globalUsedTriangles);

	bool checkIfTriangleIsInCluster(Triangle targetTriangle);

	void edgeCollapse(int edge, bool reversed, std::vector<Vertex> &globalVertices);

	std::vector<Triangle> generateOutputTriangles(std::vector<Vertex> &globalVertices);

	int getSmallestEdgeIndex();

	// Edge Collapsing Functions Below

};

#endif