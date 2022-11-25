#include "Material.hpp"
//----------------------------------------------------------------
//						Class Main Template
//----------------------------------------------------------------

//Author: Matthew Haywood

/* 

Class Description

*/

Material::Material(){

}

Material::Material(std::string _materialName){

	materialName = _materialName;

}

Material::~Material(){

}

Material::Material(const Material& a){
	materialName = a.materialName;
	
	ns = a.ns;
	
	ka = a.ka;
	kd = a.kd;
	ks = a.ks;
	ke = a.ke;

	ni = a.ni;
	d = a.d;

}

Material& Material:: operator=(const Material& a){

	materialName = a.materialName;
	
	ns = a.ns;
	
	ka = a.ka;
	kd = a.kd;
	ks = a.ks;
	ke = a.ke;

	ni = a.ni;
	d = a.d;

	return *this;
}

bool Material:: operator==(const Material& a){

	if(materialName == a.materialName){
		return true;
	} else {
		return false;
	}
}

void Material::setKdParameter(Vector3D _kdVector){
	
	kd = _kdVector;

}

void Material::setKdParameter(float r, float g, float b){

	Vector3D kdParameter = Vector3D(1, r, g, b);

	kd = kdParameter;

}

std::string Material::getMaterialName(){

	return materialName;

}

Vector3D Material::getKdParameter(){

	return kd;

}
