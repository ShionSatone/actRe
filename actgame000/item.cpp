//==============================================================
//
//アイテム処理[item.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "item.h"
#include "game.h"
#include "model.h"
#include "material.h"
#include "player.h"
#include "sound.h"
#include "score.h"

//静的メンバ変数宣言
LPD3DXMESH CItem::m_pMesh = NULL;						//メッシュ（頂点情報）へのポインタ
LPD3DXBUFFER CItem::m_pBuffMat = NULL;					//マテリアルへのポインタ
DWORD CItem::m_dwNumMat = NULL;
const char *CItem::m_pFilename[TYPE_MAX] = 			//ファイルの名前
{
	NULL,
	"data\\MODEL\\item_rhombus.x",		//ひし形
	"data\\MODEL\\item_star.x",			//星
};

//==============================================================
//コンストラクタ
//==============================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//向き
	m_type = TYPEITEM_NONE;	//種類
	m_nIdx = -1;				//モデルの番号
}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	m_pos = pos;		//位置
	m_rot = rot;		//向き
	m_type = type;		//種類
	m_nIdx = -1;		//モデルの番号
}

//==============================================================
//デストラクタ
//==============================================================
CItem::~CItem()
{

}

//==============================================================
//アイテムの生成処理
//==============================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	CItem *pItemModel = NULL;

	if (pItemModel == NULL)
	{//メモリが使用されてなかったら

		//アイテムの生成
		pItemModel = new CItem(pos, rot, type);
	}

	//初期化処理
	pItemModel->Init();

	return pItemModel;
}

//==============================================================
//アイテムの初期化処理
//==============================================================
HRESULT CItem::Init(void)
{
	CMaterial *pMaterial = CManager::GetInstance()->GetMaterial();

	//モデルの読み込み
	m_nIdx = pMaterial->Regist(m_pFilename[m_type]);

	//マテリアルの割り当て
	CObjectX::BindMaterial(m_nIdx);

	//オブジェクトXの初期化処理
	CObjectX::Init();

	//位置の設定
	CObjectX::SetPosition(m_pos);

	//種類の設定
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//アイテムの終了処理
//==============================================================
void CItem::Uninit(void)
{
	//オブジェクトXの終了処理
	CObjectX::Uninit();
}

//==============================================================
//アイテムの更新処理
//==============================================================
void CItem::Update(void)
{
	//オブジェクトXの更新処理
	CObjectX::Update();
}

//==============================================================
//アイテムの描画処理
//==============================================================
void CItem::Draw(void)
{
	//オブジェクトXの描画処理
	CObjectX::Draw();
}

//==============================================================
//アイテムのヒット処理
//==============================================================
void CItem::Hit(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	CSound *pSound = CManager::GetInstance()->GetSound();
	CScore *pScore = CGame::GetScore();

	if (m_type == TYPEITEM_RHOMBUS)
	{//ひし形アイテムのとき

		pPlayer->SetDash(0);		//ダッシュ回数リセット

		//	//SE再生
		//	pSound->Play(pSound->SOUND_LABEL_SE_ITEM000);
	}
	else if (m_type == TYPEITEM_STAR)
	{//星アイテムのとき

		//SE再生
		//pSound->Play(pSound->SOUND_LABEL_SE_ITEM000);

		//スコア加算
		//pScore->Add(1050);

	}

	
	//終了処理
	CItem::Uninit();
}