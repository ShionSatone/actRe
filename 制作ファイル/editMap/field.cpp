//==============================================================
//
//���̏���[field.h]
//Author:����������
//
//==============================================================
#include "field.h"
#include "manager.h"
#include "renderer.h"
#include "texture.h"

//�}�N����`
#define WIDTH_FIELD			(1000.0f * 0.5f)	//���̉���
#define HEIGHT_FIELD		(1000.0f * 0.5f)	//���̏c��
#define COL_R				(1.0f)		//�ԐF�̐��l
#define COL_G				(1.0f)		//�ΐF�̐��l
#define COL_B				(1.0f)		//�F�̐��l
#define COL_A				(1.0f)		//�s�����x�̐��l
#define TEX_LEFT_X			(0.0f)		//�e�N�X�`���̍�x�̏����l
#define TEX_RIGHT_X			(1.0f)		//�e�N�X�`���̉Ex�̏����l
#define TEX_UP_Y			(0.0f)		//�e�N�X�`���̏�y�̏����l
#define TEX_DOWN_Y			(1.0f)		//�e�N�X�`���̉�y�̏����l

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CField::m_pTexture = NULL;

//==============================================================
//�R���X�g���N�^
//==============================================================
CField::CField()
{
	m_nIdxTexture = -1;		//�e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CField::CField(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	m_pos = pos;		//�ʒu

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CField::~CField()
{

}

//==============================================================
//�e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CField::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\000.jpg",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�e�N�X�`���̔j��
//==============================================================
void CField::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//���̐�������
//==============================================================
CField *CField::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CField *pField = NULL;

	if (pField == NULL)
	{//���������g�p����ĂȂ�������

		//���̐���
		pField = new CField(pos, rot);
	}

	//����������
	pField->Init(pos, rot);

	return pField;
}

//==============================================================
//���̏���������
//==============================================================
HRESULT CField::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//�e�N�X�`���̓ǂݍ���
	m_nIdxTexture = pTexture->Regit("data\\TEXTURE\\meadow.jpg");

	//�e�N�X�`���̊��蓖��
	CObject3D::BindTexture(m_nIdxTexture);

	//�I�u�W�F�N�g3D�̏���������
	CObject3D::Init(pos, rot);

	//��ނ̐ݒ�
	CObject::SetType(CObject::TYPE_FIELD);

	//���̑傫���ݒ�
	CObject3D::SetSize(WIDTH_FIELD, HEIGHT_FIELD);

	return S_OK;
}

//==============================================================
//���̏I������
//==============================================================
void CField::UnInit(void)
{
	//�I�u�W�F�N�g3D�̏I������
	CObject3D::Uninit();
}

//==============================================================
//���̍X�V����
//==============================================================
void CField::Update(void)
{

}

//==============================================================
//���̕`�揈��
//==============================================================
void CField::Draw(void)
{
	//�I�u�W�F�N�g3D�̕`�揈��
	CObject3D::Draw();
}