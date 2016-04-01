#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "transform.h"
#include "scene.h"
#include "flib.h"




class TCamera : public TTransform{

private :

	//float m_fFOV;


public:
	float m_fFOV;
	TGfxVec3 tDirLight;

	struct TPointLight
	{
		TGfxVec3 tPos;
		TGfxVec3 tDir;	
	};

	TPointLight tPointLight;
	TCamera();

	void Render(TGfxImage * pImage, const TScene & tScene) const;
};


#endif
