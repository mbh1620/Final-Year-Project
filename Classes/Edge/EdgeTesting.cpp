#include "../Edge/Edge.cpp"
#include "../Vertex/Vertex.hpp"
#include <iostream>
#include <vector>

int main(){

	Vertex dummyVertex = Vertex(0, 3.4, 4.5, 6.7);
	Vertex vertex1 = Vertex(1, 2.3, 3.4, 5.4);
	Vertex vertex2 = Vertex(2, 3.4, 5.5, 6.5);
	Vertex vertex3 = Vertex(2, 3.4, 5.5, 6.5);

	std::vector<Vertex> globalVertices;

	std::vector<Edge> storedEdges;

 	globalVertices.push_back(dummyVertex);
	globalVertices.push_back(vertex1);
	globalVertices.push_back(vertex2);
	globalVertices.push_back(vertex3);
	
	Edge edge1 = Edge(1, 1, 2, globalVertices);
	Edge edge2 = Edge(2, 1, 2, globalVertices);
	Edge edge3 = Edge(3, 1, 2, globalVertices);

	storedEdges.push_back(edge1);
	storedEdges.push_back(edge2);
	storedEdges.push_back(edge3);

	std::cout << edge1.getVertexIndex1() << "\n";
	std::cout << edge2.getId() << "\n";
	std::cout << edge3.getId() << "\n";

	std::cout << storedEdges[0].getVertexIndex2() << "\n";
	std::cout << storedEdges[1].getId() << "\n";
	std::cout << storedEdges[2].getId() << "\n";
	
}
