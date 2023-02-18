
#include <iostream>
#include <vector>
#include <unordered_map>
#include <map>
#include "../Vertex/Vertex.cpp"
#include <utility>
#include <ctime>

int main(){


	//Set up an experiment with two containers with the same amount of objects and record the time it takes to access last element for various values of N

	std::unordered_map<int, Vertex> u_map;

	std::vector<Vertex> vertexList;

	int N = 10000000; //Number of elements

	//Speed this section up below using parallelisation

	for(int i = 0; i < N; i++){

		Vertex vertexA = Vertex(i, 1, 2, 3);
		
		std::pair <int,Vertex> my_pair (i,vertexA);

		u_map.insert(my_pair);

		vertexList.push_back(vertexA);

	}

	clock_t start = clock();


	Vertex vertexA = vertexList[N];

	
	std::cout << "Time Taken to access last element of %.2fs\n" << (double)(clock()- start)/CLOCKS_PER_SEC;

	
	start = clock();

	Vertex vertexB = u_map.at(N-1);

	std::cout << "Time Taken: %.2fs\n" << (double)(clock()- start)/CLOCKS_PER_SEC;







}
