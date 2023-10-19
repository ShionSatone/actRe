//==============================================================
//
//�v���C���[����[playerModel.cpp]
//Author:����������
//
//==============================================================
#include "player.h"
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
//#include "score.h"

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
#define FILE_HUMAN			"data\\TEXT\\motion_player.txt"		//�v���C���[���f���̃e�L�X�g

#define HIT_CNT				(60 * 2)	//�U��������܂ł̃J�E���g��
#define DAMAGE_CNT			(9)			//�_���[�W�J�E���g��
#define APP_CNT				(100)		//�_�Ŏ���
#define STEP_CNT			(25)		//�������̃J�E���^�[

//�ÓI�����o�ϐ��錾
char *CPlayer::m_apFileName[PARTS_MAX] =
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
CPlayer::CPlayer()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����p�̈ʒu
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�l�Ԃ̈ʒu�ۑ��p
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̈ʒu�ۑ��p
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���
	m_pMotion = NULL;

	m_nPressCounter = 0;	//�L�[���������t���[����

	m_bJump = false;		//�W�����v������
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_bDash = false;		//�_�b�V��������

	m_fRotDest = 0.0f;		//�ڕW
	m_fRotDiff = 0.0f;		//����

	m_nDashCounter = 0;		//�_�b�V��������

	//m_particleType = PARTICLETYPE_WATER;	//�p�[�e�B�N���̎��
	m_nType = 1;		//���Ԗڂ̃p�[�e�B�N����
	m_nParticleLife = 50;			//�p�[�e�B�N���̎���
	m_state = STATE_NONE;			//���
	m_nCntDamage = 0;				//�_���[�W�J�E���^�[
	m_nCntHit = HIT_CNT;			//�U��������܂ł̃J�E���^�[
	m_bPad = false;					//�p�b�h�̃X�e�B�b�N��|���Ă邩
	m_nCntSand = STEP_CNT;			//���̃p�[�e�B�N���J�E���^�[

}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CPlayer::CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;									//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�O��̈ʒu
	m_posSave = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�����p�̈ʒu
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�l�Ԃ̈ʒu�ۑ��p
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̈ʒu�ۑ��p
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l
	m_rot = rot;		//����

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_pMotion = NULL;		//���[�V�����̏��
	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���

	m_nPressCounter = 0;	//�L�[���������t���[����

	m_bJump = false;		//�W�����v������
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_bDash = false;		//�_�b�V��������

	m_fRotDest = 0.0f;	//�ڕW
	m_fRotDiff = 0.0f;	//����

	m_nDashCounter = 0;		//�_�b�V��������

	//m_particleType = PARTICLETYPE_WATER;	//�p�[�e�B�N���̎��
	m_nType = 1;				//���Ԗڂ̃p�[�e�B�N����
	m_nParticleLife = 50;		//�p�[�e�B�N���̎���
	m_state = STATE_NONE;		//���
	m_nCntDamage = 0;			//�_���[�W�J�E���^�[
	m_nCntHit = HIT_CNT;		//�U��������܂ł̃J�E���^�[
	m_nCntMove = STEP_CNT;		//�����̃J�E���^�[
	m_bPad = false;				//�p�b�h�̃X�e�B�b�N��|���Ă邩
	m_nCntSand = STEP_CNT;		//���̃p�[�e�B�N���J�E���^�[
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPlayer::~CPlayer()
{

}

//==============================================================
//�v���C���[�̐�������
//==============================================================
CPlayer *CPlayer::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayer *pPlayerModel = NULL;

	if (pPlayerModel == NULL)
	{//���������g�p����ĂȂ�������

		//�v���C���[�̐���
		pPlayerModel = new CPlayer(pos, rot);
	}

	//����������
	pPlayerModel->Init();

	return pPlayerModel;
}

//==============================================================
//�v���C���[�̏���������
//==============================================================
HRESULT CPlayer::Init(void)
{
	//CLife *pLife = CGame::GetLife();

	m_fRotDest = m_rot.y;

	m_posKeepFish = D3DXVECTOR3(0.0f, -5000.0f, 0.0f);		//�����̏����ʒu�ݒ�

	//�v���C���[�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���[�V�����̏������E����
	m_pMotion = m_pMotion->Create(m_pMotion->MOTIONTEXT_PLAYER);
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//���f���̃t�@�C���ǂݍ���
	CPlayer::LoadFile();

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

	CObject::SetType(CObject::TYPE_PLAYER);

	return S_OK;
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void CPlayer::Uninit(void)
{
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		if (m_apModel[nCntPlayer] != NULL)
		{//�g�p����Ă�Ƃ�

			//�I������
			m_apModel[nCntPlayer]->Uninit();
			m_apModel[nCntPlayer] = NULL;
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
//�v���C���[�̍X�V����
//==============================================================
void CPlayer::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetInstance()->GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾
	//CGame *pGame = CScene::GetGame();

	//�O��̈ʒu�X�V
	m_posOld = m_pos;

	//��O���̍X�V����
	CPlayer::UpdateFront();

	//���[�V�����̍X�V����
	m_pMotion->Update();

	//�f�o�b�O�\��
	pDebugProc->Print("\n�v���C���[�̈ʒu (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
	pDebugProc->Print("�v���C���[�̈ړ��� (%f, %f, %f)\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("�v���C���[�̌���   (%f, %f, %f)\n", m_rot.x, m_rot.y, m_rot.z);
}

//==============================================================
//��O�̍X�V����
//==============================================================
void CPlayer::UpdateFront(void)
{
	//CLife *pLife = CGame::GetLife();
	CSound *pSound = CManager::GetInstance()->GetSound();
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾

	//�v���C���[�̑���
	CPlayer::ControlFrontKeyboard();
	//CPlayer::ControlHumanPad();

	//�����炷
	if (m_bMove == true && m_bJump == false)
	{//�����Ă�Ƃ� && �W�����v���ĂȂ�

		if ((m_nCntMove % STEP_CNT) == 0)
		{//��莞�Ԃ�������

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_STEP);
		}
	}
	else
	{
		m_nCntMove = STEP_CNT;
	}

	m_nCntMove++;		//�����炷�J�E���^�[���Z

	//�ʒu�X�V
	m_pos += m_move;

	//��ԍX�V
	CPlayer::UpdateState();

	//�����蔻��
	if (CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max) == true)
	{//���n������

		m_nDashCounter = 0;		//�_�b�V�������Z�b�g

		//�Ō�ɒ��n�����ʒu
		if (m_pos.x >= 7715.0f && m_pos.x <= 8460.0f)
		{
			m_posSave = D3DXVECTOR3(7715.0f, 130.0f, m_pos.z);
		}
		else
		{
			m_posSave = m_pos;
		}

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

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;

	//�����̕␳
	CPlayer::RotCorrection();

	//��ʊO����
	CPlayer::Screen();

	//���[�V�����Ǘ�
	CPlayer::MotionManager();
}

//==============================================================
//��ԍX�V����
//==============================================================
void CPlayer::UpdateState(void)
{
	switch (m_state)
	{
	case STATE_NONE:		//�ʏ���

		break;

	case STATE_ATTACK:		//�U�����

		break;

	case STATE_DAMAGE:		//�_���[�W���

		m_nCntDamage--;		//�_���[�W���Ԍ��Z
		m_nCntHit--;		//�U��������܂ł̃J�E���^�[���Z

		if (m_nCntDamage <= 0)
		{//�_���[�W���Ԃ��I�������

			m_state = CObject::STATE_NONE;

			//��Ԑݒ�
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetState(m_state);		//�ʏ��Ԃɂ���

			}
		}

		break;

	case STATE_APPEAR:		//�_�ŏ��

		m_nCntDamage--;		//�_���[�W���Ԍ��Z

		if ((m_nCntDamage % 3) == 0)
		{//��莞�Ԍo������

			//�\���ؑ�
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetDisp();

			}
		}

		if (m_nCntDamage <= 0)
		{//�_���[�W���Ԃ��I�������

			m_state = CObject::STATE_NONE;		//�ʏ��Ԃɂ���

			//��Ԑݒ�
			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				m_apModel[nCntPlayer]->SetState(m_state);		//��Ԑݒ�

			}
		}

		break;

	case STATE_DEATH:		//���S���

		m_nCntDamage = APP_CNT;

		//CScore *pScore = CGame::GetScore();		//�X�R�A�̏��
		CFade *pFade = CManager::GetInstance()->GetFade();		//�t�F�[�h�̏��擾

		//�X�R�A�ݒ�
		//CManager::SetNumScore(pScore->Get());

		//���U���g�̔���
		//CManager::SetResult(false);

		//���U���g
		pFade->SetFade(CScene::MODE_RESULT);

		break;
	}
}

//==============================================================
//���[�V�����Ǘ�����
//==============================================================
void CPlayer::MotionManager(void)
{
	if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	{//�����Ă� && �ҋ@���

		//��������
		m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	}
	//else if (m_pMotion->IsFinish() == true && m_bAction == true)
	//{//�U�����I�������

	//	m_bAction = false;		//�U�����ĂȂ���Ԃɂ���
	//}
	else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
		(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true))
	{//���[�V�������I��������

		//�ҋ@��Ԃɖ߂�
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}
}

//==============================================================
//�����̕␳����
//==============================================================
void CPlayer::RotCorrection(void)
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
//�v���C���[�̃L�[�{�[�h���쏈��(��O��)
//==============================================================
void CPlayer::ControlFrontKeyboard(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	//�ړ�����
	CPlayer::ControlFrontKeyboardMove();

	//�W�����v����
	CPlayer::ControlFrontKeyboardJump();

	//�_�b�V������
	if (m_nDashCounter < MAX_DASH)
	{//�ő�W�����v�������̏ꍇ

		CPlayer::ControlFrontKeyboardDash();
	}
}

//==============================================================
//�v���C���[�̃L�[�{�[�h�̈ړ����쏈��(��O��)
//==============================================================
void CPlayer::ControlFrontKeyboardMove(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//�E
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

		m_bMove = true;		//��������
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//��
		m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

		m_bMove = true;		//��������
	}

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//�����ĂȂ��Ƃ�

		m_bMove = false;		//�����ĂȂ���Ԃɂ���
	}
}

//==============================================================
//�v���C���[�̃L�[�{�[�h�̃W�����v���쏈��(��O��)
//==============================================================
void CPlayer::ControlFrontKeyboardJump(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	if (pInputKeyboard->GetPress(DIK_SPACE) == true && m_bJump == false && m_move.y <= JUMP_HEIGHT)
	{
		//�W�����v����
		m_move.y += ADD_MOVE_Y;

		m_nPressCounter++;		//�t���[�������Z

		if (m_move.y >= JUMP_HEIGHT)
		{
			//�W�����v������Ԃɂ���
			m_bJump = true;
			m_bLand = false;
		}
	}

	if (pInputKeyboard->GetRelease(DIK_SPACE) == true && m_bJump == false)
	{
		//�W�����v������Ԃɂ���
		m_bJump = true;
		m_bLand = false;
	}

	//�W�����v
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{//SPACE�L�[�������Ă��� && �W�����v���ĂȂ�������

		//BGM�Đ�
		pSound->Play(pSound->SOUND_LABEL_SE_JUMP);

		//���[�V�����̐ݒ�
		//m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);
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
//�v���C���[�̃L�[�{�[�h�̃_�b�V�����쏈��(��O��)
//==============================================================
void CPlayer::ControlFrontKeyboardDash(void)
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
//�v���C���[�̃p�b�h���쏈��(�l��)
//==============================================================
void CPlayer::ControlHumanPad(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInstance()->GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInstance()->GetInputJoyPad();			//�p�b�h�̏��
	CCamera *pCamera = CManager::GetInstance()->GetCamera();		//�J�����̏��擾
	CSound *pSound = CManager::GetInstance()->GetSound();

	//�ړ�
	if (pInputJoyPad->GetPressLX(0).x > 0.0f)
	{//�E
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;

		m_bMove = true;		//��������
	}
	else if (pInputJoyPad->GetPressLX(0).x < 0.0f)
	{//��

		m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * FRONT_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;

		m_bMove = true;		//��������
	}

	if ((m_move.x <= STOP_MOVE && m_move.x >= -STOP_MOVE) && (m_move.z <= STOP_MOVE && m_move.z >= -STOP_MOVE))
	{//�����ĂȂ��Ƃ�

		m_bMove = false;		//�����ĂȂ���Ԃɂ���
	}

	if (CManager::GetInstance()->GetMode() == CScene::MODE_GAME)
	{
		//�W�����v
		if (pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_B, 0) == true && m_bJump == false)
		{//B�{�^���������Ă��� && �W�����v���ĂȂ�������

			//�W�����v����
			m_move.y = JUMP_HEIGHT;

			//�W�����v������Ԃɂ���
			m_bJump = true;
			m_bLand = false;

			//BGM�Đ�
			pSound->Play(pSound->SOUND_LABEL_SE_JUMP);

			//���[�V�����̐ݒ�
			m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);
		}
	}

	if (pInputJoyPad->GetPressRX(0).y == 0.0f && pInputJoyPad->GetPressRX(0).x == 0.0f)
	{
		m_bPad = false;		//�X�e�B�b�N��|���ĂȂ���Ԃɂ���
	}
}

//==============================================================
//��ʊO���菈��
//==============================================================
void CPlayer::Screen(void)
{
	if (m_pos.y <= -6000.0f)
	{//��ԉ��܂ōs������

		CFade *pFade = CManager::GetInstance()->GetFade();			//�t�F�[�h�̏��擾

		//�Q�[�����
		pFade->SetFade(CScene::MODE_RESULT);
	}

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

	//if (m_pos.y < -200.0f && 
	//	m_pos.x > -1000.0f && m_pos.x < 9700.0f)
	//{//��ʉ��ɏo����

	//	if (m_rot.y < 0)
	//	{
	//		m_pos = D3DXVECTOR3(m_posSave.x - 100.0f, m_posSave.y, m_posSave.z);
	//	}
	//	else if (m_rot.y > 0)
	//	{
	//		m_pos = D3DXVECTOR3(m_posSave.x + 100.0f, m_posSave.y, m_posSave.z);
	//	}

	//	m_bLand = true;		//���n����
	//	m_bJump = false;	//�W�����v���ĂȂ�

	//	m_state = STATE_NONE;		//�ʏ��Ԃɂ���

	//	//m_nCntDamage = 0;

	//	//CPlayer::Hit();
	//}
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void CPlayer::Draw(void)
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

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�v���C���[�̕`��
		m_apModel[nCntPlayer]->Draw();
	}
}

//==============================================================
//�v���C���[�̃q�b�g����
//==============================================================
void CPlayer::Hit(void)
{
	CSound *pSound = CManager::GetInstance()->GetSound();
	int nLife = 0;

	if (m_state != CObject::STATE_DAMAGE && m_state != CObject::STATE_APPEAR && m_nCntDamage <= 0)
	{
		//BGM�Đ�
		pSound->Play(pSound->SOUND_LABEL_SE_DAMAGE001);

		//�̗͌��炷
		//pLife->SetNum(-40);

		//�����擾
		//nLife = pLife->GetMax();

		if (nLife > 0)
		{//�܂��������c���Ă���

			m_state = CObject::STATE_APPEAR;

			m_nCntDamage = HIT_CNT;			//�_���[�W��Ԃ�ۂ��Ԑݒ�
			m_nCntHit = HIT_CNT;				//�U��������܂ł̃J�E���^�[

			for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
			{
				//�v���C���[�̐F�ݒ�
				m_apModel[nCntPlayer]->SetColor(D3DXCOLOR(0.0f, 0.0f, 0.0f, 0.0f));
			}
		}
		else if (nLife <= 0)
		{//�������Ȃ�������

			m_state = CObject::STATE_DEATH;

			//�p�[�e�B�N������
			//CParticle::Create(m_pos, D3DXCOLOR(0.1f, 0.4f, 0.5f, 1.0f), PARTICLETYPE_ENEMY, 30, 40);
		}

		//��Ԑݒ�
		for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
		{
			m_apModel[nCntPlayer]->SetState(m_state);		//�_���[�W��Ԃɂ���
		}
	}
}

//==============================================================
//���f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CPlayer::LoadFile(void)
{
	FILE *pFile;				//�t�@�C���|�C���^
	char aString[MAX_STR];		//�����ǂݍ���
	int nIndex = 0, nParent = 0;	//�p�[�cNo.,�e�ԍ�
	D3DXVECTOR3 pos, rot;

	//�t�@�C���J��
	pFile = fopen(FILE_HUMAN, "r");

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