#include <DxLib.h>
#include "BaseScene.h"
#include "RootScene.h"
#include <array>

namespace {
	std::array< VERTEX2DSHADER, 4 >	vertex;
	std::array< unsigned short, 6 >	vertexIndex;
}

RootScene::RootScene()
	: BaseScene("RootScene") {
	sceneCounter_ = 0;
	hShader_ = -1;
}

RootScene::~RootScene() {
}

void RootScene::Init() {
	hShader_ = LoadPixelShader("../../../Shader/TestPixelShader.pso");
	hImage_ = LoadGraph("../../../Shader/TestTexture.png");

	auto Settings = [](VERTEX2DSHADER& vtx, float x, float y, float u, float v)
		{
			vtx.pos = VGet(x, y, 0.0f);
			vtx.u = u;
			vtx.v = v;
			vtx.su = u;
			vtx.sv = v;
			vtx.rhw = 1.0f;
			vtx.dif = GetColorU8(255, 255, 255, 255);
			vtx.spc = GetColorU8(0, 0, 0, 0);
		};

	Settings(vertex[0], 100.0f, 100.0f, 0.0f, 0.0f);
	Settings(vertex[1], 600.0f, 100.0f, 1.0f, 0.0f);
	Settings(vertex[2], 100.0f, 600.0f, 0.0f, 1.0f);
	Settings(vertex[3], 600.0f, 600.0f, 1.0f, 1.0f);

	vertexIndex = { 0, 1, 2, 1, 2, 3 };
	SetUseTextureToShader(0, hImage_);
	SetUsePixelShader(hShader_);
}

void RootScene::Update() {
	sceneCounter_++;
}

void RootScene::Draw() {
#ifdef _DEBUG //デバック用（※消しても問題なし）
	static int result = 0;
	SetTextureAddressMode(DX_TEXADDRESS_CLAMP);
	result = DrawPolygonIndexed2DToShader(vertex.data(), 4, vertexIndex.data(), 2);
#endif 
}

void RootScene::Release() {
}
