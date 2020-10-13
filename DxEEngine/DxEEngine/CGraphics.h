// Copyright YUI, Inc. All Rights Reserved.

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

START(dxengine)

class CGraphics : public Object<CGraphics>
{
public:
	CGraphics();
	CGraphics(const CGraphics&);
	~CGraphics();

public:
	// Object을(를) 통해 상속됨
	virtual bool Initialize() override;
	virtual void Shutdown() override;

	bool	Frame();

private:
	bool	Render();

public:
	bool	FULL_SCREEN = false;
	bool	VSYNC_ENABLED = false;
	float	SCREEN_DEPTH = 1000.0f;
	float	SCREEN_NEAR = false;
};

END

#endif // !GRAPHICS_H_
