#include "ConfigFile.h"
#include "../Weather95_20App.h"
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/intl.h>

ConfigFile::ConfigFile()
{
    //ctor
    m_Config = new wxFileConfig(wxT("Weather9520"), wxEmptyString, wxGetCwd() + '\\' + configFileName, wxEmptyString, wxCONFIG_USE_LOCAL_FILE);
}

void ConfigFile::SaveConfiguration()
{
    m_Config->Write(wxT("/Weather9520/LanguageID"), wxLANGUAGE_ENGLISH_CANADA);
    m_Config->Write(wxT("/Weather9520/TemperatureUnit"), wxT("C"));
    m_Config->Write(wxT("/Weather9520/24HourTimeFormat"), true);
    m_Config->Write(wxT("/Weather9520/DateFormatVariant"), 1);
    m_Config->Write(wxT("/Weather9520/UseUTF8"), false);

    m_Config->Flush();
}

void ConfigFile::SaveConfiguration(short languageID, wxString temperatureUnit, bool twentyFourHourTimeFormat, short dateFormatVariant, bool useUTF8)
{
    m_Config->Write(wxT("/Weather9520/LanguageID"), languageID);
    m_Config->Write(wxT("/Weather9520/TemperatureUnit"), temperatureUnit.Upper());
    m_Config->Write(wxT("/Weather9520/24HourTimeFormat"), twentyFourHourTimeFormat);
    m_Config->Write(wxT("/Weather9520/DateFormatVariant"), dateFormatVariant);
    m_Config->Write(wxT("/Weather9520/UseUTF8"), useUTF8);

    m_Config->Flush();
}

void ConfigFile::LoadConfiguration()
{
    wxGetApp().languageID = m_Config->Read(wxT("/Weather9520/LanguageID"), wxLANGUAGE_ENGLISH_CANADA);

    wxGetApp().userTemperatureUnit = m_Config->Read(wxT("/Weather9520/TemperatureUnit"), wxT("C"));
    wxGetApp().userTemperatureUnit.MakeLower();
    if(wxGetApp().userTemperatureUnit != wxT('c') && wxGetApp().userTemperatureUnit != wxT('f'))
    {
        wxGetApp().userTemperatureUnit = wxT('c');
    }

    wxString user24HourTimeFormatStr = m_Config->Read(wxT("/Weather9520/24HourTimeFormat"), wxT("1"));
    wxGetApp().user24HourTimeFormat = user24HourTimeFormatStr.Trim() == wxT("1");

    wxGetApp().userDateFormatVariant = m_Config->Read(wxT("/Weather9520/DateFormatVariant"), 1);

    wxString userUseUTF8Str = m_Config->Read(wxT("/Weather9520/UseUTF8"), wxT("0"));
    wxGetApp().userUseUTF8 = userUseUTF8Str.Trim() == wxT("1");
}

ConfigFile::~ConfigFile()
{
    //dtor
}
