#ifndef MACROS_H__
#define MACROS_H__

#define START(x) namespace x {
#define END }

#define USING(x) using namespace x;

#define NULLCHECK_RET_VOID(x) if(nullptr == x) {return;}
#define NULLCHECK_RET_VALUE(x, x1) if(nullptr == x) {return x1;}

#define NULLCHECK_START(x) if(nullptr == x) {
#define NULLCHECK_END }

#if _DEBUG && DXEENGINE_EXPORTS
#define DXAPI __declspec(dllexport)
#else
#define DXAPI __declspec(dllimport)
#endif

#endif // !MACROS_H__
