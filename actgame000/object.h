//==============================================================
//
//�I�u�W�F�N�g����[object.h]
//Author:����������
//
//==============================================================
#ifndef _OBJECT_H_		//���̃}�N����`������Ă��Ȃ�������
#define _OBJECT_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�}�N����`
#define MAX_OBJECT			(1280)		//�I�u�W�F�N�g�̐�
#define DEFAULT_PRIORITY	(3)			//�D�揇�ʂ̃f�t�H���g�l
#define NUM_PRIORITY		(8)			//�D�揇�ʂ̑���

//�I�u�W�F�N�g�N���X
class CObject
{
public:

	//�I�u�W�F�N�g�̎��
	enum TYPE
	{
		TYPE_NONE = 0,		//�����Ȃ�
		TYPE_PLAYER,		//�v���C���[
		TYPE_ENEMY,			//�G
		TYPE_BULLET,		//�e
		TYPE_EXPLOSION,		//����
		TYPE_EFFECT,		//�G�t�F�N�g
		TYPE_PARTICLE,		//�p�[�e�B�N��
		TYPE_SCORE,			//�X�R�A
		TYPE_BLOCK,			//�u���b�N
		TYPE_ITEM,			//�A�C�e��
		TYPE_FIELD,			//��
		TYPE_WALL,			//��
		TYPE_MODEL,			//���f��
		TYPE_ALPHA_BLOCK,	//�����u���b�N
		TYPE_PAUSE,			//�|�[�Y
		TYPE_SCENE,			//�V�[��
		TYPE_FADE,			//�t�F�[�h
		TYPE_MAX			//��ނ̍ő吔
	};

	//�p�[�e�B�N���̎��
	//typedef enum
	//{
	//	PARTICLETYPE_NONE = 0,		//�����Ȃ�
	//	PARTICLETYPE_WATER,			//��
	//	PARTICLETYPE_ICE,			//�X
	//	PARTICLETYPE_VAPOR,			//���C
	//	PARTICLETYPE_ENEMY,			//�G�̒e
	//	PARTICLETYPE_WITCH,			//�����̒e
	//	PARTICLETYPE_EXPLOSION,		//����
	//	PARTICLETYPE_LAND,			//���n
	//	PARTICLETYPE_LIFE,			//��
	//	PARTICLETYPE_JUMP,			//�W�����v
	//	PARTICLETYPE_MOVE,			//�ړ�
	//	PARTICLETYPE_MAX
	//} PARTICLETYPE;

	//�I�u�W�F�N�g�̏��
	enum STATE
	{
		STATE_NONE = 0,		//�ʏ���
		STATE_ATTACK,		//�U�����
		STATE_DAMAGE,		//�_���[�W���
		STATE_DEATH,		//���S���
		STATE_APPEAR,		//�_�ŏ��
		STATE_WAIT,			//�҂����
		STATE_MAX
	};

	CObject();				//�R���X�g���N�^
	//CObject(TYPE type);		//�R���X�g���N�^�̃I�[�o�[���[�h
	CObject(int nPriority = DEFAULT_PRIORITY);		//�R���X�g���N�^�̃I�[�o�[���[�h
	virtual ~CObject();		//�f�X�g���N�^

	static void ReleaseAll(void);		//�S�Ẵ����[�X����
	static void UpdateAll(void);		//�S�Ă̍X�V����
	static void DrawAll(void);			//�S�Ă̕`�揈��
	static void ResetMapAll(void);		//�}�b�v���Z�b�g����
	static void DeathAll(void);			//�S�ĂɎ��S�t���O�𗧂Ă鏈��

	virtual HRESULT Init() = 0;			//����������
	virtual void Uninit(void) = 0;		//�I������
	virtual void Update(void) = 0;		//�X�V����
	virtual void Draw(void) = 0;		//�`�揈��

	virtual void Hit(void) {};			//�q�b�g����

	virtual void SetPotision(D3DXVECTOR3 pos, float fWidth, float fHeight) {}				//�ʒu�̐ݒ菈��
	virtual void SetRotation(D3DXVECTOR3 rot, float fWidth, float fHeight) {}				//�����̐ݒ菈��(2D)
	virtual void SetRotation(D3DXVECTOR3 rot) {}											//�����̐ݒ菈��(3D)

	virtual D3DXVECTOR3 GetPosition(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�ʒu�̎擾
	virtual D3DXVECTOR3 GetRotation(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�����̎擾
	virtual D3DXVECTOR3 GetSizeMin(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f);}			//�傫���̍ŏ��l�擾
	virtual D3DXVECTOR3 GetSizeMax(void) { return D3DXVECTOR3(0.0f, 0.0f, 0.0f); }			//�傫���̍ő�l�擾

	virtual void SetState(STATE state){}					//�I�u�W�F�N�g�̏�Ԑݒ�
	virtual STATE GetState(void) { return STATE_NONE; }		//�I�u�W�F�N�g�̏�Ԏ擾
	//virtual int GetItemType(void) { return PARTICLETYPE_WATER; }	//�A�C�e���̎�ގ擾

	void SetType(TYPE type) { m_type = type; }	//�I�u�W�F�N�g�̎�ނ̐ݒ�
	TYPE GetType(void) { return m_type; }		//�I�u�W�F�N�g�̎�ނ̎擾

	static CObject *GetObject(int nPriority, int nIdx) /*{ return m_apObject[nIdx]; }*/;	//�I�u�W�F�N�g�̏��擾
	static CObject *GetTop(int nPriority);		//�擪�I�u�W�F�N�g�̃|�C���^�擾

protected:
	void Release(void);		//�����[�X����

private:
	//static CObject *m_apObject[NUM_PRIORITY][MAX_OBJECT];
	static int m_nNumAll;	//�I�u�W�F�N�g����
	int m_nID;				//�������g��ID
	int m_nPriority;		//�D�揇�ʂ̈ʒu
	TYPE m_type;			//�I�u�W�F�N�g�̎��
	STATE m_state;			//�I�u�W�F�N�g�̏��

	static CObject *m_apTop[NUM_PRIORITY];		//�擪�̃I�u�W�F�N�g�ւ̃|�C���^
	static CObject *m_apCur[NUM_PRIORITY];		//�Ō���̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pPrev;			//�O�̃I�u�W�F�N�g�ւ̃|�C���^
	CObject *m_pNext;			//���̃I�u�W�F�N�g�ւ̃|�C���^
	bool m_bDeath;				//���S�t���O
};

#endif
