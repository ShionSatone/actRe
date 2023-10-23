//==============================================================
//
//�A�C�e������[item.cpp]
//Author:����������
//
//==============================================================
#include "item.h"
#include "game.h"
#include "model.h"
#include "material.h"
#include "player.h"
#include "sound.h"
#include "score.h"

//�ÓI�����o�ϐ��錾
LPD3DXMESH CItem::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CItem::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CItem::m_dwNumMat = NULL;
const char *CItem::m_pFilename[TYPE_MAX] = 			//�t�@�C���̖��O
{
	NULL,
	"data\\MODEL\\item_rhombus.x",		//�Ђ��`
	//"data\\MODEL\\item_ice.x",			//�X
};

//==============================================================
//�R���X�g���N�^
//==============================================================
CItem::CItem()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
	m_type = TYPEITEM_NONE;	//���
	m_nIdx = -1;				//���f���̔ԍ�
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CItem::CItem(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����
	m_type = type;		//���
	m_nIdx = -1;		//���f���̔ԍ�
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CItem::~CItem()
{

}

//==============================================================
//�A�C�e���̐�������
//==============================================================
CItem *CItem::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, TYPEITEM type)
{
	CItem *pItemModel = NULL;

	if (pItemModel == NULL)
	{//���������g�p����ĂȂ�������

		//�A�C�e���̐���
		pItemModel = new CItem(pos, rot, type);
	}

	//����������
	pItemModel->Init();

	return pItemModel;
}

//==============================================================
//�A�C�e���̏���������
//==============================================================
HRESULT CItem::Init(void)
{
	CMaterial *pMaterial = CManager::GetInstance()->GetMaterial();

	//���f���̓ǂݍ���
	m_nIdx = pMaterial->Regist(m_pFilename[m_type]);

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdx);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init();

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_ITEM);

	return S_OK;
}

//==============================================================
//�A�C�e���̏I������
//==============================================================
void CItem::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//�A�C�e���̍X�V����
//==============================================================
void CItem::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//�A�C�e���̕`�揈��
//==============================================================
void CItem::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}

//==============================================================
//�A�C�e���̃q�b�g����
//==============================================================
void CItem::Hit(void)
{
	CPlayer *pPlayer = CGame::GetPlayer();
	//CLife *pLife = CGame::GetLife();
	//CBulletRemain *pBR = CGame::GetBulletRemain();
	CSound *pSound = CManager::GetInstance()->GetSound();
	//CScore *pScore = CGame::GetScore();

	//if (m_type != TYPEITEM_LIFE/* && m_type != TYPEITEM_KEY*/)
	//{//����̎�ނ̃A�C�e���̎�

	//	//SE�Đ�
	//	pSound->Play(pSound->SOUND_LABEL_SE_ITEM000);

	//	////����̎�ޕύX����
	//	//pPlayer->SetWeaponType(m_type);

	//	////�e��
	//	//pBR->SetNumBullet(-100);

	//	////�X�R�A���Z
	//	//pScore->Add(1050);
	//}
	//else if (m_type == TYPEITEM_LIFE)
	//{//�񕜃A�C�e���̎�

	//	//SE�Đ�
	//	pSound->Play(pSound->SOUND_LABEL_SE_ITEM100);

	//	////�̗͑��₷
	//	//pLife->SetNum(60);

	//	////�X�R�A���Z
	//	//pScore->Add(700);
	//}

	//�I������
	CItem::Uninit();
}