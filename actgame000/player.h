//==============================================================
//
//�v���C���[�̃��f������[player.h]
//Author:����������
//
//==============================================================
#ifndef _PLAYER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _PLAYER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "object.h"

class CModelHier;	//���f���̊K�w�\��
class CMotion;		//���[�V�����̊K�w�\��

//�v���C���[�N���X�̒�`
class CPlayer : public CObject
{
public:

	CPlayer();		//�R���X�g���N�^
	CPlayer(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//�R���X�g���N�^(�I�[�o�[���[�h)
	~CPlayer();		//�f�X�g���N�^

	static CPlayer *Create(D3DXVECTOR3 pos, D3DXVECTOR3 rot);		//��������

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

	void Hit(void);

	void SetPosition(D3DXVECTOR3 pos) { m_pos = pos; }		//�ʒu�ݒ�
	void SetRotation(D3DXVECTOR3 rot) { m_rot = rot; }		//�����ݒ�
	void SetState(STATE state) { m_state = state; }			//��Ԑݒ�

	D3DXVECTOR3 GetPosition(void) { return m_pos; }			//�ʒu�擾
	D3DXVECTOR3 GetRotation(void) { return m_rot; }			//�����擾
	D3DXVECTOR3 GetMove(void) { return m_move; }			//�ړ��ʎ擾
	bool GetIsJump(void) { return m_bJump; }				//�W�����v�̎擾
	bool GetIsMove(void) { return m_bMove; }				//�ړ��̎擾
	bool GetIsLand(void) { return m_bLand; }				//���n�̎擾

	D3DXVECTOR3 GetSizeMin(void) { return m_min; }			//�傫���̍ő�l�擾
	D3DXVECTOR3 GetSizeMax(void) { return m_max; }			//�傫���̍ŏ��l�擾

private:
	//�v���C���[�̃p�[�c
	enum PARTS
	{
		PARTS_BODY = 0,		//[0]��
		PARTS_HEAD,			//[1]��
		PARTS_HAIR,			//[2]��
		PARTS_LU_ARM,		//[3]���r��
		PARTS_LD_ARM,		//[4]���r��
		PARTS_L_HAND,		//[5]����
		PARTS_RU_ARM,		//[6]�E�r��
		PARTS_RD_ARM,		//[7]�E�r��
		PARTS_R_HAND,		//[8]�E��
		PARTS_WAIST,		//[9]��
		PARTS_LU_LEG,		//[10]��������
		PARTS_LD_LEG,		//[11]���ӂ���͂�
		PARTS_L_SHOE,		//[12]���C
		PARTS_RU_LEG,		//[13]�E������
		PARTS_RD_LEG,		//[14]�E�ӂ���͂�
		PARTS_R_SHOE,		//[15]�E�C
		PARTS_MAX
	};

	void UpdateFront(void);			//��O���̍X�V����
	void UpdateState(void);			//��Ԃ̍X�V����

	void MotionManager(void);				//���[�V�����Ǘ�
	void ControlFrontKeyboard(void);		//�v���C���[�L�[�{�[�h����(��O��)
	void ControlFrontKeyboardMove(void);	//�v���C���[�L�[�{�[�h�̈ړ�����(��O��)
	void ControlFrontKeyboardJump(void);	//�v���C���[�L�[�{�[�h�̃W�����v����(��O��)
	void ControlFrontKeyboardDash(void);	//�v���C���[�L�[�{�[�h�̃_�b�V������(��O��)

	void ControlHumanPad(void);				//�v���C���[�R���g���[���[����(�l��)
	void Screen(void);						//��ʊO����
	void LoadFile(void);					//���f���t�@�C���ǂݍ���
	void RotCorrection(void);				//�����̕␳����

	static char *m_apFileName[PARTS_MAX];		//�t�@�C����

	D3DXVECTOR3 m_pos;		//�ʒu
	D3DXVECTOR3 m_posOld;	//�O��̈ʒu
	D3DXVECTOR3 m_posSave;		//�����p�̈ʒu
	D3DXVECTOR3 m_posKeepHuman;	//�l�Ԃ̈ʒu�ۑ��p
	D3DXVECTOR3 m_posKeepFish;	//�����̈ʒu�ۑ��p
	D3DXVECTOR3 m_move;		//�ړ���
	D3DXVECTOR3 m_rot;		//����
	D3DXVECTOR3 m_max;		//�l�Ԃ̍ő�l
	D3DXVECTOR3 m_min;		//�l�Ԃ̍ŏ��l
	D3DXMATRIX m_mtxWorld;	//���[���h�}�g���b�N�X
	CModelHier *m_apModel[PARTS_MAX];		//���f��(�p�[�c)�ւ̃|�C���^
	int m_nNumModel;		//���f��(�p�[�c)�̑���
	int m_nCntDamage;		//�_���[�W�J�E���^�[

	bool m_bMove;			//�����Ă邩�̔���
	bool m_bMoveL;			//�������Ă��邩�̔���
	bool m_bMoveR;			//�E�����Ă��邩�̔���
	bool m_bJump;			//�W�����v�������̔���
	bool m_bLand;			//���n������
	bool m_bDash;			//�_�b�V��������

	float m_fRotDest;		//�ڕW
	float m_fRotDiff;		//����

	STATE m_state;			//�v���C���[�̏��

	int m_nDashCounter;		//�_�b�V��������

	//int m_particleType;		//�p�[�e�B�N���̎��
	int m_nType;			//���Ԗڂ̃p�[�e�B�N����
	int m_nParticleLife;	//�p�[�e�B�N���̎���
	int m_nCntHit;			//�q�b�g�ł���܂ł̃J�E���^�[
	int m_nCntMove;			//�����̃J�E���^�[
	int m_nCntSand;			//���̃p�[�e�B�N���J�E���^�[

	bool m_bPad;			//�p�b�h�̃X�e�B�b�N��|���Ă邩

	CMotion *m_pMotion;		//���[�V�������
};

#endif
