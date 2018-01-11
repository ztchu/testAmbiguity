#pragma once
#include <Windows.h>
#include <DbgHelp.h>
#include <tchar.h>
#include <direct.h>

namespace CoreDumpFile
{
    bool IsDataSectionNeeded(const WCHAR* pModuleName)
    {
        if (pModuleName == 0)
        {
            return false;
        }

        WCHAR szFileName[_MAX_FNAME] = L"";
        WCHAR drive[_MAX_DRIVE];
        WCHAR dir[_MAX_DIR];
        WCHAR fname[_MAX_FNAME];
        WCHAR ext[_MAX_EXT];
        _wsplitpath_s(pModuleName, drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

        if (_wcsicmp(fname, L"ntdll") == 0)
            return true;

        return false;
    }

    BOOL CALLBACK MiniDumpCallback(PVOID pParam, const PMINIDUMP_CALLBACK_INPUT pInput, PMINIDUMP_CALLBACK_OUTPUT pOutput)
    {
        if (pInput == 0 || pOutput == 0)
            return FALSE;
        switch (pInput->CallbackType)
        {
        case ModuleCallback:
            if (pOutput->ModuleWriteFlags & ModuleWriteDataSeg)
            {
                if (!IsDataSectionNeeded(pInput->Module.FullPath))
                {
                    pOutput->ModuleWriteFlags &= (~ModuleWriteDataSeg);
                }
            }
        case IncludeModuleCallback:
        case IncludeThreadCallback:
        case ThreadCallback:
        case ThreadExCallback:
            return TRUE;
        default:;
        }
        return FALSE;
    }

    void CreateMiniDump(EXCEPTION_POINTERS* pep, LPCWSTR filename)
    {
        HANDLE hFile = CreateFile(filename, GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

        if ((hFile != NULL) && (hFile != INVALID_HANDLE_VALUE))
        {
            MINIDUMP_EXCEPTION_INFORMATION mdei;
            mdei.ThreadId = GetCurrentThreadId();
            mdei.ExceptionPointers = pep;
            mdei.ClientPointers = FALSE;

            MINIDUMP_CALLBACK_INFORMATION mci;
            mci.CallbackParam = 0;
            mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
            //MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | MiniDumpWithDataSegs
            //    | MiniDumpWithHandleData
            //    | 0x00000800     //MiniDumpWithFullMemoryInfo
            //    | 0x00001000     //MiniDumpWithThreadInfo
            //    | MiniDumpWithUnloadedModules
            //    ); 
            //MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory | MiniDumpScanMemory);
            MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(MiniDumpWithIndirectlyReferencedMemory);

            BOOL rv = MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hFile, mdt, (pep != 0) ? &mdei : 0, 0, &mci);

            if (!rv)
                _tprintf(_T("MiniDumpWriteDump failed. Error: %u \n"), GetLastError());
            else
                _tprintf(_T("Minidump created.\n"));

            CloseHandle(hFile);
        }
    }

    LONG _stdcall MyUnhandleExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
    {
        /*char crushFile[100];
        _getcwd(crushFile, 100);
        strcat_s(crushFile, sizeof(crushFile), "\\CreateDumpFile.dmp");
        std::cout << crushFile << std::endl;*/
        //CreateMiniDump(pExceptionInfo, (LPCWSTR)crushFile);
        CreateMiniDump(pExceptionInfo, L"CreateDumpFileXXX.dmp");
        return EXCEPTION_EXECUTE_HANDLER;
    }

    /*std::ostream& operator<<(std::ostream& os, const EXCEPTION_RECORD& red)
    {
    return os << " Thread ID: " << GetCurrentThreadId()
    << "  ExceptionCode: " << red.ExceptionCode << std::endl
    << "  ExceptionFlags: " << red.ExceptionFlags << std::endl
    << "  ExceptionAddress: " << red.ExceptionAddress << std::endl
    << "  NumberParameters:" << red.NumberParameters << std::endl;
    }

    LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
    {
    CreateMiniDump(pExceptionInfo, L"CrashException.dmp");
    std::cerr << "Unknown error: " << (*pExceptionInfo->ExceptionRecord) << std::endl;
    exit(pExceptionInfo->ExceptionRecord->ExceptionCode);
    return EXCEPTION_EXECUTE_HANDLER;
    }*/
}

void SetUnhandleException()
{
    //DumpFile::RunCrashHandler();
    SetUnhandledExceptionFilter(CoreDumpFile::MyUnhandleExceptionFilter);
    //SetUnhandledExceptionFilter(CoreDumpFile::GPTUnhandledExceptionFilter);
}
