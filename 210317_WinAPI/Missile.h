#pragma once
#include "GameNode.h"

class Image;
class Missile : public GameNode
{

private:
	// ÀÌ¹ÌÁö
	Image* imgDown;
	Image* imgLeft;
	Image* imgRight;
	Image* imgUp;

	FPOINT pos;
	float moveSpeed;
	int size;
	RECT shape;
	int damage;
	float angle;
	bool isFired;

	PLAYER_TYPE playerType;
	MOVE_DIRECTION moveDirection;

	HRESULT LoadImage();

public:
	HRESULT Init(PLAYER_TYPE playerType);
	void Release();		
	void Update();		
	void Render(HDC hdc);
	void Move();

	inline void SetPos(FPOINT pos) { this->pos = pos; }
	inline FPOINT GetPos() { return this->pos; }
	void SetIsFired(bool isFired);
	inline bool GetIsFired() { return this->isFired; }

	inline void SetPlayerType(PLAYER_TYPE playerType) { this->playerType = playerType; }
	inline PLAYER_TYPE GetPlayerType() { return this->playerType; }
	inline void SetAngle(float angle) { this->angle = angle; }
	inline void SetMoveDirection(MOVE_DIRECTION moveDirection) { this->moveDirection = moveDirection; }
	inline RECT& GetShape() { return shape; }

	inline int GetSize() { return this->size; }
};

