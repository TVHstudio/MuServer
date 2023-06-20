#ifndef __BMD_H__
#define __BMD_H__

//#include "zzzMathLib.h"

class BMD
{
public:
	BMD(void);

	void TransformPosition(float (*Matrix)[4],vec3_t Position,vec3_t WorldPosition,bool Translate=false);
	void TransformByObjectBone(vec3_t vResultPosition, void* pObject, int iBoneNumber, vec3_t vRelativePosition = NULL);

public:
	char Name[32];
char Version;
short NumBones; // 34
short NumMeshs; // 36
short NumActions; // 38
void *Meshs; // 40
void *Bones; // 44
void *Actions; // 48
void *Textures; // 50
short *IndexTexture; // 54
short NumLightMaps; // 58
short IndexLightMap; // 60
void *LightMaps; // 64
bool LightEnable; // 68
bool ConstratEnable; // 69
vec3_t BodyLight; // 72, 76, 80
int BoneHead; // 84
int BoneFoot[4]; // 88 92 96 100
float BodyScale; // 104
vec3_t BodyOrigin; // 108, 112, 116
vec3_t BodyAngle; // 120, 124, 128
float BodyHeight; // 133
char StreamMesh; // 136
vec3_t ShadowAngle; // 137, 141, 145
char Skin; // 152
bool HideSkin; // 153
float Velocity;
unsigned char CurrentAction; // 160
unsigned char PriorAction; // 161
float CurrentAnimation; // 164
short CurrentAnimationFrame; // 168
short Sounds[10]; // 170
bool LightMapEnable;

#ifdef SEASON3_5
BYTE Other[50]; // size 0xF0
#else
BYTE Other[52]; // size 0xF4
#endif // SEASON3_5

// size OK
};

extern BMD   *&Models;

extern vec34_t*	BoneTransform;

#endif