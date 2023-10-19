//==============================================================
//
//敵の処理[enemy.h]
//Author:佐藤根詩音
//
//==============================================================
#include "enemy.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "modelHierarchy.h"
#include "input.h"
#include "motion.h"
#include "camera.h"
#include "debugproc.h"
#include "game.h"
#include "sound.h"
#include "fade.h"
#include "player.h"

//マクロ定義
#define PRIORITY			(3)			//優先順位
#define POS					(10.0f)		//pos初期値
#define CURVE_RL			(0.5f)		//左右の角度
#define CURVE_UP			(0.0f)		//上の角度
#define CURVE_DOWN			(1.0f)		//下の角度
#define MOVE_Y				(0.7f)		//移動量Y
#define ADD_MOVE_Y			(1.5f)		//移動量Y加算する数
#define JUMP_HEIGHT			(10.0f)		//ジャンプの高さ
#define MAX_STR				(128)		//文字の最大数
#define FRONT_MOVE			(0.6f)		//手前の時の移動量
#define FRONT_DASH_MOVE		(15.0f)		//手前のダッシュ時の移動量
#define MAX_DASH			(2)			//ダッシュの最大数
#define STOP_MOVE			(0.8f)		//止まる判定の移動量
#define FILE_ENEMY			"data\\TEXT\\motion_player.txt"		//敵モデルのテキスト

#define HIT_CNT				(60 * 2)	//攻撃当たるまでのカウント数
#define DAMAGE_CNT			(9)			//ダメージカウント数
#define APP_CNT				(100)		//点滅時間
#define STEP_CNT			(25)		//歩く音のカウンター

#define DELEY_CNT			(20)		//行動するまでのカウンター

//静的メンバ変数宣言
char *CEnemy::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\enemy\\00_body.x",
	"data\\MODEL\\enemy\\01_head.x",
	"data\\MODEL\\enemy\\02_hair.x",
	"data\\MODEL\\enemy\\03_LU_arm.x",
	"data\\MODEL\\enemy\\04_LD_arm.x",
	"data\\MODEL\\enemy\\05_L_hand.x",
	"data\\MODEL\\enemy\\06_RU_arm.x",
	"data\\MODEL\\enemy\\07_RD_arm.x",
	"data\\MODEL\\enemy\\08_R_arm.x",
	"data\\MODEL\\enemy\\09_waist.x",
	"data\\MODEL\\enemy\\10_LU_leg.x",
	"data\\MODEL\\enemy\\11_LD_leg.x",
	"data\\MODEL\\enemy\\12_L_shoe.x",
	"data\\MODEL\\enemy\\13_RU_leg.x",
	"data\\MODEL\\enemy\\14_RD_leg.x",
	"data\\MODEL\\enemy\\15_R_shoe.x",

};

//==============================================================
//コンストラクタ
//==============================================================
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//向き
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最小値

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		m_apModel[nCntEnemy] = NULL;		//敵(パーツ)へのポインタ
	}

	m_nNumModel = 0;		//敵(パーツ)の総数
	m_pMotion = NULL;

	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//位置保存用
	m_rotSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//向き保存用
	m_moveSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//移動量保存用

	m_bJump = false;		//ジャンプしたか
	m_bMoveL = false;		//左に歩いてるかの判定
	m_bMoveR = false;		//右に歩いてるかの判定
	m_bMove = false;		//歩いてるかの判定
	m_bLand = true;			//着地した
	m_bDash = false;		//ダッシュしたか

	m_bPreMoveL = false;	//左に歩く準備判定
	m_bPreMoveR = false;	//右に歩く準備の判定
	m_bPreMove = false;		//歩く準備判定
	m_bPreJump = false;		//ジャンプの準備判定
	m_bPreDash = false;		//ダッシュ準備判定
	m_bPreStopR = false;		//止まる準備判定
	m_bPreStopL = false;		//止まる準備判定

	m_fRotDest = 0.0f;		//目標
	m_fRotDiff = 0.0f;		//差分

	m_nDashCounter = 0;		//ダッシュした回数

	m_state = STATE_NONE;			//状態
	m_enemyState = ENEMYSTATE_NONE;	//止まってる状態
	m_nCntDamage = 0;				//ダメージカウンター

	m_nStateNoneCounter = 0;	//敵の停止状態変更カウンター
	m_nStateMoveRCounter = 0;	//敵の移動状態変更カウンター
	m_nStateMoveLCounter = 0;	//敵の移動状態変更カウンター
	m_nStateJumpCounter = 0;	//敵の移ジャンプ状態変更カウンター
	m_nStateLandCounter = 0;	//敵の着地状態変更カウンター
	m_nStateDashCounter = 0;	//敵のダッシュ状態変更カウンター
	m_nJumpLengthCounter = 0;	//ジャンプした時間
	m_nStateStopRCounter = 0;	//敵の停止状態変更カウンター
	m_nStateStopLCounter = 0;	//敵の停止状態変更カウンター

}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;									//位置
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//前回の位置
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//移動量
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最大値
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//モデルの最小値
	m_rot = rot;		//向き

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		m_apModel[nCntEnemy] = NULL;		//敵(パーツ)へのポインタ
	}

	m_pMotion = NULL;		//モーションの情報
	m_nNumModel = 0;		//敵(パーツ)の総数

	m_bJump = false;		//ジャンプしたか
	m_bMoveL = false;		//左に歩いてるかの判定
	m_bMoveR = false;		//右に歩いてるかの判定
	m_bMove = false;		//歩いてるかの判定
	m_bLand = true;			//着地した
	m_bDash = false;		//ダッシュしたか

	m_bPreMoveL = false;	//左に歩く準備判定
	m_bPreMoveR = false;	//右に歩く準備の判定
	m_bPreMove = false;		//歩く準備判定
	m_bPreJump = false;		//ジャンプの準備判定
	m_bPreDash = false;		//ダッシュ準備判定
	m_bPreStopR = false;		//止まる準備判定
	m_bPreStopL = false;		//止まる準備判定

	m_fRotDest = 0.0f;	//目標
	m_fRotDiff = 0.0f;	//差分

	m_nDashCounter = 0;		//ダッシュした回数
	m_state = STATE_NONE;		//状態
	m_enemyState = ENEMYSTATE_NONE;	//止まってる状態
	m_nCntDamage = 0;			//ダメージカウンター

	m_nStateNoneCounter = 0;	//敵の停止状態変更カウンター
	m_nStateMoveRCounter = 0;	//敵の移動状態変更カウンター
	m_nStateMoveLCounter = 0;	//敵の移動状態変更カウンター

	m_nStateJumpCounter = 0;	//敵の移ジャンプ状態変更カウンター
	m_nStateLandCounter = 0;	//敵の着地状態変更カウンター
	m_nStateDashCounter = 0;	//敵のダッシュ状態変更カウンター
	m_nJumpLengthCounter = 0;	//ジャンプした時間
	m_nStateStopRCounter = 0;	//敵の停止状態変更カウンター
	m_nStateStopLCounter = 0;	//敵の停止状態変更カウンター

}

//==============================================================
//デストラクタ
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//敵の生成処理
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemyModel = NULL;

	if (pEnemyModel == NULL)
	{//メモリが使用されてなかったら

		//敵の生成
		pEnemyModel = new CEnemy(pos, rot);
	}

	//初期化処理
	pEnemyModel->Init();

	return pEnemyModel;
}

//==============================================================
//敵の初期化処理
//==============================================================
HRESULT CEnemy::Init(void)
{
	m_fRotDest = m_rot.y;

	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モーションの初期化・生成
	m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//モデルのファイル読み込み
	CEnemy::LoadFile();

	//最大値・最小値代入
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//最大値Y
		if ((nCntPlayer <= PARTS_HEAD) || (nCntPlayer >= PARTS_WAIST && nCntPlayer <= PARTS_L_SHOE))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//最小値Z

		}
	}

	m_max.y += 40.0f;

	CObject::SetType(CObject::TYPE_ENEMY);

	return S_OK;
}

//==============================================================
//敵の終了処理
//==============================================================
void CEnemy::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//使用されてるとき

			//終了処理
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//使用されてるとき

		//モーションの破棄
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//オブジェクト（自分自身の破棄）
	CObject::Release();
}

//==============================================================
//敵の更新処理
//==============================================================
void CEnemy::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得
	//CGame *pGame = CScene::GetGame();

	//前回の位置更新
	m_posOld = m_pos;

	//敵の操作
	CEnemy::ControlFrontKeyboard();

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//手前側の更新処理
	CEnemy::UpdateFront();

	//モーションの更新処理
	m_pMotion->Update();

	//デバッグ表示
	pDebugProc->Print("\n敵の位置 (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("敵の移動量 (%f, %f, %f)\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("敵の向き   (%f, %f, %f)\n", m_rot.x, m_rot.y, m_rot.z);
}

//==============================================================
//手前の更新処理
//==============================================================
void CEnemy::UpdateFront(void)
{
	//CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetInstance()->GetSound();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得

	//当たり判定
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//着地したら

		m_nDashCounter = 0;		//ダッシュ数リセット

		if (m_bLand == false)
		{
			//パーティクルの生成
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(0.8f, 0.7f, 0.6f, 0.8f), PARTICLETYPE_MOVE, 20, 10.0f);
		}

		m_bJump = false;	//ジャンプしてない状態にする
		m_bLand = true;		//着地した状態にする

		//if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_MOVE && m_bMove == true && m_bJump == false && m_bLand == true))
		//{//地面についたら(そのあと移動)

		//	//移動状態にする
		//	m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);


		//}
		//else if ((m_pMotion->GetType() == m_pMotion->MOTIONTYPE_JUMP && m_bMove == false && m_bJump == false && m_bLand == true))
		//{//地面についたら(完全に止まる)

		//	//着地状態にする
		//	m_pMotion->Set(m_pMotion->MOTIONTYPE_LAND);
		//}

		//パーティクル生成
		//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);
	}
	else if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == false &&
		pInputKeyboard->GetPress(DIK_SPACE) == false)
	{//地面についてない && ジャンプボタン押してない

		m_bJump = true;		//ジャンプしてる状態にする
		m_bLand = false;	//着地してない状態にする
	}

	//状態更新
	CEnemy::UpdateState();

	//向きの補正
	CEnemy::RotCorrection();

	//画面外処理
	CEnemy::Screen();

	//モーション管理
	CEnemy::MotionManager();
}

//==============================================================
//状態更新処理
//==============================================================
void CEnemy::UpdateState(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得

	switch (m_enemyState)
	{
	case ENEMYSTATE_NONE:		//何もしてない(止まってる状態)


		break;

	case ENEMYSTATE_MOVE:		//歩いてる状態

		break;

	case ENEMYSTATE_JUMP:		//ジャンプしてる状態

		break;

	case ENEMYSTATE_LAND:		//着地した状態

		break;

	case ENEMYSTATE_DASH:		//ダッシュ状態

		break;
	}
}
//void CEnemy::UpdateState(void)
//{
//	CPlayer *pPlayer = CGame::GetPlayer();
//	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得
//
//	if (pPlayer->GetIsMove() == true)
//	{//プレイヤーが歩いたら
//
//		//歩く準備をする
//		if (pPlayer->GetRotation().y > 0.0f)
//		{
//			m_bMoveL = true;		//左
//		}
//		else if (pPlayer->GetRotation().y < 0.0f)
//		{
//			m_bMoveR = true;		//右
//		}
//	}
//
//	if (m_bMoveL == true || m_bMoveR == true)
//	{//敵の歩く準備が開始したら
//
//		if (pPlayer->GetIsMove() == false)
//		{//プレイヤーが歩くのをやめたら
//
//			m_posSave = pPlayer->GetPosition();		//位置保存
//			m_rotSave = pPlayer->GetRotation();		//向き保存
//			m_moveSave = pPlayer->GetMove();		//移動量保存
//		}
//
//		if (m_nStateMoveCounter >= DELEY_CNT)
//		{//歩く準備ができたら
//
//			m_enemyState = ENEMYSTATE_MOVE;		//移動させる
//
//			m_posSave = pPlayer->GetPosition();		//位置保存
//			m_rotSave = pPlayer->GetRotation();		//向き保存
//			m_moveSave = pPlayer->GetMove();		//移動量保存
//
//			m_nStateMoveCounter = 0;		//動くまでのカウンターリセット
//		}
//		else
//		{
//			m_nStateMoveCounter++;		//動くまでのカウンター加算
//
//		}
//	}
//
//	//if (pPlayer->GetIsDash() == true)
//	//{//プレイヤーがダッシュしたら
//
//	//	m_bDash = true;		//ダッシュの準備する
//	//}
//
//	//if (m_bDash == true)
//	//{//ダッシュ準備開始したら
//
//	//	m_nDashCounter++;		//ダッシュするまでのカウンター加算
//
//	//	if (m_nStateMoveCounter >= DELEY_CNT)
//	//	{//ダッシュする準備ができたら
//
//	//		m_enemyState = ENEMYSTATE_MOVE;		//ダッシュさせる
//	//		m_nDashCounter = 0;		//ダッシュカウンターリセット
//	//	}
//
//	//}
//
//	switch (m_enemyState)
//	{
//	case ENEMYSTATE_NONE:		//何もしてない(止まってる状態)
//
//
//		break;
//
//	case ENEMYSTATE_MOVE:		//歩いてる状態
//
//		if(m_pos.x - m_posSave.x >= 40.0f || m_pos.x - m_posSave.x <= -40.0f)
//		{//目的の場所に行ってないとき
//
//			if (m_bMoveR == true && m_bMoveL == false)
//			{//右
//
//				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
//			}
//			else if (m_bMoveL == true && m_bMoveR == false)
//			{//左
//
//				m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
//			}
//		}
//		else
//		{
//			m_enemyState = ENEMYSTATE_NONE;		//何もしてない状態にする
//
//			if (m_bMoveL == true)
//			{//左
//
//				m_bMoveL = false;		//止める
//			}
//			else if (m_bMoveR == true)
//			{//右
//				m_bMoveR = false;		//止める
//			}
//		}
//
//		break;
//
//	case ENEMYSTATE_JUMP:		//ジャンプしてる状態
//
//		break;
//
//	case ENEMYSTATE_LAND:		//着地した状態
//
//		break;
//
//	case ENEMYSTATE_DASH:		//ダッシュ状態
//
//		break;
//	}
//}

//==============================================================
//敵のキーボード操作処理(手前側)
//==============================================================
void CEnemy::ControlFrontKeyboard(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CSound *pSound = CManager::GetInstance()->GetSound();

	//移動処理
	CEnemy::ControlFrontKeyboardMove();

	//ジャンプ処理
	CEnemy::ControlFrontKeyboardJump();

	//ダッシュ処理
	if (m_nDashCounter < MAX_DASH)
	{//最大ジャンプ数未満の場合

		CEnemy::ControlFrontKeyboardDash();
	}
}

//==============================================================
//敵のキーボードの移動操作処理(手前側)
//==============================================================
void CEnemy::ControlFrontKeyboardMove(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得

	//移動
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//右
		
		m_bPreMoveR = true;	//右に歩く準備をする
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//左

		m_bPreMoveL = true;	//左に歩く準備をする
	}

	//キーボード離したとき
	if (pInputKeyboard->GetRelease(DIK_D) == true)
	{//右

		m_bPreStopR = true;		//止まる準備する
	}

	if (pInputKeyboard->GetRelease(DIK_A) == true)
	{//左

		m_bPreStopL = true;		//止まる準備する
	}

	if (m_bPreMoveR == true)
	{//右に歩く準備するとき

		if (m_nStateMoveRCounter >= DELEY_CNT)
		{//一定時間経過したら

			m_bPreMoveR = false;
			m_bMove = true;		//歩かせる
			m_bMoveR = true;	//右に歩いてる状態にする

			m_nStateMoveRCounter = 0;
		}
		else
		{
			m_nStateMoveRCounter++;
		}
	}

	if (m_bPreMoveL == true)
	{//左に歩く準備するとき

		if (m_nStateMoveLCounter >= DELEY_CNT)
		{//一定時間経過したら

			m_bPreMoveL = false;
			m_bMove = true;		//歩かせる
			m_bMoveL = true;	//右に歩いてる状態にする

			m_nStateMoveLCounter = 0;
		}
		else
		{
			m_nStateMoveLCounter++;
		}
	}

	if (m_bMoveR == true)
	{//右に歩いてるとき

		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
	}
	else if (m_bMoveL == true)
	{//左に歩いてるとき

		m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
	}

	if (m_bPreStopR == true)
	{//止まる準備するとき

		if (m_nStateStopRCounter >= DELEY_CNT)
		{
			m_bMove = false;
			m_bMoveR = false;	//右に歩いてる状態にする
			m_bPreStopR = false;

			m_nStateStopRCounter = 0;		//止まるまでの時間初期化
		}
		else
		{
			m_nStateStopRCounter++;			//止まるまでの時間加算
		}
	}
	else if (m_bPreStopL == true)
	{//止まる準備するとき

		if (m_nStateStopLCounter >= DELEY_CNT)
		{
			m_bMove = false;
			m_bMoveL = false;	//右に歩いてる状態にする
			m_bPreStopL = false;

			m_nStateStopLCounter = 0;		//止まるまでの時間初期化
		}
		else
		{
			m_nStateStopLCounter++;			//止まるまでの時間加算
		}
	}

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//歩いてないとき

		m_bMove = false;		//歩いてない状態にする
	}
}

//==============================================================
//敵のキーボードのジャンプ操作処理(手前側)
//==============================================================
void CEnemy::ControlFrontKeyboardJump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CPlayer *pPlayer = CGame::GetPlayer();		//プレイヤーの情報取得
	CSound *pSound = CManager::GetInstance()->GetSound();
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();

	if (pInputKeyboard->GetPress(DIK_SPACE) == true && m_bJump == false && m_move.y <= JUMP_HEIGHT)
	{//SPACEキーを押したら

		m_bPreJump = true;		//ジャンプ準備状態にする

		m_nJumpLengthCounter++;		//ジャンプしたフレーム数取得
	}

	if (m_bPreJump == true)
	{//ジャンプ準備状態のとき

		if (m_nStateJumpCounter >= DELEY_CNT)
		{//一定時間経過したら

			if (m_nJumpLengthCounter <= 0)
			{//ジャンプしたい長さまで飛んだら

				//ジャンプした状態にする
				m_bJump = true;
				m_bLand = false;

				m_nJumpLengthCounter = 0;		//ジャンプした時間リセット
				m_nStateJumpCounter = 0;		//ジャンプするまでのカウンターリセット
				m_bPreJump = false;				//ジャンプの準備終了
			}
			else if (m_move.y >= JUMP_HEIGHT)
			{
				//ジャンプした状態にする
				m_bJump = true;
				m_bLand = false;

				m_nJumpLengthCounter = 0;		//ジャンプした時間リセット
				m_nStateJumpCounter = 0;		//ジャンプするまでのカウンターリセット
				m_bPreJump = false;				//ジャンプの準備終了
			}
			else
			{
				m_nJumpLengthCounter--;		//ジャンプする時間減算

				//ジャンプする
				m_move.y += ADD_MOVE_Y;

				pDebugProc->Print("\nジャンプ中\n");

			}
		}
		else
		{
			m_nStateJumpCounter++;		//ジャンプするまでのカウンター加算

		}
	}

	if (m_move.y >= JUMP_HEIGHT ||
		(m_bJump == true && (m_move.x <= 7.0f && m_move.x >= -7.0f)) ||
		(m_bDash == true && (m_move.x <= 7.0f && m_move.x >= -7.0f)))
	{
		//移動量加算
		m_move.y -= MOVE_Y;

		if (m_move.y <= 0.0f)
		{//着地したら

			m_bDash = false;
		}
	}
}

//==============================================================
//敵のキーボードのダッシュ操作処理(手前側)
//==============================================================
void CEnemy::ControlFrontKeyboardDash(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//カメラの情報取得

	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//右

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//上
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//移動量リセット
				m_move.y = 0.0f;		//移動量リセット
				m_bDash = true;			//ダッシュした状態にする
				m_bJump = true;			//ジャンプした状態にする

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//ダッシュ回数加算

			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//下
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//移動量リセット
				m_move.y = 0.0f;		//移動量リセット
				m_bDash = true;			//ダッシュした状態にする
				m_bJump = true;			//ジャンプした状態にする

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//ダッシュ回数加算

			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//移動量リセット
			m_move.z = 0.0f;		//移動量リセット
			m_bDash = true;			//ダッシュした状態にする
			m_bJump = true;			//ジャンプした状態にする

			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			m_nDashCounter++;		//ダッシュ回数加算

		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//左
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//上
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//移動量リセット
				m_move.y = 0.0f;		//移動量リセット
				m_bDash = true;			//ダッシュした状態にする
				m_bJump = true;			//ジャンプした状態にする

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//ダッシュ回数加算

			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//下
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//移動量リセット
				m_move.y = 0.0f;		//移動量リセット
				m_bDash = true;			//ダッシュした状態にする
				m_bJump = true;			//ジャンプした状態にする

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//ダッシュ回数加算

			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//移動量リセット
			m_move.z = 0.0f;		//移動量リセット
			m_bDash = true;			//ダッシュした状態にする
			m_bJump = true;			//ジャンプした状態にする

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			m_nDashCounter++;		//ダッシュ回数加算

		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//上
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//移動量リセット
			m_move.y = 0.0f;		//移動量リセット
			m_bDash = true;			//ダッシュした状態にする
			m_bJump = true;			//ジャンプした状態にする

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_UP) * FRONT_DASH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_UP) * FRONT_DASH_MOVE;

			m_nDashCounter++;		//ダッシュ回数加算

		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//下
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//移動量リセット
			m_move.y = 0.0f;		//移動量リセット
			m_bDash = true;			//ダッシュした状態にする
			m_bJump = true;			//ジャンプした状態にする

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_DOWN) * FRONT_DASH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_DOWN) * FRONT_DASH_MOVE;

			m_nDashCounter++;		//ダッシュ回数加算

		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_J) == true)
	{//Jキーだけを押したとき

		if (m_rot.y > 0)
		{//プレイヤーの向きが左だったら

			m_move.x = 0.0f;		//移動量リセット
			m_move.z = 0.0f;		//移動量リセット

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			m_nDashCounter++;		//ダッシュ回数加算

		}
		else if (m_rot.y <= 0)
		{
			m_move.x = 0.0f;		//移動量リセット
			m_move.z = 0.0f;		//移動量リセット

			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			m_nDashCounter++;		//ダッシュ回数加算

		}

		m_bDash = true;		//ダッシュした状態にする
		m_bJump = true;		//ジャンプした状態にする
	}
}

//==============================================================
//モーション管理処理
//==============================================================
void CEnemy::MotionManager(void)
{
	if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	{//歩いてる && 待機状態

		//歩かせる
		m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	}
	//else if (m_pMotion->IsFinish() == true && m_bAction == true)
	//{//攻撃が終わったら

	//	m_bAction = false;		//攻撃してない状態にする
	//}
	else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
		(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true))
	{//モーションが終了したら

		//待機状態に戻す
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}
}

//==============================================================
//向きの補正処理
//==============================================================
void CEnemy::RotCorrection(void)
{
	//向きの差分を求める
	m_fRotDiff = m_fRotDest - m_rot.y;

	//目標の方向までの差分を修正
	if (m_fRotDiff < -D3DX_PI)
	{
		m_fRotDiff += D3DX_PI * 2;
	}
	else if (m_fRotDiff > D3DX_PI)
	{
		m_fRotDiff -= D3DX_PI * 2;
	}

	//差分足す
	m_rot.y += m_fRotDiff * 0.1f;

	//現在の方向修正
	if (m_rot.y > D3DX_PI)
	{
		m_rot.y -= D3DX_PI * 2;
	}
	else if (m_rot.y < -D3DX_PI)
	{
		m_rot.y += D3DX_PI * 2;
	}
}

//==============================================================
//画面外判定処理
//==============================================================
void CEnemy::Screen(void)
{
	//if (m_pos.y < 0.0f)
	//{//画面下に出たら

	//	m_move.y = 0.0f;
	//	m_pos.y = 0.0f;

	//	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//キーボードの情報取得

	//	if (pInputKeyboard->GetPress(DIK_SPACE) == false)
	//	{
	//		m_bLand = true;		//着地した
	//		m_bJump = false;	//ジャンプしてない
	//	}

	//	m_nDashCounter = 0;		//ダッシュ数リセット

	//	//m_state = STATE_NONE;		//通常状態にする
	//}
}

//==============================================================
//敵の描画処理
//==============================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//デバイスの取得
	D3DXMATRIX mtxRot, mtxTrans;	//計算用マトリックス

	//ワールドマトリックスを初期化
	D3DXMatrixIdentity(&m_mtxWorld);

	//向きを反映
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//位置を反映
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//ワールドマトリックスの設定
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//敵の描画
		m_apModel[nCntEnemy]->Draw();
	}
}

//==============================================================
//モデルファイル読み込み処理
//==============================================================
void CEnemy::LoadFile(void)
{
	FILE *pFile;				//ファイルポインタ
	char aString[MAX_STR];		//文字読み込み
	int nIndex = 0, nParent = 0;	//パーツNo.,親番号
	D3DXVECTOR3 pos, rot;

	//ファイル開く
	pFile = fopen(FILE_ENEMY, "r");

	if (pFile != NULL)
	{//ファイルが開けた場合

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]するまでの間

			fscanf(pFile, "%s", &aString[0]);		//文字読み込み
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]が来たら

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]がくるまでの間

				fscanf(pFile, "%s", &aString[0]);		//文字読み込み

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]が来たら

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]がくるまでの間

						fscanf(pFile, "%s", &aString[0]);		//文字読み込み

						if (strcmp(&aString[0], "INDEX") == 0)
						{//パーツNo.

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nIndex);			//パーツNo.読み込み

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//親情報

							fscanf(pFile, "%s", &aString[0]);		//文字読み込み
							fscanf(pFile, "%d", &nParent);			//親番号読み込み

							if (nParent == -1)
							{//親がいなかったら

								m_apModel[nIndex]->SetParent(NULL);		//NULLを入れる
							}
							else
							{//親がいたら

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//親番号入れる
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//位置情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &pos.x);		//位置読み込み
							fscanf(pFile, "%f", &pos.y);		//位置読み込み
							fscanf(pFile, "%f", &pos.z);		//位置読み込み

							m_apModel[nIndex]->SetPosition(pos);		//位置設定
							m_apModel[nIndex]->SetDefaultPosition(pos);	//初期位置設定

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//向き情報

							fscanf(pFile, "%s", &aString[0]);	//文字読み込み

							fscanf(pFile, "%f", &rot.x);		//向き読み込み
							fscanf(pFile, "%f", &rot.y);		//向き読み込み
							fscanf(pFile, "%f", &rot.z);		//向き読み込み

							m_apModel[nIndex]->SetRotation(rot);		//向き設定
							m_apModel[nIndex]->SetDefaultRotation(rot);	//初期向き設定
						}
					}
				}
			}
		}

		//ファイル閉じる
		fclose(pFile);
	}
}