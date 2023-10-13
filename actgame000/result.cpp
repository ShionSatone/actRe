//==============================================================
//
//���U���g����[result.cpp]
//Author:����������
//
//==============================================================
#include "result.h"
#include "manager.h"
#include "wall.h"
#include "input.h"
#include "camera.h"
#include "fade.h"
#include "sound.h"

//�ÓI�����o�ϐ��錾
bool CResult::bReset = true;					//���Z�b�g�������ǂ���

//==============================================================
//�R���X�g���N�^
//==============================================================
CResult::CResult()
{

}

//==============================================================
//�f�X�g���N�^
//==============================================================
CResult::~CResult()
{

}

//==============================================================
//����������
//==============================================================
HRESULT CResult::Init(void)
{
	//CSound *pSound = CManager::GetSound();

	////BGM�Đ�
	//if (CManager::GetResult() == true)
	//{
	//	pSound->Play(pSound->SOUND_LABEL_BGM003);
	//}
	//else if (CManager::GetResult() == false)
	//{
	//	pSound->Play(pSound->SOUND_LABEL_BGM004);
	//}

	return S_OK;
}

//==============================================================
//�I������
//==============================================================
void CResult::Uninit(void)
{
	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�V����
//==============================================================
void CResult::Update(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CInputJoyPad *pInputJoyPad = CManager::GetInputJoyPad();			//�p�b�h�̏��擾
	CFade *pFade = CManager::GetFade();			//�t�F�[�h�̏��擾

	if ((pInputKeyboard->GetTrigger(DIK_RETURN) == true || pInputJoyPad->GetTrigger(pInputJoyPad->BUTTON_A, 0) == true) && bReset == false)
	{//ENTER�L�[��������

		//CManager::SetBgm(false);

		//�����L���O���
		//CManager::SetMode(CScene::MODE_RANKING);
		pFade->SetFade(CScene::MODE_RANKING);
		bReset = true;
	}
	else
	{
		bReset = false;
	}

}

//==============================================================
//�`�揈��
//==============================================================
void CResult::Draw(void)
{

}