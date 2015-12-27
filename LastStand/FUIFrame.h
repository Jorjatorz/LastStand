#pragma once

#include "FObject.h"

#include "FStaticMesh.h"
#include "Vector3.h"

class Texture;

//Class that represents a renderable frame of the UI
class FUIFrame : public FObject
{
public:
	FUIFrame(std::string frameName);
	~FUIFrame();

	//Type of the different frames
	enum FrameType
	{
		DEFAULT_FRAME = 0,
		INPUT_FRAME = 1,
		SHADER_FRAME = 2
	};
	FrameType getType() const;

	virtual void setPostion(const Vector3& newPos); //Clamped [-1, 1]
	virtual void setScale(const Vector3& newScale); //Clamped [0, 1]

	//Sets the texture attached to the frame
	void setTexture(Texture* texture);

	//Called each frame.
	virtual void tickFrame(float deltaTime);

	//Renders the frameMesh with the texture. If no texture exists its not rendered.
	//WARNING! Called only by the FUIManager.
	void renderFrame();

protected:
	FrameType _frameType;
	//Mesh that represents the Frame. By default a screen quad.
	FStaticMesh _frameMesh;
	Vector3 _position; //Clamped [-1, 1]
	Vector3 _scale; //Clamped [0, 1]
	//Texture that will be rendered into the mesh
	Texture* _frameTexture;
};

