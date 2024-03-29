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

Cluster::Cluster(int _id, Triangle &initialTriangle, float _angleTolerance) {

	id = _id;

	angleTolerance = _angleTolerance;

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

		if(checkTriangleAgainstClusterNormal(candidateTriangles.front(), globalVertices) == true && 
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

bool Cluster::checkTriangleAgainstClusterNormal(Triangle triangle, std::vector<Vertex> &globalVertices){

	float angleDifference = triangle.getTriangleNormal().angleBetweenVectors(averageClusterNormal);

	if(angleDifference < angleTolerance){
		return true;
	} else {
		
		assignEdgeOfClusterVertices(triangle, globalVertices);

		return false;

	}
}

bool Cluster::checkTriangleAgainstClusterNormal(Triangle triangle, float angleTolerance){

	float angleDifference = triangle.getTriangleNormal().angleBetweenVectors(averageClusterNormal);

	if(angleDifference < angleTolerance){
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

		candidateTriangles.push_back(triangleVector[targetTriangle.getNeighbouringTriangles()[i]]);

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

bool Cluster::checkValidCollapse(){

	//Check the collapse rules

	//2 manifold without boundary

	//


	return true;

}

void Cluster::edgeCollapse(int edge, bool reversed, std::vector<Triangle> &triangles, std::vector<Vertex> &globalVertices){

	//Connect all edges from one node of the edge to the other then pop the edge.

	//node1 <---- node2 Edge contraction

	int node1 = clusterEdges[edge].getVertexIndex1();
	int node2 = clusterEdges[edge].getVertexIndex2();

	if(globalVertices[node1].getEdgeOfCluster() == true && globalVertices[node2].getEdgeOfCluster()){

		std::cout << "Edge of Cluster Edge! will not collapse to maintain boundary of cluster! \n";

		//We need to do something with this edge so that it does not get used in the next iteration otherwise an inifinity loop is caused.

		return;
	} 

	if(globalVertices[node1].getEdgeOfCluster() == true){

		std::cout << "edgeOfCluster Encountered! Reversing the collapsing Direction \n";

		//Node2 collapse towards node1
		reversed = false;

	} else if (globalVertices[node2].getEdgeOfCluster() == true){

		std::cout << "edgeOfCluster Encountered! Reversing the collapsing Direction \n";

		//Node1 collapse towards node2
		reversed = true;

	}

	if(reversed == true){

		int node1 = clusterEdges[edge].getVertexIndex1();
		int node2 = clusterEdges[edge].getVertexIndex2();

		for(int i = 0; i < clusterEdges.size(); i++){

			int v1 = clusterEdges[i].getVertexIndex1();
			int v2 = clusterEdges[i].getVertexIndex2();

			if(v1 == node1){
				clusterEdges[i].setVertexIndex1(node2);
			} 

			if(v2 == node1){
				clusterEdges[i].setVertexIndex2(node2);
			}
		}

		// if(node1 < globalVertices.size()){

		std::cout << "globalVertices: " << globalVertices.size() << "node1: " << node1 << "\n";

			globalVertices.erase(globalVertices.begin()+node1);
				
		// }

		shiftVertexIndices(node1);
		shiftTriangleVertexIndices(node1, triangles);

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

		std::cout << "globalVertices: " << globalVertices.size() << " node2: " << node2 << "\n";

		globalVertices.erase(globalVertices.begin()+node2); //THIS CODE HERE CAUSES THE SEGFAULT 11 - what is node2? as this is causing the proble

		//The segfault is caused by trying to erase a node index which is above the size of the node list

		//Think it is something to do with the shift vertex indices not being called properly.

		std::cout << "TEST THAT CODE REACHES THIS POINT! TESTDaksda skdjas dajdkawj d" << edge << "\n";

		shiftVertexIndices(node2);
		shiftTriangleVertexIndices(node2, triangles);

	}

	clusterEdges.erase(clusterEdges.begin()+edge);

	for(int i = 0; i < clusterEdges.size(); i++){

		int v1 = clusterEdges[i].getVertexIndex1();
		int v2 = clusterEdges[i].getVertexIndex2();

		if(v1 == v2){
			
			clusterEdges.erase(clusterEdges.begin()+i);

		}

		for(int j = 0; j < clusterEdges.size(); j++){

			int v3 = clusterEdges[j].getVertexIndex1();
			int v4 = clusterEdges[j].getVertexIndex2();

			if(i != j){
				if((v1 == v3 && v2 == v4) || (v1 == v4 && v2 == v3)){
					clusterEdges.erase(clusterEdges.begin()+j);
				}
			}
		}
	}
}

void Cluster::shiftVertexIndices(int startIndex){

	//Function to be used for when the globalVertices is reduced by 1

	for(int i = 0; i < clusterEdges.size(); i++){

		int v1 = clusterEdges[i].getVertexIndex1();
		int v2 = clusterEdges[i].getVertexIndex2();

		if(v1 > startIndex){
			clusterEdges[i].setVertexIndex1(v1 - 1);
		}

		if(v2 > startIndex){
			clusterEdges[i].setVertexIndex2(v2 - 1);
		}
	}
}

void Cluster::shiftTriangleVertexIndices(int startIndex, std::vector<Triangle> &globalTriangles){

	for(int i = 0; i < globalTriangles.size(); i++){

		int v1 = globalTriangles[i].getVertexIndices()[0]; 
		int v2 = globalTriangles[i].getVertexIndices()[1]; 
		int v3 = globalTriangles[i].getVertexIndices()[2];

		if (v1 > startIndex){
			v1 = v1 - 1;
		}

		if (v2 > startIndex){
			v2 = v2 - 1;
		}

		if (v3 > startIndex){
			v3 = v3 - 1;
		}

		globalTriangles[i].setVertexIndices(v1, v2, v3);

	}

}

void Cluster::iterativelyEdgeCollapse(std::vector<Vertex> &globalVertices, std::vector<Triangle> &globalTriangles){

	//Get smallest edge and collapse until there are only 5 edges left

	//This function seems to cause infinity loop problems occasionally!

	while(clusterEdges.size() > 5){  //Change this so that the cluster edges left is n-2 where n is the starting boundary size of the cluster

		if(getSmallestEdgeIndex(globalVertices) != 0){

			std::cout << clusterEdges.size() << "\n";

			for(int i = 0; i < clusterEdges.size(); i++){
				std::cout << clusterEdges[i].getVertexIndex1() << " " << clusterEdges[i].getVertexIndex2() << " index: "<< i <<" \n";
			}

			edgeCollapse(getSmallestEdgeIndex(globalVertices), false, globalTriangles, globalVertices);

		} else {
			// edgeCollapse(5, false, globalVertices);
			break;
		}

		// std::cout << "edge array size: " << clusterEdges.size() << "\n";

		// std::cout << "smallest edge: " << getSmallestEdgeIndex() << "\n";

		recalculateEdgeLengths(globalVertices);
	}
	
}

void Cluster::recalculateEdgeLengths(std::vector<Vertex> &globalVertices){

	for(int i = 0; i < clusterEdges.size(); i++){

		clusterEdges[i].reCalculateEdgeLength(globalVertices);

	}

}

std::vector<Triangle> Cluster::generateOutputTriangles(std::vector<Vertex> &globalVertices){

	// A triangle is when 3 edges make a loop.

	// A duplicate triangle is when 3 nodes are used in a triangle more than once.

	// This needs to be optimized!!

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
							if(checkTriangleAgainstClusterNormal(outputTriangle, 70) == true){
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
							if(checkTriangleAgainstClusterNormal(outputTriangle, 70) == true){
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
							if(checkTriangleAgainstClusterNormal(outputTriangle, 70) == true){
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
							if(checkTriangleAgainstClusterNormal(outputTriangle, 70) == true){
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

std::vector<Triangle> Cluster::getOutputTriangles(){

	return outputTriangles;

}

int Cluster::getSmallestEdgeIndex(std::vector<Vertex> &globalVertices){

	float smallestValue = 100.0;
	int smallestIndex = 0;

	//Place the edge lenths into a ordered set 

	for( int i = 0; i < clusterEdges.size(); i++){
		if(clusterEdges[i].getEdgeLength().getMagnitude() < smallestValue){


			if(globalVertices[clusterEdges[i].getVertexIndex1()].getEdgeOfCluster() != true && globalVertices[clusterEdges[i].getVertexIndex2()].getEdgeOfCluster() != true){
				smallestValue = clusterEdges[i].getEdgeLength().getMagnitude();
				smallestIndex = i;
			}
		}
	}

	return smallestIndex;

}

void Cluster::assignEdgeOfClusterVertices(Triangle rejectedTriangle, std::vector<Vertex> &globalVertices){

	//For vertices in the rejected Triangle assign the ones that are edge vertices

	for(int i = 0; i < rejectedTriangle.getVertexIndices().size(); i++){

		for(int j = 0; j < clusterTriangles.size(); j++){

			if(rejectedTriangle.getVertexIndices()[i] == clusterTriangles[j].getVertexIndices()[0]){
				globalVertices[rejectedTriangle.getVertexIndices()[i]].setEdgeOfCluster(true);
			}

			if(rejectedTriangle.getVertexIndices()[i] == clusterTriangles[j].getVertexIndices()[1]){
				globalVertices[rejectedTriangle.getVertexIndices()[i]].setEdgeOfCluster(true);
			}

			if(rejectedTriangle.getVertexIndices()[i] == clusterTriangles[j].getVertexIndices()[2]){
				globalVertices[rejectedTriangle.getVertexIndices()[i]].setEdgeOfCluster(true);
			}

		}
	}
}

