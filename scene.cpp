#include "scene.h"

//
//TScene::TScene()
//{
//	
//
//
//}

void TScene::AddTransform(TTransform *pTransform )
{

	if(m_iTransformCount<MAX_TRANSFORMS)
	{
		m_pTransforms[m_iTransformCount++] = pTransform;
	
	}




}

bool TScene::Trace(THit & tHit, const TRay & tRay) const 
{

	for (int i = 0; i < m_iTransformCount; ++i)
	{

		THit tCurrentHit;
	
		if(m_pTransforms[ i ]->TraceWorld( tCurrentHit, tRay ))
		{
			
				if(tHit.iPixelColor != 0)
				{
					if( (tCurrentHit.m_tPos - tRay.m_tSrc).Length() < (tHit.m_tPos - tRay.m_tSrc).Length())
					{
						tHit = tCurrentHit;					
					}

				} else 
					{
					tHit = tCurrentHit;				
					}
			

			

			








			


		}


	}


	if(tHit.iPixelColor != 0)
	{
	return true;
	}else

	return false;

}