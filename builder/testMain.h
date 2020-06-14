/***************************************************************
 * Name:      testMain.h
 * Purpose:   Defines Application Frame
 * Author:    Fahad (fahad@email.com)
 * Created:   2020-06-13
 * Copyright: Fahad (no.com)
 * License:
 **************************************************************/

#ifndef TESTMAIN_H
#define TESTMAIN_H

//(*Headers(testDialog)
#include <wx/button.h>
#include <wx/checkbox.h>
#include <wx/dialog.h>
#include <wx/filedlg.h>
#include <wx/statbox.h>
#include <wx/stattext.h>
#include <wx/textctrl.h>
//*)

class testDialog: public wxDialog
{
    public:

        testDialog(wxWindow* parent,wxWindowID id = -1);
        virtual ~testDialog();

    private:

        //(*Handlers(testDialog)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnButton1Click(wxCommandEvent& event);
        void OnCheckBox1Click(wxCommandEvent& event);
        void OnInit(wxInitDialogEvent& event);
        void OnsmtpserverText(wxCommandEvent& event);
        void OnButton4Click(wxCommandEvent& event);
        void OnCheckBox2Click(wxCommandEvent& event);
        void OnButton2Click(wxCommandEvent& event);
        //*)

        //(*Identifiers(testDialog)
        static const long ID_STATICBOX1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_CHECKBOX1;
        static const long ID_TEXTCTRL1;
        static const long ID_STATICTEXT1;
        static const long ID_BUTTON3;
        static const long ID_STATICBOX2;
        static const long ID_STATICTEXT3;
        static const long ID_TEXTCTRL3;
        static const long ID_STATICTEXT4;
        static const long ID_TEXTCTRL4;
        static const long ID_BUTTON4;
        //*)

        //(*Declarations(testDialog)
        wxButton* Button1;
        wxButton* Button2;
        wxButton* Button3;
        wxButton* Button4;
        wxCheckBox* msgbox;
        wxFileDialog* FileDialog1;
        wxStaticBox* StaticBox1;
        wxStaticBox* StaticBox2;
        wxStaticText* StaticText1;
        wxStaticText* StaticText3;
        wxStaticText* StaticText4;
        wxTextCtrl* gmail;
        wxTextCtrl* msg;
        wxTextCtrl* passw;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // TESTMAIN_H
