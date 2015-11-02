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

	void setPostion(const Vector3& newPos);
	void setScale(const Vector3& newScale);

	//Sets the texture attached to the frame
	void setTexture(Texture* texture);

	//Called each frame.
	virtual void tick(float deltaTime);

	//Renders the frameMesh with the texture. If no texture exists its not rendered.
	//WARNING! Called only by the FUIManager.
	void renderFrame();

private:
	//Mesh that represents the Frame. By default a screen quad.
	FStaticMesh _frameMesh;
	Vector3 _position; //Clamped [-1, 1]
	Vector3 _scale; //Clamped [0, 1]
	//Texture that will be rendered into the mesh
	Texture* _frameTexture;
};

