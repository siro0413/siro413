#include "stdafx.h"


class Renderer
{
public:

	static Renderer& Get()
	{
		static Renderer instance;
		return instance;
	}
	void Render(class status* status);
	void Render(const struct Pos& pos, const char* str);

private:
	Renderer() = default;
	~Renderer()= default;
	void MoveCursor(const struct Pos& pos, const char* str);
};

