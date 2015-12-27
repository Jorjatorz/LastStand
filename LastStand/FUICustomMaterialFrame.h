#pragma once
#include "FUIFrame.h"

//UI Frame in which the information displayed can be shader-generated (for example for  procedural graphics, post-process effects, etc).
class FUICustomMaterialFrame :	public FUIFrame
{
public:
	FUICustomMaterialFrame(std::string frameName);
	~FUICustomMaterialFrame();

	void setMaterial(std::string materialPathName);
};

