#include "FUIFrame.h"
#include "Matrix4.h"
#include "Math.h"
#include "Texture.h"

FUIFrame::FUIFrame(std::string frameName)
	:FObject(frameName),
	_frameMesh("UnitQuad.obj"), //Screen Quad by default
	_position(-1.0, 1.0, 0.0),
	_scale(1.0),
	_frameTexture(NULL),
	_frameType(DEFAULT_FRAME)
{
	_frameMesh.getMeshMaterialList().at(0)->setNewMaterialShader("UIPassShader"); //Default material
}


FUIFrame::~FUIFrame()
{
}

void FUIFrame::tickFrame(float deltaTime)
{
	FObject::tickObject(deltaTime);
}

void FUIFrame::renderFrame()
{
	if (_frameTexture || _frameType == SHADER_FRAME)
	{
		Matrix4 transformMatrix;
		transformMatrix.translate(_position + Vector3(_scale.x, -_scale.y, 0.0));
		transformMatrix.scale(_scale);
		_frameMesh.renderStaticMesh(transformMatrix);
	}
}

void FUIFrame::setPostion(const Vector3& newPos)
{
	_position = Math::clamp(newPos, -1, 1);
}

void FUIFrame::setScale(const Vector3& newScale)
{
	_scale = Math::clamp(newScale, 0.0, 1.0);
}

void FUIFrame::setTexture(Texture* texture)
{
	_frameTexture = texture;

	_frameMesh.getMeshMaterialList().at(0)->setTextureForTheMaterial("frameTexture", _frameTexture);
}

FUIFrame::FrameType FUIFrame::getType() const
{
	return _frameType;
}
