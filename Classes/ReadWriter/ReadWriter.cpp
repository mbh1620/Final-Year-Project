#include <fstream>
#include <sstream>
#include "ReadWriter.hpp"

#include "../Vertex/Vertex.hpp"
#include "../Triangle/Triangle.hpp"
#include "../../Functions/stringSplit.hpp"

//----------------------------------------------------------------
//						ReadWriter Class Main
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

ReadWriter for reading in and writing to .obj and .tri files

*/

ReadWriter::ReadWriter() {

}

ReadWriter::~ReadWriter() {

}

ReadWriter::ReadWriter(const ReadWriter& a){

}

ReadWriter& ReadWriter:: operator=(const ReadWriter& a){

	return *this;
}

void ReadWriter::readTriFile(std::string fileName){

	std::ifstream file;

	std::string line;

	if(checkFileType(".tri", fileName) == true){

		file.open(fileName);

		if(file.is_open()){
			while(getline(file, line)){
				std::cout << line << "\n";
				//processObjLine();
			}
		} else {
			std::cout << "ERROR: File will not open!\n";
			throw;
		}

	} else {
		std::cout << "ERROR: File is not .tri!\n";
		throw;
	}

}

void ReadWriter::processTriLine(std::string line){

}

void ReadWriter::writeTriFile(std::string fileName){

}

std::vector<Vertex> ReadWriter::readObjFile(std::string fileName, std::vector<Vertex>& vertices, std::vector<Triangle>& triangles){

	std::ifstream file;

	std::string line;

	int v = 1;
	int t = 1;

	if(checkFileType(".obj", fileName) == true){

		file.open(fileName);

		if(file.is_open()){
			while(getline(file, line)){
				switch(line[0]){

					case '#':
						break;
					case 'v':
						if(line[1] == ' '){
							Vertex tempVertex = vertexParser(line, v);

							vertices.push_back(tempVertex);

							v++;
						}
						break;
					case 'f': {

						std::vector<Triangle> outputTriangles;

						outputTriangles = faceParser(line, t, vertices);

						for(int i = 0; i < outputTriangles.size(); i++){
							triangles.push_back(outputTriangles[i]);
						}

						if(outputTriangles.size() == 1){
							t++;
						} else if( outputTriangles.size() == 2){
							t += 2;
						}
					
					}
						break;
					default:
						break;
					}
			}
		} else {
			std::cout << "ERROR: File will not open!\n";
			throw;
		}

	} else {
		std::cout << "ERROR: File is not .obj!\n";
		throw;
	}

	return vertices;

}

Vertex ReadWriter::vertexParser(std::string vertexLine, int vertexCount){

	//Function for parsing the vertices in the .obj file

	std::vector<std::string> words = stringSplit(vertexLine, ' ');

	Vertex outputVertex = Vertex(vertexCount, std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));

	return outputVertex;

}

std::vector<Triangle> ReadWriter::faceParser(std::string faceLine, int triangleCount, std::vector<Vertex> &vertices){

	//Function for parsing the faces in the file

	std::vector<Triangle> outputTriangles;

	std::vector<std::string> words = stringSplit(faceLine, ' ');

	if(words.size() == 4){

		std::vector<int> vertexIndices;

		int index;

		for( int i = 0; i < words.size(); i++){

			if(words[i] != "f"){

				index = std::stoi(stringSplit(words[i], '/')[0]);

				vertexIndices.push_back(index);

			} 

		}

		Triangle outputTriangle = Triangle(triangleCount, vertexIndices[0], vertexIndices[1], vertexIndices[2], vertices);

		outputTriangles.push_back(outputTriangle);

		return outputTriangles;

	} else if(words.size() == 5){
		std::vector<int> vertexIndices;

		int index;

		for( int i = 0; i < words.size(); i++){

			if(words[i] != "f"){

				index = std::stoi(stringSplit(words[i], '/')[0]);

				vertexIndices.push_back(index);

			} 

		}

		Triangle outputTriangle1 = Triangle(triangleCount, vertexIndices[0], vertexIndices[1], vertexIndices[2], vertices);
		Triangle outputTriangle2 = Triangle(triangleCount+1, vertexIndices[0], vertexIndices[2], vertexIndices[3], vertices);
		
		outputTriangles.push_back(outputTriangle1);
		outputTriangles.push_back(outputTriangle2);

		return outputTriangles;
	}

	return outputTriangles;
}

void ReadWriter::writeObjFile(std::string fileName, std::vector<Vertex> &vertices, std::vector<Triangle> &triangles, std::vector<Material> &materials, std::vector<Edge> &edges, bool materialFile, bool colourClusters){

	//Write all of the elements to file

	std::ofstream file;

	std::string objFileName = fileName + ".obj";

	file.open(objFileName);

	file << "# Matthew Haywood - Mesh Simplification Project output file.\n";

	file << "# Electronic and Electrical Engineering, The University of Nottingham.\n";

	file << "# Vertices: " << vertices.size() << " Triangles: " << triangles.size() << "\n" ;

	file << "mtllib " + fileName + ".mtl\n";

	file << "o Cube \n";

	vertices.erase(vertices.begin());

	for(int i = 0; i < vertices.size(); i++){
		file << "v " << float(vertices[i].get('x'))<< " " << float(vertices[i].get('y')) << " " << float(vertices[i].get('z')) << "\n";
	}

	for(int i = 1; i < triangles.size(); i++){

		file << "vn " << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[0] << " " << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[1] << " " << triangles[i].getTriangleNormal().getNormalisedDirectionComponents()[2] << "\n"; 

	}

	file << "\n";

	std::vector<Triangle> trianglesCopy = triangles;

	trianglesCopy.erase(trianglesCopy.begin());

	for(int i = 0; i < materials.size(); i++){

		file << "g Cube_Cube_Material\n";
		file << "usemtl " << materials[i].getMaterialName() << "\n";
		file << "s off \n";

		

		for(int j = 0; j < trianglesCopy.size(); j++){
			if(trianglesCopy[j].getTriangleMaterial() == materials[i]){

				file << "f " << trianglesCopy[j].getVertexIndices()[0] << "//" << j+1 << " " << trianglesCopy[j].getVertexIndices()[1] << "//" << j+1 << " " << trianglesCopy[j].getVertexIndices()[2] << "//" << j+1 << "\n";

			}
		}

		file << "\n";
	}

	for(int i = 1; i < edges.size(); i++){

		file << "l " << edges[i].getVertexIndex1() << " " <<edges[i].getVertexIndex2() << "\n";
	}

	file.close();

	if(materialFile == true){

		std::string mtlFileName = fileName + ".mtl";

		writeMtlFile(mtlFileName, materials);

	}

}

void ReadWriter::writeMtlFile(std::string fileName, std::vector<Material> &materials){

	//Write the materials to file

	std::ofstream file;

	file.open(fileName);

	file << "# Matthew Haywood - Mesh Simplification Project output Material File.\n";
	file << "# Material1 \n\n";

	for(int i = 0; i < materials.size(); i++){

		file << "newmtl " << materials[i].getMaterialName() <<"\n";
		file << "Kd " << materials[i].getKdParameter().getDirectionComponents()[0] << " " << materials[i].getKdParameter().getDirectionComponents()[1] << " " << materials[i].getKdParameter().getDirectionComponents()[2] << "\n";
		file << "\n";
	}

	file.close();

}

bool ReadWriter::checkFileType(std::string fileType, std::string fileName){

	std::string actualFileType = fileName.substr(fileName.find('.'), fileName.length());

	if(actualFileType == fileType){
		return true;
	} else {
		return false;
	}

}