//==============================================================
//
//���f������[model.cpp]
//Author:����������
//
//==============================================================
#include "model.h"
#include "manager.h"
#include "renderer.h"
#include "material.h"

//�}�N����`
#define NUM_MODEL			(2)			//���f���̎��
#define POS					(10.0f)		//pos�����l
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l
#define MODEL_LEN			(3.0f)		//����
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x

//�ÓI�����o�ϐ��錾
LPD3DXMESH CModel::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CModel::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CModel::m_dwNumMat = NULL;
const char *CModel::m_pFilename = NULL;					//�t�@�C���̖��O

//==============================================================
//�R���X�g���N�^
//==============================================================
CModel::CModel()
{
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CModel::CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu
	m_rot = rot;		//����

	//CModel::Load(pFilename);
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CModel::~CModel()
{

}

//==============================================================
//X�t�@�C���̓ǂݍ���
//==============================================================
HRESULT CModel::Load(const char *pFilename)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	//X�t�@�C���̓ǂݍ���
	D3DXLoadMeshFromX(pFilename,
		D3DXMESH_SYSTEMMEM,
		pDevice,
		NULL,
		&m_pBuffMat,
		NULL,
		&m_dwNumMat,
		&m_pMesh);

	return S_OK;
}

////==============================================================
////�}�e���A���E���b�V���̔j��
////==============================================================
//void CModel::Unload(void)
//{
//	//���b�V���̔j��
//	if (m_pMesh != NULL)
//	{
//		m_pMesh->Release();
//		m_pMesh = NULL;
//	}
//
//	//�}�e���A���̔j��
//	if (m_pBuffMat != NULL)
//	{
//		m_pBuffMat->Release();
//		m_pBuffMat = NULL;
//	}
//}

//==============================================================
//���f���̐�������
//==============================================================
CModel *CModel::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename)
{
	CModel *pModel = NULL;

	if (pModel == NULL)
	{//���������g�p����ĂȂ�������

		//���f���̐���
		pModel = new CModel(pos, rot);
	}

	//�t�@�C�������
	m_pFilename = pFilename;

	//����������
	pModel->Init(pos, rot);

	return pModel;
}

//==============================================================
//���f���̏���������
//==============================================================
HRESULT CModel::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CMaterial *pMaterial = CManager::GetMaterial();

	//���f���̓ǂݍ���
	m_nIdxModel = pMaterial->Regit(m_pFilename);

	//�}�e���A���̊��蓖��
	CObjectX::BindMaterial(m_nIdxModel);

	//�I�u�W�F�N�gX�̏���������
	CObjectX::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_MODEL);

	return S_OK;
}

//==============================================================
//���f���̏I������
//==============================================================
void CModel::Uninit(void)
{
	//�I�u�W�F�N�gX�̏I������
	CObjectX::Uninit();
}

//==============================================================
//���f���̍X�V����
//==============================================================
void CModel::Update(void)
{
	//�I�u�W�F�N�gX�̍X�V����
	CObjectX::Update();
}

//==============================================================
//���f���̕`�揈��
//==============================================================
void CModel::Draw(void)
{
	//�I�u�W�F�N�gX�̕`�揈��
	CObjectX::Draw();
}