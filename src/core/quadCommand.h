#ifndef _QUAD_COMMAND_H_
#define _QUAD_COMMAND_H_

#include"core\renderCommand.h"
#include"core\types.h"
#include"core\glProgramState.h"


/**
*	\brief ����quad����Ⱦ����
*/
class QuadCommand : public RenderCommand
{
public:
	QuadCommand();
	virtual ~QuadCommand();

	void Init(float globalOrder,GLProgramStatePtr programState,
			GLuint textureID, GLuint normalTextureID, Quad quads,
			int quadCounts,const BlendFunc&blendFunc,
			const Matrix4& transfomr,const Matrix4& modelView, 
			bool autoReleased = false);

	void UseShade();

	int GetQuadCounts()const;
	const Quad* GetQuads()const;
	uint32_t GetShadeState()const;
	BlendFunc GetBlendFunc()const;
	Matrix4 GetTransfomr()const;
	Matrix4 GetModelView()const;
	bool IsDeferredShade()const;
	void SetDeferredShade(bool isDeferred);
	void SetNormalTexture(GLuint normalTextureID);

private:
	void GenerateShadeState();

	GLProgramStatePtr mProgramState;
	GLuint mTextureID;
	GLuint mNormalTextureID;
	Quad  mQuads;
	int   mQuadCounts;
	BlendFunc mBlendFunc;
	uint32_t mShadeState;
	Matrix4 mTransform;
	Matrix4 mModelView;
	bool mIsDeferredShade;
};

using QuadCommandPtr = std::shared_ptr<QuadCommand>;

#endif