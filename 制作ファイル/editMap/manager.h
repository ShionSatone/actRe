//==============================================================
//
//�}�l�[�W������[manager.h]
//Author:����������
//
//==============================================================
#ifndef _MANAGER_H_		//���̃}�N����`������Ă��Ȃ�������
#define _MANAGER_H_		//2�d�C���N���[�h�h�~�̃}�N�����`����

#include "main.h"

//�O���錾
class CRenderer;		//�����_���[
class CInputKeyboard;	//�L�[�{�[�h����
class CInputJoyPad;		//�Q�[���p�b�h�̓���
class CCamera;			//�J����
class CLight;			//���C�g
class CDebugProc;		//�f�o�b�O�\��
class CTexture;			//�e�N�X�`��
class CEdit;			//���f���z�u
class CPlayerModel;		//�v���C���[
class CMaterial;		//�}�e���A��

//�}�l�[�W���N���X�̒�`
class CManager
{
public:

	CManager();		//�R���X�g���N�^
	~CManager();	//�f�X�g���N�^

	HRESULT Init(HINSTANCE hInstance,
		HWND hWnd,
		BOOL bWindow);		//����������
	void Uninit(void);		//�I������
	void Update(void);		//�X�V����
	void Draw(void);		//�`�揈��
	void Load3DAll(void);	//�S�Ẵe�N�X�`��2D�̓ǂݍ���
	void UnLoad3DAll(void);	//�S�Ẵe�N�X�`��2D�̔j��
	void Create3DAll(void);	//�S�ẴI�u�W�F�N�g3D�̐���
	void ResetMap(void);	//�}�b�v�̍Đ���

	static CRenderer *GetRenderer(void) { return m_pRenderer; }		//�����_���[�̎擾
	static CInputKeyboard *GetInputKeyboard(void) { return m_pInputKeyboard; }		//�L�[�{�[�h�̎擾
	static CInputJoyPad *GetInputJoyPad(void) { return m_pInputJoyPad; }			//�Q�[���p�b�h�̎擾

	static CDebugProc *GetDebugProc(void) { return m_pDebugProc; }	//�f�o�b�O�\���̎擾

	static CCamera *GetCamera(void) { return m_pCamera; }			//�J�����̏��
	static CLight *GetLight(void) { return m_pLight; }				//���C�g�̏��
	static CTexture *GetTexture(void) { return m_pTexture; }		//�e�N�X�`���̏��
	static CEdit *GetEdit(void) { return m_pEdit; }					//���f���z�u�̏��
	static CPlayerModel *GetPlayerModel(void) { return m_pPlayerModel; }		//���f���z�u�̏��
	static CMaterial *GetMaterial(void) { return m_pMaterial; }		//�}�e���A���̏��

private:
	static CRenderer *m_pRenderer;		//�����_���[�̏��
	static CInputKeyboard *m_pInputKeyboard;	//�L�[�{�[�h�̏��
	static CInputJoyPad *m_pInputJoyPad;		//�Q�[���p�b�h�̏��

	static CDebugProc *m_pDebugProc;		//�f�o�b�O�\���̏��

	static CCamera *m_pCamera;			//�J�����̏��
	static CLight *m_pLight;			//���C�g�̏��
	static CTexture *m_pTexture;		//�e�N�X�`���̏��
	static CEdit *m_pEdit;				//���f���z�u�̏��
	static CPlayerModel *m_pPlayerModel;		//�v���C���[�̏��
	static CMaterial *m_pMaterial;		//�}�e���A���̏��
	
	HINSTANCE m_hInstance;
	HWND m_hWnd;
	BOOL m_bWindow;
};

#endif
