#ifndef PLANE_H_INCLUDED
#define PLANE_H_INCLUDED

#include "transform.h"
#include "flib_vec3.h"
#include "hit.h"
#include "ray.h"



class TPlane : public TTransform{ 

private :


	TGfxTexture * m_pTexture;


public:

	TGfxVec3 tNormale;	
//	unsigned int m_iColor;

	bool Trace(THit & tHit, const TRay & tRay) const ;



};




#endif
