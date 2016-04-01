#include "sphere.h" 
#include "scene.h"
#include "transform.h"
#include "camera.h" 
#include "flib.h"
#include "flib_vec3.h"
#include "plane.h"
#include "axes.h"
#include "box.h"
#include <math.h>

TGfxImage * g_pImage;

TGfxSprite * g_pSprite;
TGfxTexture * g_pTexture;
unsigned int * pData;

TScene g_tScene;
TCamera g_tCamera;
TSphere * pSphere = new TSphere;
TSphere * pSphere2 = new TSphere;
TSphere * pSphere3 = new TSphere;
TPlane * pPlane;

TBox * pBox;

float fAngleCamX=0;
float fAngleCamY = 0;


float fAngle = 0;
void Initialize()
{
/*	GfxSetMouseCapture(true);
	GfxSetMouseVisible(false);
*/

	
	g_tScene.AddTransform( pSphere );	
	
	pSphere->m_iColor = EGfxColor_Red;
	pSphere->Initialize();
	pSphere->m_tScale = TGfxVec3(1,1,1);
	
	pSphere2 = new TSphere;
//	g_tScene.AddTransform( pSphere2 );	
	pSphere2->m_tPosition = TGfxVec3(-2.0f, 0.0f, 0.0f);
	pSphere2->m_iColor = EGfxColor_Blue;
	

	pSphere2->Initialize();

	pSphere3 = new TSphere;
	pSphere3->m_tPosition = TGfxVec3(0.0f, -1.0f, 0.0f);
	pSphere3->m_iColor = GfxColor(255,0,255,255);
	//g_tScene.AddTransform( pSphere3 );	
	


	pPlane = new TPlane;
	
	pPlane->m_iColor = EGfxColor_Green;
	pPlane->tNormale = TGfxVec3(0.0,1.0,0);
//	g_tScene.AddTransform( pPlane );	
	pPlane->m_tScale = TGfxVec3(1,1,1);


	pBox = new TBox;
	pBox->Initialize();
	pBox->m_iColor = EGfxColor_Blue;
	//g_tScene.AddTransform(pBox);
	pBox->isTextured = true;
	pBox->m_tScale = TGfxVec3(0.3,0.3,0.3);
	pBox->m_tPosition = TGfxVec3(2, 2, 2);


	//pPlane = new TPlane;
	//
	//pPlane->m_iColor = EGfxColor_Red;
	//pPlane->tNormale = TGfxVec3(-1.0,0.0,0);
	//g_tScene.AddTransform( pPlane );	

	//pPlane = new TPlane;
	//
	//pPlane->m_iColor = EGfxColor_Red;
	//pPlane->tNormale = TGfxVec3(1.0,0.0,0);
	//g_tScene.AddTransform( pPlane );	


	g_pImage = GfxImageCreate(480,272);
	pData = GfxImageGetData(g_pImage);

	g_tCamera.m_tPosition.x = 0.0f;
	g_tCamera.m_tPosition.y = 0.0f;
	g_tCamera.m_tPosition.z = 5.0f;


}


void Update()
{



	if(GfxInputIsPressed(EGfxInputID_KeyPlus))
	{g_tCamera.m_fFOV+=0.1f;}

	if(GfxInputIsPressed(EGfxInputID_KeyMinus))
	{g_tCamera.m_fFOV-=0.1f;}


	if(GfxInputIsPressed(EGfxInputID_KeyEscape))
	{
		GfxExitRequest();	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharQ))
	{
	//	g_tCamera.m_tPosition.x-=0.1;	
		pSphere->m_tPosition.x+=0.1;
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharD))
	{
	//	g_tCamera.m_tPosition.x+=0.1;
		pSphere->m_tPosition.x-=0.1;
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharZ))
	{
		pSphere->m_tPosition.z+=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharS))
	{
		pSphere->m_tPosition.z-=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharE))
	{
		pSphere->m_tPosition.y-=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharA))
	{
		pSphere->m_tPosition.y+=0.1;	
	}



	
	if(GfxInputIsPressed(EGfxInputID_KeyCharK))
	{
	//	g_tCamera.m_tPosition.x-=0.1;	
		pBox->m_tPosition.x-=0.1;
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharM))
	{
	//	g_tCamera.m_tPosition.x+=0.1;
		pBox->m_tPosition.x+=0.1;
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharO))
	{
		pBox->m_tPosition.z-=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharL))
	{
		pBox->m_tPosition.z+=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharI))
	{
		pBox->m_tPosition.y-=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyCharP))
	{
		pBox->m_tPosition.y+=0.1;	
	}







		if(GfxInputIsPressed(EGfxInputID_KeyNumPad1))
	{
		g_tCamera.m_tPosition.x-=0.1;	
	}
			if(GfxInputIsPressed(EGfxInputID_KeyNumPad3))
	{
		g_tCamera.m_tPosition.x+=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyNumPad5))
	{
		g_tCamera.m_tPosition.z-=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyNumPad2))
	{
		g_tCamera.m_tPosition.z+=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyNumPad4))
	{
		g_tCamera.m_tPosition.y-=0.1;	
	}
	if(GfxInputIsPressed(EGfxInputID_KeyNumPad6))
	{
		g_tCamera.m_tPosition.y+=0.1;	
	}

	if(GfxInputIsPressed(EGfxInputID_KeyNumPad7))
	{
		fAngleCamY+=0.1;
		g_tCamera.m_tAxes = TAxes::CreateYRotation(fAngleCamY);	
	}
	if(GfxInputIsPressed(EGfxInputID_KeyNumPad9))
	{
			fAngleCamY-=0.1;
		g_tCamera.m_tAxes = TAxes::CreateYRotation(fAngleCamY);	
	}


			
			float fSpeedMove = 0.2;
			if(GfxInputIsPressed(EGfxInputID_KeyArrowLeft))	{			
				g_tCamera.tDirLight.x -= fSpeedMove;
				g_tCamera.tDirLight = g_tCamera.tDirLight.Normalize();			
			}

			if(GfxInputIsPressed(EGfxInputID_KeyArrowRight)){			
				g_tCamera.tDirLight.x += fSpeedMove;
				g_tCamera.tDirLight = g_tCamera.tDirLight.Normalize();			
			}

			if(GfxInputIsPressed(EGfxInputID_KeyArrowUp))	{			
				g_tCamera.tDirLight.y += fSpeedMove;
				g_tCamera.tDirLight = g_tCamera.tDirLight.Normalize();			
			}

			if(GfxInputIsPressed(EGfxInputID_KeyArrowDown))		{			
				g_tCamera.tDirLight.y -=fSpeedMove ;
				g_tCamera.tDirLight = g_tCamera.tDirLight.Normalize();			
			}

			 fAngle +=  M_PI / 120;


		//	pSphere->m_tAxes = 	pSphere->m_tAxes.Multiply(TGfxVec3(0.2f,0.0f,0.0f));
		//	  pSphere->m_tAxes = TAxes::CreateXRotation(fAngle);

			 pSphere->m_tAxes = TAxes::CreateYRotation(fAngle);

			 pBox->m_tAxes = TAxes::CreateXRotation(fAngle);

			 pBox->m_tAxes = TAxes::CreateYRotation(fAngle);
			




			// pBox->m_tAxes = ;

		//	 pSphere->m_tAxes = TAxes::CreateZRotation(fAngle);
			
	

/*	float MouseAccellX = GfxGetCurrentMouseX()-GfxGetPreviousMouseX() ;
	float MouseAccellY = GfxGetCurrentMouseY()-GfxGetPreviousMouseY() ;

	fAngleCamX += ( MouseAccellY / 100);
	fAngleCamY += (MouseAccellX / 100);


			g_tCamera.m_tAxisX = TGfxVec3(	1,		0,				0);
			g_tCamera.m_tAxisY = TGfxVec3(	0,		cos(fAngleCamX),	-sin(fAngleCamX));
			g_tCamera.m_tAxisZ = TGfxVec3(	0,		sin(fAngleCamX),	cos(fAngleCamX));


			g_tCamera.m_tAxisX = TGfxVec3(	cos(fAngleCamY),	0,		sin(fAngleCamY));
			g_tCamera.m_tAxisY = TGfxVec3(	0,				1,		0);
			g_tCamera.m_tAxisZ = TGfxVec3(	-sin(fAngleCamY),	0,		cos(fAngleCamY));


			*/





	if(GfxInputIsPressed(EGfxInputID_KeyCharP))
	{
	g_tCamera.m_tAxisX.x +=  0.05f;
	g_tCamera.m_tAxisX.y +=  0.05f;
	g_tCamera.m_tAxisX.z +=  0.05f;
	//g_tCamera.m_tAxisY.y +=  0.05f;
	g_tCamera.m_tAxisZ.x +=  0.05f;
		g_tCamera.m_tAxisZ.y +=  0.05f;
			g_tCamera.m_tAxisZ.z +=  0.05f;
	}
			if(GfxInputIsPressed(EGfxInputID_KeyCharO))
	{
//	g_tCamera.m_tAxisX.x -=   0.05f;
	g_tCamera.m_tAxisY.y -=   0.05f;
	g_tCamera.m_tAxisZ.z -=   0.05f;
	}



	//g_tCamera.m_tAxisY.y -=  MouseAccellX/20;
	/*g_tCamera.m_tAxisX.x -=  MouseAccellX/20;
	g_tCamera.m_tAxisY.x -=  MouseAccellX/20;
	g_tCamera.m_tAxisZ.x -=  MouseAccellX/20;*/
	if(g_pTexture!=0) GfxTextureDestroy(g_pTexture);
	if(g_pSprite!=0)  GfxSpriteDestroy(g_pSprite);




	g_tCamera.Render(g_pImage,  g_tScene);



	g_pTexture = GfxTextureCreate(g_pImage);
	g_pSprite = GfxSpriteCreate(g_pTexture);





}


void Render()
{

	GfxClear(EGfxColor_Black);
	if(g_pSprite!=0) GfxSpriteRender(g_pSprite);


}





void GfxMain( int, char * [] )
{

	GfxCallbacks(Initialize, Update, Render);
}
