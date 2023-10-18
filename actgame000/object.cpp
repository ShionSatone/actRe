//==============================================================
//
//オブジェクト処理[object.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"
#include "manager.h"
#include "debugproc.h"
//#include "game.h"

//静的メンバ変数の宣言
//CObject *CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;		//全てのオブジェクトの総数
CObject *CObject::m_apTop[NUM_PRIORITY] = {};		//先頭のオブジェクトへのポインタ
CObject *CObject::m_apCur[NUM_PRIORITY] = {};		//最後尾のオブジェクトへのポインタ

//==============================================================
//コンストラクタ
//==============================================================
CObject::CObject()
{
	m_pPrev = NULL;		//前のオブジェクトへのポインタ
	m_pNext = NULL;		//次のオブジェクトへのポインタ
	m_bDeath = false;	//死亡しない状態にする
	m_nPriority = DEFAULT_PRIORITY;		//デフォルト優先順位

	//オブジェクト(自分)をリストに追加
	m_pPrev = m_apCur[m_nPriority];		//前のオブジェクト代入
	m_apCur[m_nPriority] = this;		//最後尾に自分自身を代入
	m_nNumAll++;						//オブジェクトの総数加算

	if (m_apTop[m_nPriority] == NULL)
	{//先頭がいなかったら

		m_apTop[m_nPriority] = this;		//先頭に自分自身を代入
	}
	else
	{
		m_pPrev->m_pNext = m_apCur[m_nPriority];
	}
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
//CObject::CObject(TYPE type)
//{
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObject[nCntObject] == NULL)
//		{//メモリが使用されてなかったら
//
//			m_apObject[nCntObject] = this;		//自分自身を代入
//			m_nID = nCntObject;		//自分自身のIDを保存
//			m_type = type;			//オブジェクトの種類を設定
//			m_nNumAll++;			//総数をカウントアップ
//
//			break;
//		}
//	}
//}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CObject::CObject(int nPriority)
{
	m_pPrev = NULL;		//前のオブジェクトへのポインタ
	m_pNext = NULL;		//次のオブジェクトへのポインタ
	m_bDeath = false;	//死亡しない状態にする
	m_nPriority = nPriority;		//優先順位

	//オブジェクト(自分)をリストに追加
	m_pPrev = m_apCur[m_nPriority];		//前のオブジェクト代入
	m_apCur[m_nPriority] = this;		//最後尾に自分自身を代入
	m_nNumAll++;						//オブジェクトの総数加算

	if (m_apTop[m_nPriority] == NULL)
	{//先頭がいなかったら

		m_apTop[m_nPriority] = this;	//先頭に自分自身を代入
	}
	else
	{
		m_pPrev->m_pNext = m_apCur[m_nPriority];
	}
}

//==============================================================
//デストラクタ
//==============================================================
CObject::~CObject()
{

}

//==============================================================
//全てのオブジェクトの破棄
//==============================================================
void CObject::ReleaseAll(void)
{
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入

		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			//終了処理
			pObject->Uninit();

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入

		//死亡フラグをチェックしてオブジェクトをリストから削除して破棄する
		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			if (pObject->m_bDeath == true)
			{//死亡フラグが立っているとき

					//オブジェクト(自分)をリストから削除
				if (m_apTop[nCntPri] == pObject)
				{//先頭だったら

					m_apTop[nCntPri] = pObjectNext;		//先頭変更
				}
				else if (m_apCur[nCntPri] == pObject)
				{//最後尾だったら

					m_apCur[nCntPri] = pObject->m_pPrev;		//最後尾変更
					pObject->m_pPrev->m_pNext = NULL;
				}
				else
				{
					pObjectNext->m_pPrev = pObject->m_pPrev;
					pObject->m_pPrev->m_pNext = pObjectNext;
				}

				//オブジェクト(自分)を破棄
				delete pObject;

				m_nNumAll--;		//総数をカウントダウン
			}

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}
}

//==============================================================
//全てのオブジェクトの更新処理
//==============================================================
void CObject::UpdateAll(void)
{
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入
		//CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();		//デバッグ表示の情報取得
		//CGame *pGame = CGame::GetGame();

		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			if (pObject->m_bDeath == false)
			{//死亡フラグが立ってないとき

				//if (pGame->GetPauseDisp() == true)
				//{//ポーズ画面のとき

				//	if (pObject->GetType() == TYPE_PAUSE || pObject->GetType() == TYPE_SCENE || pObject->GetType() == TYPE_FADE)
				//	{
				//		//更新処理
				//		pObject->Update();
				//	}
				//}
				//else if (pGame->GetPauseDisp() == false)
				{//ポーズ画面じゃないとき

					if (pObject->GetType() != TYPE_PAUSE)
					{
						//更新処理
						pObject->Update();
					}
				}
			}

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入

		//死亡フラグをチェックしてオブジェクトをリストから削除して破棄する
		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			if (pObject->m_bDeath == true)
			{//死亡フラグが立っているとき

				//オブジェクト(自分)をリストから削除
				if (m_apTop[nCntPri] == pObject)
				{//先頭だったら

					m_apTop[nCntPri] = pObjectNext;		//先頭変更
				}
				else if (m_apCur[nCntPri] == pObject)
				{//最後尾だったら

					m_apCur[nCntPri] = pObject->m_pPrev;		//最後尾変更
					pObject->m_pPrev->m_pNext = NULL;
				}
				else
				{
					pObjectNext->m_pPrev = pObject->m_pPrev;
					pObject->m_pPrev->m_pNext = pObjectNext;
				}

				//オブジェクト(自分)を破棄
				delete pObject;

				m_nNumAll--;		//総数をカウントダウン
			}

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}

	//pDebugProc->Print("\nオブジェクトの数[%d]\n\n", m_nNumAll);
}

//==============================================================
//全てのオブジェクトの描画処理
//==============================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();
	CObject *pObject;
	//CGame *pGame = CGame::GetGame();

	//カメラの設定
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入

		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			//if (pGame->GetPauseDisp() == true)
			{//ポーズ画面のとき

				//描画処理
				pObject->Draw();
			}
			//else if (pGame->GetPauseDisp() == false)
			//{//ポーズ画面じゃないとき

			//	if (pObject->GetType() != TYPE_PAUSE)
			//	{
			//		//描画処理
			//		pObject->Draw();
			//	}
			//}

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}
}

//==============================================================
//オブジェクトの破棄
//==============================================================
void CObject::Release(void)
{
	//死亡フラグを立てる
	m_bDeath = true;
}

//==============================================================
//オブジェクトの情報取得
//==============================================================
CObject *CObject::GetObject(int nPriority, int nIdx)
{
	CObject *pObject = m_apTop[nPriority];		//先頭のオブジェクトを代入
	int nCntIdx = 0;				//現在何番目か

	while (nCntIdx != nIdx)
	{//オブジェクトが使用されてる間

		if (pObject->m_pNext != NULL)
		{
			pObject = pObject->m_pNext;		//次のオブジェクトを代入
		}
		else
		{
			return NULL;
		}

		nCntIdx++;
	}

	return pObject;
}

//==============================================================
//終了処理
//==============================================================
void CObject::DeathAll(void)
{
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//先頭のオブジェクトを代入

		while (pObject != NULL)
		{//オブジェクトが使用されてる間

			CObject *pObjectNext = pObject->m_pNext;		//次のオブジェクトを保存

			if (pObject->m_bDeath == false)
			{//死亡フラグが立ってないとき

				//終了処理
				pObject->Uninit();
			}

			pObject = pObjectNext;		//次のオブジェクトを代入
		}
	}
}

//==============================================================
//マップのオブジェクトのリセット処理
//==============================================================
void CObject::ResetMapAll(void)
{
	//for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	//{
	//	if (m_apObject[nCntObject] != NULL)
	//	{//メモリが使用されてたら

	//		if (m_apObject[nCntObject]->m_type != TYPE_PLAYER &&
	//			m_apObject[nCntObject]->m_type != TYPE_NONE)
	//		{
	//			//終了処理
	//			m_apObject[nCntObject]->Uninit();
	//		}
	//	}
	//}
}