#include "Cluster.hpp"
#include <algorithm>

//----------------------------------------------------------------
//						Cluster Class Implementation
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class Description

*/

bool triangleChecker(int triangle[3]){

	if(triangle[0] == triangle[1] || triangle[0] == triangle[2]){
		return false;
	}
	if(triangle[1] == triangle[2]){
		return false;
	}

	return true;

}

bool triangleDuplicateChecker(std::vector<Triangle> triangles, int triangle[3]){

	for(int i = 0; i < triangles.size(); i++){

		std::vector<int> vertexIndices = triangles[i].getVertexIndices();

		if(vertexIndices[0] == triangle[0] && vertexIndices[1] == triangle[1] && vertexIndices[2] == triangle[2]){
			return false;
		}

		if(vertexIndices[0] == triangle[0] && vertexIndices[1] == triangle[2] && vertexIndices[2] == triangle[1]){
			return false;
		}

		if(vertexIndices[0] == triangle[1] && vertexIndices[1] == triangle[0] && vertexIndices[2] == triangle[2]){
			return false;
		}

		if(vertexIndices[0] == triangle[1] && vertexIndices[1] == triangle[2] && vertexIndices[2] == triangle[0]){
			return false;
		}

		if(vertexIndices[0] == triangle[2] && vertexIndices[1] == triangle[0] && vertexIndices[2] == triangle[1]){
			return false;
		}

		if(vertexIndices[0] == triangle[2] && vertexIndices[1] == triangle[1] && vertexIndices[2] == triangle[0]){
			return false;
		}
	}

	return true;
}

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

Vector3D Cluster::getClusterNormal(){

	return averageClusterNormal;

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

void Cluster::createCluster(std::vector<Triangle> &triangleVector, std::unordered_map<int, Triangle> &globalUsedTriangles, std::vector<Vertex> &globalVertices ){

	while(candidateTriangles.size() > 0){

		if(checkTriangleAgainstClusterNormal(candidateTriangles.front()) == true && 
			checkIfTriangleIsInCluster(candidateTriangles.front()) == false &&
			checkIfTriangleIsInDiscardedTriangles(candidateTriangles.front(), globalUsedTriangles) == false){

			clusterTriangles.push_back(candidateTriangles.front());

			inputEdges(candidateTriangles.front(), globalVertices);

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

void Cluster::inputEdges(Triangle triangle1, std::vector<Vertex> &globalVertices){
	
	Edge edge1 = Edge(clusterEdges.size(), triangle1.getVertexIndices()[0], triangle1.getVertexIndices()[1], globalVertices);

	if(checkEdgeInList(edge1, clusterEdges) != true){

		clusterEdges.push_back(edge1);

	}

	Edge edge2 = Edge(clusterEdges.size(), triangle1.getVertexIndices()[1], triangle1.getVertexIndices()[2], globalVertices);

	if(checkEdgeInList(edge2, clusterEdges) == false){

		clusterEdges.push_back(edge2);

	}

	Edge edge3 = Edge(clusterEdges.size(), triangle1.getVertexIndices()[2], triangle1.getVertexIndices()[0], globalVertices);

	if(checkEdgeInList(edge3, clusterEdges) == false){

		clusterEdges.push_back(edge3);

	}

}

bool Cluster::checkEdgeInList(Edge edge1, std::vector<Edge> &edgeList){

	for(int i = 0; i < edgeList.size(); i++){
		if (edge1 == edgeList[i]){
			return true;
		}
	}
	return false;
}

void Cluster::displayEdges(){

	std::cout << "Cluster Edges: \n";

	std::cout << "Number of Edges: "<< clusterEdges.size() << "\n";

	for(int i = 0; i < clusterEdges.size(); i++){

		std::cout << "Vertices: " << clusterEdges[i].getVertexIndex1() << " " << clusterEdges[i].getVertexIndex2() << " Length: " << clusterEdges[i].getEdgeLength().getMagnitude() <<"\n";

	}
}

std::vector<Edge> Cluster::getClusterEdges(){
	return clusterEdges;
}

bool Cluster::checkTriangleAgainstClusterNormal(Triangle triangle){

	Vector3D difference = triangle.getTriangleNormal() - averageClusterNormal;

	if(difference < tolerance){
		return true;
	} else {
		return false;
	}
}

bool Cluster::checkTriangleAgainstClusterNormal(Triangle triangle, float tolerance){

	Vector3D difference = triangle.getTriangleNormal() - averageClusterNormal;

	Vector3D toleranceVec = Vector3D(1, tolerance, tolerance, tolerance);

	if(difference < toleranceVec){
		return true;
	} else {
		return false;
	}
}

void Cluster::displayClusterTriangles(){

	for(int i = 0; i < clusterTriangles.size(); i++){

		std::cout << "Triangle: " << clusterTriangles[i].getId() << "\n\n";

		std::cout << "Vertex Indices: " << clusterTriangles[i].getVertexIndices()[0] << " " << clusterTriangles[i].getVertexIndices()[1] << " " << clusterTriangles[i].getVertexIndices()[2] << "\n\n";

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

void Cluster::edgeCollapse(int edge, bool reversed, std::vector<Vertex> &globalVertices){

	//Connect all edges from one node of the edge to the other then pop the edge.

	//node1 <---- node2 Edge contraction

	//For all edges that go to node2, now go to node1

	if(reversed == true){

		int node1 = clusterEdges[edge].getVertexIndex1();
		int node2 = clusterEdges[edge].getVertexIndex2();

		for(int i = 0; i < clusterEdges.size(); i++){

			int v1 = clusterEdges[i].getVertexIndex1();
			int v2 = clusterEdges[i].getVertexIndex2();

			if(v1 == node1){
				clusterEdges[i].setVertexIndex1(v1 - 1);
			} 

			if(v2 == node1){
				clusterEdges[i].setVertexIndex2(v2 - 1);
			}
		}

		globalVertices.erase(globalVertices.begin()+node1);

		for(int i = 0; i < clusterEdges.size(); i++){

		//For all vertex indices above removed node reducde by 1

		int v1 = clusterEdges[i].getVertexIndex1();
		int v2 = clusterEdges[i].getVertexIndex2();

		if(v1 > node2){
			clusterEdges[i].setVertexIndex1(v1 - 1);
		}

		if(v2 > node2){
			clusterEdges[i].setVertexIndex2(v2 - 1);
		}
	}


	} else {

		int node1 = clusterEdges[edge].getVertexIndex1();
		int node2 = clusterEdges[edge].getVertexIndex2();

		for(int i = 0; i < clusterEdges.size(); i++){

			int v1 = clusterEdges[i].getVertexIndex1();
			int v2 = clusterEdges[i].getVertexIndex2();

			if(v1 == node2){
				clusterEdges[i].setVertexIndex1(node1);
			} 

			if(v2 == node2){
				clusterEdges[i].setVertexIndex2(node1);
			}

		}

		globalVertices.erase(globalVertices.begin()+node2);

		for(int i = 0; i < clusterEdges.size(); i++){

		//For all vertex indices above removed node reducde by 1

		int v1 = clusterEdges[i].getVertexIndex1();
		int v2 = clusterEdges[i].getVertexIndex2();

		if(v1 > node2){
			node2 -= 1;
		}

		if(v2 > node2){
			node2 -= 1;
		}
	}

	}

	clusterEdges.erase(clusterEdges.begin()+edge);



}

std::vector<Triangle> Cluster::generateOutputTriangles(std::vector<Vertex> &globalVertices){

	// A triangle is when 3 edges make a loop.

	// A duplicate triangle is when 3 nodes are used in a triangle more than once.

	//This needs to be optimized!!

	std::vector<Triangle> outputTriangles;

	for(int i = 0; i < clusterEdges.size(); i++){

		std::vector<Edge> e1;
		std::vector<Edge> e2;

		int v1 = clusterEdges[i].getVertexIndex1();
		int v2 = clusterEdges[i].getVertexIndex2();

		//Find all E1 edges (these are edges with a starting vertex v1)
		//Find all E2 edges (these are edges with a starting vertex v2)

		for(int j = 0; j < clusterEdges.size(); j++){

			int j1 = clusterEdges[j].getVertexIndex1();
			int j2 = clusterEdges[j].getVertexIndex2();

			if(j1 == v1 && clusterEdges[j] != clusterEdges[i]){
				e1.push_back(clusterEdges[j]);
			}

			if(j2 == v1 && clusterEdges[j] != clusterEdges[i]){
				e1.push_back(clusterEdges[j]);
			}

			if(j1 == v2 && clusterEdges[j] != clusterEdges[i]){
				e2.push_back(clusterEdges[j]);
			}

			if(j2 == v2 && clusterEdges[j] != clusterEdges[i]){
				e2.push_back(clusterEdges[j]);
			}

		}

		//Now test all edges against each other to see whether they have the same final Edge, If they do then this is a triangle

		//this will be O(n^2)

		for(int x = 0; x < e1.size(); x++){
			for(int y = 0; y < e2.size(); y++){

				int e1n1 = e1[x].getVertexIndex1();
				int e1n2 = e1[x].getVertexIndex2();

				int e2n1 = e2[y].getVertexIndex1();
				int e2n2 = e2[y].getVertexIndex2();

				int triangle[3];

				if(e1n1 != v1 && e1n1 != v2){
					if (e1n1 == e2n1){
						
						triangle[0] = clusterEdges[i].getVertexIndex1();
						triangle[1] = clusterEdges[i].getVertexIndex2();
						triangle[2] = e1n1;

						Triangle outputTriangle = Triangle(1, triangle[0], triangle[1], triangle[2], globalVertices);

						if(triangleChecker(triangle) == true){
							if(checkTriangleAgainstClusterNormal(outputTriangle, 1.0) == true){
								if(triangleDuplicateChecker(outputTriangles, triangle) == true){
								
									std::cout << "Triangle Found!\n";
									std::cout << triangle[0] << " " << triangle[1] << " " << triangle[2] << "\n";
									outputTriangles.push_back(outputTriangle);

								}
							}
						}
					} else if (e1n1 == e2n2){
						
						triangle[0] = clusterEdges[i].getVertexIndex1();
						triangle[1] = clusterEdges[i].getVertexIndex2();
						triangle[2] = e1n1;

						Triangle outputTriangle = Triangle(1, triangle[0], triangle[1], triangle[2], globalVertices);

						if(triangleChecker(triangle) == true){
							if(checkTriangleAgainstClusterNormal(outputTriangle, 1.0) == true){
								if(triangleDuplicateChecker(outputTriangles, triangle) == true){
								
									std::cout << "Triangle Found!\n";
									std::cout << triangle[0] << " " << triangle[1] << " " << triangle[2] << "\n";
									outputTriangles.push_back(outputTriangle);

								}
							}
						}
					}
				} else {
					if (e1n2 == e2n1){
						
						triangle[0] = clusterEdges[i].getVertexIndex1();
						triangle[1] = clusterEdges[i].getVertexIndex2();
						triangle[2] = e1n2;

						Triangle outputTriangle = Triangle(1, triangle[0], triangle[1], triangle[2], globalVertices);

						if(triangleChecker(triangle) == true){
							if(checkTriangleAgainstClusterNormal(outputTriangle, 1.0) == true){
								if(triangleDuplicateChecker(outputTriangles, triangle) == true){
								
									std::cout << "Triangle Found!\n";
									std::cout << triangle[0] << " " << triangle[1] << " " << triangle[2] << "\n";
									outputTriangles.push_back(outputTriangle);

								}
							}
						}

					} else if (e1n2 == e2n2){
						
						triangle[0] = clusterEdges[i].getVertexIndex1();
						triangle[1] = clusterEdges[i].getVertexIndex2();
						triangle[2] = e1n2;

						Triangle outputTriangle = Triangle(1, triangle[0], triangle[1], triangle[2], globalVertices);

						if(triangleChecker(triangle) == true){
							if(checkTriangleAgainstClusterNormal(outputTriangle, 1.0) == true){
								if(triangleDuplicateChecker(outputTriangles, triangle) == true){
								
									std::cout << "Triangle Found!\n";
									std::cout << triangle[0] << " " << triangle[1] << " " << triangle[2] << "\n";
									outputTriangles.push_back(outputTriangle);

								}
							}
						}
					}
				}
			}
		}	
	}

	return outputTriangles;

}

int Cluster::getSmallestEdgeIndex(){

	float smallestValue = 100.0;
	int smallestIndex = 0;

	for( int i = 0; i < clusterEdges.size(); i++){
		if(clusterEdges[i].getEdgeLength().getMagnitude() < smallestValue){
			smallestValue = clusterEdges[i].getEdgeLength().getMagnitude();
			smallestIndex = i;
		}
	}

	return smallestIndex;

}



// bool Cluster::triangleDuplicateChecker(){
// 	//Function for checking if a triangle is duplicated
// }

// void Cluster::triangleEdgeChecker(){

// 	//Function for working out if a group of Edges is a triangle


// }










