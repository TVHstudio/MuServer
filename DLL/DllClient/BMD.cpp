#include "StdAfx.h"
#include "Defines.h"
#include "BMD.h"

BMD *&Models = *(BMD**)0x0596CB28;
vec34_t* BoneTransform = (vec34_t*)(0x06AB486C); // MAX BONE 200

BMD::BMD(void)
{
}

void BMD::TransformPosition(float (*Matrix)[4],vec3_t Position,vec3_t WorldPosition,bool Translate)
{
	const DWORD dwFunc = 0x004CC40E;
	__asm
	{
		xor eax, eax;
		mov al, Translate;
		push eax;

		mov eax, WorldPosition;
		push eax;

		mov eax, Position;
		push eax;

		mov eax, Matrix;
		push eax;

		mov ecx, this;
		call dwFunc;
	}
}

void BMD::TransformByObjectBone(vec3_t vResultPosition, void* pObject, int iBoneNumber, vec3_t vRelativePosition)
{
	const DWORD dwFunc = 0x004CC249;
	__asm
	{
		mov eax, vRelativePosition;
		push eax;

		mov eax, iBoneNumber;
		push eax;

		mov eax, pObject;
		push eax;

		mov eax, vResultPosition;
		push eax;

		mov ecx, this;
		call dwFunc;
	}
}