//==============================================================
//
//�}�l�[�W������[manager.cpp]
//Author:����������
//
//==============================================================
#include "manager.h"
#include "object.h"
#include "renderer.h"
#include "debugproc.h"
#include "input.h"
#include "object3D.h"
#include "camera.h"
#include "light.h"
#include "field.h"
#include "objectX.h"
#include "model.h"
#include "texture.h"
#include "edit.h"
#include "playerModel.h"
#include "material.h"

//�ÓI�����o�ϐ��錾
CRenderer *CManager::m_pRenderer = NULL;		//�����_���[�̏��
CInputKeyboard *CManager::m_pInputKeyboard = NULL;	//�L�[�{�[�h�̏��
CInputJoyPad *CManager::m_pInputJoyPad = NULL;		//�Q�[���p�b�h�̏��

CDebugProc *CManager::m_pDebugProc = NULL;		//�f�o�b�O�\���̏��

CCamera *CManager::m_pCamera = NULL;			//�J�����̏��
CLight *CManager::m_pLight = NULL;				//���C�g�̏��
CTexture *CManager::m_pTexture = NULL;			//�e�N�X�`���̏��
CEdit *CManager::m_pEdit = NULL;				//���f���z�u�̏��
CPlayerModel *CManager::m_pPlayerModel = NULL;	//�v���C���[���f���z�u�̏��
CMaterial *CManager::m_pMaterial = NULL;		//�}�e���A���̏��

//==============================================================
//�R���X�g���N�^
//==============================================================
CManager::CManager()
{
	m_hInstance = NULL;
	m_hWnd = NULL;
	m_bWindow = false;
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CManager::~CManager()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CManager::Init(HINSTANCE hInstance, HWND hWnd, BOOL bWindow)
{
	m_hInstance = hInstance;
	m_hWnd = hWnd;
	m_bWindow = bWindow;

	//�����_���[�̐���
	if (m_pRenderer == NULL)
	{//���������g�p����ĂȂ��Ƃ�

		m_pRenderer = new CRenderer;
	}

	//�����_���[�̏���������
	if (m_pRenderer != NULL)
	{//�������m�ۂł��Ă���

		//�����_���[�̏�����
		if (FAILED(m_pRenderer->Init(hWnd, TRUE)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�f�o�b�O�\���̐���
	if (m_pDebugProc == NULL)
	{//���������g�p����ĂȂ��Ƃ�

		m_pDebugProc = new CDebugProc;
	}

	if (m_pDebugProc != NULL)
	{//���������m�ۂ��ꂽ�Ƃ�

		//�f�o�b�O�\���̏���������
		m_pDebugProc->Init();
	}

	//�L�[�{�[�h�̐���
	if (m_pInputKeyboard == NULL)
	{//�L�[�{�[�h���g�p����ĂȂ��Ƃ�

		m_pInputKeyboard = new CInputKeyboard;
	}

	if (m_pInputKeyboard != NULL)
	{//�������m�ۂł��Ă���

		//�L�[�{�[�h�̏�����
		if (FAILED(m_pInputKeyboard->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�Q�[���p�b�h�̐���
	if (m_pInputJoyPad == NULL)
	{
		m_pInputJoyPad = new CInputJoyPad;
	}

	if (m_pInputJoyPad != NULL)
	{//�������m�ۂł��Ă���

		//�p�b�h�̏�����
		if (FAILED(m_pInputJoyPad->Init(hInstance, hWnd)))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�J�����̐���
	if (m_pCamera == NULL)
	{
		m_pCamera = new CCamera;
	}

	if (m_pCamera != NULL)
	{//�������m�ۂł��Ă���

		//�J�����̏�����
		if (FAILED(m_pCamera->Init()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//���C�g�̐���
	if (m_pLight == NULL)
	{
		m_pLight = new CLight;
	}

	if (m_pLight != NULL)
	{//�������m�ۂł��Ă���

		//���C�g�̏�����
		if (FAILED(m_pLight->Init()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�e�N�X�`���̐���
	if (m_pTexture == NULL)
	{
		m_pTexture = new CTexture;
	}

	if (m_pTexture != NULL)
	{//�������m�ۂł��Ă���

		//�e�N�X�`���̏�����
		if (FAILED(m_pTexture->Load()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�}�e���A���̐���
	if (m_pMaterial == NULL)
	{
		m_pMaterial = new CMaterial;
	}

	if (m_pMaterial != NULL)
	{//�������m�ۂł��Ă���

		//�}�e���A���̏�����
		if (FAILED(m_pMaterial->Load()))
		{//���������������s�����ꍇ

			return E_FAIL;
		}
	}

	//�S�Ẵe�N�X�`��3D�̓ǂݍ���
	CManager::Load3DAll();

	float posX = -5400.0f;
	float posY = 1000.0f;

	//�v���C���[�̐���
	m_pPlayerModel = CPlayerModel::Create(D3DXVECTOR3(posX, posY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	//�S�ẴI�u�W�F�N�g3D�̐���
	CManager::Create3DAll();

	//�G�f�B�b�g�̐���
	CEdit::Create(D3DXVECTOR3(posX, posY, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	return S_OK;
}

//==============================================================
//�I�u�W�F�N�g3D�̐�������
//==============================================================
void CManager::Create3DAll(void)
{
	
}

//==============================================================
//�I������
//==============================================================
void CManager::Uninit(void)
{
	//�S�ẴI�u�W�F�N�g�̔j��
	CObject::ReleaseAll();

	//�S�Ẵe�N�X�`��3D�̔j��
	CManager::UnLoad3DAll();

	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		//�e�N�X�`���̔j��
		m_pTexture->Unload();

		//�������J��
		delete m_pTexture;
		m_pTexture = NULL;
	}

	//�}�e���A���̔j��
	if (m_pMaterial != NULL)
	{
		//�e�N�X�`���̔j��
		m_pMaterial->Unload();

		//�������J��
		delete m_pMaterial;
		m_pMaterial = NULL;
	}

	//�L�[�{�[�h�̔j��
	if (m_pInputKeyboard != NULL)
	{
		//�L�[�{�[�h�̏I������
		m_pInputKeyboard->Uninit();

		//�������J��
		delete m_pInputKeyboard;
		m_pInputKeyboard = NULL;
	}

	//�Q�[���p�b�h�̔j��
	if (m_pInputJoyPad != NULL)
	{
		//�Q�[���p�b�h�̏I������
		m_pInputJoyPad->Uninit();

		//�������J��
		delete m_pInputJoyPad;
		m_pInputJoyPad = NULL;
	}

	//���C�g�̔j��
	if (m_pLight != NULL)
	{
		//���C�g�̏I������
		m_pLight->Uninit();

		//�������J��
		delete m_pLight;
		m_pLight = NULL;
	}

	//�J�����̔j��
	if (m_pCamera != NULL)
	{
		//�J�����̏I������
		m_pCamera->Uninit();

		//�������J��
		delete m_pCamera;
		m_pCamera = NULL;
	}

	//�f�o�b�O�\���̔j��
	if (m_pDebugProc != NULL)
	{
		//�f�o�b�O�\���̏I������
		m_pDebugProc->Uninit();

		//�������J��
		delete m_pDebugProc;
		m_pDebugProc = NULL;
	}

	//�����_���[�̔j��
	if (m_pRenderer != NULL)
	{
		//�����_���[�̏I������
		m_pRenderer->Uninit();

		//�������J��
		delete m_pRenderer;
		m_pRenderer = NULL;
	}
}

//==============================================================
//�S�Ẵe�N�X�`��3D�̓ǂݍ���
//==============================================================
void CManager::Load3DAll(void)
{
	//���f���̓ǂݍ���
	//CModel::Load();

	//�G�̓ǂݍ���
	//CEnemyModel::Load();
}

//==============================================================
//�S�Ẵe�N�X�`��3D�̔j��
//==============================================================
void CManager::UnLoad3DAll(void)
{
	//���f���̔j��
	//CModel::Unload();

	//�G�̔j��
	//CEnemyModel::Unload();
}

//==============================================================
//�X�V����
//==============================================================
void CManager::Update(void)
{
	//�L�[�{�[�h�̍X�V����
	m_pInputKeyboard->Update();

	//�Q�[���p�b�h�̍X�V����
	m_pInputJoyPad->Update();

	//�f�o�b�O�\���̍X�V����
	m_pDebugProc->Update();

	//�}�b�v�̍Đ���
	CManager::ResetMap();

	//�����_���[�̍X�V����
	m_pRenderer->Update();

	//�J�����̍X�V����
	m_pCamera->Update();
}

//==============================================================
//�`�揈��
//==============================================================
void CManager::Draw(void)
{
	//�����_���[�̕`�揈��
	m_pRenderer->Draw();
}

//==============================================================
//�}�b�v�̔z�u���Z�b�g
//==============================================================
void CManager::ResetMap(void)
{
	//���Z�b�g
	//if (m_pInputKeyboard->GetPress(DIK_F2) == true)
	//{//F2���������Ƃ�

	//	//�}�b�v�̃I�u�W�F�N�g�̃��Z�b�g
	//	CObject::ResetMapAll();

	//	////�I�u�W�F�N�g3D�̐���
	//	CManager::Create3DAll();
	//}
}