#pragma once
struct float2
{
	float x;
	float y;
};
struct rectangle_
{
	float posX;
	float posY;
	float width;
	float height;
};
struct intPair
{
	int x;
	int y;
};
enum ItemType
{
	FRIES,
	MELON
};
enum ComponentType
{
	TRANSFORMCOMP,
	SPRITECOMP,
	PHYSICSCOMP,
	BOUNDINGBOXCOMP,
	TEXTURECOMPONENT,
	HEALTHCOMPONENT,
	INPUTCOMPONENT,
	PLAYERCOMPONENT,
	ZENCHANCOMPONENT,
	GHOSTAICOMPONENT,
	BUBBLECOMPONENT,
	COLLISIONCOMPONENT,
	FPSCOMPONENT
};
