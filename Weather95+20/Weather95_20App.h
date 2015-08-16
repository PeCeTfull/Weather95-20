/***************************************************************
 * Name:      Weather95_20App.h
 * Purpose:   Defines Application Class
 * Author:    PeCeT_full (pecetfull@komputermania.pl.eu.org)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.komputermania.pl.eu.org/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef WEATHER95_20APP_H
#define WEATHER95_20APP_H

#include "wxTranslationHelper.h"
#include "ConfigFile.h"
#include <wx/app.h>

class Weather95_20App : public wxApp
{
    wxTranslationHelper *m_TranslationHelper;
    public:
        virtual bool OnInit();
        virtual int OnExit();
        void OnSetLanguage(short languageID);
        short SelectLanguage();
        bool DoesLangsFolderExist();
        short languageID = wxLANGUAGE_ENGLISH_CANADA; // parameter 1
        wxString userTemperatureUnit = wxT('c'); // parameter 2
        bool user24HourTimeFormat = true; // parameter 3
        short userDateFormatVariant = 1; // parameter 4
        bool userUseUTF8 = false; // parameter 5
};

DECLARE_APP(Weather95_20App);

#endif // WEATHER95_20APP_H
