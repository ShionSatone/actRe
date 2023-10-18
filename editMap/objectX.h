//==============================================================
//
//�I�u�W�F�N�gX����[objectX.h]
//Author:����������
//
//==============================================================
#ifndef _OBJECTX_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECTX_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�}�N����`
#define MAX_TEX		(128)		//�e�N�X�`���̍ő吔

//�I�u�W�F�N�gX�N���X
class CObjectX : public CObject
{
public:
	CObjectX();	//�R���X�g���N�^
	~CObjectX();	//�f�X�g���N�^

	static CObjectX *Create(void);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	//void BindTexture(LPDIRECT3DTEXTURE9 pTexture,int nCntTex);		//�O������e�N�X�`���w��
	void BindMaterial(int nIdx);		//�O������e�N�X�`���w��

	void BindXFile(LPD3DXMESH pMesh, LPD3DXBUFFER pBuffMat, DWORD dwNumMat);

	void SetPosition(TYPE type, D3DXVECTOR3 pos) { m_pos = pos; }			//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�擾
	void SetRotation(TYPE type, D3DXVECTOR3 rot) { m_rot = rot; }			//�����ݒ�
	D3DXVECTOR3 GetRotation(void) { return m_rot; }		//�����̎擾

	void SetSize(D3DXVECTOR3 vtxMin, D3DXVECTOR3 vtxMax) { m_vtxMin = vtxMin;  m_vtxMax = vtxMax; }		//���f���̑傫���ݒ�
	D3DXVECTOR3 GetSizeMin(void) { return m_vtxMin; }		//�ŏ��̑傫���擾
	D3DXVECTOR3 GetSizeMax(void) { return m_vtxMax; }		//�ő�̑傫���擾

	void SetModel(void);		//���f���̐ݒ菈��
	static void Collision(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max);		//���f���̓����蔻��
	static void Collision2DModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max, D3DXVECTOR3 posModel, D3DXVECTOR3 minModel, D3DXVECTOR3 maxModel);		//���f����2D�̓����蔻��
	static void Collision3DModel(D3DXVECTOR3 *pPos, D3DXVECTOR3 *pPosOld, D3DXVECTOR3 *pMove, D3DXVECTOR3 Min, D3DXVECTOR3 Max, D3DXVECTOR3 posModel, D3DXVECTOR3 minModel, D3DXVECTOR3 maxModel);		//���f����3D�̓����蔻��
	static int CollisionEdit(D3DXVECTOR3 pos, D3DXVECTOR3 Min, D3DXVECTOR3 Max);		//�G�f�B�b�g�̃��f���Ƃ̓����蔻��

	void SetState(STATE state) { m_state = state; }		//�G�̏�Ԑݒ�
	STATE GetState(void) { return m_state; }			//�G�̏�Ԏ擾

private:
	LPDIRECT3DTEXTURE9 *m_apTexture;	//�e�N�X�`���ւ̃|�C���^
	int m_nIdxTexture[MAX_TEX];		//�e�N�X�`���̔ԍ�

	LPD3DXMESH m_pMesh;							//���b�V���i���_���j�ւ̃|�C���^
	LPD3DXBUFFER m_pBuffMat;					//�}�e���A���ւ̃|�C���^
	DWORD m_dwNumMat;							//�}�e���A���̐�

	D3DXMATRIX m_mtxWorld;						//���[���h�}�g���b�N�X
	D3DXVECTOR3 m_vtxMin;						//���f���̍ŏ��l
	D3DXVECTOR3 m_vtxMax;						//���f���̍ő�l

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		//�F
	TYPE m_type;			//���
	STATE m_state;			//���

	int m_nIdxParent;				//�e���f���̃C���f�b�N�X
	D3DXMATERIAL m_matColor;		//�}�e���A���f�[�^�ւ̃|�C���^
	int m_nIndexNum;				//���f���ԍ�

	int m_nIdxModel;		//���f���̔ԍ�
};

#endif