#pragma once

#include "Includes.h"

START(dxengine)

class IObject
{
public:
	IObject();
	IObject(const IObject& other);
	~IObject();

public:
	virtual void Awake() = 0;
	virtual void OnEnable() = 0;
	virtual void Start() = 0;

	virtual void FixedUpdate() = 0;
	virtual void Update() = 0;
	virtual void LateUpdate() = 0;

	virtual void OnPreRender() = 0;
	virtual void OnRenderObject() = 0;
	virtual void OnPostRender() = 0;
	virtual void OnGUI() = 0;

	virtual void OnDisable() = 0;
	virtual void OnDestroy() = 0;

public:
	int GetReferenceCnt() { return refCnt; }

private:
	int refCnt = 1;
};

class ISystemObject : public IObject
{
public:
	ISystemObject() {}
	ISystemObject(const ISystemObject& other) {}
	~ISystemObject() {}

public:
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
};

END
