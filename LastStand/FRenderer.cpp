#include "FRenderer.h"

#include "FEngine.h"
#include "FResourceManager.h"
#include "Matrix4.h"
#include "FWorld.h"
#include "FObject.h"
#include "Shader.h"
#include "FDeferredFrameBuffer.h"
#include "Texture.h"
#include "FScene.h"
#include "FCameraManager.h"
#include "FCameraComponent.h"

FRenderer::FRenderer(unsigned short int width, unsigned short int height)
	:_currentFrameProjectionM(NULL),
	_currentFrameViewM(NULL)
{
	//Create the FScene
	_sceneToRender = new FScene();

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

	_gBuffer = new FDeferredFrameBuffer("FGBuffer", width, height);
	_deferredShader_combinationPass = FResourceManager::getInstance()->getShaderInMemory("DeferredShading_Combination");
}


FRenderer::~FRenderer()
{
	glDeleteBuffers(1, &screenQuadVBO);
	glDeleteVertexArrays(1, &screenQuadVAO);

	delete _gBuffer;
	delete _sceneToRender;
}

void FRenderer::renderObjectsInTheWorld()
{
	FCameraManager* cameraManagerPtr = FEngine::getInstance()->getCameraManagerPtr();
	for (auto &it : cameraManagerPtr->getCameraComponentsList())
	{
		if (it != cameraManagerPtr->getViewportCamera())
		{
			//It's only useful to render from a camera if it has a rendering target
			if (it->hasRenderingTarget())
			{
				doDeferredPass(it);
			}
		}
	}

	//DO the deferred pass only with the viewport camera and draw the output to the ScreenQuad
	FCameraComponent* viewCamera = cameraManagerPtr->getViewportCamera();
	doDeferredPass(viewCamera);
	//Combine passes
	drawToScreenQuad(-1, -1, 1, 1);
}

void FRenderer::doDeferredPass(FCameraComponent* currentCamera)
{
	//Set frame matrices
	currentCamera->getCameraProjectionAndViewMatricesPtr(_currentFrameProjectionM, _currentFrameViewM);

	//Bind GBuffer
	_gBuffer->bindForGeometryPass();
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Fill Pass
	_sceneToRender->drawAllElements();

	//Light Pass
	_gBuffer->bindForLightPass();

	//Combine passes
	//Bind shader
	_deferredShader_combinationPass->bind();

	///TODO -- Set here the combination texture
	if (currentCamera->hasRenderingTarget())
	{
		Texture::copyTextureRawData(_gBuffer->getFrameBufferTexture("DeferredFrameBufferText_Color"), currentCamera->getRendeingTargetPtr());
	}

	Shader::unBind();
}

void FRenderer::drawToScreenQuad(float startX, float startY, float endX, float endY)
{
	//Unbind any active framebuffer
	_gBuffer->unBindFrameBuffer();

	//Update Vertex and UV data
	const GLfloat vertex_positions[] =
	{
		startX, startY, 0.0f, 0.0f,
		endX, startY, 1.0f, 0.0f,
		endX, endY, 1.0f, 1.0f,

		endX, endY, 1.0f, 1.0f,
		startX, endY, 0.0f, 1.0f,
		startX, startY, 0.0f, 0.0f
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

FScene* const FRenderer::getCurrentFScene()
{
	return _sceneToRender;
}

const Matrix4& FRenderer::getCurrentFrameProjectionMatrix()
{
	return *_currentFrameProjectionM;
}

const Matrix4& FRenderer::getCurrentFrameViewMatrix()
{
	return *_currentFrameViewM;
}
