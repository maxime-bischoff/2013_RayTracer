#include "camera.h"
#include "scene.h"
#include <math.h>

bool g_bMagicMod = false;

unsigned int Vec3ColorToInt(TGfxVec3 tColor)
{
	/*if(tColor.x> 1) tColor.x = 1;
	if(tColor.y> 1) tColor.y = 1;
	if(tColor.z> 1) tColor.z = 1;*/


	return (GfxColor(tColor.x * 255 , tColor.y * 255, tColor.z * 255, 255));
}

TGfxVec3 IntColorToVec3(unsigned int iColor)
{
	unsigned char * pColor = reinterpret_cast<unsigned char *>(&iColor);
	TGfxVec3 tColor;
	tColor.x = pColor[ 0 ] / 255.0f;
	tColor.y = pColor[ 1 ] / 255.0f;
	tColor.z = pColor[ 2 ] / 255.0f;
	return tColor;

}




TCamera::TCamera() : 
	m_fFOV( static_cast< float >( M_PI / 3)) 
	, tDirLight(TGfxVec3(-1,-2,-1 ) )
{
	tDirLight =  tDirLight.Normalize();

}

void TCamera::Render(TGfxImage * pImage, const TScene & tScene) const
{

		///TGfxVec3 tDirLight( 1,1,0);
		//tDirLight = tDirLight.Normalize();
		float fAmbiant = 0.4f;

	const int iSizeX =  GfxImageGetSizeX(pImage);
	const int iSizeY = GfxImageGetSizeY(pImage);

	unsigned int * pData = GfxImageGetData(pImage);


		if(GfxInputIsJustPressed(EGfxInputID_KeySpace))
					{
						if (g_bMagicMod)
						{ 
							g_bMagicMod = false;
						}
						else{ 
							g_bMagicMod = true;
						}				
					}


	for (int x = 0; x<iSizeX; ++x)
	{
		for (int y=0; y<iSizeY; ++y)
		{
			const int iIndex = x + y * iSizeX;

			THit tHit;
			TRay tRay;

			tRay.m_tSrc = this->m_tPosition;
			tHit.iPixelColor = 0;

			const float fX = (2 * x / ( iSizeX - 1.0f ) - 1) * tanf ( m_fFOV/2 );
			const float fY = ( 1   - 2 * y / ( iSizeY - 1.0f )) * tanf ( m_fFOV/2 ) * (iSizeY / static_cast< float >(iSizeX) );
		
			tRay.m_tDir = ( -m_tAxes.z + m_tAxes.x * fX + m_tAxes.y * fY ).Normalize();


	//		(tHit.m_tPos -  this->m_tPosition).Length();

		if(tScene.Trace(tHit, tRay))
		{				
			const int iTileX = static_cast< int > (tHit.m_tUV.x * 2 ) % 2;
			const int iTileY = static_cast< int > (tHit.m_tUV.y * 2 ) % 2;	


			if(!tHit.m_pTransform->isTextured)
			{	
				float dotProduct = tDirLight.DotProduct(-tHit.m_tNormale); 								
				TGfxVec3 tColor = IntColorToVec3(tHit.m_pTransform->m_iColor);
				unsigned iColor;
				
				THit tHitShadow;
				TRay tRayShadow;
				tRayShadow.m_tSrc = tHit.m_tPos;
				tRayShadow.m_tDir =   tHit.m_tPos - tDirLight;

				
				if(!tScene.m_pTransforms[0]->TraceWorld( tHitShadow, tRayShadow ))
				{

					if(dotProduct<fAmbiant)
					{					
						tColor*=fAmbiant;				
					}else{		
						tColor *= dotProduct;					
					}				


					if((iTileX + iTileY) %2 >0)
					{}
					else
					{				
						tColor /=3;					
					}	

				}
				else{
					tColor *= fAmbiant;
				}

				iColor  = Vec3ColorToInt(tColor);
				pData[ iIndex ] =  iColor;


			}else{			
		
				
				int x =	  static_cast<int>(( tHit.m_pTransform->m_iMapX * tHit.m_tUV.x) - tHit.m_pTransform->m_iMapX)*-1;
				int y =   static_cast<int>(( tHit.m_pTransform->m_iMapY * tHit.m_tUV.y) - tHit.m_pTransform->m_iMapY)*-1;


				int iTabIndex = static_cast<int>(  x + y * tHit.m_pTransform->m_iMapX );		

				TGfxVec3 tNormaleSphere = tHit.m_pTransform->m_tPosition - tHit.m_tPos;

				float diffuse = tDirLight.DotProduct(tHit.m_tNormale);
				float diffuseSphere = tDirLight.DotProduct(tNormaleSphere);
				

				float fFresnel =  tRay.m_tDir.DotProduct(tHit.m_tNormale);
				

				if(diffuse<0) diffuse =0;

				if(fFresnel<0) fFresnel = 0;
				if(fFresnel>1) fFresnel = 1;
				fFresnel = 1-fFresnel ;			
				
			//	fFresnel = pow(fFresnel, 2);
			fFresnel-= 0.3;

				TGfxVec3 diffPoint =  ( tHit.m_tNormale) * diffuse;

				TGfxVec3 reflectPoint = ( - tDirLight) + diffPoint*2;
		
				float spec =  reflectPoint.DotProduct(  tRay.m_tDir );
				spec = pow(spec,13);

				unsigned int iColor;
			//	if(diffuse<0.8)
			//	{
			//	 iColor = tHit.m_pTransform->pDataNight[iTabIndex];
			//	}else {
					 iColor = tHit.m_pTransform->pDataTexture[iTabIndex];
			//	}




				TGfxVec3 tNewColor = IntColorToVec3(iColor);

				//diffuse+= spec;

				if(spec <0) spec = 0;
				if(spec >1) spec = 1;


				TGfxVec3 colorSpec = TGfxVec3(1,1,1);
				TGfxVec3 colorFresnel = TGfxVec3(1.0f,1.0f,1.0f);
				
				unsigned int iSpecValue;
				TGfxVec3 tSpecValue(0,0,0);
				if(tHit.m_pTransform->m_pImageSpec!=0)
				{
				 iSpecValue = tHit.m_pTransform->pDataSpec[ iTabIndex ] ;
				 tSpecValue = IntColorToVec3(iSpecValue);

				}


				
				if(diffuse<fAmbiant)
				{					
					tNewColor *= fAmbiant;	
			
				}else{					
					tNewColor *= diffuse ;
						
				
				spec /=2;
				float fModifier = 0.0f;
				TGfxVec3 tColorTest;
				tColorTest = TGfxVec3(	tNewColor.x *2 +fModifier,
										tNewColor.y *2 +fModifier,
										tNewColor.z *2+fModifier);

				if(tColorTest.x>1) tColorTest.x = 1;
				if(tColorTest.y>1) tColorTest.y = 1;
				if(tColorTest.z>1) tColorTest.z = 1;
					
				 tColorTest = colorSpec;
				 spec = spec * tSpecValue.x;

				tNewColor.x = tNewColor.x *(1-spec) +  tColorTest.x*spec ;
				tNewColor.y =  tNewColor.y *(1-spec) + tColorTest.y*spec ;
				tNewColor.z = tNewColor.z *(1-spec) +  tColorTest.z* spec ;

											
				}

				fFresnel= fFresnel - (1 - diffuseSphere);

				
				if(fFresnel >1) fFresnel = 1;

				if(fFresnel<0)fFresnel = 0;

				fFresnel = 0;
								
				tNewColor.x = tNewColor.x *(1-fFresnel) + colorFresnel.x*fFresnel ;
				tNewColor.y =  tNewColor.y *(1-fFresnel) +	colorFresnel.y*fFresnel ;
				tNewColor.z = tNewColor.z *(1-fFresnel) +	colorFresnel.z* fFresnel ;
			

				iColor  = Vec3ColorToInt(tNewColor);

				if(g_bMagicMod)
				{
					TGfxVec3 tPreviousColor = IntColorToVec3(pData[ iIndex ]);
					TGfxVec3 tNewColor = IntColorToVec3(tHit.m_pTransform->pDataTexture[ iIndex ]);
					tNewColor.x= tPreviousColor.y;			
					unsigned int iNewColor = Vec3ColorToInt(tNewColor);
					pData[ iIndex ] += tHit.m_pTransform->pDataTexture[iTabIndex] ;

				}else pData[ iIndex ] =  iColor ;

			}
				


		}else
		{
			pData[ iIndex ] =  EGfxColor_Black;
		}




		}
	
	}



}