#include "Mesh.h"

#include <assert.h>

#include "FLog.h"
#include "Shader.h"

Mesh::Mesh()
{
}


Mesh::~Mesh()
{
	for (auto& subMeshComp : _subMeshComponentsList)
	{
		glDeleteBuffers(1, &subMeshComp.vertexBuffer);
		glDeleteBuffers(1, &subMeshComp.normalBuffer);
		glDeleteBuffers(1, &subMeshComp.texCoordsBuffer);
		glDeleteBuffers(1, &subMeshComp.tangentBuffer);
		glDeleteBuffers(1, &subMeshComp.indexBuffer);
		glDeleteVertexArrays(1, &subMeshComp.vertexArrayObject);
	}
}

bool Mesh::loadMesh(std::string meshPath)
{
	Assimp::Importer mImporter;
	const aiScene *mAiScene = mImporter.ReadFile(meshPath.c_str(), aiProcess_Triangulate | aiProcess_GenUVCoords | aiProcess_CalcTangentSpace);

	if (!mAiScene)
	{
		FLog(FLog::FAILURE, "Assimp couldn't laod the mesh. " + std::string(mImporter.GetErrorString()));
		return false;
	}

	clearSubMeshesVectors();

	//Information data to print into screen when the load is done
	unsigned int numberOfVertices = 0;
	unsigned int numberOfFaces = 0;

	//Process all the submeshes
	_subMeshComponentsList.reserve(mAiScene->mNumMeshes);
	for (unsigned int i = 0; i < mAiScene->mNumMeshes; ++i)
	{
		aiMesh* loadedMesh = mAiScene->mMeshes[i];

		tMeshComponentsStruct newSubMesh;
		generateMeshComponentsBuffers(newSubMesh);

		newSubMesh._vertexVector.reserve(loadedMesh->mNumVertices); numberOfVertices += loadedMesh->mNumVertices;
		newSubMesh._normalsVector.reserve(loadedMesh->mNumVertices);
		newSubMesh._texCoordsVector.reserve(loadedMesh->mNumVertices);
		newSubMesh._tangentsVector.reserve(loadedMesh->mNumVertices);
		newSubMesh._indexVector.reserve(loadedMesh->mNumFaces); numberOfFaces += loadedMesh->mNumFaces;
		for (unsigned int j = 0; j < loadedMesh->mNumVertices; ++j)
		{
			if (loadedMesh->HasPositions())
			{
				const aiVector3D* vertex = &loadedMesh->mVertices[j];

				newSubMesh._vertexVector.push_back(vertex->x);
				newSubMesh._vertexVector.push_back(vertex->y);
				newSubMesh._vertexVector.push_back(vertex->z);
			}

			if (loadedMesh->HasNormals())
			{
				const aiVector3D* normal = &loadedMesh->mNormals[j];

				newSubMesh._normalsVector.push_back(normal->x);
				newSubMesh._normalsVector.push_back(normal->y);
				newSubMesh._normalsVector.push_back(normal->z);
			}

			if (loadedMesh->HasTextureCoords(0))
			{
				const aiVector3D* texCoord = &loadedMesh->mTextureCoords[0][j];

				newSubMesh._texCoordsVector.push_back(texCoord->x);
				newSubMesh._texCoordsVector.push_back(texCoord->y);
			}

			if (loadedMesh->HasTangentsAndBitangents())
			{
				const aiVector3D* tangent = &loadedMesh->mTangents[j];

				newSubMesh._tangentsVector.push_back(tangent->x);
				newSubMesh._tangentsVector.push_back(tangent->y);
				newSubMesh._tangentsVector.push_back(tangent->z);
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
			glVertexAttribPointer(Shader::VERTEX_POSITION, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write vertices position to the shader
			glEnableVertexAttribArray(Shader::VERTEX_POSITION);
		}
		//Tormals
		if (loadedMesh->HasNormals())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.normalBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._normalsVector.size() * sizeof(GLfloat), &newSubMesh._normalsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEX_NORMALS, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEX_NORMALS);
		}
		//UV coords
		if (loadedMesh->HasTextureCoords(0))
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.texCoordsBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._texCoordsVector.size() * sizeof(GLfloat), &newSubMesh._texCoordsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEX_TEXCOORDS, 2, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEX_TEXCOORDS);
		}
		//Tangents
		if (loadedMesh->HasTangentsAndBitangents())
		{
			glBindBuffer(GL_ARRAY_BUFFER, newSubMesh.tangentBuffer);
			glBufferData(GL_ARRAY_BUFFER, newSubMesh._tangentsVector.size() * sizeof(GLfloat), &newSubMesh._tangentsVector[0], GL_STATIC_DRAW);
			glVertexAttribPointer(Shader::VERTEX_TANGENTS, 3, GL_FLOAT, GL_FALSE, 0, NULL); //write normals position to the shader
			glEnableVertexAttribArray(Shader::VERTEX_TANGENTS);
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

	FLog(FLog::INFO, meshPath + " Vertices: " + std::to_string(numberOfVertices) + " Faces: " + std::to_string(numberOfFaces));

	return true;
}

void Mesh::generateMeshComponentsBuffers(tMeshComponentsStruct& mMeshComp)
{
	glGenVertexArrays(1, &mMeshComp.vertexArrayObject);
	glGenBuffers(1, &mMeshComp.vertexBuffer);
	glGenBuffers(1, &mMeshComp.normalBuffer);
	glGenBuffers(1, &mMeshComp.texCoordsBuffer);
	glGenBuffers(1, &mMeshComp.tangentBuffer);
	glGenBuffers(1, &mMeshComp.indexBuffer);
}

void Mesh::renderAllSubMeshes(const Matrix4& worldTransformationM, std::vector<FMaterial>& meshMaterials)
{
	//For each submesh renders its vertex array to the buffer
	unsigned short int i = 0;
	for(const auto &it : _subMeshComponentsList)
	{
		//Apply the material
		meshMaterials.at(i).sendMaterialInformationToGPU(worldTransformationM);

		glBindVertexArray(it.vertexArrayObject);

		glDrawElements(GL_TRIANGLES, it._indexVector.size(), GL_UNSIGNED_INT, 0);

		glBindVertexArray(0);

		//Shader of the amterial must be detached
		Shader::unBind();

		i++;
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