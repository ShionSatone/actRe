//==============================================================
//
//�G�̏���[enemy.h]
//Author:����������
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

//�}�N����`
#define PRIORITY			(3)			//�D�揇��
#define POS					(10.0f)		//pos�����l
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x
#define MOVE_Y				(0.7f)		//�ړ���Y
#define ADD_MOVE_Y			(1.5f)		//�ړ���Y���Z���鐔
#define JUMP_HEIGHT			(10.0f)		//�W�����v�̍���
#define MAX_STR				(128)		//�����̍ő吔
#define FRONT_MOVE			(0.6f)		//��O�̎��̈ړ���
#define FRONT_DASH_MOVE		(15.0f)		//��O�̃_�b�V�����̈ړ���
#define MAX_DASH			(2)			//�_�b�V���̍ő吔
#define STOP_MOVE			(0.8f)		//�~�܂锻��̈ړ���
#define FILE_ENEMY			"data\\TEXT\\motion_player.txt"		//�G���f���̃e�L�X�g

#define HIT_CNT				(60 * 2)	//�U��������܂ł̃J�E���g��
#define DAMAGE_CNT			(9)			//�_���[�W�J�E���g��
#define APP_CNT				(100)		//�_�Ŏ���
#define STEP_CNT			(25)		//�������̃J�E���^�[

#define DELEY_CNT			(20)		//�s������܂ł̃J�E���^�[

//�ÓI�����o�ϐ��錾
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
//�R���X�g���N�^
//==============================================================
CEnemy::CEnemy()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		m_apModel[nCntEnemy] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�G(�p�[�c)�̑���
	m_pMotion = NULL;

	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ʒu�ۑ��p
	m_rotSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����ۑ��p
	m_moveSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�ړ��ʕۑ��p

	m_bJump = false;		//�W�����v������
	m_bMoveL = false;		//���ɕ����Ă邩�̔���
	m_bMoveR = false;		//�E�ɕ����Ă邩�̔���
	m_bMove = false;		//�����Ă邩�̔���
	m_bLand = true;			//���n����
	m_bDash = false;		//�_�b�V��������

	m_bPreMoveL = false;	//���ɕ�����������
	m_bPreMoveR = false;	//�E�ɕ��������̔���
	m_bPreMove = false;		//������������
	m_bPreJump = false;		//�W�����v�̏�������
	m_bPreDash = false;		//�_�b�V����������
	m_bPreStopR = false;		//�~�܂鏀������
	m_bPreStopL = false;		//�~�܂鏀������

	m_fRotDest = 0.0f;		//�ڕW
	m_fRotDiff = 0.0f;		//����

	m_nDashCounter = 0;		//�_�b�V��������

	m_state = STATE_NONE;			//���
	m_enemyState = ENEMYSTATE_NONE;	//�~�܂��Ă���
	m_nCntDamage = 0;				//�_���[�W�J�E���^�[

	m_nStateNoneCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[
	m_nStateMoveRCounter = 0;	//�G�̈ړ���ԕύX�J�E���^�[
	m_nStateMoveLCounter = 0;	//�G�̈ړ���ԕύX�J�E���^�[
	m_nStateJumpCounter = 0;	//�G�̈ڃW�����v��ԕύX�J�E���^�[
	m_nStateLandCounter = 0;	//�G�̒��n��ԕύX�J�E���^�[
	m_nStateDashCounter = 0;	//�G�̃_�b�V����ԕύX�J�E���^�[
	m_nJumpLengthCounter = 0;	//�W�����v��������
	m_nStateStopRCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[
	m_nStateStopLCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[

}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CEnemy::CEnemy(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;									//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l
	m_rot = rot;		//����

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		m_apModel[nCntEnemy] = NULL;		//�G(�p�[�c)�ւ̃|�C���^
	}

	m_pMotion = NULL;		//���[�V�����̏��
	m_nNumModel = 0;		//�G(�p�[�c)�̑���

	m_bJump = false;		//�W�����v������
	m_bMoveL = false;		//���ɕ����Ă邩�̔���
	m_bMoveR = false;		//�E�ɕ����Ă邩�̔���
	m_bMove = false;		//�����Ă邩�̔���
	m_bLand = true;			//���n����
	m_bDash = false;		//�_�b�V��������

	m_bPreMoveL = false;	//���ɕ�����������
	m_bPreMoveR = false;	//�E�ɕ��������̔���
	m_bPreMove = false;		//������������
	m_bPreJump = false;		//�W�����v�̏�������
	m_bPreDash = false;		//�_�b�V����������
	m_bPreStopR = false;		//�~�܂鏀������
	m_bPreStopL = false;		//�~�܂鏀������

	m_fRotDest = 0.0f;	//�ڕW
	m_fRotDiff = 0.0f;	//����

	m_nDashCounter = 0;		//�_�b�V��������
	m_state = STATE_NONE;		//���
	m_enemyState = ENEMYSTATE_NONE;	//�~�܂��Ă���
	m_nCntDamage = 0;			//�_���[�W�J�E���^�[

	m_nStateNoneCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[
	m_nStateMoveRCounter = 0;	//�G�̈ړ���ԕύX�J�E���^�[
	m_nStateMoveLCounter = 0;	//�G�̈ړ���ԕύX�J�E���^�[

	m_nStateJumpCounter = 0;	//�G�̈ڃW�����v��ԕύX�J�E���^�[
	m_nStateLandCounter = 0;	//�G�̒��n��ԕύX�J�E���^�[
	m_nStateDashCounter = 0;	//�G�̃_�b�V����ԕύX�J�E���^�[
	m_nJumpLengthCounter = 0;	//�W�����v��������
	m_nStateStopRCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[
	m_nStateStopLCounter = 0;	//�G�̒�~��ԕύX�J�E���^�[

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEnemy::~CEnemy()
{

}

//==============================================================
//�G�̐�������
//==============================================================
CEnemy *CEnemy::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEnemy *pEnemyModel = NULL;

	if (pEnemyModel == NULL)
	{//���������g�p����ĂȂ�������

		//�G�̐���
		pEnemyModel = new CEnemy(pos, rot);
	}

	//����������
	pEnemyModel->Init();

	return pEnemyModel;
}

//==============================================================
//�G�̏���������
//==============================================================
HRESULT CEnemy::Init(void)
{
	//CLife *pLife = CGame::GetLife();

	m_fRotDest = m_rot.y;

	//�G�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���[�V�����̏������E����
	/*m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();*/

	//���f���̃t�@�C���ǂݍ���
	CEnemy::LoadFile();

	//�ő�l�E�ŏ��l���
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�ő�lY
		if ((nCntPlayer <= PARTS_HEAD) || (nCntPlayer >= PARTS_WAIST && nCntPlayer <= PARTS_L_SHOE))
		{
			m_max.y += m_apModel[nCntPlayer]->GetSizeMax().y;		//�ő�l���Z
		}

		//�ő�l����ւ�
		if (m_max.x < m_apModel[nCntPlayer]->GetSizeMax().x)
		{
			m_max.x = m_apModel[nCntPlayer]->GetSizeMax().x;		//�ŏ��lX
		}
		if (m_max.z < m_apModel[nCntPlayer]->GetSizeMax().z)
		{
			m_max.z = m_apModel[nCntPlayer]->GetSizeMax().z;		//�ŏ��lZ

		}

		//�ŏ��l����ւ�
		if (m_min.x > m_apModel[nCntPlayer]->GetSizeMin().x)
		{
			m_min.x = m_apModel[nCntPlayer]->GetSizeMin().x;		//�ŏ��lX
		}
		if (m_min.y > m_apModel[nCntPlayer]->GetSizeMin().y)
		{
			m_min.y = m_apModel[nCntPlayer]->GetSizeMin().y;		//�ŏ��lY
		}
		if (m_min.z > m_apModel[nCntPlayer]->GetSizeMin().z)
		{
			m_min.z = m_apModel[nCntPlayer]->GetSizeMin().z;		//�ŏ��lZ

		}
	}

	m_max.y += 40.0f;

	CObject::SetType(CObject::TYPE_ENEMY);

	return S_OK;
}

//==============================================================
//�G�̏I������
//==============================================================
void CEnemy::Uninit(void)
{
	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		if (m_apModel[nCntEnemy] != NULL)
		{//�g�p����Ă�Ƃ�

			//�I������
			m_apModel[nCntEnemy]->Uninit();
			m_apModel[nCntEnemy] = NULL;
		}
	}

	if (m_pMotion != NULL)
	{//�g�p����Ă�Ƃ�

		//���[�V�����̔j��
		delete m_pMotion;
		m_pMotion = NULL;
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�G�̍X�V����
//==============================================================
void CEnemy::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾
	//CGame *pGame = CScene::GetGame();

	//�O��̈ʒu�X�V
	m_posOld = m_pos;

	//�G�̑���
	CEnemy::ControlFrontKeyboard();

	//�ʒu�X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//��O���̍X�V����
	CEnemy::UpdateFront();

	//���[�V�����̍X�V����
	//m_pMotion->Update();

	//�f�o�b�O�\��
	pDebugProc->Print("\n�G�̈ʒu (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("�G�̈ړ��� (%f, %f, %f)\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("�G�̌���   (%f, %f, %f)\n", m_rot.x, m_rot.y, m_rot.z);
}

//==============================================================
//��O�̍X�V����
//==============================================================
void CEnemy::UpdateFront(void)
{
	//CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetInstance()->GetSound();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾

	//�����蔻��
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//���n������

		m_nDashCounter = 0;		//�_�b�V�������Z�b�g

		if (m_bLand == false)
		{
			//�p�[�e�B�N���̐���
			//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y, m_pos.z), D3DXCOLOR(0.8f, 0.7f, 0.6f, 0.8f), PARTICLETYPE_MOVE, 20, 10.0f);
		}

		m_bJump = false;	//�W�����v���ĂȂ���Ԃɂ���
		m_bLand = true;		//���n������Ԃɂ���

		//if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_MOVE && m_bMove == true && m_bJump == false && m_bLand == true))
		//{//�n�ʂɂ�����(���̂��ƈړ�)

		//	//�ړ���Ԃɂ���
		//	m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);


		//}
		//else if ((m_pMotion->GetType() == m_pMotion->MOTIONTYPE_JUMP && m_bMove == false && m_bJump == false && m_bLand == true))
		//{//�n�ʂɂ�����(���S�Ɏ~�܂�)

		//	//���n��Ԃɂ���
		//	m_pMotion->Set(m_pMotion->MOTIONTYPE_LAND);
		//}

		//�p�[�e�B�N������
		//CParticle::Create(D3DXVECTOR3(m_pos.x, m_pos.y + 100.0f, m_pos.z), D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f), m_particleType, m_nParticleLife, 50.0f);
	}
	else if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == false &&
		pInputKeyboard->GetPress(DIK_SPACE) == false)
	{//�n�ʂɂ��ĂȂ� && �W�����v�{�^�������ĂȂ�

		m_bJump = true;		//�W�����v���Ă��Ԃɂ���
		m_bLand = false;	//���n���ĂȂ���Ԃɂ���
	}

	//��ԍX�V
	CEnemy::UpdateState();

	//�����̕␳
	CEnemy::RotCorrection();

	//��ʊO����
	CEnemy::Screen();

	//���[�V�����Ǘ�
	CEnemy::MotionManager();
}

//==============================================================
//��ԍX�V����
//==============================================================
void CEnemy::UpdateState(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾

	switch (m_enemyState)
	{
	case ENEMYSTATE_NONE:		//�������ĂȂ�(�~�܂��Ă���)


		break;

	case ENEMYSTATE_MOVE:		//�����Ă���

		break;

	case ENEMYSTATE_JUMP:		//�W�����v���Ă���

		break;

	case ENEMYSTATE_LAND:		//���n�������

		break;

	case ENEMYSTATE_DASH:		//�_�b�V�����

		break;
	}
}
//void CEnemy::UpdateState(void)
//{
//	CPlayer *pPlayer = CGame::GetPlayer();
//	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾
//
//	if (pPlayer->GetIsMove() == true)
//	{//�v���C���[����������
//
//		//��������������
//		if (pPlayer->GetRotation().y > 0.0f)
//		{
//			m_bMoveL = true;		//��
//		}
//		else if (pPlayer->GetRotation().y < 0.0f)
//		{
//			m_bMoveR = true;		//�E
//		}
//	}
//
//	if (m_bMoveL == true || m_bMoveR == true)
//	{//�G�̕����������J�n������
//
//		if (pPlayer->GetIsMove() == false)
//		{//�v���C���[�������̂���߂���
//
//			m_posSave = pPlayer->GetPosition();		//�ʒu�ۑ�
//			m_rotSave = pPlayer->GetRotation();		//�����ۑ�
//			m_moveSave = pPlayer->GetMove();		//�ړ��ʕۑ�
//		}
//
//		if (m_nStateMoveCounter >= DELEY_CNT)
//		{//�����������ł�����
//
//			m_enemyState = ENEMYSTATE_MOVE;		//�ړ�������
//
//			m_posSave = pPlayer->GetPosition();		//�ʒu�ۑ�
//			m_rotSave = pPlayer->GetRotation();		//�����ۑ�
//			m_moveSave = pPlayer->GetMove();		//�ړ��ʕۑ�
//
//			m_nStateMoveCounter = 0;		//�����܂ł̃J�E���^�[���Z�b�g
//		}
//		else
//		{
//			m_nStateMoveCounter++;		//�����܂ł̃J�E���^�[���Z
//
//		}
//	}
//
//	//if (pPlayer->GetIsDash() == true)
//	//{//�v���C���[���_�b�V��������
//
//	//	m_bDash = true;		//�_�b�V���̏�������
//	//}
//
//	//if (m_bDash == true)
//	//{//�_�b�V�������J�n������
//
//	//	m_nDashCounter++;		//�_�b�V������܂ł̃J�E���^�[���Z
//
//	//	if (m_nStateMoveCounter >= DELEY_CNT)
//	//	{//�_�b�V�����鏀�����ł�����
//
//	//		m_enemyState = ENEMYSTATE_MOVE;		//�_�b�V��������
//	//		m_nDashCounter = 0;		//�_�b�V���J�E���^�[���Z�b�g
//	//	}
//
//	//}
//
//	switch (m_enemyState)
//	{
//	case ENEMYSTATE_NONE:		//�������ĂȂ�(�~�܂��Ă���)
//
//
//		break;
//
//	case ENEMYSTATE_MOVE:		//�����Ă���
//
//		if(m_pos.x - m_posSave.x >= 40.0f || m_pos.x - m_posSave.x <= -40.0f)
//		{//�ړI�̏ꏊ�ɍs���ĂȂ��Ƃ�
//
//			if (m_bMoveR == true && m_bMoveL == false)
//			{//�E
//
//				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
//			}
//			else if (m_bMoveL == true && m_bMoveR == false)
//			{//��
//
//				m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
//				m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
//			}
//		}
//		else
//		{
//			m_enemyState = ENEMYSTATE_NONE;		//�������ĂȂ���Ԃɂ���
//
//			if (m_bMoveL == true)
//			{//��
//
//				m_bMoveL = false;		//�~�߂�
//			}
//			else if (m_bMoveR == true)
//			{//�E
//				m_bMoveR = false;		//�~�߂�
//			}
//		}
//
//		break;
//
//	case ENEMYSTATE_JUMP:		//�W�����v���Ă���
//
//		break;
//
//	case ENEMYSTATE_LAND:		//���n�������
//
//		break;
//
//	case ENEMYSTATE_DASH:		//�_�b�V�����
//
//		break;
//	}
//}

//==============================================================
//�G�̃L�[�{�[�h���쏈��(��O��)
//==============================================================
void CEnemy::ControlFrontKeyboard(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	//�ړ�����
	CEnemy::ControlFrontKeyboardMove();

	//�W�����v����
	CEnemy::ControlFrontKeyboardJump();

	//�_�b�V������
	if (m_nDashCounter < MAX_DASH)
	{//�ő�W�����v�������̏ꍇ

		CEnemy::ControlFrontKeyboardDash();
	}
}

//==============================================================
//�G�̃L�[�{�[�h�̈ړ����쏈��(��O��)
//==============================================================
void CEnemy::ControlFrontKeyboardMove(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//�E
		
		m_bPreMoveR = true;	//�E�ɕ�������������
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//��

		m_bPreMoveL = true;	//���ɕ�������������
	}

	//�L�[�{�[�h�������Ƃ�
	if (pInputKeyboard->GetRelease(DIK_D) == true)
	{//�E

		m_bPreStopR = true;		//�~�܂鏀������
	}

	if (pInputKeyboard->GetRelease(DIK_A) == true)
	{//��

		m_bPreStopL = true;		//�~�܂鏀������
	}

	if (m_bPreMoveR == true)
	{//�E�ɕ�����������Ƃ�

		if (m_nStateMoveRCounter >= DELEY_CNT)
		{//��莞�Ԍo�߂�����

			m_bPreMoveR = false;
			m_bMove = true;		//��������
			m_bMoveR = true;	//�E�ɕ����Ă��Ԃɂ���

			m_nStateMoveRCounter = 0;
		}
		else
		{
			m_nStateMoveRCounter++;
		}
	}

	if (m_bPreMoveL == true)
	{//���ɕ�����������Ƃ�

		if (m_nStateMoveLCounter >= DELEY_CNT)
		{//��莞�Ԍo�߂�����

			m_bPreMoveL = false;
			m_bMove = true;		//��������
			m_bMoveL = true;	//�E�ɕ����Ă��Ԃɂ���

			m_nStateMoveLCounter = 0;
		}
		else
		{
			m_nStateMoveLCounter++;
		}
	}

	if (m_bMoveR == true)
	{//�E�ɕ����Ă�Ƃ�

		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
	}
	else if (m_bMoveL == true)
	{//���ɕ����Ă�Ƃ�

		m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
	}

	if (m_bPreStopR == true)
	{//�~�܂鏀������Ƃ�

		if (m_nStateStopRCounter >= DELEY_CNT)
		{
			m_bMove = false;
			m_bMoveR = false;	//�E�ɕ����Ă��Ԃɂ���
			m_bPreStopR = false;

			m_nStateStopRCounter = 0;		//�~�܂�܂ł̎��ԏ�����
		}
		else
		{
			m_nStateStopRCounter++;			//�~�܂�܂ł̎��ԉ��Z
		}
	}
	else if (m_bPreStopL == true)
	{//�~�܂鏀������Ƃ�

		if (m_nStateStopLCounter >= DELEY_CNT)
		{
			m_bMove = false;
			m_bMoveL = false;	//�E�ɕ����Ă��Ԃɂ���
			m_bPreStopL = false;

			m_nStateStopLCounter = 0;		//�~�܂�܂ł̎��ԏ�����
		}
		else
		{
			m_nStateStopLCounter++;			//�~�܂�܂ł̎��ԉ��Z
		}
	}

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//�����ĂȂ��Ƃ�

		m_bMove = false;		//�����ĂȂ���Ԃɂ���
	}
}

//==============================================================
//�G�̃L�[�{�[�h�̃W�����v���쏈��(��O��)
//==============================================================
void CEnemy::ControlFrontKeyboardJump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CPlayer *pPlayer = CGame::GetPlayer();		//�v���C���[�̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();

	if (pInputKeyboard->GetPress(DIK_SPACE) == true && m_bJump == false && m_move.y <= JUMP_HEIGHT && pPlayer->GetIsJump() == true)
	{//SPACE�L�[����������

		m_bPreJump = true;		//�W�����v������Ԃɂ���

		m_nJumpLengthCounter++;		//�W�����v�����t���[�����擾

		pDebugProc->Print("\n�ҋ@��\n");

	}

	if (m_bPreJump == true)
	{//�W�����v������Ԃ̂Ƃ�

		if (m_nStateJumpCounter >= DELEY_CNT)
		{//��莞�Ԍo�߂�����

			if (m_nJumpLengthCounter <= 0)
			{//�W�����v�����������܂Ŕ�񂾂�

				//�W�����v������Ԃɂ���
				m_bJump = true;
				m_bLand = false;

				m_nJumpLengthCounter = 0;		//�W�����v�������ԃ��Z�b�g
				m_nStateJumpCounter = 0;		//�W�����v����܂ł̃J�E���^�[���Z�b�g
				m_bPreJump = false;				//�W�����v�̏����I��
			}
			else
			{
				m_nJumpLengthCounter--;		//�W�����v���鎞�Ԍ��Z

				//�W�����v����
				m_move.y += ADD_MOVE_Y;

				pDebugProc->Print("\n�W�����v��\n");

			}

			//if (m_move.y >= JUMP_HEIGHT)
			//{
			//	//�W�����v������Ԃɂ���
			//	m_bJump = true;
			//	m_bLand = false;
			//}
		}
		else
		{
			m_nStateJumpCounter++;		//�W�����v����܂ł̃J�E���^�[���Z

		}
	}

	if (m_move.y >= JUMP_HEIGHT ||
		(m_bJump == true && (m_move.x <= 7.0f && m_move.x >= -7.0f)) ||
		(m_bDash == true && (m_move.x <= 7.0f && m_move.x >= -7.0f)))
	{
		//�ړ��ʉ��Z
		m_move.y -= MOVE_Y;

		if (m_move.y <= 0.0f)
		{//���n������

			m_bDash = false;
		}
	}
}

//==============================================================
//�G�̃L�[�{�[�h�̃_�b�V�����쏈��(��O��)
//==============================================================
void CEnemy::ControlFrontKeyboardDash(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾

	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//�E

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
				m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
				m_bDash = true;			//�_�b�V��������Ԃɂ���
				m_bJump = true;			//�W�����v������Ԃɂ���

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//�_�b�V���񐔉��Z

			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
				m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
				m_bDash = true;			//�_�b�V��������Ԃɂ���
				m_bJump = true;			//�W�����v������Ԃɂ���

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//�_�b�V���񐔉��Z

			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.z = 0.0f;		//�ړ��ʃ��Z�b�g
			m_bDash = true;			//�_�b�V��������Ԃɂ���
			m_bJump = true;			//�W�����v������Ԃɂ���

			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//��
		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
				m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
				m_bDash = true;			//�_�b�V��������Ԃɂ���
				m_bJump = true;			//�W�����v������Ԃɂ���

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//�_�b�V���񐔉��Z

			}
		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��
			if (pInputKeyboard->GetTrigger(DIK_J) == true)
			{
				m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
				m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
				m_bDash = true;			//�_�b�V��������Ԃɂ���
				m_bJump = true;			//�W�����v������Ԃɂ���

				m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FRONT_DASH_MOVE;
				m_move.y += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * FRONT_DASH_MOVE;

				m_nDashCounter++;		//�_�b�V���񐔉��Z

			}
		}
		else if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.z = 0.0f;		//�ړ��ʃ��Z�b�g
			m_bDash = true;			//�_�b�V��������Ԃɂ���
			m_bJump = true;			//�W�����v������Ԃɂ���

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}
	}
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//��
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
			m_bDash = true;			//�_�b�V��������Ԃɂ���
			m_bJump = true;			//�W�����v������Ԃɂ���

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_UP) * FRONT_DASH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_UP) * FRONT_DASH_MOVE;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}
	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//��
		if (pInputKeyboard->GetTrigger(DIK_J) == true)
		{
			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.y = 0.0f;		//�ړ��ʃ��Z�b�g
			m_bDash = true;			//�_�b�V��������Ԃɂ���
			m_bJump = true;			//�W�����v������Ԃɂ���

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_DOWN) * FRONT_DASH_MOVE;
			m_move.y += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_DOWN) * FRONT_DASH_MOVE;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_J) == true)
	{//J�L�[�������������Ƃ�

		if (m_rot.y > 0)
		{//�v���C���[�̌���������������

			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.z = 0.0f;		//�ړ��ʃ��Z�b�g

			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}
		else if (m_rot.y <= 0)
		{
			m_move.x = 0.0f;		//�ړ��ʃ��Z�b�g
			m_move.z = 0.0f;		//�ړ��ʃ��Z�b�g

			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_DASH_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

			m_nDashCounter++;		//�_�b�V���񐔉��Z

		}

		m_bDash = true;		//�_�b�V��������Ԃɂ���
		m_bJump = true;		//�W�����v������Ԃɂ���
	}
}

//==============================================================
//���[�V�����Ǘ�����
//==============================================================
void CEnemy::MotionManager(void)
{
	//if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	//{//�����Ă� && �ҋ@���

	//	//��������
	//	m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	//}
	//else if (m_pMotion->IsFinish() == true && m_bAction == true)
	//{//�U�����I�������

	//	m_bAction = false;		//�U�����ĂȂ���Ԃɂ���
	//}
	//else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
	//	(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true && m_bAction == false))
	//{//���[�V�������I��������

	//	//�ҋ@��Ԃɖ߂�
	//	m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	//}
}

//==============================================================
//�����̕␳����
//==============================================================
void CEnemy::RotCorrection(void)
{
	//�����̍��������߂�
	m_fRotDiff = m_fRotDest - m_rot.y;

	//�ڕW�̕����܂ł̍������C��
	if (m_fRotDiff < -D3DX_PI)
	{
		m_fRotDiff += D3DX_PI * 2;
	}
	else if (m_fRotDiff > D3DX_PI)
	{
		m_fRotDiff -= D3DX_PI * 2;
	}

	//��������
	m_rot.y += m_fRotDiff * 0.1f;

	//���݂̕����C��
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
//��ʊO���菈��
//==============================================================
void CEnemy::Screen(void)
{
	//if (m_pos.y < 0.0f)
	//{//��ʉ��ɏo����

	//	m_move.y = 0.0f;
	//	m_pos.y = 0.0f;

	//	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾

	//	if (pInputKeyboard->GetPress(DIK_SPACE) == false)
	//	{
	//		m_bLand = true;		//���n����
	//		m_bJump = false;	//�W�����v���ĂȂ�
	//	}

	//	m_nDashCounter = 0;		//�_�b�V�������Z�b�g

	//	//m_state = STATE_NONE;		//�ʏ��Ԃɂ���
	//}
}

//==============================================================
//�G�̕`�揈��
//==============================================================
void CEnemy::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetInstance()->GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X

	//���[���h�}�g���b�N�X��������
	D3DXMatrixIdentity(&m_mtxWorld);

	//�����𔽉f
	D3DXMatrixRotationYawPitchRoll(&mtxRot, m_rot.y, m_rot.x, m_rot.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxRot);

	//�ʒu�𔽉f
	D3DXMatrixTranslation(&mtxTrans, m_pos.x, m_pos.y, m_pos.z);
	D3DXMatrixMultiply(&m_mtxWorld, &m_mtxWorld, &mtxTrans);

	//���[���h�}�g���b�N�X�̐ݒ�
	pDevice->SetTransform(D3DTS_WORLD, &m_mtxWorld);

	for (int nCntEnemy = 0; nCntEnemy < PARTS_MAX; nCntEnemy++)
	{
		//�G�̕`��
		m_apModel[nCntEnemy]->Draw();
	}
}

//==============================================================
//���f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CEnemy::LoadFile(void)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[MAX_STR];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(FILE_ENEMY, "r");

	if (pFile != NULL)
	{//�t�@�C�����J�����ꍇ

		while (strcmp(&aString[0], "CHARACTERSET") != 0)
		{//[CHARACTERSET]����܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
		}

		if (strcmp(&aString[0], "CHARACTERSET") == 0)
		{//[CHARACTERSET]��������

			while (strcmp(&aString[0], "END_CHARACTERSET") != 0)
			{//[END_CHARACTERSET]������܂ł̊�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				if (strcmp(&aString[0], "PARTSSET") == 0)
				{//[PARTSSET]��������

					while (strcmp(&aString[0], "END_PARTSSET") != 0)
					{//[END_PARTSSET]������܂ł̊�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						if (strcmp(&aString[0], "INDEX") == 0)
						{//�p�[�cNo.

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nIndex);			//�p�[�cNo.�ǂݍ���

						}
						else if (strcmp(&aString[0], "PARENT") == 0)
						{//�e���

							fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
							fscanf(pFile, "%d", &nParent);			//�e�ԍ��ǂݍ���

							if (nParent == -1)
							{//�e�����Ȃ�������

								m_apModel[nIndex]->SetParent(NULL);		//NULL������
							}
							else
							{//�e��������

								m_apModel[nIndex]->SetParent(m_apModel[nParent]);		//�e�ԍ������
							}
						}
						else if (strcmp(&aString[0], "POS") == 0)
						{//�ʒu���

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &pos.x);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.y);		//�ʒu�ǂݍ���
							fscanf(pFile, "%f", &pos.z);		//�ʒu�ǂݍ���

							m_apModel[nIndex]->SetPosition(pos);		//�ʒu�ݒ�
							m_apModel[nIndex]->SetDefaultPosition(pos);	//�����ʒu�ݒ�

						}
						else if (strcmp(&aString[0], "ROT") == 0)
						{//�������

							fscanf(pFile, "%s", &aString[0]);	//�����ǂݍ���

							fscanf(pFile, "%f", &rot.x);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.y);		//�����ǂݍ���
							fscanf(pFile, "%f", &rot.z);		//�����ǂݍ���

							m_apModel[nIndex]->SetRotation(rot);		//�����ݒ�
							m_apModel[nIndex]->SetDefaultRotation(rot);	//���������ݒ�
						}
					}
				}
			}
		}

		//�t�@�C������
		fclose(pFile);
	}
}