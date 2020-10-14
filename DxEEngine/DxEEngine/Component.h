#ifndef COMPONENT_H__
#define COMPONENT_H__

#include "Includes.h"

START(dxengine)

class DXAPI Component : public IObject
{
	// IObject을(를) 통해 상속됨
	virtual void Awake() override;
	virtual void OnEnable() override;
	virtual void Start() override;
	virtual void FixedUpdate() override;
	virtual void Update() override;
	virtual void LateUpdate() override;
	virtual void OnPreRender() override;
	virtual void OnRenderObject() override;
	virtual void OnPostRender() override;
	virtual void OnGUI() override;
	virtual void OnDisable() override;
	virtual void OnDestroy() override;

public:
	Component() {}
};

END
#endif // !COMPONENT_H__



