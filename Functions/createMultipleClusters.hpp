

//----------------------------------------------------------------
//						createMultipleClusters
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Function Description

*/

//Function Input

//Function Output

bool checkInGlobalTriangles(int startingTriangleId, std::unordered_map<int, Triangle> globalUsedTriangles){
	
	std::unordered_map<int, Triangle>::iterator it = globalUsedTriangles.find(startingTriangleId);

	if( globalUsedTriangles.end() != it){

		return true;

	} else {

		return false;

	}
}

std::vector<Triangle> createMultipleClusters(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles, std::vector<Material> &materials, std::vector<Edge> &edges, int numberOfClusters, float clusterTolerance){

	std::vector<Triangle> trianglesCopy = triangles;

	std::vector<Cluster> clusters;

	std::vector<Triangle> outputTriangles;

	Triangle dummyTriangle = Triangle(-1,0,0,0, vertices);

	outputTriangles.push_back(dummyTriangle);

	std::unordered_map<int, Triangle> globalUsedTriangles;

	int startingValue = 1;

	int numOfTriangles = trianglesCopy.size()-1;

	for(int i = 0; i < numberOfClusters; i++){

		// startingValue = rand() % numOfTriangles + 1;

		int count = 0;

		int startingValue = numOfTriangles/numberOfClusters * i;

		std::cout << "Cluster: " << i << "starting Triangle: " << startingValue << "\n";

		Cluster tempCluster = Cluster(1, trianglesCopy[startingValue], clusterTolerance);

		tempCluster.createCluster(trianglesCopy, globalUsedTriangles, vertices);

		tempCluster.colourCluster(materials, trianglesCopy);

		// tempCluster.displayClusterTriangles();

		// count = 0;
		// for(int i = 0; i < vertices.size(); i++){

		// // std::cout << vertices[i].getEdgeOfCluster() << "\n";

		// // count += vertices[i].getEdgeOfCluster();

		// }

		// std::cout << "STARTING THE ITERATIVE EDGE COLLAPSING HERE! " << i << "\n";

		if(i == 5){

			std::cout << "Cluster 5";

			for(int z = 0; z < tempCluster.getClusterEdges().size(); z++){

				std::cout << tempCluster.getClusterEdges()[z].getVertexIndex1() << "\n";

			}

		}

		tempCluster.iterativelyEdgeCollapse(vertices, trianglesCopy); //Seem to be getting a segfault from this command

		tempCluster.displayEdges();

		std::vector<Triangle> tempTriangles = tempCluster.generateOutputTriangles(vertices);

		for(int i = 0; i < tempTriangles.size(); i++){
			outputTriangles.push_back(tempTriangles[i]);
		}

		// for(int i = 0; i < tempCluster.getClusterEdges().size(); i++){
		// 	edges.push_back(tempCluster.getClusterEdges()[i]);
		// }

		clusters.push_back(tempCluster);

	}
	
	return outputTriangles;

}





