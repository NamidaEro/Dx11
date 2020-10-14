#ifndef CGAMEOBJECT_H__
#define CGAMEOBJECT_H__

#include "Includes.h"
#include "Transform.h"

START(dxengine)
class CGameObject : public IObject
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
	Transform transform;
};
END
#endif // !CGAMEOBJECT_H__



