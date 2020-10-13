#ifndef MACROS_H__
#define MACROS_H__

#define START(x) namespace x {
#define END }

#define EXTERN_START extern "C" {
#define EXTERN_END }

#define USING(x) using namespace x;

#if _DEBUG && DXEENGINE_EXPORTS
#define DXAPI __declspec(dllexport)
#else
#define DXAPI __declspec(dllimport)
#endif

#endif // !MACROS_H__
