#include "dump.h"
#include <iostream>
#include <Windows.h>
#include <DbgHelp.h>
#include <tchar.h>
#include <direct.h>

#pragma comment(lib, "Dbghelp.lib")

void TestCreateDumpFile()
{
    int *p = nullptr;
    *p = 4;
}

void TestDeleteNullptr()
{
    int *ptr = new int(4);
    delete ptr;
    //ptr = nullptr;
    //delete ptr;
    if (ptr == nullptr)
    {
        std::cout << "ptr is nullptr when deleted." << std::endl;
    }
    else
    {
        std::cout << "ptr is unknown when deleted." << std::endl;
    }
}


namespace DumpFile
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

    void CreateDumpFile(LPCWSTR lpstrDumpFilePathName, EXCEPTION_POINTERS *pException)
    {
        // create dump file
        HANDLE hDumpFile = CreateFile(lpstrDumpFilePathName, GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, 
            FILE_ATTRIBUTE_NORMAL, NULL);

        //dump information
        MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;

        MINIDUMP_CALLBACK_INFORMATION mci;
        mci.CallbackRoutine = (MINIDUMP_CALLBACK_ROUTINE)MiniDumpCallback;
        mci.CallbackParam = 0;

        //write dump file
        MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, &mci);
        CloseHandle(hDumpFile);
    }

    LPTOP_LEVEL_EXCEPTION_FILTER WINAPI MyDummySetUnhandledExceptionFilter(LPTOP_LEVEL_EXCEPTION_FILTER lpTopLevelExceptionFilter)
    {
        return NULL;
    }

    BOOL PreventSetUnhandledExceptionFilter()
    {
        HMODULE hKernel32 = LoadLibrary(_T("kernel32.dll"));
        if (hKernel32 == NULL)
        {
            return false;
        }

        void *pOrgEntry = GetProcAddress(hKernel32, "SetUnhandledExceptionFilter"); 
        if (pOrgEntry == nullptr)
        {
            return false;
        }

        unsigned char newJump[100];
        DWORD dwOrgEntryAddr = (DWORD)pOrgEntry;
        dwOrgEntryAddr += 5; //add 5 for 5 op-codes for jmp far

        void *pNewFunc = &MyDummySetUnhandledExceptionFilter;
        DWORD dwNewEntryAddr = (DWORD)pNewFunc;
        DWORD dwRelativeAddr = dwNewEntryAddr - dwOrgEntryAddr;

        newJump[0] = 0xE9; //jmp absolute
        memcpy(&newJump[1], &dwRelativeAddr, sizeof(pNewFunc));
        SIZE_T bytesWritten;
        BOOL bRet = WriteProcessMemory(GetCurrentProcess(), pOrgEntry, newJump, sizeof(pNewFunc) + 1, &bytesWritten);
        return bRet;
    }

    LONG WINAPI UnhandleExceptionFilterEx(struct _EXCEPTION_POINTERS *pException)
    {
        TCHAR szMbsFile[MAX_PATH] = { 0 };
        ::GetModuleFileName(NULL, szMbsFile, MAX_PATH);
        TCHAR* pFind = _tcsrchr(szMbsFile, '\\');
        if (pFind)
        {
            *(pFind + 1) = 0;
            wcscat_s(szMbsFile, sizeof(szMbsFile), _T("CrashDumpFile.dmp"));
            CreateDumpFile(szMbsFile, pException);
        }

        //TODO:MiniDumpWriteDump
        FatalAppExit(-1, _T("Fatal Error"));
        return EXCEPTION_CONTINUE_SEARCH;
    }

    void RunCrashHandler()
    {
        SetUnhandledExceptionFilter(UnhandleExceptionFilterEx);
        PreventSetUnhandledExceptionFilter();
    }
}




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
            MINIDUMP_TYPE mdt = (MINIDUMP_TYPE)(MiniDumpWithPrivateReadWriteMemory | MiniDumpWithDataSegs
                | MiniDumpWithHandleData
                | 0x00000800     //MiniDumpWithFullMemoryInfo
                | 0x00001000     //MiniDumpWithThreadInfo
                | MiniDumpWithUnloadedModules
                );    
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
        char crushFile[100];
        _getcwd(crushFile, 100);
        strcat_s(crushFile, sizeof(crushFile), "\\CreateFile.dmp");
        CreateMiniDump(pExceptionInfo, (LP)crushFile);
        return EXCEPTION_EXECUTE_HANDLER;
    }

    std::ostream& operator<<(std::ostream& os, const EXCEPTION_RECORD& red)
    {
        return os << " Thread ID: " << GetCurrentThreadId()
            << "  ExceptionCode: " << red.ExceptionCode << std::endl
            << "  ExceptionFlags: " << red.ExceptionFlags << std::endl
            << "  ExceptionAddress: " << red.ExceptionAddress << std::endl
            << "  NumberParameters:" << red.NumberParameters << std::endl;
    }

    LONG WINAPI GPTUnhandledExceptionFilter(PEXCEPTION_POINTERS pExceptionInfo)
    {
        CreateMiniDump(pExceptionInfo, L"Exception.dmp");
        std::cerr << "Unknown error: " << (*pExceptionInfo->ExceptionRecord) << std::endl;
        exit(pExceptionInfo->ExceptionRecord->ExceptionCode);
        return EXCEPTION_EXECUTE_HANDLER;
    }
}

void SetUnhandleException()
{
    //DumpFile::RunCrashHandler();
    //SetUnhandledExceptionFilter(CoreDumpFile::MyUnhandleExceptionFilter);
    SetUnhandledExceptionFilter(CoreDumpFile::GPTUnhandledExceptionFilter);
}

void TestDumpDivideZero()
{
    //
    
    
    int a = 0;
    int ans = 10 / a;
    //int *ptr = &a;
    //delete ptr;
    //delete ptr;
}