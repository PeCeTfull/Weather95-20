/***************************************************************
 * Name:      Weather95_20App.h
 * Purpose:   Defines Application Class
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef WEATHER95_20APP_H
#define WEATHER95_20APP_H

#include "wxTranslationHelper.h"
#include "ConfigFile.h"
#include "DevConfig.h"
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

        short languageID = wxLANGUAGE_ENGLISH_CANADA;
        wxString userTemperatureUnit = wxT('c');
        bool user24HourTimeFormat = true;
        short userDateFormatVariant = 1;
        bool userUseUTF8 = false;
    private:
        bool ValidateApiServiceKey();
};

DECLARE_APP(Weather95_20App);

#endif // WEATHER95_20APP_H
