#include "FRenderer.h"

#include "FEngine.h"
#include "FResourceManager.h"
#include "Matrix4.h"
#include "FWorld.h"
#include "FObject.h"
#include "FDeferredFrameBuffer.h"
#include "Texture.h"
#include "FScene.h"
#include "FCameraManager.h"
#include "FCameraComponent.h"
#include "FMaterial.h"

FRenderer::FRenderer(unsigned short int width, unsigned short int height)
	:_currentFrameProjectionM(NULL),
	_currentFrameViewM(NULL)
{
	//Create the FScene
	_sceneToRender = new FScene();

	//Create the GBuffer
	_gBuffer = new FDeferredFrameBuffer("FGBuffer", width, height);

	//Create the screenQuad and sets its material
	_screenQuadMesh.setNewMesh("UnitQuad.obj");
	_screenQuadMesh.getMeshMaterialList().at(0)->setTextureForTheMaterial("colorTex", "DeferredFrameBufferText_Color");
	_screenQuadMesh.getMeshMaterialList().at(0)->setTextureForTheMaterial("normalsTex", "DeferredFrameBufferText_Normals");
	_screenQuadMesh.getMeshMaterialList().at(0)->setTextureForTheMaterial("lightTex", "DeferredFrameBufferText_Light");
	_screenQuadMesh.getMeshMaterialList().at(0)->setTextureForTheMaterial("finalTex", "DeferredFrameBufferText_Final");
}


FRenderer::~FRenderer()
{
	delete _gBuffer;
	delete _sceneToRender;
}

void FRenderer::renderObjectsInTheWorld()
{
	FCameraManager* cameraManagerPtr = FEngine::getInstance()->getPlayerController()->getCameraManagerPtr();
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
	drawToScreenQuad();
}

void FRenderer::doDeferredPass(FCameraComponent* currentCamera)
{
	//Set frame matrices
	currentCamera->getCameraProjectionAndViewMatricesPtr(_currentFrameProjectionM, _currentFrameViewM);

	//Geometry Pass
	geometryPass();

	//Light Pass
	lightPass();

	//Combine pass
	finalPass();
	if (currentCamera->hasRenderingTarget())
	{
		Texture::copyTextureRawData(_gBuffer->getFrameBufferTexture("DeferredFrameBufferText_Final"), currentCamera->getRendeingTargetPtr());
	}
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

void FRenderer::geometryPass()
{
	//Bind GBuffer for geometry pass
	_gBuffer->bindForGeometryPass();

	glDepthMask(GL_TRUE);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);

	_sceneToRender->drawAllStaticComponents();

	glDepthMask(GL_FALSE);
}

void FRenderer::lightPass()
{
	//glDepthFunc(GL_GREATER);
	glEnable(GL_BLEND);
	glBlendEquation(GL_FUNC_ADD);
	glBlendFunc(GL_ONE, GL_ONE);

	//Bind GBuffer for light pass
	_gBuffer->bindForLightPass();

	glClearColor(0.0, 0.0, 0.0, 1.0);
	glClear(GL_COLOR_BUFFER_BIT);

	_sceneToRender->drawAllLightComponents();

	glDisable(GL_BLEND);
	glDepthFunc(GL_LEQUAL);
}

void FRenderer::finalPass()
{
	//Unbind any active framebuffer
	_gBuffer->bindForFinalPass();
	glClear(GL_COLOR_BUFFER_BIT);

	glDisable(GL_DEPTH_TEST);

	_screenQuadMesh.getMeshMaterialList().at(0)->setNewMaterialShader("DeferredShading_FinalToBuffer");
	_screenQuadMesh.renderStaticMesh(Matrix4(1.0));

	glEnable(GL_DEPTH_TEST);

	_gBuffer->unBindFrameBuffer();
}

void FRenderer::drawToScreenQuad()
{
	_gBuffer->unBindFrameBuffer();

	glDisable(GL_DEPTH_TEST);

	_screenQuadMesh.getMeshMaterialList().at(0)->setNewMaterialShader("DeferredShading_FinalToScreen");
	_screenQuadMesh.renderStaticMesh(Matrix4(1.0));

	glEnable(GL_DEPTH_TEST);
}
