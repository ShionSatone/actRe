//==============================================================
//
//チュートリアル画像の処理[tutorial_texture.cpp]
//Author:佐藤根詩音
//
//==============================================================
#include "tutorial_texture.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//マクロ定義
#define WIDTH_UI			(380.0f * 0.5f)		//壁の横幅
#define HEIGHT_UI			(150.0f * 0.5f)		//壁の縦幅
#define COL_R				(1.0f)		//赤色の数値
#define COL_G				(1.0f)		//緑色の数値
#define COL_B				(1.0f)		//青色の数値
#define COL_A				(1.0f)		//不透明度の数値
#define TEX_LEFT_X			(0.0f)		//テクスチャの左xの初期値
#define TEX_RIGHT_X			(1.0f)		//テクスチャの右xの初期値
#define TEX_UP_Y			(0.0f)		//テクスチャの上yの初期値
#define TEX_DOWN_Y			(1.0f)		//テクスチャの下yの初期値

//静的メンバ変数宣言
LPDIRECT3DTEXTURE9 CTutorialUI::m_pTexture = NULL;
const char *CTutorialUI::m_apFilename[STEP_MAX] =
{
	"data\\TEXTURE\\tutorial000.png",		//移動
	"data\\TEXTURE\\tutorial001.png",		//ジャンプ
	"data\\TEXTURE\\tutorial002.png",		//ダッシュ
	"data\\TEXTURE\\tutorial003.png",		//通り抜け
	"data\\TEXTURE\\tutorial004.png",		//アイテム
	"data\\TEXTURE\\tutorial005.png",		//敵
};

//==============================================================
//コンストラクタ
//==============================================================
CTutorialUI::CTutorialUI()
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//位置
	m_nType = 0;
}

//==============================================================
//コンストラクタ
//==============================================================
CTutorialUI::CTutorialUI(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	m_nIdxTexture = -1;		//テクスチャの番号
	m_pos = pos;		//位置
	m_nType = nType;	//壁の種類

}

//==============================================================
//デストラクタ
//==============================================================
CTutorialUI::~CTutorialUI()
{

}

//==============================================================
//壁の生成処理
//==============================================================
CTutorialUI *CTutorialUI::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType)
{
	CTutorialUI *pWall = NULL;

	if (pWall == NULL)
	{//メモリが使用されてなかったら

		//壁の生成
		pWall = new CTutorialUI(pos, rot, nType);
	}

	//初期化処理
	pWall->Init();

	return pWall;
}

//==============================================================
//壁の初期化処理
//==============================================================
HRESULT CTutorialUI::Init(void)
{
	CTexture *pTexture = CManager::GetInstance()->GetTexture();

	//テクスチャの読み込み
	m_nIdxTexture = pTexture->Regist(m_apFilename[m_nType]);

	//テクスチャの割り当て
	CObject3D::BindTexture(m_nIdxTexture);

	//ビルボードの初期化処理
	CObject3D::Init();

	//種類の設定
	CObject::SetType(CObject::TYPE_WALL);

	//位置の設定
	CObject3D::SetPosition(m_pos);

	//壁の大きさ設定
	CObject3D::SetSize(WIDTH_UI, HEIGHT_UI);

	return S_OK;
}

//==============================================================
//壁の終了処理
//==============================================================
void CTutorialUI::UnInit(void)
{
	//オブジェクト3Dの終了処理
	CObject3D::Uninit();
}

//==============================================================
//壁の更新処理
//==============================================================
void CTutorialUI::Update(void)
{

}

//==============================================================
//壁の描画処理
//==============================================================
void CTutorialUI::Draw(void)
{
	//オブジェクト3Dの描画処理
	CObject3D::Draw();
}