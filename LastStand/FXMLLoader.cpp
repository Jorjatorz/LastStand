#include "FXMLLoader.h"

#include "FMaterial.h"
#include "FLog.h"

#include <pugixml.hpp>

FXMLLoader::FXMLLoader()
{
}


FXMLLoader::~FXMLLoader()
{
}

FMaterial FXMLLoader::loadMaterialDataFromXML(std::string XMLfilePath)
{
	//Load the XML file
	pugi::xml_document doc;
	pugi::xml_parse_result result = doc.load_file(("Data\\Materials\\" + XMLfilePath).c_str());
	//In case of error
	if (!result)
	{
		FLog(FLog::ERROR, "Error reading XML material file: " + XMLfilePath);
		FLog(FLog::ERROR, "Error description: %s", result.description());
		FLog(FLog::ERROR, "Error offset: %d", result.offset);

		//Return default material
		return FMaterial();
	}

	FMaterial toRetMaterial;
	//Start getting properties for the material
	std::string firstElementName = doc.begin()->name();
	if (firstElementName == "Material")
	{
		pugi::xml_node childs = doc.begin()->first_child();

		while (childs)
		{
			//Shader information
			if (std::string(childs.name()) == "Shader")
			{
				std::string shaderPath = childs.attribute("path").as_string();
				if (!shaderPath.empty())
				{
					toRetMaterial.setNewMaterialShader(shaderPath);
				}
			}
			//Texture information
			else if (std::string(childs.name()) == "Texture")
			{
				std::string samplerName, texturePath;
				samplerName = childs.attribute("uniformName").as_string();
				texturePath = childs.attribute("path").as_string();

				//If the information of the texture is incomplete don't add it
				if (samplerName.empty() || texturePath.empty())
				{
					FLog(FLog::ERROR, "Incomplete Texture information in Material XML: %s", XMLfilePath.c_str());
				}
				else
				{
					toRetMaterial.setTextureForTheMaterial(samplerName, texturePath);
				}
			}
			//Float information
			else if (std::string(childs.name()) == "Float")
			{
				std::string uniformName;
				float value = 0.0; //Default value

				uniformName = childs.attribute("uniformName").as_string();
				value = childs.attribute("value").as_float();

				//If no uniform name dont add it
				if (uniformName.empty())
				{
					FLog(FLog::ERROR, "Need uniform name for Float in Material XML: %s", XMLfilePath.c_str());
				}
				else
				{
					toRetMaterial.addUniform_float(uniformName, value);
				}
			}
			//Vector3 information
			else if (std::string(childs.name()) == "Vector3")
			{
				std::string uniformName;
				Vector3 value(0.0); //Default value

				uniformName = childs.attribute("uniformName").as_string();
				//Get the values of the vector. If the value is not specified in the XML file it takes the default value (0.0)
				value.x = childs.attribute("x").as_float();
				value.y = childs.attribute("y").as_float();
				value.z = childs.attribute("z").as_float();

				//If no uniform name dont add it
				if (uniformName.empty())
				{
					FLog(FLog::ERROR, "Need uniform name for Vector3 in Material XML: %s", XMLfilePath.c_str());
				}
				else
				{
					toRetMaterial.addUniform_vector3(uniformName, value);
				}
			}

			childs = childs.next_sibling();
		}
	}
	else
	{
		FLog(FLog::ERROR, "Material XML error: Root element not found! Must be called Material");
	}

	return toRetMaterial;
}