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

	int v;
	int t;

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
						t++;
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

	std::vector<std::string> words = stringSplit(vertexLine, ' ');

	Vertex outputVertex = Vertex(vertexCount, std::stof(words[1]), std::stof(words[2]), std::stof(words[3]));

	return outputVertex;

}

std::vector<Triangle> ReadWriter::faceParser(std::string faceLine, int triangleCount, std::vector<Vertex> &vertices){

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
		Triangle outputTriangle2 = Triangle(triangleCount, vertexIndices[0], vertexIndices[2], vertexIndices[3], vertices);

		outputTriangles.push_back(outputTriangle1);
		outputTriangles.push_back(outputTriangle2);

		return outputTriangles;
	}

	return outputTriangles;
}

void ReadWriter::writeObjFile(std::string fileName){

}

bool ReadWriter::checkFileType(std::string fileType, std::string fileName){

	std::string actualFileType = fileName.substr(fileName.find('.'), fileName.length());

	if(actualFileType == fileType){
		return true;
	} else {
		return false;
	}

}