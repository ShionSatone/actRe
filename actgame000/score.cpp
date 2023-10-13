//=============================================================================
//
//�X�R�A���� [score.cpp]
//Author:����������
//
//=============================================================================
#include "score.h"
#include "manager.h"
#include "renderer.h"
#include "number.h"
#include "texture.h"
#include "playerModel.h"
#include "game.h"

//�}�N����`
#define SCORE_POS_X		(880.0f)			//�X�R�A��X�̈ʒu
#define SCORE_POS_Y		(50.0f)				//�X�R�A��Y�̈ʒu
#define RESULT_SCORE_POS_X		(700.0f)			//�X�R�A��X�̈ʒu
#define RESULT_SCORE_POS_Y		(SCREEN_HEIGHT * 0.5f)				//�X�R�A��Y�̈ʒu
#define SCORE_WIDTH		(50.0f * 0.5f)		//�X�R�A�̉���
#define SCORE_HEIGHT	(80.0f * 0.5f)		//�X�R�A�̏c��
#define SCORE_INTER		(50.0f)				//�X�R�A�̊Ԋu
#define NUM_TEX			(10)				//�e�N�X�`���̐����̐�

//�ÓI�����o�ϐ��錾
LPDIRECT3DTEXTURE9 CScore::m_pTexture = NULL;		//�e�N�X�`��
CNumber *CScore::m_apNumber[NUM_DIGIT] = {};
int CScore::m_nNum = 0;			//�X�R�A�̒l
int CScore::m_aTexU[NUM_DIGIT] = {};

//==============================================================
//�R���X�g���N�^
//==============================================================
CScore::CScore()
{
	//�ϐ�������
	m_nGroundIdxTex = -1;		//�n��e�N�X�`���̔ԍ�
	m_nUnderIdxTex = -1;		//�����e�N�X�`���̔ԍ�
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
	m_nNum = 0;		//�X�R�A�̒l

	for (int nCntScore = 0; nCntScore < NUM_DIGIT; nCntScore++)
	{
		m_aTexU[nCntScore] = 0;
	}
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CScore::~CScore()
{

}

//==============================================================
//�X�R�A�̃e�N�X�`���̓ǂݍ���
//==============================================================
HRESULT CScore::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	if (m_pTexture == NULL)
	{//�e�N�X�`���ݒ肳��ĂȂ��Ƃ�

		//�e�N�X�`���̓ǂݍ���
		D3DXCreateTextureFromFile(pDevice,
			"data\\TEXTURE\\score002.png",
			&m_pTexture);
	}

	return S_OK;
}

//==============================================================
//�X�R�A�̃e�N�X�`���̔j��
//==============================================================
void CScore::Unload(void)
{
	//�e�N�X�`���̔j��
	if (m_pTexture != NULL)
	{
		m_pTexture->Release();
		m_pTexture = NULL;
	}
}

//==============================================================
//��������
//==============================================================
CScore *CScore::Create(void)
{
	CScore *pScore = NULL;

	if (pScore == NULL)
	{//���������g�p����ĂȂ�������

		//�X�R�A�̐���
		pScore = new CScore;
	}

	if (pScore != NULL)
	{//�������m�ۂł��Ă���

		if (CManager::GetMode() == CScene::MODE_RESULT)
		{//���U���g��������

			//����������
			pScore->Init(D3DXVECTOR3(RESULT_SCORE_POS_X, RESULT_SCORE_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
			m_nNum = CManager::GetNumScore();

		}
		else
		{
			//����������
			pScore->Init(D3DXVECTOR3(SCORE_POS_X, SCORE_POS_Y, 0.0f), D3DXVECTOR3(0.0f, 0.0f, 0.0f));
		}

		//�X�R�A�̐ݒ�
		pScore->Set(m_nNum);

		//��ސݒ�
		pScore->SetType(TYPE_SCORE);
	}

	return pScore;
}

//==============================================================
//�X�R�A�̏���������
//==============================================================
HRESULT CScore::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CTexture *pTexture = CManager::GetTexture();

	//�n��e�N�X�`���̓ǂݍ���
	m_nGroundIdxTex = pTexture->Regit("data\\TEXTURE\\score00.png");

	//�����e�N�X�`���̓ǂݍ���
	m_nUnderIdxTex = pTexture->Regit("data\\TEXTURE\\score01.png");

	//����������
	for (int nCntScore = 0; nCntScore < NUM_DIGIT; nCntScore++)
	{
		if (m_apNumber[nCntScore] == NULL)
		{//�g�p����ĂȂ��Ƃ�

			//��������
			m_apNumber[nCntScore] = CNumber::Create();

			if (m_apNumber[nCntScore] != NULL)
			{//�����o������

				//�傫���ݒ�
				m_apNumber[nCntScore]->SetSize(SCORE_WIDTH, SCORE_HEIGHT);

				//�n��e�N�X�`�����蓖��
				m_apNumber[nCntScore]->BindTexture(m_nGroundIdxTex);

				//�X�R�A�̈ʒu�ݒ�
				m_apNumber[nCntScore]->SetPosition(CObject::TYPE_SCORE, 
					D3DXVECTOR3(pos.x + (nCntScore * SCORE_INTER), pos.y, pos.z), SCORE_WIDTH, SCORE_HEIGHT);
			}
		}
	}

	return S_OK;
}

//==============================================================
//�X�R�A�̏I������
//==============================================================
void CScore::Uninit(void)
{
	for (int nCntScore = 0; nCntScore < NUM_DIGIT; nCntScore++)
	{
		if (m_apNumber[nCntScore] != NULL)
		{//�g�p����Ă�Ƃ�

			//�I������
			m_apNumber[nCntScore]->Uninit();
			m_apNumber[nCntScore] = NULL;

		}
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//�X�R�A�̍X�V����
//==============================================================
void CScore::Update(void)
{
	
}

//==============================================================
//�X�R�A�̕`�揈��
//==============================================================
void CScore::Draw(void)
{
	
}

//==============================================================
//�X�R�A�̐ݒ菈��
//==============================================================
void CScore::Set(int nNum)
{
	int nDigit;		//����
	m_nNum = nNum;	//�X�R�A���

	//�X�R�A������
	for (int nCntScore = 0; nCntScore < NUM_DIGIT; nCntScore++)
	{
		nDigit = (int)pow(10, (NUM_DIGIT - nCntScore));		//����

		m_aTexU[nCntScore] = (int)(m_nNum % nDigit / (nDigit * 0.1f));

		//�X�R�A�̃e�N�X�`���ݒ�
		m_apNumber[nCntScore]->SetTex(CObject::TYPE_SCORE, m_aTexU[nCntScore], 1.0f / NUM_TEX);
	}
}

//==============================================================
//�X�R�A�̉��Z����
//==============================================================
void CScore::Add(int nValue)
{
	int nDigit;		//����
	m_nNum += nValue;	//�X�R�A���Z

	//�X�R�A������
	for (int nCntScore = 0; nCntScore < NUM_DIGIT; nCntScore++)
	{
		nDigit = (int)pow(10, (NUM_DIGIT - nCntScore));		//����

		m_aTexU[nCntScore] = (int)(m_nNum % nDigit / (nDigit * 0.1f));

		//�X�R�A�̃e�N�X�`���ݒ�
		m_apNumber[nCntScore]->SetTex(CObject::TYPE_SCORE, m_aTexU[nCntScore], 1.0f / NUM_TEX);
	}
}

//==============================================================
//�e�N�X�`�����蓖�ď���
//==============================================================
void CScore::BindTexture(LPDIRECT3DTEXTURE9 pTexture)
{
	m_pTexture = pTexture;		//�e�N�X�`�����蓖��
}