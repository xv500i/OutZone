#pragma once
class BoundingBox
{
public:
	BoundingBox(const float top, const float bottom, const float left, const float right);
	~BoundingBox(void);

	bool isIntersectedBy(const BoundingBox &b) const;
	void translate(const float x, const float y);
	bool contains(const float x, const float y) const;
	bool containsX(const float x) const;
	bool containsY(const float y) const;
private:
	float top;
	float bottom;
	float left;
	float right;
};

