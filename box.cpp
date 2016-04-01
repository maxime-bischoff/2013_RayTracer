#include "box.h"	
#include "flib_vec3.h"
#include <math.h>

bool TBox::Trace( struct THit & tHit, const struct TRay & tRay ) const
{
	const TGfxVec3 pSides[ 6 ] = 
	{
		TGfxVec3 ( 1.0f, 0.0f, 0.0f ),
		TGfxVec3 ( 0.0f, 1.0f, 0.0f ),
		TGfxVec3 ( 0.0f, 0.0f, 1.0f ),

		TGfxVec3 ( -1.0f, 0.0f, 0.0f  ),
		TGfxVec3 ( 0.0f, -1.0f, 0.0f  ),
		TGfxVec3 ( 0.0f,  0.0f, -1.0f ),	
	};


	
	for (int iSide= 0; iSide < 6 ; ++iSide )
	{	
		float H = ( pSides[iSide]-tRay.m_tSrc ).DotProduct(pSides[iSide]);
		float h = pSides[iSide].DotProduct(tRay.m_tDir);
		if(h<0)
		{
		float length =  H / h;

		TGfxVec3 tHitPoint = tRay.m_tSrc +  tRay.m_tDir * length;
		tHit.m_tPos = tHitPoint;		


			if(tHit.m_tPos.x * tHit.m_tPos.x <=1.001f 
				&& tHit.m_tPos.y * tHit.m_tPos.y <=1.001f 
				&& tHit.m_tPos.z * tHit.m_tPos.z <=1.001f  )
			{
				if(true)
				{
					tHit.m_tUV.x = tHit.m_tPos.x;
					tHit.m_tUV.y = tHit.m_tPos.z;	

					switch (iSide)
					{
					case 0 : tHit.m_tUV.x = 1- tHit.m_tPos.z;
							 tHit.m_tUV.y = 1-tHit.m_tPos.y;	
							 break;

					case 1 : tHit.m_tUV.x = tHit.m_tPos.x;
							tHit.m_tUV.y = 1-tHit.m_tPos.z;	
							break;

					case 2 : tHit.m_tUV.x = 1-tHit.m_tPos.x ;
							tHit.m_tUV.y = 1+tHit.m_tPos.y ;	
							break;

					case 3 : tHit.m_tUV.x = 1-tHit.m_tPos.z;
							tHit.m_tUV.y = 1+tHit.m_tPos.y;	
							break;

					case 4 : tHit.m_tUV.x = tHit.m_tPos.x;
							tHit.m_tUV.y =  1-tHit.m_tPos.z;	
							break;

					case 5 : tHit.m_tUV.x = 1-tHit.m_tPos.x ;
							tHit.m_tUV.y = 1-tHit.m_tPos.y;	
							break;


					default:
						break;
					}

					//tHit.m_tUV.x -= floor(tHit.m_tUV.x);
					//tHit.m_tUV.y -= floor(tHit.m_tUV.y);
					tHit.m_tUV.x /=2;
					tHit.m_tUV.y /=2;

					tHit.iPixelColor = this->m_iColor;	
					tHit.m_tNormale = pSides[iSide];
					tHit.m_pTransform = this;
				}
		

				return true;

			}	
	





		}
	}

	
	
	
	
	return false;


}


void TBox::Initialize()
{

m_pImageTexture = GfxImageLoad("borg.tga");

	m_iMapX = GfxImageGetSizeX(m_pImageTexture);
	m_iMapY = GfxImageGetSizeY(m_pImageTexture);
	pDataTexture = GfxImageGetData(m_pImageTexture);
	
}


TBox::TBox()
{

	





}