#ifndef VERTEX_H
#define VERTEX_H

//----------------------------------------------------------------
//							Vertex Class
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Vertex Class

*/

/* Variables

	float x
	float y
	float z

*/

/* Functions

	Add

	Subtract


*/

class Vertex{

private:

	int id;
	float x;
	float y;
	float z;

public:

	Vertex(int id, float x, float y, float z);

	~Vertex();

	Vertex(const Vertex& a);

	Vertex& operator=(const Vertex& a);

	Vertex& operator+(const Vertex& a);

	Vertex& operator-(const Vertex& a);

	float get(char d);

	float getId();

	void set(char d, float value);

};

#endif