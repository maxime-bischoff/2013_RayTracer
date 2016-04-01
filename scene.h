#ifndef SCENE_H_INCLUDED
#define SCENE_H_INCLUDED

#include "transform.h"
#include "sphere.h"
#include "flib_vec3.h"
#include "ray.h"
#include "hit.h"


class TScene{

private :

	 static const int MAX_TRANSFORMS = 32;
	
	 int m_iTransformCount;


public :
	 TTransform * m_pTransforms[ MAX_TRANSFORMS];
	//TScene();
    void  AddTransform(TTransform * pTransform);
	bool Trace(THit & tHit, const TRay & tRay) const ; 


};




#endif
