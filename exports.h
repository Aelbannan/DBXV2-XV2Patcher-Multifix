//  exports.h
//
//	Simple header to instruct the linker to forward function exports to another library.
//

#pragma comment(linker,"/export:DirectInput8Create=DINPUT8_orig.DirectInput8Create,@1")
#pragma comment(linker,"/export:DllCanUnloadNow=DINPUT8_orig.DllCanUnloadNow,@2")
#pragma comment(linker,"/export:DllGetClassObject=DINPUT8_orig.DllGetClassObject,@3")
#pragma comment(linker,"/export:DllRegisterServer=DINPUT8_orig.DllRegisterServer,@4")
#pragma comment(linker,"/export:DllUnregisterServer=DINPUT8_orig.DllUnregisterServer,@5")
#pragma comment(linker,"/export:GetdfDIJoystick=DINPUT8_orig.GetdfDIJoystick,@6")
