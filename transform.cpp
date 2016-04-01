#include "transform.h"
#include <math.h>


TTransform::TTransform()
	: m_tPosition(0.0f,0.0f,0.0f) 
	//, m_tAxes.x(1.0f,0.0f,0.0f) 
	//, m_tAxes.y(0.0f,1.0f,0.0f) 
	//, m_tAxes.z(0.0f,0.0f,1.0f) 
	, m_iColor ( EGfxColor_Red)
	, isTextured (false)
{

 m_pImageTexture = 0 ;
 m_pImageMapNight =0;
 m_pImageNorm =0;
 m_pImageSpec =0;



}

void TTransform::LookAt( const TGfxVec3 & tTarget )
{	
	m_tAxes.z =   (m_tPosition - tTarget ).Normalize();
	m_tAxes.x =  TGfxVec3 (0.0f,1.0f,0.0f).CrossProduct(m_tAxes.z).Normalize();
	m_tAxisY = m_tAxes.z.CrossProduct(m_tAxes.x);
}


bool TTransform::TraceWorld(THit & tHit, const TRay & tRay) const
{
	TRay tLocalRay;
	tLocalRay.m_tSrc = tRay.m_tSrc -this->m_tPosition  ;
	tLocalRay.m_tDir = tRay.m_tDir  ;
	

	TGfxVec3 tProductSrc = TGfxVec3(this->m_tAxes.x.DotProduct(tLocalRay.m_tSrc) / m_tScale.x  , this->m_tAxes.y.DotProduct(tLocalRay.m_tSrc) / m_tScale.y,this->m_tAxes.z.DotProduct(tLocalRay.m_tSrc)/ m_tScale.z );
	TGfxVec3 tProductDir = TGfxVec3(this->m_tAxes.x.DotProduct(tLocalRay.m_tDir) / m_tScale.x,this->m_tAxes.y.DotProduct(tLocalRay.m_tDir) / m_tScale.y,this->m_tAxes.z.DotProduct(tLocalRay.m_tDir)/ m_tScale.z);

	//float fAngleX = asin(  this->m_tAxes.x

	
	tLocalRay.m_tSrc = tProductSrc;
	tLocalRay.m_tDir = tProductDir.Normalize() ;




	THit tLocalHit;
	
	if(Trace(tLocalHit, tLocalRay))
	{		
		tHit.m_pTransform = tLocalHit.m_pTransform;
		tHit.m_tUV = tLocalHit.m_tUV;
		tHit.m_tPos = tLocalHit.m_tPos;
	
		
		//tHit = tLocalHit;
		tHit.m_tNormale = m_tAxes.Multiply(tLocalHit.m_tNormale) ;

	//	tHit.m_tPos = tLocalHit.m_tPos - this->m_tPosition;
		tHit.m_tPos = m_tAxes.Multiply(tLocalHit.m_tPos) + this->m_tPosition ;

		tHit.m_tPos.x  *= m_tScale.x;
		tHit.m_tPos.y  *= m_tScale.y;
		tHit.m_tPos.z  *= m_tScale.z;

		//tHit.m_tPos /= m_fScale;
		return true;
	}



	return false;


}


  bool TTransform::Trace(THit & tHit, const TRay & tRay) const 
{

	return false;
}