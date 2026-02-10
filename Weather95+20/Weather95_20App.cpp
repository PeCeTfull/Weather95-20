/***************************************************************
 * Name:      Weather95_20App.cpp
 * Purpose:   Code for Application Class
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#include "Weather95_20App.h"
#include <wx/filename.h>
#include <wx/dir.h>

//(*AppHeaders
#include "Weather95_20Main.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(Weather95_20App);

bool Weather95_20App::OnInit()
{
    m_TranslationHelper = new wxTranslationHelper(*this);
    bool doesLangsFolderExist = DoesLangsFolderExist();

    wxString *parameters;
    ConfigFile *newConfigFile = new ConfigFile();
    if(!wxFileName::FileExists(newConfigFile->configFileName))
        newConfigFile->NewFileContents();
    else
    {
        parameters = newConfigFile->ReadFileContents();

        const wxChar equalitySign = '=';
        size_t equalitySignPos;
        if(doesLangsFolderExist)
        {
            equalitySignPos = parameters[1].Find(equalitySign);
            languageID = wxAtoi(parameters[1].SubString(equalitySignPos + 1, parameters[1].Length()));
        }
        equalitySignPos = parameters[2].Find(equalitySign);
        userTemperatureUnit = parameters[2].SubString(equalitySignPos + 1, parameters[2].Length());
        userTemperatureUnit.MakeLower();
        if(userTemperatureUnit != wxT('c') && userTemperatureUnit != wxT('f'))
            userTemperatureUnit = wxT('c');
        equalitySignPos = parameters[3].Find(equalitySign);
        user24HourTimeFormat = wxAtoi(parameters[3].SubString(equalitySignPos + 1, parameters[3].Length()));
        equalitySignPos = parameters[4].Find(equalitySign);
        userDateFormatVariant = wxAtoi(parameters[4].SubString(equalitySignPos + 1, parameters[4].Length()));
        equalitySignPos = parameters[5].Find(equalitySign);
        userUseUTF8 = wxAtoi(parameters[5].SubString(equalitySignPos + 1, parameters[5].Length()));
    }
    wxDELETE(newConfigFile);
    if(doesLangsFolderExist)
        m_TranslationHelper->Load(languageID);

    //(*AppInitialize
    bool wxsOK = ValidateApiServiceKey();
    wxInitAllImageHandlers();
    if ( wxsOK )
    {
    	Weather95_20Frame* Frame = new Weather95_20Frame(0);
    	Frame->Show();
    	SetTopWindow(Frame);
    }
    //*)
    return wxsOK;

}

int Weather95_20App::OnExit()
{
    if(m_TranslationHelper)
        wxDELETE(m_TranslationHelper);
    return 0;
}

void Weather95_20App::OnSetLanguage(short languageID)
{
    m_TranslationHelper->SetLanguage(languageID);
}

short Weather95_20App::SelectLanguage()
{
    wxArrayString names;
    wxArrayShort identifiers;
    m_TranslationHelper->GetInstalledLanguages(names, identifiers);
    return m_TranslationHelper->AskUserForLanguage(names, identifiers);
}

bool Weather95_20App::DoesLangsFolderExist()
{
    return wxDir::Exists(m_TranslationHelper->languagesPath) ? true : false;
}

bool Weather95_20App::ValidateApiServiceKey()
{
    bool result = true;

    if (API_SERVICE_KEY == "CHANGE_ME")
    {
        wxMessageBox(_("You are using a version of Weather 95+20 that has an invalid API key for the WeatherAPI.com service. Please contact your software provider and ask for a valid build.\n\nThe application will terminate now."), _("Error"), wxICON_HAND);
        result = false;
    }

    return result;
}
