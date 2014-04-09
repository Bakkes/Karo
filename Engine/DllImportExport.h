// DLL export macro gets defined when compiling the Engine project.
// DLL import macro gets defined when compiling the unit test project.
//
// Every file that contains functions/methods/classes that should be exposed,
// should include this file and use the ENGINE_API macro.
//
// For example:
// class Example {
// public:
//     static ENGINE_API int ReturnNumber();
//     static string ReturnString();
// };
//
// Here ReturnNumber() can be called from projects that use this DLL. This
// includes C# projects. ReturnString can be used from within ReturnNumber(),
// but not from outside the DLL (like the unit test project).

#ifdef ENGINE_EXPORTS
#define ENGINE_API __declspec(dllexport) 
#else
#define ENGINE_API __declspec(dllimport) 
#endif