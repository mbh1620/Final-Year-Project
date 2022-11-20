#ifndef READWRITER_H
#define READWRITER_H

#include "../Triangle/Triangle.hpp"
//----------------------------------------------------------------
//						ReadWriter Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class used to Read and Write from various file types. Main File type is .tri

*/

//Class Variables

/*

Read from .tri file

Write to .tri file

*/

class ReadWriter{

private:

public:

	ReadWriter();

	~ReadWriter();

	ReadWriter(const ReadWriter& a);

	ReadWriter& operator=(const ReadWriter& a);

	void readTriFile(std::string fileName);

	void processTriLine(std::string line);

	void writeTriFile(std::string fileName);

	std::vector<Vertex> readObjFile(std::string fileName, std::vector<Vertex> &vertices, std::vector<Triangle> &triangles);

	Vertex vertexParser(std::string vertexLine, int vertexCount);

	std::vector<Triangle> faceParser(std::string faceLine, int triangleCount);

	void writeObjFile(std::string fileName);
	
	bool checkFileType(std::string fileType, std::string fileName);

};

#endif