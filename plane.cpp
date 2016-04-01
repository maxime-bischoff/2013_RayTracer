#include "plane.h"
#include <math.h>
#include "flib_vec2.h"

unsigned int VecColorToInt(TGfxVec3 tColor)
{

	return (GfxColor(tColor.x * 255 , tColor.y * 255, tColor.z * 255, 255));

}

TGfxVec3 IntColorToVec(unsigned int iColor)
{
	unsigned char * pColor = reinterpret_cast<unsigned char *>(&iColor);
	TGfxVec3 tColor;
	tColor.x = pColor[ 0 ] / 255.0f;
	tColor.y = pColor[ 1 ] / 255.0f;
	tColor.z = pColor[ 2 ] / 255.0f;
	return tColor;

}


bool TPlane::Trace(THit & tHit, const TRay & tRay) const 
{
	float dot = tRay.m_tDir.DotProduct(tNormale);
	if(dot < 0)
	{
		float lengthTest = tRay.m_tSrc.y /-dot;
		tHit.m_tPos = tRay.m_tSrc +  tRay.m_tDir * lengthTest;			

		tHit.m_tUV.x = tHit.m_tPos.x;
		tHit.m_tUV.y = tHit.m_tPos.z;	


		tHit.m_tUV.x -= floor(tHit.m_tUV.x);
		tHit.m_tUV.y -= floor(tHit.m_tUV.y);		

		tHit.iPixelColor = this->m_iColor;

	
		tHit.m_tNormale = this->tNormale;
		tHit.m_pTransform = this;
		return true;	

	}else{
		return false;
		}

}