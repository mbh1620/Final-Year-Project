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

	std::list<Triangle> candidateTriangles;								// List of potential triangles to add to cluster

	std::vector<Triangle> clusterTriangles;								// List of cluster member triangles

	std::vector<Triangle> outputTriangles;								// List of Output triangles created

	std::vector<Edge> clusterEdges;										// List of cluster member edges

	Vector3D averageClusterNormal;										// 3D Vector of the Cluster Normal

	float angleTolerance;												// Tolerance angle to check against 

	Vector3D sumOfNormals;												// Accumulated sum total of Normals

	int countOfTriangles;												// Count of triangles in the cluster

public:

	Cluster(int id, Triangle &initialTriangle, float angleTolerance);

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

	bool checkTriangleAgainstClusterNormal(Triangle triangle, std::vector<Vertex> &globalVertices);

	bool checkTriangleAgainstClusterNormal(Triangle triangle, float tolerance);

	void displayClusterTriangles();

	std::vector<Triangle> getClusterTriangles();

	bool checkIfTriangleIsInVector(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	void addNeighbouringTriangles(Triangle &targetTriangle, std::vector<Triangle> triangleVector);

	bool checkIfTriangleIsInDiscardedTriangles(Triangle targetTriangle, std::unordered_map<int, Triangle> &globalUsedTriangles);

	bool checkIfTriangleIsInCluster(Triangle targetTriangle);

	bool checkValidCollapse();

	void edgeCollapse(int edge, bool reversed,  std::vector<Triangle> &globalTriangles, std::vector<Vertex> &globalVertices);

	void shiftVertexIndices(int fromIndex);

	void shiftTriangleVertexIndices(int startIndex, std::vector<Triangle> &globalTriangles);

	void iterativelyEdgeCollapse(std::vector<Vertex> &globalVertices, std::vector<Triangle> &globalTriangles);

	void recalculateEdgeLengths(std::vector<Vertex> &globalVertices);

	std::vector<Triangle> generateOutputTriangles(std::vector<Vertex> &globalVertices);

	std::vector<Triangle> getOutputTriangles();

	int getSmallestEdgeIndex(std::vector<Vertex> &globalVertices);

	void assignEdgeOfClusterVertices(Triangle rejectedTriangle, std::vector<Vertex> &globalVertices);

	// Edge Collapsing Functions Below

};

#endif