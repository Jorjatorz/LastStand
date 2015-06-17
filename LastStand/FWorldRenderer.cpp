#include "FWorldRenderer.h"

#include "FEngine.h"
#include "FResourceManager.h"
#include "Matrix4.h"
#include "FWorld.h"
#include "FObject.h"
#include "Shader.h"
#include "DeferredFrameBuffer.h"
#include "Texture.h"

FWorldRenderer::FWorldRenderer(unsigned short int width, unsigned short int height)
{
	//Create ScreenQuad buffers
	glGenVertexArrays(1, &screenQuadVAO);
	glBindVertexArray(screenQuadVAO);

	glGenBuffers(1, &screenQuadVBO);
	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);

	glVertexAttribPointer(Shader::VERTEXPOSITION, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
	glVertexAttribPointer(Shader::VERTEXTEXCOORD, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	glEnableVertexAttribArray(Shader::VERTEXPOSITION);
	glEnableVertexAttribArray(Shader::VERTEXTEXCOORD);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	_gBuffer = new DeferredFrameBuffer("FGBuffer", width, height);
	_deferredShader_combinationPass = FEngine::getSingleton()->getResourceManagerPtr()->getShaderInMemory("DeferredShading_Combination");
}


FWorldRenderer::~FWorldRenderer()
{
	delete _gBuffer;
}

void FWorldRenderer::renderObjectsInTheWorld(FWorld* currentWorld, const Matrix4& projectionViewMatrix)
{
	//Render all objects into the buffers
	auto objectsList = currentWorld->getObjectsInWorldConstPtr();

	//Apply global uniforms to shader

	//Render all the visible objects into the gBuffers
	for (auto obj : *objectsList)
	{
//		obj.second->renderComponentToGBuffer();
	}

	//Light Pass

	//Combine passes
	drawToScreenQuad(-1, -1, 1, 1);
}

void FWorldRenderer::drawToScreenQuad(float startX, float startY, float endX, float endY)
{
	//Unbind any active framebuffer
	_gBuffer->unBind();

	//Update Vertex and UV data
	const GLfloat vertex_positions[] =
	{
		startX, startY, 0.0f, 1.0f,
		endX, startY, 1.0f, 1.0f,
		endX, endY, 1.0f, 0.0f,

		endX, endY, 1.0f, 0.0f,
		startX, endY, 0.0f, 0.0f,
		startX, startY, 0.0f, 1.0f
	};

	glBindBuffer(GL_ARRAY_BUFFER, screenQuadVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex_positions), vertex_positions, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	//Bind shader
	_deferredShader_combinationPass->bind();

	glDisable(GL_DEPTH_TEST);

	glBindVertexArray(screenQuadVAO);
	//Bind color texture
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, _gBuffer->getFrameBufferTexture("DeferredFrameBufferText_Color")->getTextureId());
	_deferredShader_combinationPass->uniformTexture("colorTex", 0);
	//Bind normals texture
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, _gBuffer->getFrameBufferTexture("DeferredFrameBufferText_Normals")->getTextureId());
	_deferredShader_combinationPass->uniformTexture("normalsTex", 1);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glBindTexture(GL_TEXTURE_2D, 0);
	glBindVertexArray(0);

	glEnable(GL_DEPTH_TEST);

	Shader::unBind();
}