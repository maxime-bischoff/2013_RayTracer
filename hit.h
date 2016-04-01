#ifndef HIT_H_INCLUDED
#define HIT_H_INCLUDED

#include "flib.h"
#include "flib_vec3.h"
#include "flib_vec2.h"

struct THit{

TGfxVec3 m_tDir;


TGfxVec2 m_tUV;
TGfxVec3 m_tPos;
TGfxVec3 m_tNormale;

const class TTransform * m_pTransform;
unsigned int iPixelColor;

};




#endif