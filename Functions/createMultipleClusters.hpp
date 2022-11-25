

//----------------------------------------------------------------
//						createMultipleClusters
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Function Description

*/

//Function Input

//Function Output

void createMultipleClusters(std::vector<Vertex> &vertices, std::vector<Triangle> &triangles, std::vector<Material> &materials){

	std::vector<Triangle> trianglesCopy = triangles;

	std::vector<Cluster> clusters; 

	while(trianglesCopy.size() > 1){

		std::cout << "trianglesCopy \n";

		for(int i = 1; i < trianglesCopy.size(); i++){
			std::cout << trianglesCopy[i].getId() << " ";
		}

		std::cout << "\n";

		Cluster newCluster = Cluster(1, trianglesCopy[1], 0.05);

		newCluster.createCluster(trianglesCopy);

		std::cout << "clusterTriangles \n";

		newCluster.displayClusterTriangles();

		for(int i = 0; i < newCluster.getClusterTriangles().size(); i++){

			for(int j = 1; j < trianglesCopy.size(); j++){
				if(newCluster.getClusterTriangles()[i].getId() == trianglesCopy[j].getId()){
					// std::cout << newCluster.getClusterTriangles()[i].getId() << " " << trianglesCopy[j].getId() << "\n";
		
					trianglesCopy.erase(trianglesCopy.begin() + j);
				}
			}
		}

		newCluster.colourCluster(materials, triangles);

		clusters.push_back(newCluster);

	}

	for(int i = 0; i < clusters.size(); i++){
		clusters[i].displayClusterTriangles();
	}

	// std::cout << clusters.size() << "\n";

	

}



