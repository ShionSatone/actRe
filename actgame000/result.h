//==============================================================
//
//���U���g����[result.h]
//Author:����������
//
//==============================================================
#ifndef _RESULT_H_		//���̃}�N����`������Ă��Ȃ�������
#define _RESULT_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "manager.h"

//�O���錾
class CScore;			//�X�R�A�̏��

//���U���g��ʃN���X�̒�`
class CResult : public CScene
{
public:
	CResult();
	~CResult();

	HRESULT Init(void);
	void Uninit(void);
	void Update(void);
	void Draw(void);

private:
	static CScore *m_pScore;		//�X�R�A�̏��

	static bool bReset;				//���Z�b�g������
};

#endif

