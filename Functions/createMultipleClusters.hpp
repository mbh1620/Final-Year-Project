

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

void createMultipleClusters(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles, std::vector<Material> &materials, int numberOfClusters, float clusterTolerance){

	std::vector<Triangle> trianglesCopy = triangles;

	std::vector<Cluster> clusters;

	std::unordered_map<int, Triangle> globalUsedTriangles;

	int startingValue = 1;

	int numOfTriangles = trianglesCopy.size()-1;

	for(int i = 0; i < numberOfClusters; i++){

		startingValue = rand() % numOfTriangles + 1;

		int count = 0;

		while(checkInGlobalTriangles(startingValue, globalUsedTriangles) == true){
			startingValue = rand() % numOfTriangles + 1;
			count += 1;
			if(count > 10){
				break;
			}
		}

		std::cout << "addingValue" << startingValue << "\n";

		Cluster tempCluster = Cluster(1, trianglesCopy[startingValue], clusterTolerance);

		tempCluster.createCluster(trianglesCopy, globalUsedTriangles);

		tempCluster.colourCluster(materials, triangles);

		tempCluster.displayClusterTriangles();

		clusters.push_back(tempCluster);

	}

}





