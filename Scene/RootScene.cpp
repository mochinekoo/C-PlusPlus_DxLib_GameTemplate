#include <DxLib.h>
#include "BaseScene.h"
#include "RootScene.h"

RootScene::RootScene()
	: BaseScene("RootScene") {
	sceneCounter_ = 0;
}

RootScene::~RootScene() {
}

void RootScene::Init() {
}

void RootScene::Update() {
	sceneCounter_++;
}

void RootScene::Draw() {
#ifdef _DEBUG //デバック用（※消しても問題なし）
	DrawFormatString(10, 10, GetColor(255, 0, 0), "%s: %d", name_.c_str(), sceneCounter_);
#endif 
}

void RootScene::Release() {
}
