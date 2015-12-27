#include "FUICustomMaterialFrame.h"

#include "Matrix4.h"
#include "FXMLLoader.h"

FUICustomMaterialFrame::FUICustomMaterialFrame(std::string frameName)
	:FUIFrame(frameName)
{
	_frameType = SHADER_FRAME;
}


FUICustomMaterialFrame::~FUICustomMaterialFrame()
{
}

void FUICustomMaterialFrame::setMaterial(std::string materialPathName)
{
	*(_frameMesh.getMeshMaterialList().at(0)) = FXMLLoader::loadMaterialDataFromXML(materialPathName); //Default material
}
