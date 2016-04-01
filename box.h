
#ifndef BOX_H_INCLUDED
#define BOX_H_INCLUDED
#include "transform.h"

class TBox : public TTransform{

public:
	bool Trace( struct THit & tHit, const struct TRay & tRay ) const;
	TBox();
	void Initialize();

private:

};



#endif