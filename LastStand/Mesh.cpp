#include "Mesh.h"

#include <assert.h>

#include "FLog.h"
#include "Shader.h"
#include "Matrix4.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
}

bool Mesh::loadMesh(std::string meshPath)
{
	Assimp::Importer mImporter;
	const aiScene *mAiScene = mImporter.ReadFile(meshPath.c_str(), aiProcessPreset_TargetRealtime_Fast);

	if (!mAiScene)
	{
		FLog(FLog::ERROR, "Assimp couldn't laod the mesh. " + std::string(mImporter.GetErrorString()));
		return false;
	}

	clearSubMeshesVectors();

	//Process all the submeshes
	_subMeshComponentsList.reserve(mAiScene->mNumMeshes);
	for (unsigned int i = 0; i < mAiScene->mNumMeshes; ++i)
	{
		aiMesh* loadedMesh = mAiScene->mMeshes[i];

		tMeshComponentsStruct newSubMesh;
		generateMeshComponentsBuffers(newSubMesh);

		newSubMesh._vertexVector.reserve(loadedMesh->mNumVertices * 3);
		newSubMesh._normalsVector.reserve(loadedMesh->mNumVertices * 3);
		newSubMesh._texCoordsVector.reserve(loadedMesh->mNumVertices * 2);
		newSubMesh._indexVector.reserve(loadedMesh->mNumFaces * 3);
		for (unsigned int j = 0; j < loadedMesh->mNumVertices; ++j)
		{
			//create vertex array
			const aiVector3D* vertex = &loadedMesh->mVertices[j]; //copy the vertices
			const aiVector3D* normal = &loadedMesh->mNormals[j]; //copy the vertices
			const aiVector3D* texCoord = &loadedMesh->mTextureCoords[0][j];

			if (loadedMesh->HasPositions())
			{
				newSubMesh._vertexVector.push_back(vertex->x);
				newSubMesh._vertexVector.push_back(vertex->y);
				newSubMesh._vertexVector.push_back(vertex->z);
			}

			if (loadedMesh->HasNormals())
			{
				newSubMesh._normalsVector.push_back(normal->x);
				newSubMesh._normalsVector.push_back(normal->y);
				newSubMesh._normalsVector.push_back(normal->z);
			}

			if (loadedMesh->HasTextureCoords(0))
			{
				newSubMesh._texCoordsVector.push_back(texCoord->x);
				newSubMesh._texCoordsVector.push_back(texCoord->y);
			}
		}

		for (unsigned int j = 0; j < loadedMesh->mNumFaces; ++j)
		{
			//create index array
			const aiFace* face = &loadedMesh->mFaces[j];

			assert(face->mNumIndices == 3);

			newSubMesh._indexVector.push_back(face->mIndices[0]);
			newSubMesh._indexVector.push_back(face->mIndices[1]);
			newSubMesh._indexVector.push_back(face->mIndices[2]);
		}

		glBindVertexArray(newSubMesh.vertexArrayObject);

		//Fill buffers
		//vertices
		if (loadedMesh->HasPositions())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.vertexBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._vertexVector.size() * sizeof(GLfloat), &newSubMesh._vertexVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXPOSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write vertices position to the shader
			glEnableVertexAttribArray(Shader::VERTEXPOSITION);
		}
		//normals
		if (loadedMesh->HasNormals())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._normalsVector.size() * sizeof(GLfloat), &newSubMesh._normalsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXNORMALS, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEXNORMALS);
		}
		//UV coords
		if (loadedMesh->HasTextureCoords(0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.texCoordsBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._texCoordsVector.size() * sizeof(GLfloat), &newSubMesh._texCoordsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEXTEXCOORD, 2, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEXTEXCOORD);
		}

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, newSubMesh.indexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, newSubMesh._indexVector.size() * sizeof(GLuint), &newSubMesh._indexVector[0], GL_STATIC_DRAW);

		//Save the new mesh
		_subMeshComponentsList.push_back(newSubMesh);
	}

	// unbind buffers
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	return true;
}

void Mesh::generateMeshComponentsBuffers(tMeshComponentsStruct& mMeshComp)
{
	glGenVertexArrays(1, &mMeshComp.vertexArrayObject);
	glGenBuffers(1, &mMeshComp.vertexBuffer);
	glGenBuffers(1, &mMeshComp.normalBuffer);
	glGenBuffers(1, &mMeshComp.texCoordsBuffer);
	glGenBuffers(1, &mMeshComp.indexBuffer);
}

void Mesh::renderAllSubMeshes(const Matrix4& worldTransformationM)
{
	//For each submesh renders its vertex array to the buffer
	for(auto &it : _subMeshComponentsList)
	{
		//Apply the material
		it._subMeshMaterial.applyMaterialToStaticMesh();

		//Send the mesh matrices
		it._subMeshMaterial.getMaterialShader()->uniformMatrix("Renderer_ModelMatrix", worldTransformationM);
		it._subMeshMaterial.getMaterialShader()->uniformMatrix("Renderer_NormalMatrix", worldTransformationM.getInverseTransposeMatrix());

		glBindVertexArray(it.vertexArrayObject);

		glDrawElements(GL_TRIANGLES, it._indexVector.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		//Shader of the amterial must be detached
		Shader::unBind();
	}
}

void Mesh::clearSubMeshesVectors()
{
	if (!_subMeshComponentsList.empty())
	{
		for (auto &it : _subMeshComponentsList)
		{
			it._vertexVector.clear();
			it._vertexVector.reserve(0);
			it._normalsVector.clear();
			it._normalsVector.reserve(0);
			it._texCoordsVector.clear();
			it._texCoordsVector.reserve(0);
			it._indexVector.clear();
			it._indexVector.reserve(0);
		}
		_subMeshComponentsList.clear();
		_subMeshComponentsList.reserve(0);
	}
}

std::vector<FMaterial*> Mesh::getMaterialList()
{
	std::vector<FMaterial*> toRetVector;
	for (auto &it : _subMeshComponentsList)
	{
		toRetVector.push_back(&(it._subMeshMaterial));
	}

	return toRetVector;
}
