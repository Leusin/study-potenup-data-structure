#pragma once

class Bounds
{
public: // RAII

	Bounds(float x, float y, float width = 1.0f, float height = 1.0f);

	~Bounds() = default;

public:

	// 겹침 행성 판정 함수.
	bool Intersects(const Bounds& other) const;

public: // GET SET

	float GetX() const { return x; }
	float GetY() const { return y; }
	float GetWidth() const { return width; }
	float GetHeight() const { return height; }

	float MaxX() const { return x + width; }
	float MaxY() const { return y + height; }

private:
	float x = 0.0f;
	float y = 0.0f;
	float width = 1.0f;
	float height = 1.0f;
};