//==============================================================
//
//リザルト処理[result.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "result.h"
#include "manager.h"
#include "wall.h"
#include "input.h"
#include "camera.h"
#include "fade.h"
#include "sound.h"

//静的メンバ変数宣言
bool CResult::bReset = true;					//リセットしたかどうか

//==============================================================
//コンストラクタ
//==============================================================
CResult::CResult()
{

}

//==============================================================
//デストラクタ
//==============================================================
CResult::~CResult()
{

}

//==============================================================
//初期化処理
//==============================================================
HRESULT CResult::Init(void)
{
	//CSound *pSound = CManager::GetInstance()->GetSound();

	////BGM再生
	//if (CManager::GetResult() == true)
	//{
	//	pSound->Play(pSound->SOUND_LABEL_BGM003);
	//}
	//else if (CManager::GetResult() == false)
	//{
	//	pSound->Play(pSound->SOUND_LABEL_BGM004);
	//}

	return S_OK;
}

//==============================================================
//終了処理
//==============================================================
void CResult::Uninit(void)
{
	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//更新処理
//==============================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CInputJoyPad *pInputJoyPad = CManager::GetInstance()->GetInputJoyPad();			//パッドの情報取得
	CFade *pFade = CManager::GetInstance()->GetFade();			//フェードの情報取得

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true) && bReset == false)
	{//ENTERキー押したら

		//CManager::SetBgm(false);

		//ランキング画面
		//CManager::SetMode(CScene::MODE_RANKING);
		pFade->SetFade(CScene::MODE_RANKING);
		bReset = true;
	}
	else
	{
		bReset = false;
	}

}

//==============================================================
//描画処理
//==============================================================
void CResult::Draw(void)
{

}