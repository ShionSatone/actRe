//==============================================================
//
//�I�u�W�F�N�g3D����[object3D.h]
//Author:����������
//
//==============================================================
#ifndef _OBJECT3D_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT3D_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

//�I�u�W�F�N�g3D�N���X
class CObject3D : public CObject
{
public:
	CObject3D();	//�R���X�g���N�^
	~CObject3D();	//�f�X�g���N�^

	static CObject3D *Create(void);		//��������

	virtual HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//����������
	virtual void Uninit(void);		//�I������
	virtual void Update(void);		//�X�V����
	virtual void Draw(void);		//�`�揈��

	void BindTexture(int nIdxTexture);		//�O������e�N�X�`���w��
	void SetSize(float fWidth, float fHeight);			//�I�u�W�F�N�g�̃T�C�Y�ݒ�

	void SetPosition(TYPE type, D3DXVECTOR3 pos) { m_pos = pos; }			//�ʒu�ݒ�
	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�擾
	//void SetMove(D3DXVECTOR3 move) { m_move = move; }	//�ړ��ʐݒ�
	//D3DXVECTOR3 GetMove(void) { return m_move; }		//�ړ��ʎ擾
	//void SetColor(TYPE type, D3DXCOLOR col);		//�F�ݒ�
	//D3DXCOLOR GetColor(void) { return m_col; }		//�F�ݒ�


private:
	LPDIRECT3DTEXTURE9 m_pTexture;			//�e�N�X�`���ւ̃|�C���^
	LPDIRECT3DVERTEXBUFFER9 m_pVtxBuff;		//���_�o�b�t�@�ւ̃|�C���^
	D3DXMATRIX m_mtxWorld;					//���[���h�}�g���b�N�X
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXCOLOR m_col;		//�F
	float m_fHeight;		//����
	float m_fWidth;			//����
	TYPE m_type;			//���
};

#endif
