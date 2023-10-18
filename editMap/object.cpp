//==============================================================
//
//�I�u�W�F�N�g����[object.cpp]
//Author:����������
//
//==============================================================
#include "object.h"
#include "renderer.h"
#include "manager.h"
#include "camera.h"

//�ÓI�����o�ϐ��̐錾
CObject *CObject::m_apObject[MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;		//�S�ẴI�u�W�F�N�g�̑���

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject::CObject()
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{//���������g�p����ĂȂ�������

			m_apObject[nCntObject] = this;		//�������g����
			m_nID = nCntObject;		//�������g��ID��ۑ�
			m_nNumAll++;			//�������J�E���g�A�b�v

			break;
		}
	}
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CObject::CObject(TYPE type)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] == NULL)
		{//���������g�p����ĂȂ�������

			m_apObject[nCntObject] = this;		//�������g����
			m_nID = nCntObject;		//�������g��ID��ۑ�
			m_type = type;			//�I�u�W�F�N�g�̎�ނ�ݒ�
			m_nNumAll++;			//�������J�E���g�A�b�v

			break;
		}
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CObject::~CObject()
{

}

//==============================================================
//�S�ẴI�u�W�F�N�g�̔j��
//==============================================================
void CObject::ReleaseAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{//���������g�p����Ă���

			//�I������
			m_apObject[nCntObject]->Uninit();
		}
	}
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̍X�V����
//==============================================================
void CObject::UpdateAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{//�������m�ۂ���Ă���

			//�X�V����
			m_apObject[nCntObject]->Update();
		}
	}
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̕`�揈��
//==============================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{//�������m�ۂ���Ă���

			//�`�揈��
			m_apObject[nCntObject]->Draw();
		}
	}
}

//==============================================================
//�I�u�W�F�N�g�̔j��
//==============================================================
void CObject::Release(void)
{
	int nID = m_nID;		//ID���

	if (m_apObject[nID] != NULL)
	{//���������g�p����Ă���

		//�������J��
		delete m_apObject[nID];
		m_apObject[nID] = NULL;

		m_nNumAll--;		//�������J�E���g�_�E��
	}
}

//==============================================================
//�}�b�v�̃I�u�W�F�N�g�̃��Z�b�g����
//==============================================================
void CObject::ResetMapAll(void)
{
	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	{
		if (m_apObject[nCntObject] != NULL)
		{//���������g�p����Ă���

			if (m_apObject[nCntObject]->m_type != TYPE_PLAYER &&
				m_apObject[nCntObject]->m_type != TYPE_NONE)
			{
				//�I������
				m_apObject[nCntObject]->Uninit();
			}
		}
	}
}