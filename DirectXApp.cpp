#include "DirectXApp.h"
#include "CubeNode.h"
#include "TextureCubeNode.h"
#include "TeapotNode.h"
#include "ResourceManager.h"
#include "MeshNode.h"

DirectXApp app; 

void DirectXApp::CreateSceneGraph()
{

	SceneGraphPointer sceneGraph = GetSceneGraph();
	shared_ptr<ResourceManager> manager = GetResourceManager();
	shared_ptr<Mesh> _mesh = manager->GetMesh(L"airplane.x");
	// Plane
	SceneGraphPointer planeSceneGraph = make_shared<SceneGraph>(L"Plane");
	sceneGraph->Add(planeSceneGraph);
	shared_ptr<MeshNode> plane = make_shared<MeshNode>(L"Plane", Vector4(0.2f, 0.2f, 0.2f, 1.0f), _mesh);
	plane->SetWorldTransform( Matrix::CreateScale(Vector3(4.0f, 4.0f, 4.0f)) * Matrix::CreateTranslation(Vector3(3.0f, 45.0f, -5.0f)));
	planeSceneGraph->Add(plane);

	SetBackgroundColour(Vector4(0.392156889f, 0.584313750f, 0.929411829f, 1.0f));


	// Teapot
	SceneGraphPointer teapotSceneGraph = make_shared<SceneGraph>(L"Teapot");
	sceneGraph->Add(teapotSceneGraph);
	shared_ptr<TeapotNode> teapot = make_shared<TeapotNode>(L"Teapot", Vector4(0.0f, 0.0f, 1.0f, 1.0f));
	teapot->SetWorldTransform(Matrix::CreateScale(Vector3(8.0f, 8.0f, 8.0f)) );
	teapotSceneGraph->Add(teapot);

	// Robot
	SceneGraphPointer bodySceneGraph = make_shared<SceneGraph>(L"Body");
	sceneGraph->Add(bodySceneGraph);

	// Body, left and right led
	shared_ptr<TextureCubeNode> textcube = make_shared<TextureCubeNode>(L"Body", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	textcube->SetWorldTransform(Matrix::CreateScale(Vector3(5.0f, 8.0f, 2.5f))* Matrix::CreateTranslation(Vector3(0, 23.0f, 0)) );
	bodySceneGraph->Add(textcube);
	textcube = make_shared<TextureCubeNode>(L"LeftLeg", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	textcube->SetWorldTransform(Matrix::CreateScale(Vector3(1.0, 7.5, 1.0)) * Matrix::CreateTranslation(Vector3(-4.0f, 7.5, 0)));
	bodySceneGraph->Add(textcube);
	textcube = make_shared<TextureCubeNode>(L"RightLeg", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	textcube->SetWorldTransform(Matrix::CreateScale(Vector3(1.0, 7.5, 1.0)) * Matrix::CreateTranslation(Vector3(4.0f, 7.5, 0)));
	bodySceneGraph->Add(textcube);

	// Head
	shared_ptr<CubeNode> cube = make_shared<CubeNode>(L"Head", Vector4(0.8f, 0.6f, 0.4f, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(3.0f, 3.0f, 3.0f)) * Matrix::CreateTranslation(Vector3(0, 34, 0)));
	bodySceneGraph->Add(cube);

	// Left shoulder and left arm 
	SceneGraphPointer shoulderSceneGraph = make_shared<SceneGraph>(L"LeftShoulder");
	bodySceneGraph->Add(shoulderSceneGraph);
	cube = make_shared<CubeNode>(L"Leftshoulder", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(0.5f, 0.5f, 0.5f)));
	shoulderSceneGraph->Add(cube);
	textcube = make_shared<TextureCubeNode>(L"LeftArm", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	shoulderSceneGraph->Add(textcube);
	
	// Right shoulder and right arm
	SceneGraphPointer rshoulderSceneGraph = make_shared<SceneGraph>(L"RightShoulder");
	bodySceneGraph->Add(rshoulderSceneGraph);
	cube = make_shared<CubeNode>(L"Rightshoulder", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	cube->SetWorldTransform(Matrix::CreateScale(Vector3(0.5f, 0.5f, 0.5f)));
	rshoulderSceneGraph->Add(cube);
	textcube = make_shared<TextureCubeNode>(L"RightArm", Vector4(0.2f, 0.2f, 0.2f, 1.0f));
	rshoulderSceneGraph->Add(textcube);
	
	_rotationAngle = 0;
	_armSwingAngle = 0.0f;
	
}


void DirectXApp::UpdateSceneGraph()
{


	SceneGraphPointer sceneGraph = GetSceneGraph();
	SceneNodePointer plane = sceneGraph->Find(L"Plane");
	plane->SetWorldTransform(Matrix::CreateRotationY(-_rotationAngle * XM_PI / 200.0f));

	SceneNodePointer body = sceneGraph->Find(L"Body");

	_rotationAngle += 0.5f;
	_armSwingAngle += 0.02f;

	// Apply rotation to the entire robot	
	body->SetWorldTransform(Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f));

	
	//SceneNodePointer body = sceneGraph->Find(L"Body");

	
	_rotationAngle += 0.5f;
	_armSwingAngle += 0.02f;

	// Apply rotation to the entire robot	
//	body->SetWorldTransform(Matrix::CreateRotationY(_rotationAngle * XM_PI / 180.0f));

	// Find and update the left shoulder node
	SceneNodePointer ShoulderNode = sceneGraph->Find(L"LeftShoulder");
	if (ShoulderNode) {
		
		ShoulderNode->SetWorldTransform(Matrix::CreateRotationX(_rotationAngle * XM_PI / 180.0f) * Matrix::CreateTranslation(Vector3(-6, 27, 0)));

	}

	// Find and update the right shoulder node
	SceneNodePointer rShoulderNode = sceneGraph->Find(L"RightShoulder");
	if (rShoulderNode) {

		rShoulderNode->SetWorldTransform(Matrix::CreateRotationX(-_rotationAngle * XM_PI / 180.0f) * Matrix::CreateTranslation(Vector3(6, 27, 0)));

	}

	// Find and update the left arm node
	SceneNodePointer armNode = sceneGraph->Find(L"LeftArm");
	if (armNode) {

		armNode->SetWorldTransform( Matrix::CreateScale(Vector3(1, 8.5f, 1)) * Matrix::CreateTranslation(Vector3(0, 8, 0)));

	}
	// Find and update the right arm node
	SceneNodePointer rarmNode = sceneGraph->Find(L"RightArm");
	if (rarmNode) {

		rarmNode->SetWorldTransform(Matrix::CreateScale(Vector3(1, 8.5f, 1)) * Matrix::CreateTranslation(Vector3(0, 8, 0)));

	}
	// Find and update the Teapot
	SceneNodePointer teapot = sceneGraph->Find(L"Teapot");
	if (teapot) {
		teapot->SetWorldTransform(Matrix::CreateRotationY(-_rotationAngle * XM_PI / 180.0f) * Matrix::CreateTranslation(Vector3(-30, 25.0f, 0)));
	}
	
	
}


	

