#ifndef MATERIAL_H
#define MATERIAL_H

#include "../Vector3D/Vector3D.cpp"

//----------------------------------------------------------------
//						Material Class Header
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class used to store materials colours and textures etc..

*/

/* Class Variables
		
	string Name
	float Ns
	3D vector ka	
	3D vector kd
	3D vector ks
	3D vector ke
	float Ni
	float d

*/

/* Class Functions
	
	getters setters etc..

*/

class Material{

private:

	std::string materialName;

	float ns;

	Vector3D ka;
	Vector3D kd;
	Vector3D ks;
	Vector3D ke;

	float ni;
	float d;

public:

	Material();

	Material(std::string name);

	~Material();

	Material(const Material& a);

	Material& operator=(const Material& a);

	bool operator==(const Material& a);

	void setKdParameter(Vector3D _kdVector);

	void setKdParameter(float r, float g, float b);

	std::string getMaterialName();

	Vector3D getKdParameter();

};

#endif