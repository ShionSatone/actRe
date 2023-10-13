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
	"data\\MODEL\\player\\00_body.x",
	"data\\MODEL\\player\\01_head.x",
	"data\\MODEL\\player\\02_hair.x",
	"data\\MODEL\\player\\03_LU_arm.x",
	"data\\MODEL\\player\\04_LD_arm.x",
	"data\\MODEL\\player\\05_L_hand.x",
	"data\\MODEL\\player\\06_RU_arm.x",
	"data\\MODEL\\player\\07_RD_arm.x",
	"data\\MODEL\\player\\08_R_arm.x",
	"data\\MODEL\\player\\09_waist.x",
	"data\\MODEL\\player\\10_LU_leg.x",
	"data\\MODEL\\player\\11_LD_leg.x",
	"data\\MODEL\\player\\12_L_shoe.x",
	"data\\MODEL\\player\\13_RU_leg.x",
	"data\\MODEL\\player\\14_RD_leg.x",
	"data\\MODEL\\player\\15_R_shoe.x",

};

//==============================================================
//コンストラクタ
//==============================================================
CEnemy::CEnemy() : CObject(PRIORITY)
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
	m_bLand = true;			//着地した
	m_bDash = false;		//ダッシュしたか

	m_fRotDest = 0.0f;		//目標
	m_fRotDiff = 0.0f;		//差分

	m_nDashCounter = 0;		//ダッシュした回数

	m_state = STATE_NONE;			//状態
	m_enemyState = ENEMYSTATE_NONE;	//止まってる状態
	m_nCntDamage = 0;				//ダメージカウンター

	m_nStateNoneCounter = 0;	//敵の停止状態変更カウンター
	m_nStateMoveCounter = 0;	//敵の移動状態変更カウンター
	m_nStateJumpCounter = 0;	//敵の移ジャンプ状態変更カウンター
	m_nStateLandCounter = 0;	//敵の着地状態変更カウンター
	m_nStateDashCounter = 0;	//敵のダッシュ状態変更カウンター

}

//==============================================================
//コンストラクタ(オーバーロード)
//==============================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot) : CObject(PRIORITY)
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
	m_bLand = true;			//着地した
	m_bDash = false;		//ダッシュしたか

	m_fRotDest = 0.0f;	//目標
	m_fRotDiff = 0.0f;	//差分

	m_nDashCounter = 0;		//ダッシュした回数
	m_state = STATE_NONE;		//状態
	m_enemyState = ENEMYSTATE_NONE;	//止まってる状態
	m_nCntDamage = 0;			//ダメージカウンター

	m_nStateNoneCounter = 0;	//敵の停止状態変更カウンター
	m_nStateMoveCounter = 0;	//敵の移動状態変更カウンター
	m_nStateJumpCounter = 0;	//敵の移ジャンプ状態変更カウンター
	m_nStateLandCounter = 0;	//敵の着地状態変更カウンター
	m_nStateDashCounter = 0;	//敵のダッシュ状態変更カウンター
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
	//CLife *pLife = CGame::GetLife();

	m_fRotDest = m_rot.y;

	//敵の生成（全パーツ分）
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//モーションの初期化・生成
	/*m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();*/

	//モデルのファイル読み込み
	CEnemy::LoadFile();

	//最大値・最小値代入
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//最大値Y
		if ((nCntEnemy <= PARTS_BODY && nCntEnemy <= PARTS_HEAD) ||
			(nCntEnemy >= PARTS_RU_LEG && nCntEnemy <= PARTS_R_SHOE))
		{
			m_max.y += m_apModel[nCntEnemy]->GetSizeMax().y;		//最大値加算
		}

		//最大値入れ替え
		if (m_max.x < m_apModel[nCntEnemy]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntEnemy]->GetSizeMax().x;		//最小値X
		}
		if (m_max.z < m_apModel[nCntEnemy]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntEnemy]->GetSizeMax().z;		//最小値Z

		}

		//最小値入れ替え
		if (m_min.x > m_apModel[nCntEnemy]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntEnemy]->GetSizeMin().x;		//最小値X
		}
		if (m_min.y > m_apModel[nCntEnemy]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntEnemy]->GetSizeMin().y;		//最小値Y
		}
		if (m_min.z > m_apModel[nCntEnemy]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntEnemy]->GetSizeMin().z;		//最小値Z

		}
	}

	m_max.y += 10.0f;

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
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得
	//CGame *pGame = CScene::GetGame();

	//前回の位置更新
	m_posOld = m_pos;

	//手前側の更新処理
	CEnemy::UpdateFront();

	//モーションの更新処理
	//m_pMotion->Update();

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
	CSound *pSound = CManager::GetSound();

	//位置更新
	m_pos += m_move;

	//移動量を更新
	m_move.x += (0.0f - m_move.x) * 0.1f;

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
	CCamera *pCamera = CManager::GetCamera();		//カメラの情報取得

	if (pPlayer->GetIsMove() == true)
	{//プレイヤーが歩いたら

		//歩く準備をする
		if (pPlayer->GetRotation().y > 0.0f)
		{
			m_bMoveR = true;		//右
		}
		else if (pPlayer->GetRotation().y < 0.0f)
		{
			m_bMoveL = true;		//左
		}
	}

	if (m_bMoveL == true || m_bMoveR == true)
	{//敵の歩く準備が開始したら

		if (pPlayer->GetIsMove() == false)
		{//プレイヤーが歩くのをやめたら

			m_posSave = pPlayer->GetPosition();		//位置保存
			m_rotSave = pPlayer->GetRotation();		//向き保存
			m_moveSave = pPlayer->GetMove();		//移動量保存
		}

		if (m_nStateMoveCounter >= DELEY_CNT)
		{//歩く準備ができたら

			m_enemyState = ENEMYSTATE_MOVE;		//移動させる

			m_posSave = pPlayer->GetPosition();		//位置保存
			m_rotSave = pPlayer->GetRotation();		//向き保存
			m_moveSave = pPlayer->GetMove();		//移動量保存

			m_nStateMoveCounter = 0;		//動くまでのカウンターリセット
		}
		else
		{
			m_nStateMoveCounter++;		//動くまでのカウンター加算

		}
	}

	switch (m_enemyState)
	{
	case ENEMYSTATE_NONE:		//何もしてない(止まってる状態)


		break;

	case ENEMYSTATE_MOVE:		//歩いてる状態

		if(m_pos.x - m_posSave.x >= 40.0f || m_pos.x - m_posSave.x <= -40.0f)
		{//目的の場所に行ってないとき

			if (m_rotSave.y < 0.0f)
			{//右

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
				m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
			}
			else if (m_rotSave.y > 0.0f)
			{//左

				m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
				m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
			}
		}
		//else
		//{
		//	m_enemyState = ENEMYSTATE_NONE;		//何もしてない状態にする
		//	m_bMove = false;					//移動の準備してない状態にする
		//}

		break;

	case ENEMYSTATE_JUMP:		//ジャンプしてる状態

		break;

	case ENEMYSTATE_LAND:		//着地した状態

		break;

	case ENEMYSTATE_DASH:		//ダッシュ状態

		break;
	}
}

//==============================================================
//モーション管理処理
//==============================================================
void CEnemy::MotionManager(void)
{
	//if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	//{//歩いてる && 待機状態

	//	//歩かせる
	//	m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	//}
	//else if (m_pMotion->IsFinish() == true && m_bAction == true)
	//{//攻撃が終わったら

	//	m_bAction = false;		//攻撃してない状態にする
	//}
	//else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
	//	(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true && m_bAction == false))
	//{//モーションが終了したら

	//	//待機状態に戻す
	//	m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	//}
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
	if (m_pos.y < 0.0f)
	{//画面下に出たら

		m_move.y = 0.0f;
		m_pos.y = 0.0f;

		CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//キーボードの情報取得

		if (pInputKeyboard->GetPress(DIK_SPACE) == false)
		{
			m_bLand = true;		//着地した
			m_bJump = false;	//ジャンプしてない
		}

		m_nDashCounter = 0;		//ダッシュ数リセット

		//m_state = STATE_NONE;		//通常状態にする
	}
}

//==============================================================
//敵の描画処理
//==============================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//デバイスの取得
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