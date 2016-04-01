#ifndef TRANSFORM_H_INCLUDED
#define TRANSFORM_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include "hit.h"
#include "ray.h"
#include "axes.h"



class TTransform{

private :
	virtual bool Trace(THit & tHit, const TRay & tRay) const ;

public :

	TGfxImage * m_pImageTexture ;
	TGfxImage * m_pImageMapNight ;
	TGfxImage * m_pImageNorm ;
	TGfxImage * m_pImageSpec ;

	int m_iMapX ;
	int m_iMapY ;

	unsigned int * pDataTexture ;
	unsigned int * pDataNight ;
	unsigned int * pDataNorm ;
	unsigned int * pDataSpec ;

	bool isTextured;
	TAxes m_tAxes;



	TGfxVec3 m_tPosition;
	TGfxVec3 m_tAxisX;
	TGfxVec3 m_tAxisY;
	TGfxVec3 m_tAxisZ;
	TGfxVec3 m_tScale;
	unsigned int m_iColor;

	TTransform();
	
	void LookAt( const TGfxVec3 & tTarget );

	 bool TraceWorld(THit & tHit, const TRay & tRay) const;
	

};

#endif
