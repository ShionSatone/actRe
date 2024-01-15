//==============================================================
//
//���̏���[field.h]
//Author:����������
//
//==============================================================
#ifndef _FIELD_H_		//���̃}�N����`������Ă��Ȃ�������
#define _FIELD_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include"object3D.h"

//���N���X�̒�`
class CField : public CObject3D
{
public:
	CField();		//�R���X�g���N�^
	CField(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CField();		//�f�X�g���N�^

	static HRESULT Load(void);		//�e�N�X�`���̓ǂݍ���
	static void Unload(void);		//�e�N�X�`���̔j��
	static CField *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(D3DXVECTOR3 pos, D3DXVECTOR3 rot);
	void UnInit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
};

#endif
