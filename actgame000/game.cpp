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
#include "edit.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "item.h"
//#include "ranking.h"
#include "pause.h"
#include "fade.h"
#include "score.h"
#include "sound.h"

//静的メンバ変数宣言
CEdit *CGame::m_pEdit = NULL;				//エディットの情報
CPlayer *CGame::m_pPlayer = NULL;			//プレイヤーの情報
bool CGame::m_bReset = true;				//リセットしたかどうか
bool CGame::m_bPause = false;				//ポーズ画面か
CPause *CGame::m_pPause = NULL;			//ポーズ画面の情報
CScore *CGame::m_pScore = NULL;				//スコアの情報
bool CGame::m_bEnemySpawn = false;			//スタートしたか
CGame::GAMEMODE CGame::m_gameMode = GAMEMODE_START;	//ゲームモード

//==============================================================
//コンストラクタ
//==============================================================
CGame::CGame()
{
	m_nCntEnemy = 0;				//敵出現カウント

	m_bEnemySpawn = false;			//敵出現したか
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
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	m_bReset = true;		//リセットしてる状態にする
	m_bPause = false;		//ポーズしてない

	//カメラの初期化処理
	pCamera->Init();

	//プレイヤーの生成
	m_pPlayer = m_pPlayer->Create(D3DXVECTOR3(1080.0f, -150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//エディットの生成
	m_pEdit = CEdit::Create();

	//ひし形アイテム
	CItem::Create(D3DXVECTOR3(600.0f, -1400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(1150.0f, -1550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(450.0f, -2450.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(750.0f, -3050.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(300.0f, -3200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);

	//星アイテム
	CItem::Create(D3DXVECTOR3(150.0f, -350.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(300.0f, -1000.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(1200.0f, -1400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(350.0f, -2650.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(150.0f, -2850.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(150.0f, -4050.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(1250.0f, -4150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(150.0f, -4750.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(1250.0f, -5100.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(150.0f, -5050.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);
	CItem::Create(D3DXVECTOR3(200.0f, -5550.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);

	//スコアの生成
	m_pScore = CScore::Create();

	//ポーズ画面の生成
	m_pPause = CPause::Create();

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
	CSound *pSound = CManager::GetInstance()->GetSound();

	//BGMの停止
	pSound->Stop();

	//プレイヤーの破棄
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	//エディターの破棄
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//ポーズの破棄
	if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInstance()->GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetInstance()->GetFade();			//フェードの情報取得

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
	else if(m_bPause == false)
	{//ポーズしてないとき

		//敵出現させる
		CGame::SetEnemy();

		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTERキー押したら

			//ゲーム画面
			pFade->SetFade(CScene::MODE_RESULT);
		}
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

//==============================================================
//敵出現処理
//==============================================================
void CGame::SetEnemy(void)
{
	D3DXVECTOR3 posPlayer = m_pPlayer->GetPosition();		//プレイヤーの位置取得
	int nNumSavePoint = m_pPlayer->GetNumSavePoint();		//何番目のセーブポイントか取得

	if (nNumSavePoint == 1 && m_bEnemySpawn == false)
	{//最初のセーブポイントに来たら

		//敵の生成
		CEnemy::Create(D3DXVECTOR3(1080.0f, -150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

		m_bEnemySpawn = true;		//敵出現した状態にする
	}
}