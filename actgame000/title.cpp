//==============================================================
//
//タイトル処理[title.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "title.h"
#include "manager.h"
#include "wall.h"
#include "input.h"
#include "camera.h"
#include "sound.h"
#include "fade.h"
#include "texture.h"
#include "ranking.h"

#include "bg.h"

//マクロ定義
#define TRANS_TIME		(60 * 10)			//遷移するまでの時間

//静的メンバ変数宣言
CEdit *CTitle::m_pEdit = NULL;				//エディットの情報
bool CTitle::bReset = true;				//リセットしたかどうか

//==============================================================
//コンストラクタ
//==============================================================
CTitle::CTitle()
{
	for (int nCntTex = 0; nCntTex < NUM_TITLE_TEX; nCntTex++)
	{
		m_nIdxTexture[nCntTex] = -1;		//テクスチャ番号
	}

	m_nCntTrans = 0;				//遷移するまでの時間
}

//==============================================================
//デストラクタ
//==============================================================
CTitle::~CTitle()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CTitle::Init(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得
	CSound *pSound = CManager::GetInstance()->GetSound();
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//カメラの初期化処理
	pCamera->Init();

	CBg::Create();
	
	if (CManager::GetInstance()->GetBgm() == false)
	{

		//BGM再生
		//pSound->Play(pSound->SOUND_LABEL_BGM000);
	}

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CTitle::Uninit(void)
{
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CTitle::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CFade *pFade = CManager::GetInstance()->GetFade();		//フェードの情報取得

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//ENTERキー押したら

		//ゲーム画面
		pFade->SetFade(CScene::MODE_GAME);
	}

	//if (m_nCntTrans >= TRANS_TIME)
	//{//遷移する時間になったら

	//	CManager::GetInstance()->SetBgm(true);
	//	pFade->SetFade(CScene::MODE_RANKING);

	//	CRanking *pRanking = CScene::GetRanking();		//ランキングの情報取得
	//	pRanking->SetSound(true);
	//}

	//m_nCntTrans++;
}

//==============================================================
//描画処理
//==============================================================
void CTitle::Draw(void)
{
	
}