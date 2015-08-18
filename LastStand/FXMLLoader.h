#pragma once

#include <string>

class FMaterial;

//Auxiliary class that loads different type of data from xml files
class FXMLLoader
{
public:
	FXMLLoader();
	~FXMLLoader();

	static FMaterial loadMaterialDataFromXML(std::string XMLfilePath);
};

