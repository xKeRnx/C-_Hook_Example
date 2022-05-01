// dllmain.cpp : Definiert den Einstiegspunkt für die DLL-Anwendung.
#include "pch.h"
#include <iostream>
#include <detours.h>



BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
                     )
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        DetourTransactionBegin();
        DetourUpdateThread(GetCurrentThread());
        DetourAttach(&(PVOID&)Hook::Org_Main, MemberFuncToPtrr(&Hook::Main));
        DetourTransactionCommit();
    case DLL_THREAD_ATTACH:
    case DLL_THREAD_DETACH:
    case DLL_PROCESS_DETACH:
        break;
    }
    return TRUE;
}

Hook::Hook_Main Hook::Org_Main = reinterpret_cast<Hook_Main>(0x412480);
int Hook::Main() {
    std::cout << "ICH BIN EIN HOOK \n";
    return Org_Main();
}