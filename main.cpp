#include <windows.h>
#include<TlHelp32.h>
#include <iostream>
#include <tchar.h> 
#include <vector>

#define color_black      0
#define color_dark_blue  1
#define color_dark_green 2
#define color_light_blue 3
#define color_dark_red   4
#define color_magenta    5
#define color_orange     6
#define color_light_gray 7
#define color_gray       8
#define color_blue       9
#define color_green     10
#define color_cyan      11
#define color_red       12
#define color_pink      13
#define color_yellow    14
#define color_white     15

DWORD diamondBaseAdress = 0x01037CE8;
std::vector<DWORD> diamondOffsets{ 0x48, 0x8, 0x318, 0x8, 0x28, 0x14, 0x4FC };


std::vector<DWORD> moneyOffsets{};

DWORD baseAddress = NULL;
int num;
int newValue;

uintptr_t GetModuleBaseAddress(DWORD procId, const wchar_t* modName)
{
    uintptr_t modBaseAddr = 0;
    HANDLE hSnap = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, procId);
    if (hSnap != INVALID_HANDLE_VALUE)
    {
        MODULEENTRY32 modEntry;
        modEntry.dwSize = sizeof(modEntry);
        if (Module32First(hSnap, &modEntry))
        {
            do
            {
                if (!_wcsicmp(modEntry.szModule, modName))
                {
                    modBaseAddr = (uintptr_t)modEntry.modBaseAddr;
                    break;
                }
            } while (Module32Next(hSnap, &modEntry));
        }
    }
    CloseHandle(hSnap);
    return modBaseAddr;
}

int main()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color_red);
    std::cout << "CrushCrush cheat made by Mepon\n\n\n";
    SetConsoleTextAttribute(hConsole, color_white);
    HWND hGameWindow = FindWindow(NULL, L"Crush Crush");

    if (hGameWindow == NULL) 
    {
        MessageBoxA(NULL,"Cant find process --> CrushCrush.exe","Error",NULL);
        return 0;
    }

    DWORD pID = NULL; 
    GetWindowThreadProcessId(hGameWindow, &pID);
    HANDLE processHandle = NULL;
    processHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pID);

    if (processHandle == INVALID_HANDLE_VALUE || processHandle == NULL)
    { 
        MessageBoxA(NULL, "Failed to open process", "Error", NULL);
        return 0;
    }

    DWORD gameBaseAddress = GetModuleBaseAddress(pID, L"CrushCrush.exe");
    
    SetConsoleTextAttribute(hConsole, color_yellow);
    std::cout << "Features:\n\n";
    SetConsoleTextAttribute(hConsole, color_blue);
    std::cout << "Diamond hack[1]\nMoney hack[2]\nNSFW unlocker[3]";
    SetConsoleTextAttribute(hConsole, color_white);
    std::cout << "\n\nEnter number: ";
    std::cin >> num;

    if (num == 1)
    {
        system("CLS");
        SetConsoleTextAttribute(hConsole, color_green);
        std::cout << "Diamond hack\n\n";
        SetConsoleTextAttribute(hConsole, color_white);
        ReadProcessMemory(processHandle, (LPVOID)(gameBaseAddress + diamondBaseAdress), &baseAddress, sizeof(baseAddress), NULL);
        DWORD diamondAddress = baseAddress;
        for (int i = 0; i < diamondOffsets.size() - 1; i++)
        {
            ReadProcessMemory(processHandle, (LPVOID)(diamondAddress + diamondOffsets.at(i)), &diamondAddress, sizeof(diamondAddress), NULL);
        }
        diamondAddress += diamondOffsets.at(diamondOffsets.size() - 1);
        std::cout << "How many diamonds you want: ";
        std::cin >> newValue;
        WriteProcessMemory(processHandle, (LPVOID)(diamondAddress), &newValue,4,0);
        system("CLS");
        SetConsoleTextAttribute(hConsole, color_green);
        std::cout << "Diamond hack\n\n";
        SetConsoleTextAttribute(hConsole, color_white);
        std::cout << "Diamonds changed to " << newValue << ". Buy something to have the diamonds";
        Sleep(8000);
        return 0;
    }

    if (num == 2)
    {
        std::cout << "Buy the paid version. Dm me on Discord(Mepon#0127).";
        Sleep(8000);
        return 0;
    }

    if (num == 3)
    {
        std::cout << "Buy the paid version. Dm me on Discord(Mepon#0127).";
        Sleep(8000);
        return 0;
    }

    else
    {
        MessageBoxA(NULL, "Invalid key", "Error", NULL);
        return 0;
    }
}
