 #pragma once
#include "DirectXFramework.h"
#include "CubeNode.h"

class DirectXApp : public DirectXFramework
{
public:
	void CreateSceneGraph();
	void UpdateSceneGraph();
private:
	float _rotationAngle = 0 ;
	float _armSwingAngle = 0;
	bool _isGoingUp = true;


};

