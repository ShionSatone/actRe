//==============================================================
//
//�`���[�g���A���摜�̏���[tutorial_texture.h]
//Author:����������
//
//==============================================================
#ifndef _TUTORIAL_TEXTURE_H_		//���̃}�N����`������Ă��Ȃ�������
#define _TUTORIAL_TEXTURE_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object3D.h"

//�`���[�g���A��UI�N���X�̒�`
class CTutorialUI : public CObject3D
{
public:

	//�`���[�g���A���̃X�e�b�v
	enum STEP
	{
		STEP_MOVE = 0,		//�ړ�
		STEP_JUMP,			//�W�����v
		STEP_DASH,			//�_�b�V��
		STEP_ALPHA,			//�ʂ蔲��
		STEP_ITEM,			//�A�C�e��
		STEP_ENEMY,			//�G
		STEP_MAX
	};

	CTutorialUI();		//�R���X�g���N�^
	CTutorialUI(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CTutorialUI();		//�f�X�g���N�^

	static CTutorialUI *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot, int nType);		//��������

	HRESULT Init(void);
	void UnInit(void);
	void Update(void);
	void Draw(void);

private:
	static LPDIRECT3DTEXTURE9 m_pTexture;
	static const char *m_apFilename[STEP_MAX];		//�e�N�X�`���̖��O
	int m_nIdxTexture;		//�e�N�X�`���̔ԍ�

	D3DXVECTOR3 m_pos;		//�ʒu
	int m_nType;			//�`���[�g���A���̎��
};

#endif
