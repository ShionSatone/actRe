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
#include "manager.h"
#include "debugproc.h"
//#include "game.h"

//�ÓI�����o�ϐ��̐錾
//CObject *CObject::m_apObject[NUM_PRIORITY][MAX_OBJECT] = {};
int CObject::m_nNumAll = 0;		//�S�ẴI�u�W�F�N�g�̑���
CObject *CObject::m_apTop[NUM_PRIORITY] = {};		//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
CObject *CObject::m_apCur[NUM_PRIORITY] = {};		//�Ō���̃I�u�W�F�N�g�ւ̃|�C���^

//==============================================================
//�R���X�g���N�^
//==============================================================
CObject::CObject()
{
	m_pPrev = NULL;		//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	m_pNext = NULL;		//���̃I�u�W�F�N�g�ւ̃|�C���^
	m_bDeath = false;	//���S���Ȃ���Ԃɂ���
	m_nPriority = DEFAULT_PRIORITY;		//�f�t�H���g�D�揇��

	//�I�u�W�F�N�g(����)�����X�g�ɒǉ�
	m_pPrev = m_apCur[m_nPriority];		//�O�̃I�u�W�F�N�g���
	m_apCur[m_nPriority] = this;		//�Ō���Ɏ������g����
	m_nNumAll++;						//�I�u�W�F�N�g�̑������Z

	if (m_apTop[m_nPriority] == NULL)
	{//�擪�����Ȃ�������

		m_apTop[m_nPriority] = this;		//�擪�Ɏ������g����
	}
	else
	{
		m_pPrev->m_pNext = m_apCur[m_nPriority];
	}
}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
//CObject::CObject(TYPE type)
//{
//	for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
//	{
//		if (m_apObject[nCntObject] == NULL)
//		{//���������g�p����ĂȂ�������
//
//			m_apObject[nCntObject] = this;		//�������g����
//			m_nID = nCntObject;		//�������g��ID��ۑ�
//			m_type = type;			//�I�u�W�F�N�g�̎�ނ�ݒ�
//			m_nNumAll++;			//�������J�E���g�A�b�v
//
//			break;
//		}
//	}
//}

//==============================================================
//�R���X�g���N�^(�I�[�o�[���[�h)
//==============================================================
CObject::CObject(int nPriority)
{
	m_pPrev = NULL;		//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	m_pNext = NULL;		//���̃I�u�W�F�N�g�ւ̃|�C���^
	m_bDeath = false;	//���S���Ȃ���Ԃɂ���
	m_nPriority = nPriority;		//�D�揇��

	//�I�u�W�F�N�g(����)�����X�g�ɒǉ�
	m_pPrev = m_apCur[m_nPriority];		//�O�̃I�u�W�F�N�g���
	m_apCur[m_nPriority] = this;		//�Ō���Ɏ������g����
	m_nNumAll++;						//�I�u�W�F�N�g�̑������Z

	if (m_apTop[m_nPriority] == NULL)
	{//�擪�����Ȃ�������

		m_apTop[m_nPriority] = this;	//�擪�Ɏ������g����
	}
	else
	{
		m_pPrev->m_pNext = m_apCur[m_nPriority];
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
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			//�I������
			pObject->Uninit();

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����

		//���S�t���O���`�F�b�N���ăI�u�W�F�N�g�����X�g����폜���Ĕj������
		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			if (pObject->m_bDeath == true)
			{//���S�t���O�������Ă���Ƃ�

					//�I�u�W�F�N�g(����)�����X�g����폜
				if (m_apTop[nCntPri] == pObject)
				{//�擪��������

					m_apTop[nCntPri] = pObjectNext;		//�擪�ύX
				}
				else if (m_apCur[nCntPri] == pObject)
				{//�Ō����������

					m_apCur[nCntPri] = pObject->m_pPrev;		//�Ō���ύX
					pObject->m_pPrev->m_pNext = NULL;
				}
				else
				{
					pObjectNext->m_pPrev = pObject->m_pPrev;
					pObject->m_pPrev->m_pNext = pObjectNext;
				}

				//�I�u�W�F�N�g(����)��j��
				delete pObject;

				m_nNumAll--;		//�������J�E���g�_�E��
			}

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̍X�V����
//==============================================================
void CObject::UpdateAll(void)
{
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����
		//CDebugProc *pDebugProc = CManager::GetDebugProc();		//�f�o�b�O�\���̏��擾
		//CGame *pGame = CGame::GetGame();

		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			if (pObject->m_bDeath == false)
			{//���S�t���O�������ĂȂ��Ƃ�

				//if (pGame->GetPauseDisp() == true)
				//{//�|�[�Y��ʂ̂Ƃ�

				//	if (pObject->GetType() == TYPE_PAUSE || pObject->GetType() == TYPE_SCENE || pObject->GetType() == TYPE_FADE)
				//	{
				//		//�X�V����
				//		pObject->Update();
				//	}
				//}
				//else if (pGame->GetPauseDisp() == false)
				{//�|�[�Y��ʂ���Ȃ��Ƃ�

					if (pObject->GetType() != TYPE_PAUSE)
					{
						//�X�V����
						pObject->Update();
					}
				}
			}

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����

		//���S�t���O���`�F�b�N���ăI�u�W�F�N�g�����X�g����폜���Ĕj������
		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			if (pObject->m_bDeath == true)
			{//���S�t���O�������Ă���Ƃ�

				//�I�u�W�F�N�g(����)�����X�g����폜
				if (m_apTop[nCntPri] == pObject)
				{//�擪��������

					m_apTop[nCntPri] = pObjectNext;		//�擪�ύX
				}
				else if (m_apCur[nCntPri] == pObject)
				{//�Ō����������

					m_apCur[nCntPri] = pObject->m_pPrev;		//�Ō���ύX
					pObject->m_pPrev->m_pNext = NULL;
				}
				else
				{
					pObjectNext->m_pPrev = pObject->m_pPrev;
					pObject->m_pPrev->m_pNext = pObjectNext;
				}

				//�I�u�W�F�N�g(����)��j��
				delete pObject;

				m_nNumAll--;		//�������J�E���g�_�E��
			}

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}

	//pDebugProc->Print("\n�I�u�W�F�N�g�̐�[%d]\n\n", m_nNumAll);
}

//==============================================================
//�S�ẴI�u�W�F�N�g�̕`�揈��
//==============================================================
void CObject::DrawAll(void)
{
	CCamera *pCamera = CManager::GetCamera();
	CObject *pObject;
	//CGame *pGame = CGame::GetGame();

	//�J�����̐ݒ�
	pCamera->SetCamera();

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			//if (pGame->GetPauseDisp() == true)
			{//�|�[�Y��ʂ̂Ƃ�

				//�`�揈��
				pObject->Draw();
			}
			//else if (pGame->GetPauseDisp() == false)
			//{//�|�[�Y��ʂ���Ȃ��Ƃ�

			//	if (pObject->GetType() != TYPE_PAUSE)
			//	{
			//		//�`�揈��
			//		pObject->Draw();
			//	}
			//}

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}
}

//==============================================================
//�I�u�W�F�N�g�̔j��
//==============================================================
void CObject::Release(void)
{
	//���S�t���O�𗧂Ă�
	m_bDeath = true;
}

//==============================================================
//�I�u�W�F�N�g�̏��擾
//==============================================================
CObject *CObject::GetObject(int nPriority, int nIdx)
{
	CObject *pObject = m_apTop[nPriority];		//�擪�̃I�u�W�F�N�g����
	int nCntIdx = 0;				//���݉��Ԗڂ�

	while (nCntIdx != nIdx)
	{//�I�u�W�F�N�g���g�p����Ă��

		if (pObject->m_pNext != NULL)
		{
			pObject = pObject->m_pNext;		//���̃I�u�W�F�N�g����
		}
		else
		{
			return NULL;
		}

		nCntIdx++;
	}

	return pObject;
}

//==============================================================
//�I������
//==============================================================
void CObject::DeathAll(void)
{
	CObject *pObject;

	for (int nCntPri = 0; nCntPri < NUM_PRIORITY; nCntPri++)
	{
		pObject = m_apTop[nCntPri];		//�擪�̃I�u�W�F�N�g����

		while (pObject != NULL)
		{//�I�u�W�F�N�g���g�p����Ă��

			CObject *pObjectNext = pObject->m_pNext;		//���̃I�u�W�F�N�g��ۑ�

			if (pObject->m_bDeath == false)
			{//���S�t���O�������ĂȂ��Ƃ�

				//�I������
				pObject->Uninit();
			}

			pObject = pObjectNext;		//���̃I�u�W�F�N�g����
		}
	}
}

//==============================================================
//�}�b�v�̃I�u�W�F�N�g�̃��Z�b�g����
//==============================================================
void CObject::ResetMapAll(void)
{
	//for (int nCntObject = 0; nCntObject < MAX_OBJECT; nCntObject++)
	//{
	//	if (m_apObject[nCntObject] != NULL)
	//	{//���������g�p����Ă���

	//		if (m_apObject[nCntObject]->m_type != TYPE_PLAYER &&
	//			m_apObject[nCntObject]->m_type != TYPE_NONE)
	//		{
	//			//�I������
	//			m_apObject[nCntObject]->Uninit();
	//		}
	//	}
	//}
}