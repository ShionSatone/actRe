//==============================================================
//
//オブジェクト処理[object.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _OBJECT_H_		//このマクロ定義がされていなかったら
#define _OBJECT_H_		//2重インクルード防止のマクロを定義する

#include "main.h"

//マクロ定義
#define MAX_OBJECT			(1280)		//オブジェクトの数
#define DEFAULT_PRIORITY	(3)			//優先順位のデフォルト値
#define NUM_PRIORITY		(8)			//優先順位の総数

//オブジェクトクラス
class CObject
{
public:

	//オブジェクトの種類
	enum TYPE
	{
		TYPE_NONE = 0,		//何もなし
		TYPE_PLAYER,		//プレイヤー
		TYPE_ENEMY,			//敵
		TYPE_BULLET,		//弾
		TYPE_EXPLOSION,		//爆発
		TYPE_EFFECT,		//エフェクト
		TYPE_PARTICLE,		//パーティクル
		TYPE_SCORE,			//スコア
		TYPE_BLOCK,			//ブロック
		TYPE_ITEM,			//アイテム
		TYPE_FIELD,			//床
		TYPE_WALL,			//壁
		TYPE_MODEL,			//モデル
		TYPE_ALPHA_BLOCK,	//透明ブロック
		TYPE_PAUSE,			//ポーズ
		TYPE_SCENE,			//シーン
		TYPE_FADE,			//フェード
		TYPE_MAX			//種類の最大数
	};

	//パーティクルの種類
	//typedef enum
	//{
	//	PARTICLETYPE_NONE = 0,		//何もなし
	//	PARTICLETYPE_WATER,			//水
	//	PARTICLETYPE_ICE,			//氷
	//	PARTICLETYPE_VAPOR,			//蒸気
	//	PARTICLETYPE_ENEMY,			//敵の弾
	//	PARTICLETYPE_WITCH,			//魔女の弾
	//	PARTICLETYPE_EXPLOSION,		//爆発
	//	PARTICLETYPE_LAND,			//着地
	//	PARTICLETYPE_LIFE,			//回復
	//	PARTICLETYPE_JUMP,			//ジャンプ
	//	PARTICLETYPE_MOVE,			//移動
	//	PARTICLETYPE_MAX
	//} PARTICLETYPE;

	//オブジェクトの状態
	enum STATE
	{
		STATE_NONE = 0,		//通常状態
		STATE_ATTACK,		//攻撃状態
		STATE_DAMAGE,		//ダメージ状態
		STATE_DEATH,		//死亡状態
		STATE_APPEAR,		//点滅状態
		STATE_WAIT,			//待ち状態
		STATE_MAX
	};

	CObject();				//コンストラクタ
	//CObject(TYPE type);		//コンストラクタのオーバーロード
	CObject(int nPriority = DEFAULT_PRIORITY);		//コンストラクタのオーバーロード
	virtual ~CObject();		//デストラクタ

	static void ReleaseAll(void);		//全てのリリース処理
	static void UpdateAll(void);		//全ての更新処理
	static void DrawAll(void);			//全ての描画処理
	static void ResetMapAll(void);		//マップリセット処理
	static void DeathAll(void);			//全てに死亡フラグを立てる処理

	virtual HRESULT Init() = 0;			//初期化処理
	virtual void Uninit(void) = 0;		//終了処理
	virtual void Update(void) = 0;		//更新処理
	virtual void Draw(void) = 0;		//描画処理

	virtual void Hit(void) {};			//ヒット処理

	virtual void SetPotision(D3DXVECTOR3 pos, float fWidth, float fHeight) {}				//位置の設定処理
	virtual void SetRotation(D3DXVECTOR3 rot, float fWidth, float fHeight) {}				//向きの設定処理(2D)
	virtual void SetRotation(D3DXVECTOR3 rot) {}											//向きの設定処理(3D)

	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//位置の取得
	virtual D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//向きの取得
	virtual D3DXVECTOR3 GetSizeMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}			//大きさの最小値取得
	virtual D3DXVECTOR3 GetSizeMax(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//大きさの最大値取得

	virtual void SetState(STATE state){}					//オブジェクトの状態設定
	virtual STATE GetState(void) { return STATE_NONE; }		//オブジェクトの状態取得
	//virtual int GetItemType(void) { return PARTICLETYPE_WATER; }	//アイテムの種類取得

	void SetType(TYPE type) { m_type = type; }	//オブジェクトの種類の設定
	TYPE GetType(void) { return m_type; }		//オブジェクトの種類の取得

	static CObject *GetObject(int nPriority, int nIdx) /*{ return m_apObject[nIdx]; }*/;	//オブジェクトの情報取得
	static CObject *GetTop(int nPriority);		//先頭オブジェクトのポインタ取得

protected:
	void Release(void);		//リリース処理

private:
	//static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];
	static int m_nNumAll;	//オブジェクト総数
	int m_nID;				//自分自身のID
	int m_nPriority;		//優先順位の位置
	TYPE m_type;			//オブジェクトの種類
	STATE m_state;			//オブジェクトの状態

	static CObject *m_apTop[NUM_PRIORITY];		//先頭のオブジェクトへのポインタ
	static CObject *m_apCur[NUM_PRIORITY];		//最後尾のオブジェクトへのポインタ
	CObject *m_pPrev;			//前のオブジェクトへのポインタ
	CObject *m_pNext;			//次のオブジェクトへのポインタ
	bool m_bDeath;				//死亡フラグ
};

#endif
