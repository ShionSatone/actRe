//==============================================================
//
//�z�u����[edit.cpp]
//Author:����������
//
//==============================================================
#include "edit.h"
#include "manager.h"
#include "renderer.h"
#include "objectX.h"
#include "input.h"
#include "object.h"
#include "model.h"
#include "debugproc.h"
#include "playerModel.h"

//�}�N����`
#define MODEL_LEN			(3.0f)		//����
#define CURVE_RL			(0.5f)		//���E�̊p�x
#define CURVE_UP			(0.0f)		//��̊p�x
#define CURVE_DOWN			(1.0f)		//���̊p�x
#define MOVE_MODEL			(50.0f)		//���f���̈ړ����x
#define FILE_MAP			"data\\TEXT\\map.txt"		//�}�b�v�̔z�u���t�@�C��

//�ÓI�����o�ϐ��錾
LPD3DXMESH CEdit::m_pMesh = NULL;						//���b�V���i���_���j�ւ̃|�C���^
LPD3DXBUFFER CEdit::m_pBuffMat = NULL;					//�}�e���A���ւ̃|�C���^
DWORD CEdit::m_dwNumMat = NULL;
const char *CEdit::m_apFilename[MAX_MODEL] = {};		//���f���̔z�u�̃t�@�C����
int CEdit::m_nNumAll = 0;			//���f���̑���
CObjectX *CEdit::m_apObjectX[MAX_MODEL] = {};

//==============================================================
//�R���X�g���N�^
//==============================================================
CEdit::CEdit()
{
	//���f���̍\���̏�����
	for (int nCntEdit = 0; nCntEdit < MAX_MODEL; nCntEdit++)
	{
		m_aEdit[nCntEdit].dwNumMat = NULL;
		m_aEdit[nCntEdit].pBuffMat = NULL;		//�}�e���A���ւ̃|�C���^
		m_aEdit[nCntEdit].pMesh = NULL;			//���b�V��(���_���)�ւ̃|�C���^
		m_aEdit[nCntEdit].pTexture = NULL;		//�e�N�X�`���̃|�C���^
		m_aEdit[nCntEdit].vtxMin = D3DXVECTOR3(100000.0f, 100000.0f, 100000.0f);		//���_���̍ŏ��l
		m_aEdit[nCntEdit].vtxMax = D3DXVECTOR3(-100000.0f, -100000.0f, -100000.0f);		//���_���̍ő�l
		m_aEdit[nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		m_aEdit[nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		m_aEdit[nCntEdit].nIndex = -1;			//���f���ԍ�

		m_aSetEdit[nCntEdit].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//�ʒu
		m_aSetEdit[nCntEdit].rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		//����
		m_aSetEdit[nCntEdit].nIndex = -1;

		for (int nCntName = 0; nCntName < MAX_STR; nCntName++)
		{
			m_aEdit[nCntEdit].aFilename[nCntName] = NULL;			//�t�@�C����
			m_aEdit[nCntEdit].aFilecomment[nCntName] = NULL;		//�t�@�C���R�����g
		}
	}

	//m_pTexture = NULL;			//�e�N�X�`���ւ̃|�C���^
	m_pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//�ʒu
	m_rot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			//����
	m_nNumModel = 0;			//���f���̔ԍ�
	m_nMaxModel = 0;			//���f���̐ݒu�ő吔
}

//==============================================================
//�f�X�g���N�^
//==============================================================
CEdit::~CEdit()
{
	
}

//==============================================================
//X�t�@�C���̓ǂݍ���
//==============================================================
HRESULT CEdit::Load(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾

	CEdit::LoadFile();		//�t�@�C���ǂݍ���

	for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	{
		//X�t�@�C���̓ǂݍ���
		D3DXLoadMeshFromX(&m_aEdit[nCntEdit].aFilename[0],
			D3DXMESH_SYSTEMMEM,
			pDevice,
			NULL,
			&m_aEdit[nCntEdit].pBuffMat,
			NULL,
			&m_aEdit[nCntEdit].dwNumMat,
			&m_aEdit[nCntEdit].pMesh);
	}

	return S_OK;
}

//==============================================================
//�}�e���A���E���b�V���̔j��
//==============================================================
void CEdit::Unload(void)
{
	for (int nCntEdit = 0; nCntEdit < MAX_MODEL; nCntEdit++)
	{
		//���b�V���̔j��
		if (m_aEdit[nCntEdit].pMesh != NULL)
		{
			m_aEdit[nCntEdit].pMesh->Release();
			m_aEdit[nCntEdit].pMesh = NULL;
		}

		//�}�e���A���̔j��
		if (m_aEdit[nCntEdit].pBuffMat != NULL)
		{
			m_aEdit[nCntEdit].pBuffMat->Release();
			m_aEdit[nCntEdit].pBuffMat = NULL;
		}
	}
}

//==============================================================
//���f���̔z�u�̐�������
//==============================================================
CEdit *CEdit::Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	CEdit *pEdit = NULL;

	if (pEdit == NULL)
	{//���������g�p����ĂȂ�������

		//���f���̔z�u�̐���
		pEdit = new CEdit;
	}

	//����������
	pEdit->Init(pos, rot);

	return pEdit;
}

//==============================================================
//���f���̔z�u�̏���������
//==============================================================
HRESULT CEdit::Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATERIAL *pMat;		//�}�e���A���ւ̃|�C���^

	m_pos = pos;

	//���f���̔z�u���̓ǂݍ���
	CEdit::Load();

	for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	{
		m_aEdit[nCntEdit].pTexture = new LPDIRECT3DTEXTURE9[m_aEdit[nCntEdit].dwNumMat];

		//�}�e���A�����ɑ΂���|�C���^���擾
		pMat = (D3DXMATERIAL*)m_aEdit[nCntEdit].pBuffMat->GetBufferPointer();

		for (int nCntMat = 0; nCntMat < (int)m_aEdit[nCntEdit].dwNumMat; nCntMat++)
		{
			//if (m_pTexture[nCntMat] != NULL)
			{
				if (pMat[nCntMat].pTextureFilename != NULL)
				{//�e�N�X�`�������݂���
					D3DXCreateTextureFromFile(pDevice,
						pMat[nCntMat].pTextureFilename,
						&m_aEdit[nCntEdit].pTexture[nCntMat]);
				}
				else
				{//�e�N�X�`�������݂��Ȃ�
					m_aEdit[nCntEdit].pTexture[nCntMat] = NULL;
				}
			}
		}
	}

	//�傫���ݒ�
	CEdit::SetSize();

	return S_OK;
}

//==============================================================
//���f���̔z�u�̏I������
//==============================================================
void CEdit::Uninit(void)
{
	CEdit::Unload();		//�}�e���A���E���b�V���̔j��

	//for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	//{
	//	if (m_apObjectX[nCntEdit] != NULL)
	//	{//�g�p����Ă���

	//		//�I�u�W�F�N�gX�̏I������
	//		m_apObjectX[nCntEdit]->Uninit();
	//	}
	//}

	//�I������
	for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	{
		//for (int nCntMat = 0; nCntMat < (int)m_dwNumMat; nCntMat++)
		//{
		//	if (m_pTexture[nCntMat] != NULL)
		//	{
		//		m_pTexture[nCntMat]->Release();
		//		m_pTexture[nCntMat] = NULL;
		//	}
		//}
#if 0 // ���[�N���Ă邼�B
		for (int nCntMat = 0; nCntMat < (int)m_aEdit[nCntEdit].dwNumMat; nCntMat++)
		{
			if (m_aEdit[nCntEdit].pTexture != NULL)
			{
				if (m_aEdit[nCntEdit].pTexture[nCntMat] != NULL)
				{
					m_aEdit[nCntEdit].pTexture[nCntMat]->Release();
					m_aEdit[nCntEdit].pTexture[nCntMat] = NULL;
				}

				delete[] m_aEdit[nCntEdit].pTexture;
				m_aEdit[nCntEdit].pTexture = NULL;
			}
		}
#endif
	}

	//�I�u�W�F�N�g�i�������g�̔j���j
	CObject::Release();
}

//==============================================================
//���f���̔z�u�̍X�V����
//==============================================================
void CEdit::Update(void)
{
	CDebugProc *pDebugProc = CManager::GetDebugProc();					//�f�o�b�O�\���̏��擾

	m_aEdit[m_nNumModel].pos = m_pos;

	//���쏈��
	CEdit::Control();

	pDebugProc->Print("���f���̔ԍ��F%d\n", m_nNumModel);
	pDebugProc->Print("���f���̈ʒu�F(%f, %f, %f)\n", m_pos.x, m_pos.y, m_pos.z);
}

//==============================================================
//���f���̔z�u�̑��쏈��
//==============================================================
void CEdit::Control(void)
{
	CInputKeyboard *pInputKeyboard = CManager::GetInputKeyboard();		//�L�[�{�[�h�̏��擾
	CPlayerModel *pPlayerModel = CManager::GetPlayerModel();			//�v���C���[�̏��擾

	if (pInputKeyboard->GetTrigger(DIK_2) == true)
	{//2�L�[��������

		if (m_nNumAll - 1 > m_nNumModel && 0 <= m_nNumModel)
		{//���f���̔ԍ����ő�l�����̏ꍇ

			m_nNumModel++;		//���̃��f���ɕύX����
		}
		else if (m_nNumAll - 1 >= m_nNumModel)
		{//���f���̔ԍ����ő吔�̏ꍇ

			m_nNumModel = 0;	//�ŏ��̃��f���ɕύX����
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_1) == true)
	{//1�L�[��������

		if (m_nNumAll - 1 >= m_nNumModel && 0 < m_nNumModel)
		{//���f���̔ԍ����ŏ��l���傫���̏ꍇ

			m_nNumModel--;		//���̃��f���ɕύX����
		}
		else if (0 <= m_nNumModel)
		{//���f���̔ԍ����ŏ��l�̏ꍇ

			m_nNumModel = m_nNumAll - 1;	//�Ō�̃��f���ɕύX����
		}
	}

	if (pInputKeyboard->GetPress(DIK_RIGHT) == true)
	{//���L�[����������

		//if (pInputKeyboard->GetTrigger(DIK_UP) == true)
		//{//���L�[����������

		//	//�E��
		//	m_pos.x += sinf(m_rot.y + D3DX_PI * 0.25f) * MOVE_MODEL;
		//	m_pos.y += cosf(m_rot.y + D3DX_PI * 0.25f) * MOVE_MODEL;
		//}
		//else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
		//{//���L�[����������

		//	//�E��O
		//	m_pos.x += sinf(m_rot.y + D3DX_PI * 0.75f) * MOVE_MODEL;
		//	m_pos.y += cosf(m_rot.y + D3DX_PI * 0.75f) * MOVE_MODEL;
		//}
		/*else */if (pInputKeyboard->GetTrigger(DIK_RIGHT) == true)
		{
			//�E
			m_pos.x += sinf(m_rot.y + D3DX_PI * 0.5f) * MOVE_MODEL;
			m_pos.y += cosf(m_rot.y + D3DX_PI * 0.5f) * MOVE_MODEL;
		}
	}
	else if (pInputKeyboard->GetPress(DIK_LEFT) == true)
	{//���L�[����������

		//if (pInputKeyboard->GetTrigger(DIK_UP) == true)
		//{//���L�[����������

		//	//����
		//	m_pos.x += sinf(m_rot.y + -D3DX_PI * 0.25f) * MOVE_MODEL;
		//	m_pos.y += cosf(m_rot.y + -D3DX_PI * 0.25f) * MOVE_MODEL;
		//}
		//else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
		//{//���L�[����������

		//	//����O
		//	m_pos.x += sinf(m_rot.y + -D3DX_PI * 0.75f) * MOVE_MODEL;
		//	m_pos.y += cosf(m_rot.y + -D3DX_PI * 0.75f) * MOVE_MODEL;
		//}
		/*else */if (pInputKeyboard->GetTrigger(DIK_LEFT) == true)
		{
			//��
			m_pos.x += sinf(m_rot.y + -D3DX_PI * 0.5f) * MOVE_MODEL;
			m_pos.y += cosf(m_rot.y + -D3DX_PI * 0.5f) * MOVE_MODEL;
		}
	}
	else if (pInputKeyboard->GetTrigger(DIK_UP) == true)
	{//���L�[����������

		//m_pos.z += MOVE_MODEL;		//���ɐi��

		m_pos.y += MOVE_MODEL;		//��ɏグ��

	}
	else if (pInputKeyboard->GetTrigger(DIK_DOWN) == true)
	{//���L�[����������

		//m_pos.z += -MOVE_MODEL;		//��O�ɐi��

		m_pos.y += -MOVE_MODEL;		//���ɉ�����

	}
	//else if (pInputKeyboard->GetPress(DIK_U) == true)
	//{//U�L�[����������

	//	m_pos.y += 1.0f;		//��ɏグ��
	//}
	//else if (pInputKeyboard->GetPress(DIK_M) == true)
	//{//M�L�[����������

	//	m_pos.y += -1.0f;		//���ɉ�����
	//}

	if (pInputKeyboard->GetTrigger(DIK_RETURN) == true)
	{//ENTER�L�[����������

		//���f���̐ݒ菈��
		CEdit::SetModel();
	}

	if (pInputKeyboard->GetTrigger(DIK_F9) == true)
	{//F9�L�[����������

		//�Z�[�u����
		CEdit::SaveFile();
	}

	if (pInputKeyboard->GetTrigger(DIK_DELETE) == true)
	{//DELETE�L�[����������

		//���f���폜
		CEdit::Delete();
	}

	if (pInputKeyboard->GetTrigger(DIK_0) == true)
	{//�ʒu���f���̉��s���Z�b�g

		m_pos.z = 0.0f;
	}

	if (pInputKeyboard->GetTrigger(DIK_9) == true)
	{//�ʒu���f���̍������Z�b�g

		if (pPlayerModel->GetType() == pPlayerModel->PLAYERTYPE_HUMAN)
		{//�l�̎�

			m_pos.y = 0.0f;

		}
		else if (pPlayerModel->GetType() == pPlayerModel->PLAYERTYPE_GOLDFISH)
		{//�����̂Ƃ�

			m_pos.y = -5000.0f;
		}
	}
}

//==============================================================
//���f���̔z�u�̕`�揈��
//==============================================================
void CEdit::Draw(void)
{
	LPDIRECT3DDEVICE9 pDevice = CManager::GetRenderer()->GetDevice();		//�f�o�C�X�̎擾
	D3DXMATRIX mtxRot, mtxTrans;	//�v�Z�p�}�g���b�N�X
	D3DMATERIAL9 matDef;			//���݂̃}�e���A���ۑ��p
	D3DXMATERIAL *pMat;

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

	//���݂̃}�e���A�����擾
	pDevice->GetMaterial(&matDef);

	//�}�e���A���f�[�^�ւ̃|�C���^���擾
	pMat = (D3DXMATERIAL*)m_aEdit[m_nNumModel].pBuffMat->GetBufferPointer();

	for (int nCntMat = 0; nCntMat < (int)m_aEdit[m_nNumModel].dwNumMat; nCntMat++)
	{
		//�}�e���A���̐ݒ�
		pDevice->SetMaterial(&pMat[nCntMat].MatD3D);

		//�e�N�X�`���̐ݒ�
		pDevice->SetTexture(0, m_aEdit[m_nNumModel].pTexture[nCntMat]);

		//���f���i�p�[�c�j�̕`��
		m_aEdit[m_nNumModel].pMesh->DrawSubset(nCntMat);
	}

	//�ۑ����Ă����}�e���A����߂�
	pDevice->SetMaterial(&matDef);

	//�I�u�W�F�N�gX�̕`�揈��
	/*for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	{
		m_apObjectX[nCntEdit]->Draw();
	}*/
}

//==============================================================
//���f���̐ݒ菈��
//==============================================================
void CEdit::SetModel(void)
{
	//���f������
	CModel::Create(m_pos, m_rot, &m_aEdit[m_nNumModel].aFilename[0]);

	m_aSetEdit[m_nMaxModel].pos = m_pos;
	m_aSetEdit[m_nMaxModel].rot = m_rot;
	m_aSetEdit[m_nMaxModel].nIndex = m_nNumModel;

	m_nMaxModel++;		//�ő�ݒu�����Z
}

//==============================================================
//���f���̑傫���ݒ菈��
//==============================================================
void CEdit::SetSize(void)
{
	int nNumVtx;					//���_��
	DWORD dwSizeFVF;				//���_�t�H�[�}�b�g�̃T�C�Y
	BYTE *pVtxBuff;					//���_�o�b�t�@�ւ̃|�C���^

	for (int nCntEdit = 0; nCntEdit < m_nNumAll; nCntEdit++)
	{
		//���_�����擾
		nNumVtx = m_aEdit[nCntEdit].pMesh->GetNumVertices();

		//���_�t�H�[�}�b�g�̃T�C�Y���擾
		dwSizeFVF = D3DXGetFVFVertexSize(m_aEdit[nCntEdit].pMesh->GetFVF());

		//���_�o�b�t�@�����b�N
		m_aEdit[nCntEdit].pMesh->LockVertexBuffer(D3DLOCK_READONLY, (void**)&pVtxBuff);

		for (int nCntVtx = 0; nCntVtx < nNumVtx; nCntVtx++)
		{
			D3DXVECTOR3 vtx = *(D3DXVECTOR3*)pVtxBuff;			//���_���W�̑��

			//�S�Ă̒��_���r���ă��f���̍ő�l�𔲂��o��
			if (vtx.x > m_aEdit[nCntEdit].vtxMax.x)
			{
				m_aEdit[nCntEdit].vtxMax.x = vtx.x;
			}
			else if (vtx.y > m_aEdit[nCntEdit].vtxMax.y)
			{
				m_aEdit[nCntEdit].vtxMax.y = vtx.y;
			}
			else if (vtx.z > m_aEdit[nCntEdit].vtxMax.z)
			{
				m_aEdit[nCntEdit].vtxMax.z = vtx.z;
			}

			//�S�Ă̒��_���r���ă��f���̍ŏ��l�𔲂��o��
			if (vtx.x < m_aEdit[nCntEdit].vtxMin.x)
			{
				m_aEdit[nCntEdit].vtxMin.x = vtx.x;
			}
			else if (vtx.y < m_aEdit[nCntEdit].vtxMin.y)
			{
				m_aEdit[nCntEdit].vtxMin.y = vtx.y;
			}
			else if (vtx.z < m_aEdit[nCntEdit].vtxMin.z)
			{
				m_aEdit[nCntEdit].vtxMin.z = vtx.z;
			}

			pVtxBuff += dwSizeFVF;								//���_�t�H�[�}�b�g�̃T�C�Y���|�C���^��i�߂�
		}

		//���_�o�b�t�@���A�����b�N
		m_aEdit[nCntEdit].pMesh->UnlockVertexBuffer();
	}
}

//==============================================================
//���f���̔z�u���ۑ�����
//==============================================================
void CEdit::SaveFile(void)
{
	FILE *pFile;		//�t�@�C���|�C���^

	pFile = fopen(FILE_MAP, "w");

	if (pFile != NULL)
	{//�t�@�C�����J������

		//�w�b�_�R�����g
		fprintf(pFile, "#=======================================================================\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "# �}�b�v�z�u���t�@�C�� [map.txt]\n");
		fprintf(pFile, "# Author;����������\n");
		fprintf(pFile, "#\n");
		fprintf(pFile, "#=======================================================================\n");

		//���f����
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ���f����\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "NUM_MODEL = %d\n", m_nNumAll);

		fprintf(pFile, "\n");		//���s

		//���f���t�@�C����
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ���f���t�@�C����\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		for (int nCntModel = 0; nCntModel < m_nNumAll; nCntModel++)
		{
			fprintf(pFile, "MODEL_FILENAME = %s				# %s\n", &m_aEdit[nCntModel].aFilename[0], &m_aEdit[nCntModel].aFilecomment[0]);
		}

		fprintf(pFile, "\n");		//���s

		//���f���z�u���
		fprintf(pFile, "#------------------------------------------------------------------------------\n");
		fprintf(pFile, "# ���f���z�u���\n");
		fprintf(pFile, "#------------------------------------------------------------------------------\n");

		for (int nCntModel = 0; nCntModel < m_nMaxModel; nCntModel++)
		{
			fprintf(pFile, "MODELSET\n");
			fprintf(pFile, "	INDEX = %d						# ���f���ԍ�\n", m_aSetEdit[nCntModel].nIndex);
			fprintf(pFile, "	POS = %.1f %.1f %.1f\n", m_aSetEdit[nCntModel].pos.x, m_aSetEdit[nCntModel].pos.y, m_aSetEdit[nCntModel].pos.z);
			fprintf(pFile, "END_MODELSET\n\n");
		}

		//�t�@�C������
		fclose(pFile);
	}
}

//==============================================================
//���f���̔z�u���ǂݍ��ݏ���
//==============================================================
void CEdit::LoadFile(void)
{
	FILE *pFile;		//�t�@�C���|�C���^
	char aString[MAX_STR];		//�������
	int nCntNum = 0, nCntName = 0;			//���f���̔ԍ��A�t�@�C�����ԍ�
	int nResult = 0;			//�Ō�̍s�܂ŗ�����

	pFile = fopen(FILE_MAP, "r");

	if (pFile != NULL)
	{//�t�@�C�����J������

		//���f�����ǂݍ���
		while (strcmp(&aString[0], "NUM_MODEL") != 0)
		{//���f������ǂݍ��ނ܂ł̊�

			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

			if (strcmp(&aString[0], "NUM_MODEL") == 0)
			{//[NUM_MODEL]��ǂݍ��񂾂�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
				fscanf(pFile, "%d", &m_nNumAll);		//���f�����ǂݍ���

				break;
			}
		}

		//���f���̃t�@�C�����ǂݍ���
		while (1)
		{
			fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

			if (strcmp(&aString[0], "MODEL_FILENAME") == 0)
			{//[MODEL_FILENAME]��ǂݍ��񂾂�

				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				fscanf(pFile, "%s", &m_aEdit[nCntName].aFilename[0]);	//�t�@�C�����ǂݍ���
				fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

				fscanf(pFile, "%s", &m_aEdit[nCntName].aFilecomment[0]);	//�t�@�C���R�����g�ǂݍ���

				if (nCntName == m_nNumAll - 1)
				{//�ő�l�Ɠ����ԍ��̎�

					break;
				}
				else
				{
					//���̔ԍ��ɐi��
					nCntName++;
				}
			}
		}

		//���f���̔z�u���ǂݍ���
		while (strcmp(&aString[0], "MODELSET") != 0 && nResult != EOF)
		{//[MODELSET]��ǂݍ��ނ܂ł̊� && �Ō�̍s����Ȃ���

			nResult = fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

			if (strcmp(&aString[0], "MODELSET") == 0)
			{//[MODELSET]��ǂݍ��񂾂�

				while (strcmp(&aString[0], "END_MODELSET") != 0)
				{//[END_MODELSET]��ǂݍ��ނ܂ł̊�

					fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

					if (strcmp(&aString[0], "INDEX") == 0)
					{//[INDEX]��ǂݍ��񂾂�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���
						fscanf(pFile, "%d", &m_aSetEdit[m_nMaxModel].nIndex);		//���f���ԍ��ǂݍ���

					}
					else if (strcmp(&aString[0], "POS") == 0)
					{//[POS]��ǂݍ��񂾂�

						fscanf(pFile, "%s", &aString[0]);		//�����ǂݍ���

						//�ʒu�ǂݍ���
						fscanf(pFile, "%f", &m_aSetEdit[m_nMaxModel].pos.x);
						fscanf(pFile, "%f", &m_aSetEdit[m_nMaxModel].pos.y);
						fscanf(pFile, "%f", &m_aSetEdit[m_nMaxModel].pos.z);

					}
				}

				m_nMaxModel++;		//���f���̍ő�ݒu�����Z
			}
		}

		//�t�@�C������
		fclose(pFile);
	}

	//���f���ݒu
	for (int nCntModel = 0; nCntModel < m_nMaxModel; nCntModel++)
	{
		//���f������
		CModel::Create(m_aSetEdit[nCntModel].pos, m_aSetEdit[nCntModel].rot, &m_aEdit[m_aSetEdit[nCntModel].nIndex].aFilename[0]);
	}
}

//==============================================================
//���f���̍폜����
//==============================================================
void CEdit::Delete(void)
{
	int nCnt;

	nCnt = CObjectX::CollisionEdit(m_aEdit[m_nNumModel].pos, m_aEdit[m_nNumModel].vtxMin, m_aEdit[m_nNumModel].vtxMax);

	m_aSetEdit[nCnt].nIndex = -1;

	//���ёւ�
	for (int nCntModel = 0; nCntModel < m_nMaxModel - 1; nCntModel++)
	{
		if (m_aSetEdit[nCntModel].nIndex == -1)
		{//�����ꂽ��

			m_aSetEdit[nCntModel].nIndex = m_aSetEdit[nCntModel + 1].nIndex;
			m_aSetEdit[nCntModel].pos = m_aSetEdit[nCntModel + 1].pos;
			m_aSetEdit[nCntModel].rot = m_aSetEdit[nCntModel + 1].rot;

			m_aSetEdit[nCntModel + 1].nIndex = -1;
		}
	}

	m_nMaxModel--;		//���f���̐ݒu�����Z
}