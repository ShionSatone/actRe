//==============================================================
//
//ゲーム処理[game.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "game.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
//#include "ranking.h"
//#include "pause.h"
#include "fade.h"
#include "sound.h"

//静的メンバ変数宣言
//CEdit *CGame::m_pEdit = NULL;				//エディットの情報
CPlayer *CGame::m_pPlayer = NULL;		//プレイヤーの情報
bool CGame::m_bReset = true;					//リセットしたかどうか
bool CGame::m_bPause = false;					//ポーズ画面か
//CPause *CGame::m_pPause = NULL;				//ポーズ画面の情報
CGame::GAMEMODE CGame::m_gameMode = GAMEMODE_GAME;	//ゲームモード

//==============================================================
//コンストラクタ
//==============================================================
CGame::CGame()
{
	m_nCntEnemy = 0;				//敵出現カウント
}

//==============================================================
//デストラクタ
//==============================================================
CGame::~CGame()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CGame::Init(void)
{
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	CSound *pSound = CManager::GetSound();

	m_bReset = true;		//リセットしてる状態にする
	m_bPause = false;		//ポーズしてない

	//カメラの初期化処理
	pCamera->Init();

	//壁の生成
	CWall::Create(D3DXVECTOR3(0.0f, 0.0f, 1000.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), 0);

	//プレイヤーの生成
	m_pPlayer = m_pPlayer->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//敵の生成
	CEnemy::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エディットの生成
	//m_pEdit = CEdit::Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f),

	//スコアの生成
	//m_pScore = CScore::Create();

	//ポーズ画面の生成
	//m_pPause = CPause::Create();

	//BGM再生
	//pSound->Play(pSound->SOUND_LABEL_BGM002);

	CObject::SetType(CObject::TYPE_SCENE);

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetSound();

	//BGMの停止
	pSound->Stop();

	//プレイヤーの破棄
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	//ポーズの破棄
	/*if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}*/

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetFade();			//フェードの情報取得

	if (pInputKeyboard->GetTrigger(DIK_P) == true || 
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_START, 0) == true)
	{//Pキーを押したら

		m_bPause = m_bPause ? false : true;		//ポーズ切り替え
	}

	if (m_bPause == true)
	{//ポーズしてるとき

		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true)
		{
			m_bPause = false;
		}
	}
	else
	{
		//if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
		//	pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		//{//ENTERキー押したら

		//	//ゲーム画面
		//	pFade->SetFade(CScene::MODE_GAME);

		//	//bReset = true;
		//}
		/*else
		{
		bReset = false;
		}*/
	}
}

//==============================================================
//描画処理
//==============================================================
void CGame::Draw(void)
{

}

//==============================================================
//ポーズ画面の設定処理
//==============================================================
void CGame::SetEnablePause(bool bPouse)
{
	m_bPause = bPouse;
}