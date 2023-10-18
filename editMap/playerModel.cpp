//==============================================================
//
//�v���C���[����[playerModel.cpp]
//Author:����������
//
//==============================================================
#include "playerModel.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "modelHierarchy.h"
#include "input.h"
#include "motion.h"
#include "camera.h"
#include "debugproc.h"

//�}�N����`
#define POS					(10.0f)		//pos�����l
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x
#define MOVE_Y				(1.0f)		//�ړ���Y
#define JUMP_HEIGHT			(15.0f)		//�W�����v�̍���
#define MAX_STR				(128)		//�����̍ő吔
#define PLAYER_MOVE			(0.5f)		//�v���C���[�̈ړ���
#define FILE_HUMAN			"data\\TEXT\\motion_weapon.txt"		//�v���C���[���f���̃e�L�X�g

//�ÓI�����o�ϐ��錾
bool CPlayerModel::m_bStart = false;		//���s���Ă邩�ǂ���
char *CPlayerModel::m_apFileName[PARTS_MAX] =
{
	"data\\MODEL\\player\\00_body.x",
	"data\\MODEL\\player\\01_head.x",
	"data\\MODEL\\player\\02_hair.x",
	"data\\MODEL\\player\\03_LU_arm.x",
	"data\\MODEL\\player\\04_LD_arm.x",
	"data\\MODEL\\player\\05_L_hand.x",
	"data\\MODEL\\player\\06_RU_arm.x",
	"data\\MODEL\\player\\07_RD_arm.x",
	"data\\MODEL\\player\\08_R_hand.x",
	"data\\MODEL\\player\\09_waist.x",
	"data\\MODEL\\player\\10_skirt.x",
	"data\\MODEL\\player\\11_LU_leg.x",
	"data\\MODEL\\player\\12_LD_leg.x",
	"data\\MODEL\\player\\13_L_shoe.x",
	"data\\MODEL\\player\\14_RU_leg.x",
	"data\\MODEL\\player\\15_RD_leg.x",
	"data\\MODEL\\player\\16_R_shoe.x",
	"data\\MODEL\\player\\17_fish.x",
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CPlayerModel::CPlayerModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�l�Ԃ̈ʒu�ۑ��p
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̈ʒu�ۑ��p
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���
	m_bJump = false;		//�W�����v������
	m_pMotion = NULL;
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_bAction = false;		//�U�����Ă邩�̔���
	m_fRotDest = 0.0f;	//�ڕW
	m_fRotDiff = 0.0f;	//����
	m_Type = PLAYERTYPE_HUMAN;		//�l�Ԃ̏�Ԃɂ���
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CPlayerModel::CPlayerModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_posOld = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�O��̈ʒu
	m_posKeepHuman = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�l�Ԃ̈ʒu�ۑ��p
	m_posKeepFish = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	//�����̈ʒu�ۑ��p
	m_move = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ړ���
	m_max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ő�l
	m_min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//���f���̍ŏ��l
	m_rot = rot;		//����

	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		m_apModel[nCntPlayer] = NULL;		//�v���C���[(�p�[�c)�ւ̃|�C���^
	}

	m_nNumModel = 0;		//�v���C���[(�p�[�c)�̑���
	m_bJump = false;		//�W�����v������
	m_pMotion = NULL;
	m_bMove = false;		//�����Ă邩
	m_bLand = true;			//���n����
	m_bAction = false;		//�U�����Ă邩�̔���
	m_fRotDest = 0.0f;	//�ڕW
	m_fRotDiff = 0.0f;	//����

	m_Type = PLAYERTYPE_HUMAN;		//�l�Ԃ̏�Ԃɂ���
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CPlayerModel::~CPlayerModel()
{

}

//==============================================================
//�v���C���[�̐�������
//==============================================================
CPlayerModel *CPlayerModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CPlayerModel *pPlayerModel = NULL;

	if (pPlayerModel == NULL)
	{//���������g�p����ĂȂ�������

		//�v���C���[�̐���
		pPlayerModel = new CPlayerModel(pos, rot);
	}

	//����������
	pPlayerModel->Init(pos, rot);

	//��ނ̐ݒ�
	pPlayerModel->SetType(CObject::TYPE_PLAYER);

	return pPlayerModel;
}

//==============================================================
//�v���C���[�̏���������
//==============================================================
HRESULT CPlayerModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	//�ʒu�̐ݒ�
	m_pos = pos;

	//�����̐ݒ�
	m_rot = rot;

	m_posKeepFish = D3DXVECTOR3(0.0f, -5000.0f, 0.0f);		//�����̏����ʒu�ݒ�

	//�v���C���[�̐����i�S�p�[�c���j
	for (int nCntModel = 0; nCntModel < PARTS_MAX; nCntModel++)
	{
		m_apModel[nCntModel] = m_apModel[nCntModel]->Create(D3DXVECTOR3(0.0f, 0.0f, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f), m_apFileName[nCntModel]);
	}

	//���[�V�����̏������E����
	m_pMotion = m_pMotion->Create();
	m_pMotion->SetModel(&m_apModel[0], PARTS_MAX);
	m_pMotion->Init();

	//���f���̃t�@�C���ǂݍ���
	CPlayerModel::LoadFile();

	//�ő�l�E�ŏ��l���
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		//�ő�lY
		if ((nCntPlayer <= PARTS_BODY && nCntPlayer <= PARTS_HEAD) ||
			(nCntPlayer <= PARTS_LEG_R && nCntPlayer <= PARTS_FOOT_R))
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

	return S_OK;
}

//==============================================================
//�v���C���[�̏I������
//==============================================================
void CPlayerModel::Uninit(void)
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
void CPlayerModel::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾

	if (pInputKeyboard->GetTrigger(DIK_F4) == true)
	{//F4�������ꂽ�Ƃ�

		//�v���C���[�̎�ޓ���ւ�
		m_Type = m_Type ? PLAYERTYPE_HUMAN : PLAYERTYPE_GOLDFISH;

		if (m_Type == PLAYERTYPE_HUMAN)
		{//�l�ԂɂȂ�����

			m_posKeepFish = m_pos;		//�����̈ʒu�ۑ����Ă���
			m_pos = m_posKeepHuman;		//�n��̈ʒu�ɖ߂�
			m_rot = D3DXVECTOR3(0.0f, 0.5f * -D3DX_PI, 0.0f);
			m_fRotDest = 0.5f * -D3DX_PI;
			pCamera->SetPositionVY(m_pos.y + 189.0f + sinf(m_rot.x) * -300.0f);		//�J�����̈ʒu�ݒ�
			pCamera->SetPositionRY(m_pos.y + 168.0f + sinf(m_rot.x) * -10.0f);		//�J�����̈ʒu�ݒ�

		}
		else if(m_Type == PLAYERTYPE_GOLDFISH)
		{//�����ɂȂ�����

			m_posKeepHuman = m_pos;		//�l�Ԃ̈ʒu�ۑ����Ă���
			m_pos = m_posKeepFish;		//�����̈ʒu�ɖ߂�
			m_rot = D3DXVECTOR3(0.0f, 1.0f * D3DX_PI, 0.0f);
			m_fRotDest = 1.0f * D3DX_PI;
			pCamera->SetPositionVY(m_pos.y + 50.0f + sinf(m_rot.x) * 300.0f);		//�J�����̈ʒu�ݒ�
			pCamera->SetPositionRY(m_pos.y + 50.0f + sinf(m_rot.x) * 300.0f);		//�J�����̈ʒu�ݒ�
		}
	}

	//�O��̈ʒu�X�V
	m_posOld = m_pos;

	if (pInputKeyboard->GetTrigger(DIK_F5) == true)
	{//F5�L�[�������ꂽ��

		m_bStart = m_bStart ? false : true;
	}

	if(m_bStart == true)
	{//���s���Ă�Ƃ�

		switch (m_Type)
		{
		case PLAYERTYPE_HUMAN:		//�l��

			//�l�Ԃ̍X�V����
			CPlayerModel::UpdateHuman();

			pDebugProc->Print("\n-----[�l�Ԃ̎p]-----\n");
			pDebugProc->Print("\n�`�`[�n��G���A]�`�`\n");

			break;

		case PLAYERTYPE_GOLDFISH:	//����

			//�����̍X�V����
			CPlayerModel::UpdataFish();

			pDebugProc->Print("\n-----[�����̎p]-----\n");
			pDebugProc->Print("\n�`�`[�����G���A]�`�`\n");

			break;
		}
	}

	//���[�V�����̍X�V����
	m_pMotion->Update();

	//�f�o�b�O�\��
	pDebugProc->Print("\n�v���C���[�̈ʒu (%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
	/*pDebugProc->Print("�v���C���[�̈ړ��� (%f, %f, %f)\n", m_move.x, m_move.y, m_move.z);
	pDebugProc->Print("�v���C���[�̌���   (%f, %f, %f)\n", m_rot.x, m_rot.y, m_rot.z);*/
}

//==============================================================
//�l�Ԃ̍X�V����
//==============================================================
void CPlayerModel::UpdateHuman(void)
{
	//�v���C���[�̑���
	CPlayerModel::ControlHuman();

	//�ړ��ʉ��Z
	m_move.y -= MOVE_Y;

	//�ʒu�X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�����蔻��
	for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_min, m_max);
	}

	//�����̕␳
	CPlayerModel::RotCorrection();

	//��ʊO����
	CPlayerModel::Screen();

	if (m_bMove == true && m_pMotion->GetType() == m_pMotion->MOTIONTYPE_NEUTRAL)
	{//�����Ă� && �ҋ@���

		//��������
		m_pMotion->Set(m_pMotion->MOTIONTYPE_MOVE);
	}
	else if (m_pMotion->IsFinish() == true && m_bAction == true)
	{//�U�����I�������

		m_bAction = false;		//�U�����ĂȂ���Ԃɂ���
	}
	else if ((m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_pMotion->IsFinish() == true) ||
		(m_pMotion->GetType() != m_pMotion->MOTIONTYPE_NEUTRAL && m_bMove == false && m_bJump == false && m_bLand == true && m_bAction == false))
	{//���[�V�������I��������

		//�ҋ@��Ԃɖ߂�
		m_pMotion->Set(m_pMotion->MOTIONTYPE_NEUTRAL);
	}
}

//==============================================================
//�����̍X�V����
//==============================================================
void CPlayerModel::UpdataFish(void)
{
	//�v���C���[�̑���
	CPlayerModel::ControlGoldFish();

	//�ʒu�X�V
	m_pos += m_move;

	//�ړ��ʂ��X�V
	m_move.x += (0.0f - m_move.x) * 0.1f;
	m_move.z += (0.0f - m_move.z) * 0.1f;

	//�����蔻��
	/*for (int nCntPlayer = 0; nCntPlayer < PARTS_MAX; nCntPlayer++)
	{
		CObjectX::Collision(&m_pos, &m_posOld, &m_move, m_apModel[nCntPlayer]->GetSizeMin(), m_apModel[nCntPlayer]->GetSizeMax());
	}*/

	//�����̕␳
	CPlayerModel::RotCorrection();

	//��ʊO����
	CPlayerModel::Screen();
}

//==============================================================
//�����̕␳����
//==============================================================
void CPlayerModel::RotCorrection(void)
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
//�v���C���[�̑��쏈��(�l��)
//==============================================================
void CPlayerModel::ControlHuman(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//�E

#if _DEBUG

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��O
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.25f;

		}
		else
#endif
		{
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
		}

		m_bMove = true;		//��������
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//��

#if _DEBUG

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��O
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.25f;

		}
		else
#endif
		{
			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
		}

		m_bMove = true;		//��������
	}

#if _DEBUG
	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//��
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * PLAYER_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * PLAYER_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 1.0f;

		m_bMove = true;		//��������

	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//��O
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * PLAYER_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * PLAYER_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.0f;

		m_bMove = true;		//��������

	}
#endif

	if ((m_move.x <= 0.8f && m_move.x >= -0.8f) && (m_move.z <= 0.8f && m_move.z >= -0.8f))
	{//�����ĂȂ��Ƃ�

		m_bMove = false;		//�����ĂȂ���Ԃɂ���
	}

	//�W�����v
	if (pInputKeyboard->GetTrigger(DIK_SPACE) == true && m_bJump == false)
	{//SPACE�L�[�������Ă��� && �W�����v���ĂȂ�������

		//�W�����v����
		m_move.y = JUMP_HEIGHT;

		//�W�����v������Ԃɂ���
		//m_bJump = true;
		//m_bLand = false;

		//���[�V�����̐ݒ�
		//m_pMotion->Set(m_pMotion->MOTIONTYPE_JUMP);
	}
}

//==============================================================
//�v���C���[�̑��쏈��(����)
//==============================================================
void CPlayerModel::ControlGoldFish(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CCamera *pCamera = CManager::GetCamera();		//�J�����̏��擾

	//�ړ�
	if (pInputKeyboard->GetPress(DIK_D) == true)
	{//�E

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.25f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��O
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * 0.75f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -0.25f;

		}
		else
		{
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * -CURVE_RL;
		}

		m_bMove = true;		//��������
	}
	else if (pInputKeyboard->GetPress(DIK_A) == true)
	{//��

		if (pInputKeyboard->GetPress(DIK_W) == true)
		{//��
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.25f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.75f;

		}
		else if (pInputKeyboard->GetPress(DIK_S) == true)
		{//��O
			m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * -0.75f) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.25f;

		}
		else
		{
			m_move.x += sinf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_move.z += cosf(pCamera->GetRotation().y + -D3DX_PI * CURVE_RL) * PLAYER_MOVE;
			m_fRotDest = pCamera->GetRotation().y + D3DX_PI * CURVE_RL;
		}

		m_bMove = true;		//��������
	}

	else if (pInputKeyboard->GetPress(DIK_W) == true)
	{//��
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * PLAYER_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_UP) * PLAYER_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 1.0f;

		m_bMove = true;		//��������

	}
	else if (pInputKeyboard->GetPress(DIK_S) == true)
	{//��O
		m_move.x += sinf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * PLAYER_MOVE;
		m_move.z += cosf(pCamera->GetRotation().y + D3DX_PI * CURVE_DOWN) * PLAYER_MOVE;
		m_fRotDest = pCamera->GetRotation().y + D3DX_PI * 0.0f;

		m_bMove = true;		//��������

	}

	if ((m_move.x <= 0.8f && m_move.x >= -0.8f) && (m_move.z <= 0.8f && m_move.z >= -0.8f))
	{//�����ĂȂ��Ƃ�

		m_bMove = false;		//�����ĂȂ���Ԃɂ���
	}
}

//==============================================================
//��ʊO���菈��
//==============================================================
void CPlayerModel::Screen(void)
{
	//��ʊO����(��)
	//if (m_pos.x < WIDTH_PLAYER)
	//{//��ʍ��ɏo����

	//	m_pos.x = WIDTH_PLAYER;

	//}
	//else if (m_pos.x > SCREEN_WIDTH - WIDTH_PLAYER)
	//{//��ʉE�ɏo����

	//	m_pos.x = SCREEN_WIDTH - WIDTH_PLAYER;

	//}

	//��ʊO����(�c)
	//if (m_pos.y > HEIGHT_PLAYER)
	//{//��ʏ�ɏo����

	//	m_pos.y = HEIGHT_PLAYER;
	//}
	/*else */
	if (m_pos.y < 0.0f && m_Type == PLAYERTYPE_HUMAN)
	{//��ʉ��ɏo����

		if (m_bJump == true)
		{//�W�����v���Ă���

			//���n
			m_pMotion->Set(m_pMotion->MOTIONTYPE_LAND);
		}

		if (m_pMotion->IsFinish() == true)
		{//�I��������

			m_bLand = true;		//���n����
		}

		m_pos.y = 0.0f;
		m_move.y = 0.0f;

		m_bJump = false;
	}
}

//==============================================================
//�v���C���[�̕`�揈��
//==============================================================
void CPlayerModel::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
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
//���f���t�@�C���ǂݍ��ݏ���
//==============================================================
void CPlayerModel::LoadFile(void)
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