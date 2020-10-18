#ifndef MACROS_H__
#define MACROS_H__

#define START(x) namespace x {
#define END }

#define USING(x) using namespace x;

#define NULLCHECK_RET_VOID(x) if(nullptr == x) {return;}
#define NULLCHECK_RET_VALUE(x, x1) if(nullptr == x) {return x1;}

#define NULLCHECK_START(x) if(nullptr == x) {
#define NULLCHECK_END }

#define NNULLCHECK_START(x) if(nullptr != x) {
#define NNULLCHECK_END }
#define NNULLCHECK(x, doit) NNULLCHECK_START(x) doit; NNULLCHECK_END

#define FAILED_RETURN(value, rs) if(FAILED(value)){return rs;}

#if _DEBUG && DXEENGINE_EXPORTS
#define DXAPI __declspec(dllexport)
#else
#define DXAPI __declspec(dllimport)
#endif

#define REF_GETTER(T, val) const T& Get##val() const { return val; }
#define REF_SETTER(T, val) void Set##val(const T& rhs) { val = rhs; }
#define DEF_REF_GS(T, val) protected: T val; public: REF_GETTER(T, val) REF_SETTER(T, val)

#define PTR_GETTER(T, val) const T* Get##val() const { return val; }
#define PTR_SETTER(T, val) void Set##val(const T* rhs) { memcpy_s(val, sizeof(T), rhs, sizeof(T)); }
#define DEF_PTR_GS(T, val) protected: T* val; public: PTR_GETTER(T, val) PTR_SETTER(T, val)


#endif // !MACROS_H__
