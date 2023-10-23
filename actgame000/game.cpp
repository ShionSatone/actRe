//==============================================================
//
//�Q�[������[game.cpp]
//Author:����������
//
//==============================================================
#include "game.h"
#include "manager.h"
#include "input.h"
#include "camera.h"
#include "edit.h"
#include "player.h"
#include "enemy.h"
#include "wall.h"
#include "item.h"
//#include "ranking.h"
//#include "pause.h"
#include "fade.h"
#include "score.h"
#include "sound.h"

//�}�N����`
#define ENEMYSPAWN_TIME		(20)			//�G�o������


//�ÓI�����o�ϐ��錾
CEdit *CGame::m_pEdit = NULL;				//�G�f�B�b�g�̏��
CPlayer *CGame::m_pPlayer = NULL;			//�v���C���[�̏��
bool CGame::m_bReset = true;				//���Z�b�g�������ǂ���
bool CGame::m_bPause = false;				//�|�[�Y��ʂ�
//CPause *CGame::m_pPause = NULL;			//�|�[�Y��ʂ̏��
CScore *CGame::m_pScore = NULL;				//�X�R�A�̏��
bool CGame::m_bEnemyStart = false;			//�X�^�[�g������
CGame::GAMEMODE CGame::m_gameMode = GAMEMODE_START;	//�Q�[�����[�h

//==============================================================
//�R���X�g���N�^
//==============================================================
CGame::CGame()
{
	m_nCntEnemy = 0;				//�G�o���J�E���g

	m_bEnemyStart = false;			//�G�o��������
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CGame::~CGame()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CGame::Init(void)
{
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	m_bReset = true;		//���Z�b�g���Ă��Ԃɂ���
	m_bPause = false;		//�|�[�Y���ĂȂ�

	//�J�����̏���������
	pCamera->Init();

	//�G�̐���
	CEnemy::Create(D3DXVECTOR3(1080.0f, -150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�v���C���[�̐���
	m_pPlayer = m_pPlayer->Create(D3DXVECTOR3(1080.0f, -150.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�G�f�B�b�g�̐���
	m_pEdit = CEdit::Create();

	//�Ђ��`�A�C�e��
	CItem::Create(D3DXVECTOR3(600.0f, -1400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(750.0f, -3050.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);
	CItem::Create(D3DXVECTOR3(300.0f, -3200.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_RHOMBUS);

	//���A�C�e��
	//CItem::Create(D3DXVECTOR3(600.0f, -1400.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), CItem::TYPEITEM_STAR);

	//�X�R�A�̐���
	m_pScore = CScore::Create();

	//�|�[�Y��ʂ̐���
	//m_pPause = CPause::Create();

	//BGM�Đ�
	//pSound->Play(pSound->SOUND_LABEL_BGM002);

	CObject::SetType(CObject::TYPE_SCENE);

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CGame::Uninit(void)
{
	CSound *pSound = CManager::GetInstance()->GetSound();

	//BGM�̒�~
	pSound->Stop();

	//�v���C���[�̔j��
	if (m_pPlayer != NULL)
	{
		m_pPlayer->Uninit();
		m_pPlayer = NULL;
	}

	//�G�f�B�^�[�̔j��
	if (m_pEdit != NULL)
	{
		m_pEdit->Uninit();
		m_pEdit = NULL;
	}

	//�|�[�Y�̔j��
	/*if (m_pPause != NULL)
	{
		m_pPause->Uninit();
		m_pPause = NULL;
	}*/

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CGame::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInstance()->GetInputJoyPad();			//�p�b�h�̏��擾
	CFade *pFade = CManager::GetInstance()->GetFade();			//�t�F�[�h�̏��擾

	if (pInputKeyboard->GetTrigger(DIK_P) == true || 
		pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_START, 0) == true)
	{//P�L�[����������

		m_bPause = m_bPause ? false : true;		//�|�[�Y�؂�ւ�
	}

	if (m_bPause == true)
	{//�|�[�Y���Ă�Ƃ�

		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true)
		{
			m_bPause = false;
		}
	}
	else
	{
		if (pInputKeyboard->GetTrigger(DIK_RETURN) == true ||
			pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true)
		{//ENTER�L�[��������

			//�Q�[�����
			pFade->SetFade(CScene::MODE_RESULT);

			//bReset = true;
		}
		///*else
		//{
		//bReset = false;
		//}*/
	}
}

//==============================================================
//�`�揈��
//==============================================================
void CGame::Draw(void)
{

}

//==============================================================
//�|�[�Y��ʂ̐ݒ菈��
//==============================================================
void CGame::SetEnablePause(bool bPouse)
{
	m_bPause = bPouse;
}