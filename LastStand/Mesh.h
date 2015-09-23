#pragma once

#include <vector>

#include <gl/glew.h>
#include <gl/gl.h>

//ASSIMP
#include <assimp\Importer.hpp>
#include <assimp\postprocess.h>
#include <assimp\scene.h>
#include <assimp\types.h>
#include <assimp\vector3.h>

#include "FMaterial.h"

class Matrix4;

class Mesh
{
public:
	Mesh();
	~Mesh();

	//Load the mesh (vertices, normals, etc) from a file
	///Could make this function statis but returning a Mesh by copy is really slow (and creating insite load mesh is not good practice)
	bool loadMesh(std::string meshPath);

	//Renders all the submeshes into the buffer
	void renderAllSubMeshes(const Matrix4& worldTransformationM, std::vector<FMaterial>& meshMaterials);

	//Return the numbers of materials that the mesh can have
	unsigned short int getNumberOfMaterialsSlots()
	{
		return _subMeshComponentsList.size();
	}

private:
	//Struct with all the information need for openGL to render it.
	//A mesh is made of several submeshes, each submesh hast one associated meshstruct
	typedef struct
	{
		//Vertices info
		std::vector<GLfloat> _vertexVector;
		std::vector<GLfloat> _normalsVector;
		std::vector<GLfloat> _texCoordsVector;
		std::vector<GLfloat> _tangentsVector;
		std::vector<GLuint> _indexVector;

		//openGL buffers
		GLuint vertexBuffer, normalBuffer, texCoordsBuffer, tangentBuffer, indexBuffer, vertexArrayObject;
	} tMeshComponentsStruct;
	//List containing all the submeshes components structs
	std::vector<tMeshComponentsStruct> _subMeshComponentsList;
	
	//Clear all the submeshes components vector
	void clearSubMeshesVectors();

	//Generates all the opengl buffers given a meshComponentstruct
	void generateMeshComponentsBuffers(tMeshComponentsStruct& mMeshComp);
};

