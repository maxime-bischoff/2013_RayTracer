#include "sphere.h"
#include <math.h>
#include "flib_vec2.h"


TGfxVec3 IntColorToVec32(unsigned int iColor)
{
	unsigned char * pColor = reinterpret_cast<unsigned char *>(&iColor);
	TGfxVec3 tColor;
	tColor.x = pColor[ 0 ] / 255.0f;
	tColor.y = pColor[ 1 ] / 255.0f;
	tColor.z = pColor[ 2 ] / 255.0f;
	return tColor;

}


unsigned int VecColorToInt2(TGfxVec3 tColor)
{

	return (GfxColor(tColor.x * 255 , tColor.y * 255, tColor.z * 255, 255));

}

TSphere::TSphere()
{





}

void TSphere::Initialize()
{

	m_pImageTexture = GfxImageLoad("earth.tga");
	//m_pImageMapNight = GfxImageLoad("earth_night.tga");
	m_pImageNorm = GfxImageLoad("earth_norm.tga");
	m_pImageSpec = GfxImageLoad("earth_spec.tga");

	m_iMapX = GfxImageGetSizeX(m_pImageTexture);
	m_iMapY = GfxImageGetSizeY(m_pImageTexture);
	pDataTexture = GfxImageGetData(m_pImageTexture);
	//pDataNight = GfxImageGetData(m_pImageMapNight);
	pDataNorm = GfxImageGetData(m_pImageNorm);
	pDataSpec = GfxImageGetData(m_pImageSpec);

	isTextured = true;


}


bool TSphere::Trace(THit & tHit, const TRay & tRay) const 
{	

	TGfxVec3 greenVec = - tRay.m_tSrc;
	float dot = greenVec.DotProduct(tRay.m_tDir);
	TGfxVec3 closestPoint = tRay.m_tSrc + tRay.m_tDir * dot;
	float closestLength = greenVec.SquaredLength() - dot*dot;

if(closestLength <1)
	{
		

		float fInsideLength = sqrt( 1 - closestLength ) ;

		if( dot - fInsideLength >0)
		{
			tHit.m_tPos = tRay.m_tSrc + tRay.m_tDir * ( dot - fInsideLength ) ;	

			tHit.m_tUV.x = ((atan2(tHit.m_tPos.z, tHit.m_tPos.x) / (1*M_PI) )+ 1 )/2  * 1.0f  ;
			tHit.m_tUV.y = ((asin( tHit.m_tPos.y ) / (M_PI)) +0.5 ) * 1.0f ;	
			//tHit.iPixelColor = this->m_iColor;
			tHit.m_pTransform = this;
			tHit.m_tNormale = - tHit.m_tPos;

			TGfxVec3 tangente ;//= TGfxVec3( tHit.m_tPos.x, 0, tHit.m_tPos.z ).Normalize();
			tangente = TGfxVec3( -tHit.m_tPos.z, 0, tHit.m_tPos.x);

			int x =	  static_cast<int>(( m_iMapX * tHit.m_tUV.x) - m_iMapX)*-1;
			int y =   static_cast<int>(( m_iMapY * tHit.m_tUV.y) - m_iMapY)*-1;


			int iTabIndex = static_cast<int>(  x + y * m_iMapX );			


			TGfxVec3 tColorNormale = IntColorToVec32(pDataNorm[iTabIndex]) ;
			
			tColorNormale.x = tColorNormale.x*2-1;
			tColorNormale.y = tColorNormale.y*2-1;
			tColorNormale.z	= tColorNormale.z*2-1;
			tHit.m_tNormale = ( tangente * tColorNormale.x + 
								tHit.m_tNormale.CrossProduct(tangente) * tColorNormale.y +
								tHit.m_tNormale * tColorNormale.z
							  ).Normalize();





		return true;	

		}
	}else{	
		return false;

}
}