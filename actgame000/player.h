//==============================================================
//
//プレイヤーのモデル処理[player.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _PLAYER_H_		//このマクロ定義がされていなかったら
#define _PLAYER_H_		//2重インクルード防止のマクロを定義する

#include "object.h"

class CModelHier;	//モデルの階層構造
class CMotion;		//モーションの階層構造

//プレイヤークラスの定義
class CPlayer : public CObject
{
public:

	CPlayer();		//コンストラクタ
	CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//コンストラクタ(オーバーロード)
	~CPlayer();		//デストラクタ

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//生成処理

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Hit(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//位置設定
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		//向き設定
	void SetState(STATE state) { m_state = state; }			//状態設定

	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//位置取得
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//向き取得
	D3DXVECTOR3 GetMove(void) { return m_move; }			//移動量取得
	bool GetIsJump(void) { return m_bJump; }				//ジャンプの取得
	bool GetIsMove(void) { return m_bMove; }				//移動の取得
	bool GetIsDash(void) { return m_bDash; }				//ダッシュの取得
	bool GetIsLand(void) { return m_bLand; }				//着地の取得

	D3DXVECTOR3 GetSizeMin(void) { return m_min; }			//大きさの最大値取得
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }			//大きさの最小値取得

private:
	//プレイヤーのパーツ
	enum PARTS
	{
		PARTS_BODY = 0,		//[0]体
		PARTS_HEAD,			//[1]頭
		PARTS_HAIR,			//[2]髪
		PARTS_LU_ARM,		//[3]左腕上
		PARTS_LD_ARM,		//[4]左腕下
		PARTS_L_HAND,		//[5]左手
		PARTS_RU_ARM,		//[6]右腕上
		PARTS_RD_ARM,		//[7]右腕下
		PARTS_R_HAND,		//[8]右手
		PARTS_WAIST,		//[9]腰
		PARTS_LU_LEG,		//[10]左太もも
		PARTS_LD_LEG,		//[11]左ふくらはぎ
		PARTS_L_SHOE,		//[12]左靴
		PARTS_RU_LEG,		//[13]右太もも
		PARTS_RD_LEG,		//[14]右ふくらはぎ
		PARTS_R_SHOE,		//[15]右靴
		PARTS_MAX
	};

	void UpdateFront(void);			//手前側の更新処理
	void UpdateState(void);			//状態の更新処理

	void MotionManager(void);				//モーション管理
	void ControlFrontKeyboard(void);		//プレイヤーキーボード操作(手前側)
	void ControlFrontKeyboardMove(void);	//プレイヤーキーボードの移動操作(手前側)
	void ControlFrontKeyboardJump(void);	//プレイヤーキーボードのジャンプ操作(手前側)
	void ControlFrontKeyboardDash(void);	//プレイヤーキーボードのダッシュ操作(手前側)

	void ControlHumanPad(void);				//プレイヤーコントローラー操作(人間)
	void Screen(void);						//画面外判定
	void LoadFile(void);					//モデルファイル読み込み
	void RotCorrection(void);				//向きの補正処理

	static char *m_apFileName[PARTS_MAX];		//ファイル名

	D3DXVECTOR3 m_pos;		//位置
	D3DXVECTOR3 m_posOld;	//前回の位置
	D3DXVECTOR3 m_posSave;		//復活用の位置
	D3DXVECTOR3 m_posKeepHuman;	//人間の位置保存用
	D3DXVECTOR3 m_posKeepFish;	//金魚の位置保存用
	D3DXVECTOR3 m_move;		//移動量
	D3DXVECTOR3 m_rot;		//向き
	D3DXVECTOR3 m_max;		//人間の最大値
	D3DXVECTOR3 m_min;		//人間の最小値
	D3DXMATRIX m_mtxWorld;	//ワールドマトリックス
	CModelHier *m_apModel[PARTS_MAX];		//モデル(パーツ)へのポインタ
	int m_nNumModel;		//モデル(パーツ)の総数
	int m_nCntDamage;		//ダメージカウンター

	bool m_bMove;			//歩いてるかの判定
	bool m_bJump;			//ジャンプしたかの判定
	bool m_bLand;			//着地したか
	bool m_bDash;			//ダッシュしたか

	float m_fRotDest;		//目標
	float m_fRotDiff;		//差分

	STATE m_state;			//プレイヤーの状態

	int m_nDashCounter;		//ダッシュした回数

	//int m_particleType;		//パーティクルの種類
	int m_nType;			//何番目のパーティクルか
	int m_nParticleLife;	//パーティクルの寿命
	int m_nCntHit;			//ヒットできるまでのカウンター
	int m_nCntMove;			//足音のカウンター
	int m_nCntSand;			//砂のパーティクルカウンター

	bool m_bPad;			//パッドのスティックを倒してるか

	CMotion *m_pMotion;		//モーション情報
};

#endif
