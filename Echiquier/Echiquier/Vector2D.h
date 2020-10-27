#pragma once
class Vector2D
{
public:
	Vector2D();
	Vector2D(int x, int y);
	Vector2D(int pos[2]);
	~Vector2D();

	void SetVector(int x, int y);
	void SetVector(int pos[2]);

	Vector2D Addition(Vector2D v);
	Vector2D ScalarMultiplication(int x);

	bool IsZero();

	friend Vector2D operator + (Vector2D v1, Vector2D v2);
	friend Vector2D operator * (int x, Vector2D v);

public:
	int x, y;
};

