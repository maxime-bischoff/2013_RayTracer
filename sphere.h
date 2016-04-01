#ifndef SPHERE_H_INCLUDED
#define SPHERE_H_INCLUDED

#include "transform.h"
#include "flib_vec3.h"
#include "hit.h"
#include "ray.h"



class TSphere : public TTransform{ 

private :



	


public:
//	unsigned int m_iColor;

	




	TSphere();
	void Initialize();
	bool Trace(THit & tHit, const TRay & tRay) const ;
	
	


};




#endif
