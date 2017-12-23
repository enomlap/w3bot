#include <windows.h>
#include <iostream>
using namespace std;
HWND hHack=FindWindow(NULL,"Warcraft III");

//DECLARE FUNCTIONS
void write(LPVOID addy, DWORD mydata);
void enableDebugPrivileges();
void dohack();


//Main part
int main() {
    if(!hHack)
    {
        cout << "Warcraft III window was not found" << endl;
        system("pause");
        exit(0);
    }
	cout << "Hack is now loaded - visit <site address>  for future releases, more hacks tools and bots!" << endl;  
	enableDebugPrivileges();
    dohack();          
    system("pause");
  }
void write(LPVOID addy, DWORD mydata)
{
    DWORD PID, TID;
    TID = ::GetWindowThreadProcessId (hHack, &PID);
    HANDLE hopen=OpenProcess( PROCESS_ALL_ACCESS|PROCESS_TERMINATE|PROCESS_VM_OPERATION|PROCESS_VM_READ|
                  PROCESS_VM_WRITE,FALSE,PID);

    WriteProcessMemory(hopen,addy,&mydata,1,0);
    CloseHandle(hopen);  
}
void enableDebugPrivileges()
{
    HANDLE hcurrent=GetCurrentProcess();
    HANDLE hToken;
    BOOL bret=OpenProcessToken(hcurrent,40,&hToken);
    LUID luid;
    bret=LookupPrivilegeValue(NULL,"SeDebugPrivilege",&luid);
    TOKEN_PRIVILEGES NewState,PreviousState;
    DWORD ReturnLength;
    NewState.PrivilegeCount =1;
    NewState.Privileges[0].Luid =luid;
    NewState.Privileges[0].Attributes=2;
    AdjustTokenPrivileges(hToken,FALSE,&NewState,28,&PreviousState,&ReturnLength);
}
void dohack()
{
     // Basic reveal
     write((LPVOID)0x6F3A20C5, 0xB8);	
     write((LPVOID)0x6F3A20C6, 0xFF);
     write((LPVOID)0x6F3A20C7, 0xFF);
     write((LPVOID)0x6F3A20C8, 0xFF);
     write((LPVOID)0x6F3A20C9, 0xFF);
     write((LPVOID)0x6F3A20CA, 0x90);
     write((LPVOID)0x6F3A20CB, 0x90);
     
     //Clickable units + reveal units minimap
      write((LPVOID)0x6F285CD0, 0x40);
      write((LPVOID)0x6F285CD1, 0x90);

}
