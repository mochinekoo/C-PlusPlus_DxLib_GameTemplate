#include "DxLib.h"
#include "framework.h"
#include <assert.h>
#include "Manager/SceneManager.h"

using namespace std;

int initDxLib();
void UpdateMainLoop();
void DrawMainLoop();

int WinMain(_In_ HINSTANCE hInstance,
            _In_opt_ HINSTANCE hPrevInstance,
            _In_ LPSTR lpCmdLine,
            _In_ int nShowCmd) {
    initDxLib(); //DxLibの初期化
    SceneManager::InitManager(); //SceneManagerの初期化

    while (ProcessMessage() == 0) { //
        ClearDrawScreen();

        UpdateMainLoop();
        DrawMainLoop();

        ScreenFlip();
        WaitTimer(1000 / GameScreen::FPS);
    }
    DxLib_End();

    return 0;
}

void UpdateMainLoop() {
    BaseScene* currentScene = SceneManager::GetCurrentScene();
    if (currentScene != nullptr) {
        currentScene->Update();
    }
    
}

void DrawMainLoop() {
    BaseScene* currentScene = SceneManager::GetCurrentScene();
    if (currentScene != nullptr) {
        currentScene->Draw();
    }
}

int initDxLib() {
    SetMainWindowText(GameScreen::TITLE); //ウインドウのタイトル
    ChangeFontType(DX_FONTTYPE_ANTIALIASING_EDGE_16X16); //アンチエイリアシング＆エッジが使えるように
    ChangeWindowMode(true); //ウインドウモードで起動する
    SetGraphMode(GameScreen::WIDTH, GameScreen::HEIGHT, GameScreen::COLORBIT); //画面の設定
    SetWindowSizeChangeEnableFlag(FALSE); //ウインドウのサイズ変更
    SetAlwaysRunFlag(true); //ウインドウがアクティブじゃなくても実行
    SetUseZBuffer3D(true); //Zバッファを使用する
    SetWriteZBuffer3D(true); //Zバッファに書き込む
    SetUseDirect3DVersion(DX_DIRECT3D_9EX); //HLSLを使用するための、DirectX
    if (DxLib_Init() == -1) {
        return -1;
    }

    SetBackgroundColor(GameScreen::BACKGROUND[0], GameScreen::BACKGROUND[1], GameScreen::BACKGROUND[2]);
    SetDrawScreen(DX_SCREEN_BACK);

    return 0;
}