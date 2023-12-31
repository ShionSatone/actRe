//==============================================================
//
//ゲーム処理[game.h]
//Author:佐藤根詩音
//
//==============================================================
#ifndef _GAME_H_		//このマクロ定義がされていなかったら
#define _GAME_H_		//2重インクルード防止のマクロを定義する

#include "manager.h"

//マクロ定義
#define MAX_ENEMY_POS		(70)		//保存する最大フレーム数

//前方宣言
class CPlayer;			//プレイヤーの情報
class CScore;			//スコアの情報
class CDeathUI;			//死亡UIの情報
class CItemUI;			//アイテムUIの情報
class CEdit;			//エディットの情報
class CPause;			//ポーズ画面の情報
class CFade;			//フェード

//ゲーム画面クラスの定義
class CGame : public CScene
{
public:

	//ゲームモードの種類
	enum GAMEMODE
	{
		GAMEMODE_START = 0,			//開始
		GAMEMODE_GAME,				//ゲーム中
		GAMEMODE_OVER,				//終了
		GAMEMODE_MAX
	};

	CGame();
	~CGame();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void SetEnablePause(bool bPouse);			//ポーズ切り替え

	static CScore *GetScore(void) { return m_pScore; }			//スコアの情報
	static CDeathUI *GetDeathUI(void) { return m_pDeathUI; }	//死亡数の情報
	static CItemUI *GetItemUI(void) { return m_pItemUI; }		//アイテム数の情報
	static void SetGameMode(GAMEMODE gameMode) { m_gameMode = gameMode; }		//ゲームモードの設定
	static GAMEMODE GetGameMode(void) { return m_gameMode; }					//ゲームモードの設定
	static CPlayer *GetPlayer(void) { return m_pPlayer; }		//プレイヤーの情報取得
	static CPause *GetPause(void) { return m_pPause; }			//ポーズ画面の情報
	static bool GetPauseDisp(void) { return m_bPause; }			//ポーズしてるか取得

private:
	void SetEnemy(void);		//敵出現処理

	static CPlayer *m_pPlayer;		//プレイヤーの情報
	static CEdit *m_pEdit;			//エディットの情報
	static CPause *m_pPause;		//ポーズ画面の情報
	static CScore *m_pScore;		//スコアの情報
	static CDeathUI *m_pDeathUI;	//死亡UIの情報
	static CItemUI *m_pItemUI;		//アイテムUIの情報

	static bool m_bReset;			//リセットしたか
	static bool m_bPause;			//ポーズ画面か
	static bool m_bEnemySpawnFirst;			//敵が出現したか
	static bool m_bEnemySpawnSecond;		//敵が出現したか

	static GAMEMODE m_gameMode;		//ゲームモード
	int m_nCntEnemy;				//敵出現カウント
};

#endif

