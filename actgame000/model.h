//==============================================================
//
//���f������[model.h]
//Author:����������
//
//==============================================================
#ifndef _MODEL_H_		//���̃}�N����`������Ă��Ȃ�������
#define _MODEL_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"objectX.h"

//�}�N����`
#define MAX_MODEL			(640)		//���f���̐�

//���f���N���X�̒�`
class CModel : public CObjectX
{
public:
	CModel();		//�R���X�g���N�^
	CModel(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CModel();		//�f�X�g���N�^

	static HRESULT Load(const char *pFilename);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CModel *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, const char *pFilename);		//��������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);
	void SetType(TYPE type);		//�I�u�W�F�N�g�̎�ސݒ�

private:
	static LPD3DXMESH m_pMesh;						//���b�V���i���_���j�ւ̃|�C���^
	static LPD3DXBUFFER m_pBuffMat;					//�}�e���A���ւ̃|�C���^
	static DWORD m_dwNumMat;						//�}�e���A���̐�
	static const char *m_pFilename;					//�t�@�C���̖��O

	int m_nIdxModel;		//���f���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_rot;		//����
	TYPE m_type;
};

#endif