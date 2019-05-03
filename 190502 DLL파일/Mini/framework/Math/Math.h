#pragma once

class Math final
{
public:
	//뒤에 숫자만 만드는걸 매직넘버
	static constexpr float PI		= 3.14159265359f;
	static constexpr float PI_2		= 6.28318530718f;
	static constexpr float PI_DIV_2 = 1.57079632679f;
	static constexpr float PI_DIV_4 = 0.78539816339f;
	static constexpr float TO_DEG	= 180.0f / PI;
	static constexpr float TO_RAD	= PI / 180.0f;

	static auto ToRadian(const float& degree) { return degree * TO_RAD; }
	static auto TODegree(const float& radian) { return radian * TO_DEG; }


private:
};

