/***************************************************************
 * Name:      Weather95_20Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#include "Weather95_20Main.h"
#include "Weather95_20App.h"
#include "ConfigFile.h"
#include "wxImagePanel.h"
#include "ApiServiceLogo.h"
#include "include/WeatherForecastRequestThread.h"
#include <wx/msgdlg.h>
#include <wx/txtstrm.h>
#include <wx/aboutdlg.h>
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/filedlg.h>
#include <wx/mstream.h>
#include <wx/dir.h>
#include <wx/filename.h>
#include <cmath>

#define ICON_NAME "aaaa"

//(*InternalHeaders(Weather95_20Frame)
#include <wx/settings.h>
#include <wx/font.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

//helper functions
enum wxBuildInfoFormat {
    short_f, long_f };

wxString wxBuildInfo(wxBuildInfoFormat format)
{
    wxString wxBuild(wxVERSION_STRING);

    if (format == long_f )
    {
#if defined(__WXMSW__)
        wxBuild << _T("-Windows");
#elif defined(__UNIX__)
        wxBuild << _T("-Linux");
#endif

#if wxUSE_UNICODE
        wxBuild << _T("-Unicode build");
#else
        wxBuild << _T("-ANSI build");
#endif // wxUSE_UNICODE
    }

    return wxBuild;
}

//(*IdInit(Weather95_20Frame)
const long Weather95_20Frame::ID_LOCATIONSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_LOCATIONTEXTCTRL = wxNewId();
const long Weather95_20Frame::ID_LOGOPANEL = wxNewId();
const long Weather95_20Frame::ID_TEMPERATURESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CURRENTTEMPERATURESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CURRENTWEATHERCONDITIONSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_WINDSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_DIRECTIONSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SPEEDSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_GUSTSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_ATMOSPHERESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_PRESSURESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_PRECIPITATIONSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_HUMIDITYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CLOUDCOVERSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_VISIBILITYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_ASTRONOMYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SUNRISESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SUNSETSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_MOONPHASESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_INDEXSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_FEELSLIKESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_WINDCHILLSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_HEATINDEXSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_DEWPOINTSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_UVINDEXSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_TODAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_DASHSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_MAXWINDSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFRAINSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFSNOWSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_TOTALPRECIPITATIONSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_TOTALSNOWSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_TOMORROWSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_DASHSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_MAXWINDSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFRAINSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFSNOWSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_TOTALPRECIPITATIONSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_TOTALSNOWSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_THIRDDAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_DASHSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_MAXWINDSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFRAINSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_CHANCEOFSNOWSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_TOTALPRECIPITATIONSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_TOTALSNOWSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::idMenuCheck = wxNewId();
const long Weather95_20Frame::idMenuAsFile = wxNewId();
const long Weather95_20Frame::idMenuToClipboard = wxNewId();
const long Weather95_20Frame::idMenuSave = wxNewId();
const long Weather95_20Frame::idMenuQuit = wxNewId();
const long Weather95_20Frame::idMenuImperial = wxNewId();
const long Weather95_20Frame::idMenuMetric = wxNewId();
const long Weather95_20Frame::idMenuMeasuringUnits = wxNewId();
const long Weather95_20Frame::idMenu12HourClock = wxNewId();
const long Weather95_20Frame::idMenu24HourClock = wxNewId();
const long Weather95_20Frame::idMenuTimeFormat = wxNewId();
const long Weather95_20Frame::idMenuYearHyphenMonthHyphenDay = wxNewId();
const long Weather95_20Frame::idMenuDayHyphenMonthHyphenYear = wxNewId();
const long Weather95_20Frame::idMenuYearHyphenDayHyphenMonth = wxNewId();
const long Weather95_20Frame::idMenuMonthHyphenDayHyphenYear = wxNewId();
const long Weather95_20Frame::idMenuYearDotMonthDotDay = wxNewId();
const long Weather95_20Frame::idMenuDayDotMonthDotYear = wxNewId();
const long Weather95_20Frame::idMenuYearDotDayDotMonth = wxNewId();
const long Weather95_20Frame::idMenuMonthDotDayDotYear = wxNewId();
const long Weather95_20Frame::idMenuYearSlashMonthSlashDay = wxNewId();
const long Weather95_20Frame::idMenuDaySlashMonthSlashYear = wxNewId();
const long Weather95_20Frame::idMenuYearSlashDaySlashMonth = wxNewId();
const long Weather95_20Frame::idMenuMonthSlashDaySlashYear = wxNewId();
const long Weather95_20Frame::idMenuDateFormat = wxNewId();
const long Weather95_20Frame::idMenuANSI = wxNewId();
const long Weather95_20Frame::idMenuUTF8 = wxNewId();
const long Weather95_20Frame::idMenuTargetFileEncoding = wxNewId();
const long Weather95_20Frame::idMenuChangeLanguage = wxNewId();
const long Weather95_20Frame::idMenuSaveSettings = wxNewId();
const long Weather95_20Frame::idMenuAbout = wxNewId();
const long Weather95_20Frame::ID_MAINSTATUSBAR = wxNewId();
//*)

BEGIN_EVENT_TABLE(Weather95_20Frame,wxFrame)
EVT_MENU(idMenuCheck, Weather95_20Frame::OnCheck)
EVT_MENU(idMenuAsFile, Weather95_20Frame::OnSaveAsFile)
EVT_MENU(idMenuToClipboard, Weather95_20Frame::OnSaveToClipboard)
EVT_MENU(idMenuImperial, Weather95_20Frame::OnImperial)
EVT_MENU(idMenuMetric, Weather95_20Frame::OnMetric)
EVT_MENU(idMenuANSI, Weather95_20Frame::OnANSI)
EVT_MENU(idMenuUTF8, Weather95_20Frame::OnUTF8)
EVT_MENU(idMenu12HourClock, Weather95_20Frame::On12HourClock)
EVT_MENU(idMenu24HourClock, Weather95_20Frame::On24HourClock)
EVT_MENU(idMenuYearHyphenMonthHyphenDay, Weather95_20Frame::OnYearHyphenMonthHyphenDay)
EVT_MENU(idMenuDayHyphenMonthHyphenYear, Weather95_20Frame::OnDayHyphenMonthHyphenYear)
EVT_MENU(idMenuYearHyphenDayHyphenMonth, Weather95_20Frame::OnYearHyphenDayHyphenMonth)
EVT_MENU(idMenuMonthHyphenDayHyphenYear, Weather95_20Frame::OnMonthHyphenDayHyphenYear)
EVT_MENU(idMenuYearDotMonthDotDay, Weather95_20Frame::OnYearDotMonthDotDay)
EVT_MENU(idMenuDayDotMonthDotYear, Weather95_20Frame::OnDayDotMonthDotYear)
EVT_MENU(idMenuYearDotDayDotMonth, Weather95_20Frame::OnYearDotDayDotMonth)
EVT_MENU(idMenuMonthDotDayDotYear, Weather95_20Frame::OnMonthDotDayDotYear)
EVT_MENU(idMenuYearSlashMonthSlashDay, Weather95_20Frame::OnYearSlashMonthSlashDay)
EVT_MENU(idMenuDaySlashMonthSlashYear, Weather95_20Frame::OnDaySlashMonthSlashYear)
EVT_MENU(idMenuYearSlashDaySlashMonth, Weather95_20Frame::OnYearSlashDaySlashMonth)
EVT_MENU(idMenuMonthSlashDaySlashYear, Weather95_20Frame::OnMonthSlashDaySlashYear)
EVT_MENU(idMenuSaveSettings, Weather95_20Frame::OnSaveSettings)
EVT_MENU(idMenuChangeLanguage, Weather95_20Frame::OnChangeLanguage)
    //(*EventTable(Weather95_20Frame)
    //*)
END_EVENT_TABLE()

WeatherForecastRequestThread *weatherForecastRequestThread = NULL;

Weather95_20Frame::Weather95_20Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Weather95_20Frame)
    wxFlexGridSizer* ThirdDayFlexGridSizer;
    wxMenuItem* QuitMenuItem;
    wxMenuBar* MainMenuBar;
    wxFlexGridSizer* IndexFlexGridSizer;
    wxFlexGridSizer* ThirdDayDetailsFlexGridSizer;
    wxFlexGridSizer* AtmosphereFlexGridSizer;
    wxMenu* FileMenu;
    wxFlexGridSizer* HeaderFlexGridSizer;
    wxFlexGridSizer* TodayFlexGridSizer;
    wxFlexGridSizer* CurrentConditionsFlexGridSizer;
    wxStaticBoxSizer* WeatherForecastStaticBoxSizer;
    wxFlexGridSizer* InputFlexGridSizer;
    wxFlexGridSizer* AstronomyFlexGridSizer;
    wxFlexGridSizer* TomorrowDetailsFlexGridSizer;
    wxFlexGridSizer* WeatherForecastFlexGridSizer;
    wxMenuItem* AboutMenuItem;
    wxFlexGridSizer* ThirdDayTemperatureFlexGridSizer;
    wxFlexGridSizer* TomorrowFlexGridSizer;
    wxFlexGridSizer* TodayTemperatureFlexGridSizer;
    wxFlexGridSizer* TemperatureFlexGridSizer;
    wxFlexGridSizer* TomorrowTemperatureFlexGridSizer;
    wxFlexGridSizer* MainFlexGridSizer;
    wxFlexGridSizer* WindFlexGridSizer;
    wxMenu* HelpMenu;
    wxFlexGridSizer* TodayDetailsFlexGridSizer;
    wxStaticBoxSizer* CurrentConditionsStaticBoxSizer;

    Create(parent, wxID_ANY, _("Weather 95+20"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    MainFlexGridSizer = new wxFlexGridSizer(4, 1, 0, 0);
    HeaderFlexGridSizer = new wxFlexGridSizer(1, 2, 0, 0);
    HeaderFlexGridSizer->AddGrowableCol(0);
    HeaderFlexGridSizer->AddGrowableRow(1);
    InputFlexGridSizer = new wxFlexGridSizer(1, 2, 0, 0);
    InputFlexGridSizer->AddGrowableCol(1);
    InputFlexGridSizer->AddGrowableRow(1);
    LocationStaticText = new wxStaticText(this, ID_LOCATIONSTATICTEXT, _("Location:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LOCATIONSTATICTEXT"));
    InputFlexGridSizer->Add(LocationStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LocationTextCtrl = new wxTextCtrl(this, ID_LOCATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), 0, wxDefaultValidator, _T("ID_LOCATIONTEXTCTRL"));
    InputFlexGridSizer->Add(LocationTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    HeaderFlexGridSizer->Add(InputFlexGridSizer, 1, wxEXPAND|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LogoPanel = new wxPanel(this, ID_LOGOPANEL, wxDefaultPosition, wxSize(107,50), wxTAB_TRAVERSAL, _T("ID_LOGOPANEL"));
    HeaderFlexGridSizer->Add(LogoPanel, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    MainFlexGridSizer->Add(HeaderFlexGridSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsStaticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Current conditions"));
    CurrentConditionsFlexGridSizer = new wxFlexGridSizer(1, 5, 0, 0);
    TemperatureFlexGridSizer = new wxFlexGridSizer(3, 1, 0, 0);
    TemperatureStaticText = new wxStaticText(this, ID_TEMPERATURESTATICTEXT, _("Temperature"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEMPERATURESTATICTEXT"));
    wxFont TemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TemperatureStaticTextFont.Ok() ) TemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TemperatureStaticTextFont.SetWeight(wxBOLD);
    TemperatureStaticText->SetFont(TemperatureStaticTextFont);
    TemperatureFlexGridSizer->Add(TemperatureStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentTemperatureStaticText = new wxStaticText(this, ID_CURRENTTEMPERATURESTATICTEXT, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTTEMPERATURESTATICTEXT"));
    wxFont CurrentTemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentTemperatureStaticTextFont.Ok() ) CurrentTemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentTemperatureStaticTextFont.SetPointSize(37);
    CurrentTemperatureStaticTextFont.SetWeight(wxBOLD);
    CurrentTemperatureStaticText->SetFont(CurrentTemperatureStaticTextFont);
    TemperatureFlexGridSizer->Add(CurrentTemperatureStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentWeatherConditionStaticText = new wxStaticText(this, ID_CURRENTWEATHERCONDITIONSTATICTEXT, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTWEATHERCONDITIONSTATICTEXT"));
    TemperatureFlexGridSizer->Add(CurrentWeatherConditionStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsFlexGridSizer->Add(TemperatureFlexGridSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    WindFlexGridSizer = new wxFlexGridSizer(5, 1, 0, 0);
    WindStaticText = new wxStaticText(this, ID_WINDSTATICTEXT, _("Wind"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WINDSTATICTEXT"));
    wxFont WindStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !WindStaticTextFont.Ok() ) WindStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    WindStaticTextFont.SetWeight(wxBOLD);
    WindStaticText->SetFont(WindStaticTextFont);
    WindFlexGridSizer->Add(WindStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DirectionStaticText = new wxStaticText(this, ID_DIRECTIONSTATICTEXT, _("Direction: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DIRECTIONSTATICTEXT"));
    WindFlexGridSizer->Add(DirectionStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SpeedStaticText = new wxStaticText(this, ID_SPEEDSTATICTEXT, _("Speed: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SPEEDSTATICTEXT"));
    WindFlexGridSizer->Add(SpeedStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    GustStaticText = new wxStaticText(this, ID_GUSTSTATICTEXT, _("Gust: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_GUSTSTATICTEXT"));
    WindFlexGridSizer->Add(GustStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsFlexGridSizer->Add(WindFlexGridSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    AtmosphereFlexGridSizer = new wxFlexGridSizer(6, 1, 0, 0);
    AtmosphereStaticText = new wxStaticText(this, ID_ATMOSPHERESTATICTEXT, _("Atmosphere"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ATMOSPHERESTATICTEXT"));
    wxFont AtmosphereStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !AtmosphereStaticTextFont.Ok() ) AtmosphereStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    AtmosphereStaticTextFont.SetWeight(wxBOLD);
    AtmosphereStaticText->SetFont(AtmosphereStaticTextFont);
    AtmosphereFlexGridSizer->Add(AtmosphereStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    PressureStaticText = new wxStaticText(this, ID_PRESSURESTATICTEXT, _("Pressure: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_PRESSURESTATICTEXT"));
    AtmosphereFlexGridSizer->Add(PressureStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PrecipitationStaticText = new wxStaticText(this, ID_PRECIPITATIONSTATICTEXT, _("Precipitation: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_PRECIPITATIONSTATICTEXT"));
    AtmosphereFlexGridSizer->Add(PrecipitationStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    HumidityStaticText = new wxStaticText(this, ID_HUMIDITYSTATICTEXT, _("Humidity: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_HUMIDITYSTATICTEXT"));
    AtmosphereFlexGridSizer->Add(HumidityStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CloudCoverStaticText = new wxStaticText(this, ID_CLOUDCOVERSTATICTEXT, _("Cloud cover: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CLOUDCOVERSTATICTEXT"));
    AtmosphereFlexGridSizer->Add(CloudCoverStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VisibilityStaticText = new wxStaticText(this, ID_VISIBILITYSTATICTEXT, _("Visibility: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VISIBILITYSTATICTEXT"));
    AtmosphereFlexGridSizer->Add(VisibilityStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsFlexGridSizer->Add(AtmosphereFlexGridSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    AstronomyFlexGridSizer = new wxFlexGridSizer(4, 1, 0, 0);
    AstronomyStaticText = new wxStaticText(this, ID_ASTRONOMYSTATICTEXT, _("Astronomy"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ASTRONOMYSTATICTEXT"));
    wxFont AstronomyStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !AstronomyStaticTextFont.Ok() ) AstronomyStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    AstronomyStaticTextFont.SetWeight(wxBOLD);
    AstronomyStaticText->SetFont(AstronomyStaticTextFont);
    AstronomyFlexGridSizer->Add(AstronomyStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SunriseStaticText = new wxStaticText(this, ID_SUNRISESTATICTEXT, _("Sunrise: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SUNRISESTATICTEXT"));
    AstronomyFlexGridSizer->Add(SunriseStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SunsetStaticText = new wxStaticText(this, ID_SUNSETSTATICTEXT, _("Sunset: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SUNSETSTATICTEXT"));
    AstronomyFlexGridSizer->Add(SunsetStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    MoonPhaseStaticText = new wxStaticText(this, ID_MOONPHASESTATICTEXT, _("Moon phase: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MOONPHASESTATICTEXT"));
    AstronomyFlexGridSizer->Add(MoonPhaseStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsFlexGridSizer->Add(AstronomyFlexGridSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    IndexFlexGridSizer = new wxFlexGridSizer(5, 1, 0, 0);
    IndexStaticText = new wxStaticText(this, ID_INDEXSTATICTEXT, _("Index"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_INDEXSTATICTEXT"));
    wxFont IndexStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !IndexStaticTextFont.Ok() ) IndexStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    IndexStaticTextFont.SetWeight(wxBOLD);
    IndexStaticText->SetFont(IndexStaticTextFont);
    IndexFlexGridSizer->Add(IndexStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FeelsLikeStaticText = new wxStaticText(this, ID_FEELSLIKESTATICTEXT, _("Feels like: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_FEELSLIKESTATICTEXT"));
    IndexFlexGridSizer->Add(FeelsLikeStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    WindChillStaticText = new wxStaticText(this, ID_WINDCHILLSTATICTEXT, _("Wind chill: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WINDCHILLSTATICTEXT"));
    IndexFlexGridSizer->Add(WindChillStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    HeatIndexStaticText = new wxStaticText(this, ID_HEATINDEXSTATICTEXT, _("Heat index: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_HEATINDEXSTATICTEXT"));
    IndexFlexGridSizer->Add(HeatIndexStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DewPointStaticText = new wxStaticText(this, ID_DEWPOINTSTATICTEXT, _("Dew point: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DEWPOINTSTATICTEXT"));
    IndexFlexGridSizer->Add(DewPointStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    UvIndexStaticText = new wxStaticText(this, ID_UVINDEXSTATICTEXT, _("UV index: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_UVINDEXSTATICTEXT"));
    IndexFlexGridSizer->Add(UvIndexStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsFlexGridSizer->Add(IndexFlexGridSizer, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    CurrentConditionsStaticBoxSizer->Add(CurrentConditionsFlexGridSizer, 1, wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainFlexGridSizer->Add(CurrentConditionsStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Weather forecast"));
    WeatherForecastFlexGridSizer = new wxFlexGridSizer(1, 3, 0, 0);
    WeatherForecastFlexGridSizer->AddGrowableCol(1);
    TodayFlexGridSizer = new wxFlexGridSizer(4, 1, 0, 0);
    TodayStaticText = new wxStaticText(this, ID_TODAYSTATICTEXT, _("Today"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TODAYSTATICTEXT"));
    wxFont TodayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TodayStaticTextFont.Ok() ) TodayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TodayStaticTextFont.SetWeight(wxBOLD);
    TodayStaticText->SetFont(TodayStaticTextFont);
    TodayFlexGridSizer->Add(TodayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TodayTemperatureFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
    CurrentMinTempStaticText1 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT1, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT1"));
    wxFont CurrentMinTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText1Font.Ok() ) CurrentMinTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText1Font.SetPointSize(12);
    CurrentMinTempStaticText1Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText1->SetFont(CurrentMinTempStaticText1Font);
    TodayTemperatureFlexGridSizer->Add(CurrentMinTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DashStaticText1 = new wxStaticText(this, ID_DASHSTATICTEXT1, _("–"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DASHSTATICTEXT1"));
    wxFont DashStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !DashStaticText1Font.Ok() ) DashStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    DashStaticText1Font.SetPointSize(12);
    DashStaticText1->SetFont(DashStaticText1Font);
    TodayTemperatureFlexGridSizer->Add(DashStaticText1, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText1 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT1, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT1"));
    wxFont CurrentMaxTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText1Font.Ok() ) CurrentMaxTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText1Font.SetPointSize(12);
    CurrentMaxTempStaticText1Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText1->SetFont(CurrentMaxTempStaticText1Font);
    TodayTemperatureFlexGridSizer->Add(CurrentMaxTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TodayFlexGridSizer->Add(TodayTemperatureFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText1 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT1, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT1"));
    TodayFlexGridSizer->Add(WeatherConditionStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TodayDetailsFlexGridSizer = new wxFlexGridSizer(5, 1, 0, 0);
    MaxWindStaticText1 = new wxStaticText(this, ID_MAXWINDSTATICTEXT1, _("Maximum wind: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXWINDSTATICTEXT1"));
    TodayDetailsFlexGridSizer->Add(MaxWindStaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfRainStaticText1 = new wxStaticText(this, ID_CHANCEOFRAINSTATICTEXT1, _("Chance of rain: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFRAINSTATICTEXT1"));
    TodayDetailsFlexGridSizer->Add(ChanceOfRainStaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfSnowStaticText1 = new wxStaticText(this, ID_CHANCEOFSNOWSTATICTEXT1, _("Chance of snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFSNOWSTATICTEXT1"));
    TodayDetailsFlexGridSizer->Add(ChanceOfSnowStaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalPrecipitationStaticText1 = new wxStaticText(this, ID_TOTALPRECIPITATIONSTATICTEXT1, _("Total precipitation: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALPRECIPITATIONSTATICTEXT1"));
    TodayDetailsFlexGridSizer->Add(TotalPrecipitationStaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalSnowStaticText1 = new wxStaticText(this, ID_TOTALSNOWSTATICTEXT1, _("Total snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALSNOWSTATICTEXT1"));
    TodayDetailsFlexGridSizer->Add(TotalSnowStaticText1, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TodayFlexGridSizer->Add(TodayDetailsFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastFlexGridSizer->Add(TodayFlexGridSizer, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TomorrowFlexGridSizer = new wxFlexGridSizer(4, 1, 0, 0);
    TomorrowStaticText = new wxStaticText(this, ID_TOMORROWSTATICTEXT, _("Tomorrow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOMORROWSTATICTEXT"));
    wxFont TomorrowStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TomorrowStaticTextFont.Ok() ) TomorrowStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TomorrowStaticTextFont.SetWeight(wxBOLD);
    TomorrowStaticText->SetFont(TomorrowStaticTextFont);
    TomorrowFlexGridSizer->Add(TomorrowStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TomorrowTemperatureFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
    CurrentMinTempStaticText2 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT2, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT2"));
    wxFont CurrentMinTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText2Font.Ok() ) CurrentMinTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText2Font.SetPointSize(12);
    CurrentMinTempStaticText2Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText2->SetFont(CurrentMinTempStaticText2Font);
    TomorrowTemperatureFlexGridSizer->Add(CurrentMinTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DashStaticText2 = new wxStaticText(this, ID_DASHSTATICTEXT2, _("–"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DASHSTATICTEXT2"));
    wxFont DashStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !DashStaticText2Font.Ok() ) DashStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    DashStaticText2Font.SetPointSize(12);
    DashStaticText2->SetFont(DashStaticText2Font);
    TomorrowTemperatureFlexGridSizer->Add(DashStaticText2, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText2 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT2, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT2"));
    wxFont CurrentMaxTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText2Font.Ok() ) CurrentMaxTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText2Font.SetPointSize(12);
    CurrentMaxTempStaticText2Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText2->SetFont(CurrentMaxTempStaticText2Font);
    TomorrowTemperatureFlexGridSizer->Add(CurrentMaxTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TomorrowFlexGridSizer->Add(TomorrowTemperatureFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText2 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT2, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT2"));
    TomorrowFlexGridSizer->Add(WeatherConditionStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TomorrowDetailsFlexGridSizer = new wxFlexGridSizer(3, 1, 0, 0);
    MaxWindStaticText2 = new wxStaticText(this, ID_MAXWINDSTATICTEXT2, _("Maximum wind: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXWINDSTATICTEXT2"));
    TomorrowDetailsFlexGridSizer->Add(MaxWindStaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfRainStaticText2 = new wxStaticText(this, ID_CHANCEOFRAINSTATICTEXT2, _("Chance of rain: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFRAINSTATICTEXT2"));
    TomorrowDetailsFlexGridSizer->Add(ChanceOfRainStaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfSnowStaticText2 = new wxStaticText(this, ID_CHANCEOFSNOWSTATICTEXT2, _("Chance of snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFSNOWSTATICTEXT2"));
    TomorrowDetailsFlexGridSizer->Add(ChanceOfSnowStaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalPrecipitationStaticText2 = new wxStaticText(this, ID_TOTALPRECIPITATIONSTATICTEXT2, _("Total precipitation: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALPRECIPITATIONSTATICTEXT2"));
    TomorrowDetailsFlexGridSizer->Add(TotalPrecipitationStaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalSnowStaticText2 = new wxStaticText(this, ID_TOTALSNOWSTATICTEXT2, _("Total snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALSNOWSTATICTEXT2"));
    TomorrowDetailsFlexGridSizer->Add(TotalSnowStaticText2, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TomorrowFlexGridSizer->Add(TomorrowDetailsFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastFlexGridSizer->Add(TomorrowFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ThirdDayFlexGridSizer = new wxFlexGridSizer(4, 1, 0, 0);
    ThirdDayStaticText = new wxStaticText(this, ID_THIRDDAYSTATICTEXT, _("3rd Day"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_THIRDDAYSTATICTEXT"));
    wxFont ThirdDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !ThirdDayStaticTextFont.Ok() ) ThirdDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    ThirdDayStaticTextFont.SetWeight(wxBOLD);
    ThirdDayStaticText->SetFont(ThirdDayStaticTextFont);
    ThirdDayFlexGridSizer->Add(ThirdDayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ThirdDayTemperatureFlexGridSizer = new wxFlexGridSizer(0, 3, 0, 0);
    CurrentMinTempStaticText3 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT3, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT3"));
    wxFont CurrentMinTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText3Font.Ok() ) CurrentMinTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText3Font.SetPointSize(12);
    CurrentMinTempStaticText3Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText3->SetFont(CurrentMinTempStaticText3Font);
    ThirdDayTemperatureFlexGridSizer->Add(CurrentMinTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    DashStaticText3 = new wxStaticText(this, ID_DASHSTATICTEXT3, _("–"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DASHSTATICTEXT3"));
    wxFont DashStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !DashStaticText3Font.Ok() ) DashStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    DashStaticText3Font.SetPointSize(12);
    DashStaticText3->SetFont(DashStaticText3Font);
    ThirdDayTemperatureFlexGridSizer->Add(DashStaticText3, 1, wxTOP|wxBOTTOM|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText3 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT3, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT3"));
    wxFont CurrentMaxTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText3Font.Ok() ) CurrentMaxTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText3Font.SetPointSize(12);
    CurrentMaxTempStaticText3Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText3->SetFont(CurrentMaxTempStaticText3Font);
    ThirdDayTemperatureFlexGridSizer->Add(CurrentMaxTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ThirdDayFlexGridSizer->Add(ThirdDayTemperatureFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText3 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT3, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT3"));
    ThirdDayFlexGridSizer->Add(WeatherConditionStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ThirdDayDetailsFlexGridSizer = new wxFlexGridSizer(3, 1, 0, 0);
    MaxWindStaticText3 = new wxStaticText(this, ID_MAXWINDSTATICTEXT3, _("Maximum wind: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXWINDSTATICTEXT3"));
    ThirdDayDetailsFlexGridSizer->Add(MaxWindStaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfRainStaticText3 = new wxStaticText(this, ID_CHANCEOFRAINSTATICTEXT3, _("Chance of rain: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFRAINSTATICTEXT3"));
    ThirdDayDetailsFlexGridSizer->Add(ChanceOfRainStaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ChanceOfSnowStaticText3 = new wxStaticText(this, ID_CHANCEOFSNOWSTATICTEXT3, _("Chance of snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHANCEOFSNOWSTATICTEXT3"));
    ThirdDayDetailsFlexGridSizer->Add(ChanceOfSnowStaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalPrecipitationStaticText3 = new wxStaticText(this, ID_TOTALPRECIPITATIONSTATICTEXT3, _("Total precipitation: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALPRECIPITATIONSTATICTEXT3"));
    ThirdDayDetailsFlexGridSizer->Add(TotalPrecipitationStaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    TotalSnowStaticText3 = new wxStaticText(this, ID_TOTALSNOWSTATICTEXT3, _("Total snow: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOTALSNOWSTATICTEXT3"));
    ThirdDayDetailsFlexGridSizer->Add(TotalSnowStaticText3, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    ThirdDayFlexGridSizer->Add(ThirdDayDetailsFlexGridSizer, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastFlexGridSizer->Add(ThirdDayFlexGridSizer, 1, wxALL|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastStaticBoxSizer->Add(WeatherForecastFlexGridSizer, 1, wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    MainFlexGridSizer->Add(WeatherForecastStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(MainFlexGridSizer);
    MainMenuBar = new wxMenuBar();
    FileMenu = new wxMenu();
    CheckMenuItem = new wxMenuItem(FileMenu, idMenuCheck, _("&Check\tEnter"), _("Checks the weather in the city provided."), wxITEM_NORMAL);
    FileMenu->Append(CheckMenuItem);
    SaveMenuItem = new wxMenu();
    AsFileMenuItem = new wxMenuItem(SaveMenuItem, idMenuAsFile, _("As &file...\tCtrl+S"), _("Saves the weather details to a specified file."), wxITEM_NORMAL);
    SaveMenuItem->Append(AsFileMenuItem);
    AsFileMenuItem->Enable(false);
    ToClipboardMenuItem = new wxMenuItem(SaveMenuItem, idMenuToClipboard, _("To &Clipboard\tCtrl+Alt+C"), _("Copies the weather details to the system clipboard."), wxITEM_NORMAL);
    SaveMenuItem->Append(ToClipboardMenuItem);
    ToClipboardMenuItem->Enable(false);
    FileMenu->Append(idMenuSave, _("&Save"), SaveMenuItem, wxEmptyString);
    FileMenu->AppendSeparator();
    QuitMenuItem = new wxMenuItem(FileMenu, idMenuQuit, _("E&xit\tAlt+F4"), _("Quits the application."), wxITEM_NORMAL);
    FileMenu->Append(QuitMenuItem);
    MainMenuBar->Append(FileMenu, _("&File"));
    OptionsMenu = new wxMenu();
    MeasuringUnitsMenuItem = new wxMenu();
    ImperialMenuItem = new wxMenuItem(MeasuringUnitsMenuItem, idMenuImperial, _("&Imperial"), _("Sets the temperature unit to Fahrenheit along with distance (mi), pressure (in) and wind speed (mph)."), wxITEM_RADIO);
    MeasuringUnitsMenuItem->Append(ImperialMenuItem);
    MetricMenuItem = new wxMenuItem(MeasuringUnitsMenuItem, idMenuMetric, _("&Metric"), _("Sets the temperature unit to Celsius along with distance (km), pressure (mb) and wind speed (kph)."), wxITEM_RADIO);
    MeasuringUnitsMenuItem->Append(MetricMenuItem);
    OptionsMenu->Append(idMenuMeasuringUnits, _("Measuring &units"), MeasuringUnitsMenuItem, wxEmptyString);
    TimeFormatMenuItem = new wxMenu();
    TwelveHourClockMenuItem = new wxMenuItem(TimeFormatMenuItem, idMenu12HourClock, _("&12-hour clock"), _("Sets the time format to 12-hour (AM/PM)."), wxITEM_RADIO);
    TimeFormatMenuItem->Append(TwelveHourClockMenuItem);
    TwentyFourHourMenuItem = new wxMenuItem(TimeFormatMenuItem, idMenu24HourClock, _("&24-hour clock"), _("Sets the time format to 24-hour."), wxITEM_RADIO);
    TimeFormatMenuItem->Append(TwentyFourHourMenuItem);
    OptionsMenu->Append(idMenuTimeFormat, _("&Time format"), TimeFormatMenuItem, wxEmptyString);
    DateFormatMenuItem = new wxMenu();
    DateFormat1MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearHyphenMonthHyphenDay, _("YYYY-MM-DD"), _("Sets the date format to YYYY-MM-DD."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat1MenuItem);
    DateFormat2MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuDayHyphenMonthHyphenYear, _("DD-MM-YYYY"), _("Sets the date format to DD-MM-YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat2MenuItem);
    DateFormat3MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearHyphenDayHyphenMonth, _("YYYY-DD-MM"), _("Sets the date format to YYYY-DD-MM."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat3MenuItem);
    DateFormat4MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuMonthHyphenDayHyphenYear, _("MM-DD-YYYY"), _("Sets the date format to MM-DD-YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat4MenuItem);
    DateFormat5MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearDotMonthDotDay, _("YYYY.MM.DD"), _("Sets the date format to YYYY.MM.DD."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat5MenuItem);
    DateFormat6MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuDayDotMonthDotYear, _("DD.MM.YYYY"), _("Sets the date format to DD.MM.YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat6MenuItem);
    DateFormat7MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearDotDayDotMonth, _("YYYY.DD.MM"), _("Sets the date format to YYYY.DD.MM."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat7MenuItem);
    DateFormat8MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuMonthDotDayDotYear, _("MM.DD.YYYY"), _("Sets the date format to MM.DD.YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat8MenuItem);
    DateFormat9MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearSlashMonthSlashDay, _("YYYY/MM/DD"), _("Sets the date format to YYYY/MM/DD."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat9MenuItem);
    DateFormat10MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuDaySlashMonthSlashYear, _("DD/MM/YYYY"), _("Sets the date format to DD/MM/YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat10MenuItem);
    DateFormat11MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuYearSlashDaySlashMonth, _("YYYY/DD/MM"), _("Sets the date format to YYYY/DD/MM."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat11MenuItem);
    DateFormat12MenuItem = new wxMenuItem(DateFormatMenuItem, idMenuMonthSlashDaySlashYear, _("MM/DD/YYYY"), _("Sets the date format to MM/DD/YYYY."), wxITEM_RADIO);
    DateFormatMenuItem->Append(DateFormat12MenuItem);
    OptionsMenu->Append(idMenuDateFormat, _("&Date format"), DateFormatMenuItem, wxEmptyString);
    TargetFileEncodingMenuItem = new wxMenu();
    ANSIMenuItem = new wxMenuItem(TargetFileEncodingMenuItem, idMenuANSI, _("&ANSI"), _("Sets plain text details format to ANSI."), wxITEM_RADIO);
    TargetFileEncodingMenuItem->Append(ANSIMenuItem);
    UTF8MenuItem = new wxMenuItem(TargetFileEncodingMenuItem, idMenuUTF8, _("&UTF-8"), _("Sets plain text details format to Unicode (UTF-8)."), wxITEM_RADIO);
    TargetFileEncodingMenuItem->Append(UTF8MenuItem);
    OptionsMenu->Append(idMenuTargetFileEncoding, _("Target file &encoding"), TargetFileEncodingMenuItem, wxEmptyString);
    ChangeLanguageMenuItem = new wxMenuItem(OptionsMenu, idMenuChangeLanguage, _("&Change language"), _("Changes the user interface language."), wxITEM_NORMAL);
    OptionsMenu->Append(ChangeLanguageMenuItem);
    OptionsMenu->AppendSeparator();
    SaveSettingsMenuItem = new wxMenuItem(OptionsMenu, idMenuSaveSettings, _("&Save settings"), _("Saves current settings to the configuration file."), wxITEM_NORMAL);
    OptionsMenu->Append(SaveSettingsMenuItem);
    MainMenuBar->Append(OptionsMenu, _("&Options"));
    HelpMenu = new wxMenu();
    AboutMenuItem = new wxMenuItem(HelpMenu, idMenuAbout, _("&About...\tF1"), _("Shows info about this application."), wxITEM_NORMAL);
    HelpMenu->Append(AboutMenuItem);
    MainMenuBar->Append(HelpMenu, _("&Help"));
    SetMenuBar(MainMenuBar);
    MainStatusBar = new wxStatusBar(this, ID_MAINSTATUSBAR, 0, _T("ID_MAINSTATUSBAR"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    MainStatusBar->SetFieldsCount(1,__wxStatusBarWidths_1);
    MainStatusBar->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(MainStatusBar);
    MainFlexGridSizer->Fit(this);
    MainFlexGridSizer->SetSizeHints(this);
    Center();

    Connect(idMenuQuit,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Weather95_20Frame::OnQuit);
    Connect(idMenuAbout,wxEVT_COMMAND_MENU_SELECTED,(wxObjectEventFunction)&Weather95_20Frame::OnAbout);
    Connect(wxEVT_KEY_DOWN,(wxObjectEventFunction)&Weather95_20Frame::OnKeyUpAndDown);
    Connect(wxEVT_KEY_UP,(wxObjectEventFunction)&Weather95_20Frame::OnKeyUpAndDown);
    Connect(wxEVT_SET_FOCUS,(wxObjectEventFunction)&Weather95_20Frame::OnSetAndKillFocus);
    Connect(wxEVT_KILL_FOCUS,(wxObjectEventFunction)&Weather95_20Frame::OnSetAndKillFocus);
    Connect(wxEVT_MOTION,(wxObjectEventFunction)&Weather95_20Frame::OnMouseMove);
    //*)

    SetIcon(wxIcon(wxT(ICON_NAME)));

    LocationTextCtrl->Connect(wxEVT_KEY_UP, (wxObjectEventFunction)&Weather95_20Frame::OnKeyUpAndDown, NULL, this);
    LocationTextCtrl->Connect(wxEVT_SET_FOCUS, (wxObjectEventFunction)&Weather95_20Frame::OnSetAndKillFocus, NULL, this);
    LocationTextCtrl->Connect(wxEVT_KILL_FOCUS, (wxObjectEventFunction)&Weather95_20Frame::OnSetAndKillFocus, NULL, this);
    MainStatusBar->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Weather95_20Frame::OnLeftDown, NULL, this);

    fileMenu = FileMenu;

    if(wxGetApp().userTemperatureUnit == wxT('c'))
        MetricMenuItem->Check(true);

    if(wxGetApp().user24HourTimeFormat)
        TwentyFourHourMenuItem->Check(true);

    switch(wxGetApp().userDateFormatVariant)
    {
        case 1:
            DateFormat1MenuItem->Check(true);
            break;
        case 2:
            DateFormat2MenuItem->Check(true);
            break;
        case 3:
            DateFormat3MenuItem->Check(true);
            break;
        case 4:
            DateFormat4MenuItem->Check(true);
            break;
        case 5:
            DateFormat5MenuItem->Check(true);
            break;
        case 6:
            DateFormat6MenuItem->Check(true);
            break;
        case 7:
            DateFormat7MenuItem->Check(true);
            break;
        case 8:
            DateFormat8MenuItem->Check(true);
            break;
        case 9:
            DateFormat9MenuItem->Check(true);
            break;
        case 10:
            DateFormat10MenuItem->Check(true);
            break;
        case 11:
            DateFormat11MenuItem->Check(true);
            break;
        case 12:
            DateFormat12MenuItem->Check(true);
            break;
    }

    if(wxGetApp().userUseUTF8)
        UTF8MenuItem->Check(true);

    if(!wxGetApp().DoesLangsFolderExist())
        ChangeLanguageMenuItem->Enable(false);

    wxMemoryInputStream mInput(apiServiceLogo, API_SERVICE_LOGO_SIZE);
    wxImage apiServiceLogoImage(mInput, wxBITMAP_TYPE_PNG);
    wxPanel *drawPanel = new wxImagePanel(LogoPanel, apiServiceLogoImage);
    drawPanel->SetSize(107, 50);
    drawPanel->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Weather95_20Frame::OnLogoPanelLeftDown, NULL, this);
    drawPanel->SetCursor(wxCURSOR_HAND);
}

Weather95_20Frame::~Weather95_20Frame()
{
    //(*Destroy(Weather95_20Frame)
    //*)
}

void Weather95_20Frame::ProcessResultFromWeatherForecastRequestThread(wxJSONValue jsonRoot)
{
    if(weatherForecastRequestThread)
    {
        weatherForecastRequestThread->mainFrame = NULL;
    }

    if (jsonRoot[wxT("location")].AsString() != wxT("null"))
    {
        ParseLocationDetails(jsonRoot);
        ConvertLastUpdatedDate();
        DetermineMeasuringUnits();
        ParseCurrentConditions(jsonRoot);
        EnsureTimeFormatForSunriseAndSunset();
        ParseWeatherForecast(jsonRoot);
        UpdateFrameWithReceivedData();
        EnableSave();
    }
    else if (jsonRoot[wxT("error")].AsString() != wxT("null"))
    {
        wxString apiServiceError = wxGetTranslation(jsonRoot[wxT("error")][wxT("message")].AsString());
        wxMessageBox(wxString::Format(_("WeatherAPI.com service error. Reason: %s"), apiServiceError.c_str()) , _("Error"), wxICON_HAND);
    }
    else
    {
        wxMessageBox(_("Unknown error."), _("Error"), wxICON_HAND);
    }

    EnableCheckAndResetCursor();
}

void Weather95_20Frame::ShowErrorMessageFromWeatherForecastRequestThread(wxString errorMessage)
{
    if(weatherForecastRequestThread)
    {
        weatherForecastRequestThread->mainFrame = NULL;
    }

    if (!errorMessage.IsEmpty())
    {
        wxMessageBox(errorMessage, _("Error"), wxICON_HAND);
    }

    EnableCheckAndResetCursor();
}

void Weather95_20Frame::OnQuit(wxCommandEvent& event)
{
    Close();
}

void Weather95_20Frame::OnAbout(wxCommandEvent& event)
{
    wxString currentLanguageName = wxLocale::GetLanguageName(wxGetApp().languageID);
    if(currentLanguageName.Contains(wxT(DEFAULT_LANGUAGE_FORMAL_NAME)))
        currentLanguageName = wxT(DEFAULT_LANGUAGE_FORMAL_NAME);
    currentLanguageName = wxGetTranslation(currentLanguageName);

    wxAboutDialogInfo info;
    info.SetIcon(wxIcon(wxT(ICON_NAME)));
    info.SetName(_("Weather 95+20"));
    info.SetVersion(wxT("2.0"));
    info.SetCopyright(wxT("Copyright (C) PeCeT_full 2015-2026 <me@pecetfull.pl>"));
    info.SetDescription(_("A weather forecast program for both vintage and modern PCs. Powered by WeatherAPI.com.\n\nBuild info: ") + wxBuildInfo(long_f) + _(".\nBuild date: ") +  __TDATE__ + wxT(", ") __TTIME__ + _(".\n\nCurrent language: ") + currentLanguageName + '.');
    info.SetWebSite(_("http://www.pecetfull.pl"));
    info.SetLicence(_("This program is published under The MIT License. For more information, please refer to the Licence.txt file included with the application.\n\nThis program also includes libraries that are necessary to launch the software. The licensing information regarding those are located in the Licences directory."));

    wxAboutBox(info);
}

wxString ReturnDateOfSpecifiedFormat(short day, short month, short year)
{
    if(wxGetApp().userDateFormatVariant == 1)
        return wxString::Format(wxT("%i-%02d-%02d"), year, month, day);
    else if(wxGetApp().userDateFormatVariant == 2)
        return wxString::Format(wxT("%02d-%02d-%i"), day, month, year);
    else if(wxGetApp().userDateFormatVariant == 3)
        return wxString::Format(wxT("%i-%02d-%02d"), year, day, month);
    else if(wxGetApp().userDateFormatVariant == 4)
        return wxString::Format(wxT("%02d-%02d-%i"), month, day, year);
    else if(wxGetApp().userDateFormatVariant == 5)
        return wxString::Format(wxT("%i.%02d.%02d"), year, month, day);
    else if(wxGetApp().userDateFormatVariant == 6)
        return wxString::Format(wxT("%02d.%02d.%i"), day, month, year);
    else if(wxGetApp().userDateFormatVariant == 7)
        return wxString::Format(wxT("%i.%02d.%02d"), year, day, month);
    else if(wxGetApp().userDateFormatVariant == 8)
        return wxString::Format(wxT("%02d.%02d.%i"), month, day, year);
    else if(wxGetApp().userDateFormatVariant == 9)
        return wxString::Format(wxT("%i/%02d/%02d"), year, month, day);
    else if(wxGetApp().userDateFormatVariant == 10)
        return wxString::Format(wxT("%02d/%02d/%i"), day, month, year);
    else if(wxGetApp().userDateFormatVariant == 11)
        return wxString::Format(wxT("%i/%02d/%02d"), year, day, month);
    else if(wxGetApp().userDateFormatVariant == 12)
        return wxString::Format(wxT("%02d/%02d/%i"), month, day, year);
    else
        return _("Unknown date format");
}

void ConvertTo24HourClock(wxString& source12HourClock)
{
    int colonSignPlacement = source12HourClock.Find(wxT(':'));
    short minutes = wxAtoi(source12HourClock.SubString(colonSignPlacement + 1, source12HourClock.Length()));
    short hours = wxAtoi(source12HourClock.SubString(0, colonSignPlacement - 1));
    if(source12HourClock.Lower().Contains(wxT("am")))
    {
        if(hours == 12)
            hours = 0;
    }
    else if(source12HourClock.Lower().Contains(wxT("pm")))
    {
        if(hours != 12)
            hours += 12;
    }
    source12HourClock = wxString::Format(wxT("%02d:%02d"), hours, minutes);
}

void Weather95_20Frame::OnCheck(wxCommandEvent& event)
{
    if(LocationTextCtrl->IsEmpty())
    {
        wxMessageBox(_("You need to enter the desired location in order to proceed."), _("Warning"), wxICON_EXCLAMATION);
        return;
    }

    DisableCheckAndSetWaitCursor();

    weatherForecastRequestThread = new WeatherForecastRequestThread(LocationTextCtrl->GetValue());
    weatherForecastRequestThread->mainFrame = this;

    weatherForecastRequestThread->Create();
    weatherForecastRequestThread->Run();
}

void Weather95_20Frame::OnSaveAsFile(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, _("Save as file..."), wxT(""), wxT(""), _("Text documents (*.txt)|*.txt|All files (*.*)|*.*"), wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if(saveFileDialog.ShowModal() == wxID_OK)
    {
        wxString currentWeatherDetails = PrintWeatherDetails();
        wxString fileDestinationPath = saveFileDialog.GetPath();
        if(wxGetApp().userUseUTF8)
        {
            wxStringInputStream sInput(currentWeatherDetails);
            wxFileOutputStream file(fileDestinationPath);
            file.Write(sInput);
            file.Close();
        }
        else
        {
            wxFileOutputStream file(fileDestinationPath);
            wxTextOutputStream tInput(file, wxEOL_NATIVE, wxConvLibc);
            tInput << currentWeatherDetails;
            file.Close();
            if(wxFileName::GetSize(fileDestinationPath) == 0)
            {
                wxRemoveFile(fileDestinationPath);
                wxMessageBox(_("The file has not been successfully written because diacritics of the currently used language in this program are not compatible with the encoding of the system language. Change the language to another one (the safest one is English) or set target encoding to UTF-8."), _("Error"), wxICON_HAND);
            }
        }
    }
}

void Weather95_20Frame::OnSaveToClipboard(wxCommandEvent& event)
{
    if (systemClipboard->Open())
    {
        wxString currentWeatherDetails = PrintWeatherDetails();
        systemClipboard->SetData(new wxTextDataObject(currentWeatherDetails));
        systemClipboard->Close();
    }
}

void Weather95_20Frame::OnImperial(wxCommandEvent& event)
{
    wxGetApp().userTemperatureUnit = wxT('f');
}

void Weather95_20Frame::OnMetric(wxCommandEvent& event)
{
    wxGetApp().userTemperatureUnit = wxT('c');
}

void Weather95_20Frame::OnANSI(wxCommandEvent& event)
{
    wxGetApp().userUseUTF8 = false;
}

void Weather95_20Frame::OnUTF8(wxCommandEvent& event)
{
    wxGetApp().userUseUTF8 = true;
}

void Weather95_20Frame::On12HourClock(wxCommandEvent& event)
{
    wxGetApp().user24HourTimeFormat = false;
}

void Weather95_20Frame::On24HourClock(wxCommandEvent& event)
{
    wxGetApp().user24HourTimeFormat = true;
}

void Weather95_20Frame::OnYearHyphenMonthHyphenDay(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 1;
}

void Weather95_20Frame::OnDayHyphenMonthHyphenYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 2;
}

void Weather95_20Frame::OnYearHyphenDayHyphenMonth(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 3;
}

void Weather95_20Frame::OnMonthHyphenDayHyphenYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 4;
}

void Weather95_20Frame::OnYearDotMonthDotDay(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 5;
}

void Weather95_20Frame::OnDayDotMonthDotYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 6;
}

void Weather95_20Frame::OnYearDotDayDotMonth(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 7;
}

void Weather95_20Frame::OnMonthDotDayDotYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 8;
}

void Weather95_20Frame::OnYearSlashMonthSlashDay(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 9;
}

void Weather95_20Frame::OnDaySlashMonthSlashYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 10;
}

void Weather95_20Frame::OnYearSlashDaySlashMonth(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 11;
}

void Weather95_20Frame::OnMonthSlashDaySlashYear(wxCommandEvent& event)
{
    wxGetApp().userDateFormatVariant = 12;
}

void Weather95_20Frame::OnSaveSettings(wxCommandEvent& event)
{
    ConfigFile *configFile = new ConfigFile();
    configFile->SaveConfiguration(wxGetApp().languageID, wxGetApp().userTemperatureUnit, wxGetApp().user24HourTimeFormat, wxGetApp().userDateFormatVariant, wxGetApp().userUseUTF8);
    wxDELETE(configFile);
}

void Weather95_20Frame::OnChangeLanguage(wxCommandEvent& event)
{
    short selectedLanguageID = wxGetApp().SelectLanguage();
    if(selectedLanguageID != wxLANGUAGE_UNKNOWN && selectedLanguageID != wxGetApp().languageID)
    {
        wxGetApp().languageID = selectedLanguageID;
        wxMessageBox(_("Another language has just been selected. To reflect all the changes, please save current settings and then restart the application."), _("Message"));
    }
}

void Weather95_20Frame::OnKeyUpAndDown(wxKeyEvent& event)
{
    MainStatusBar->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnSetAndKillFocus(wxFocusEvent& event)
{
    MainStatusBar->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnMouseMove(wxMouseEvent& event)
{
    MainStatusBar->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnLeftDown(wxMouseEvent& event)
{
    wxMessageBox(locationStatus, _("Location status"));
}

void Weather95_20Frame::OnLogoPanelLeftDown(wxMouseEvent& event)
{
    wxLaunchDefaultBrowser(wxT("https://www.weatherapi.com/"));
}

void Weather95_20Frame::ConvertLastUpdatedDate()
{
    wxString currentLastUpdatedWithoutTime = lastUpdated.SubString(0, lastUpdated.Find(wxT(' ')) - 1);
    int firstHyphen = currentLastUpdatedWithoutTime.Find(wxT('-'));
    int secondHyphen = currentLastUpdatedWithoutTime.SubString(firstHyphen + 1, currentLastUpdatedWithoutTime.Length()).Find(wxT('-')) + firstHyphen + 1;
    short yearNumber = wxAtoi(currentLastUpdatedWithoutTime.SubString(0, firstHyphen - 1));
    short monthNumber = wxAtoi(currentLastUpdatedWithoutTime.SubString(firstHyphen + 1, secondHyphen - 1));
    short dayNumber = wxAtoi(currentLastUpdatedWithoutTime.SubString(secondHyphen + 1, currentLastUpdatedWithoutTime.Length()));
    lastUpdated.Replace(currentLastUpdatedWithoutTime, ReturnDateOfSpecifiedFormat(dayNumber, monthNumber, yearNumber));
}

void Weather95_20Frame::DetermineMeasuringUnits()
{
    temperatureUnit = wxGetApp().userTemperatureUnit;
    if (temperatureUnit == wxT("f"))
    {
        speedUnit = wxT("mph");
        pressureUnit = wxT("in");
        precipitationUnit = wxT("in");
        distanceUnit = wxT("miles");
    }
    else
    {
        speedUnit = wxT("kph");
        pressureUnit = wxT("mb");
        precipitationUnit = wxT("mm");
        distanceUnit = wxT("km");
    }
}

void Weather95_20Frame::DisableCheckAndSetWaitCursor()
{
    CheckMenuItem->Enable(false);
    LocationTextCtrl->Enable(false);
    this->SetCursor(wxCURSOR_ARROWWAIT);
}

void Weather95_20Frame::EnableCheckAndResetCursor()
{
    CheckMenuItem->Enable(true);
    LocationTextCtrl->Enable(true);
    this->SetCursor(wxNullCursor);
    FocusOnDummyPanelAndClose();
    LocationTextCtrl->SetFocus();
}

void Weather95_20Frame::EnableSave()
{
    fileMenu->Enable(idMenuAsFile, true);
    fileMenu->Enable(idMenuToClipboard, true);
}

void Weather95_20Frame::EnsureTimeFormatForSunriseAndSunset()
{
    if(wxGetApp().user24HourTimeFormat)
    {
        ConvertTo24HourClock(sunrise);
        ConvertTo24HourClock(sunset);
    }
}

void Weather95_20Frame::FocusOnDummyPanelAndClose()
{
    wxPanel* dummyPanel = new wxPanel(this, wxID_ANY);
    dummyPanel->SetFocus();
    dummyPanel->Close();
}

void Weather95_20Frame::ParseCurrentConditions(wxJSONValue& jsonRoot)
{
    currentTemperature = jsonRoot[wxT("current")][wxT("temp_") + temperatureUnit].AsString() + wxT(" °") + temperatureUnit.Upper();
    currentCondition = jsonRoot[wxT("current")][wxT("condition")][wxT("text")].AsString();
    windDirection = jsonRoot[wxT("current")][wxT("wind_dir")].AsString();
    windSpeed = jsonRoot[wxT("current")][wxT("wind_") + speedUnit].AsString() + ' ' + wxGetTranslation(speedUnit);
    windGust = jsonRoot[wxT("current")][wxT("gust_") + speedUnit].AsString() + ' ' + wxGetTranslation(speedUnit);
    pressure = jsonRoot[wxT("current")][wxT("pressure_") + pressureUnit].AsString() + ' ' + wxGetTranslation(pressureUnit);
    precipitation = jsonRoot[wxT("current")][wxT("precip_") + precipitationUnit].AsString() + ' ' + wxGetTranslation(precipitationUnit);
    humidity = jsonRoot[wxT("current")][wxT("humidity")].AsString() + '%';
    cloudCover = jsonRoot[wxT("current")][wxT("cloud")].AsString() + '%';
    visibility = jsonRoot[wxT("current")][wxT("vis_") + distanceUnit].AsString() + ' ' + wxGetTranslation(distanceUnit);
    sunrise = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("astro")][wxT("sunrise")].AsString();
    sunset = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("astro")][wxT("sunset")].AsString();
    moonPhase = wxGetTranslation(jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("astro")][wxT("moon_phase")].AsString());
    feelsLike = jsonRoot[wxT("current")][wxT("feelslike_") + temperatureUnit].AsString() + wxT(" °") + temperatureUnit.Upper();
    windChill = jsonRoot[wxT("current")][wxT("windchill_") + temperatureUnit].AsString() + wxT(" °") + temperatureUnit.Upper();
    heatIndex = jsonRoot[wxT("current")][wxT("heatindex_") + temperatureUnit].AsString() + wxT(" °") + temperatureUnit.Upper();
    dewPoint = jsonRoot[wxT("current")][wxT("dewpoint_") + temperatureUnit].AsString() + wxT(" °") + temperatureUnit.Upper();
    uvIndex = jsonRoot[wxT("current")][wxT("uv")].AsString();
}

void Weather95_20Frame::ParseLocationDetails(wxJSONValue& jsonRoot)
{
    city = jsonRoot[wxT("location")][wxT("name")].AsString();
    country = jsonRoot[wxT("location")][wxT("country")].AsString();
    region = jsonRoot[wxT("location")][wxT("region")].AsString();
    if(country != wxT("") && country != city)
    country = wxGetTranslation(country);
    location = city + wxT(", ") + country;
    latitude = jsonRoot[wxT("location")][wxT("lat")].AsString();
    longitude = jsonRoot[wxT("location")][wxT("lon")].AsString();
    long lastUpdatedEpoch = jsonRoot[wxT("current")][wxT("last_updated_epoch")].AsLong();
    wxDateTime dtLastUpdated = wxDateTime(lastUpdatedEpoch);
    lastUpdated = dtLastUpdated.Format(wxGetApp().user24HourTimeFormat ? wxT("%Y-%m-%d %H:%M") : wxT("%Y-%m-%d %I:%M %p"));
}

void Weather95_20Frame::ParseWeatherForecast(wxJSONValue& jsonRoot)
{
    long todayDateEpoch = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("date_epoch")].AsLong();
    wxDateTime dtTodayDate = wxDateTime(todayDateEpoch);
    todayWeekDay = wxGetTranslation(dtTodayDate.GetWeekDayName(dtTodayDate.GetWeekDay()));
    float todayTempMinFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("mintemp_") + temperatureUnit].AsDouble();
    todayTempMinFloat = std::floor(todayTempMinFloat);
    todayTempMin = wxString::Format(wxT("%.0f"), todayTempMinFloat) + wxT(" °") + temperatureUnit.Upper();
    float todayTempMaxFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("maxtemp_") + temperatureUnit].AsDouble();
    todayTempMaxFloat = std::ceil(todayTempMaxFloat);
    todayTempMax = wxString::Format(wxT("%.0f"), todayTempMaxFloat) + wxT(" °") + temperatureUnit.Upper();
    todayCondition = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("condition")][wxT("text")].AsString();
    todayMaxWind = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("maxwind_") + speedUnit].AsString() + ' ' + wxGetTranslation(speedUnit);
    todayChanceOfRain = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("daily_chance_of_rain")].AsString() + '%';
    todayChanceOfSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("daily_chance_of_snow")].AsString() + '%';
    todayTotalPrecipitation = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("totalprecip_") + precipitationUnit].AsString() + ' ' + wxGetTranslation(precipitationUnit);
    todayTotalSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][0][wxT("day")][wxT("totalsnow_cm")].AsString() + wxT(" cm");

    long tomorrowDateEpoch = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("date_epoch")].AsLong();
    wxDateTime dtTomorrowDate = wxDateTime(tomorrowDateEpoch);
    tomorrowWeekDay = wxGetTranslation(dtTomorrowDate.GetWeekDayName(dtTomorrowDate.GetWeekDay()));
    float tomorrowTempMinFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("mintemp_") + temperatureUnit].AsDouble();
    tomorrowTempMinFloat = std::floor(tomorrowTempMinFloat);
    tomorrowTempMin = wxString::Format(wxT("%.0f"), tomorrowTempMinFloat) + wxT(" °") + temperatureUnit.Upper();
    float tomorrowTempMaxFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("maxtemp_") + temperatureUnit].AsDouble();
    tomorrowTempMaxFloat = std::ceil(tomorrowTempMaxFloat);
    tomorrowTempMax = wxString::Format(wxT("%.0f"), tomorrowTempMaxFloat) + wxT(" °") + temperatureUnit.Upper();
    tomorrowCondition = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("condition")][wxT("text")].AsString();
    tomorrowMaxWind = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("maxwind_") + speedUnit].AsString() + ' ' + wxGetTranslation(speedUnit);
    tomorrowChanceOfRain = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("daily_chance_of_rain")].AsString() + '%';
    tomorrowChanceOfSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("daily_chance_of_snow")].AsString() + '%';
    tomorrowTotalPrecipitation = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("totalprecip_") + precipitationUnit].AsString() + ' ' + wxGetTranslation(precipitationUnit);
    tomorrowTotalSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][1][wxT("day")][wxT("totalsnow_cm")].AsString() + wxT(" cm");

    long thirdDayDateEpoch = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("date_epoch")].AsLong();
    wxDateTime dtThirdDayDate = wxDateTime(thirdDayDateEpoch);
    thirdDayWeekDay = wxGetTranslation(dtThirdDayDate.GetWeekDayName(dtThirdDayDate.GetWeekDay()));
    float thirdDayTempMinFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("mintemp_") + temperatureUnit].AsDouble();
    thirdDayTempMinFloat = std::floor(thirdDayTempMinFloat);
    thirdDayTempMin = wxString::Format(wxT("%.0f"), thirdDayTempMinFloat) + wxT(" °") + temperatureUnit.Upper();
    float thirdDayTempMaxFloat = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("maxtemp_") + temperatureUnit].AsDouble();
    thirdDayTempMaxFloat = std::ceil(thirdDayTempMaxFloat);
    thirdDayTempMax = wxString::Format(wxT("%.0f"), thirdDayTempMaxFloat) + wxT(" °") + temperatureUnit.Upper();
    thirdDayCondition = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("condition")][wxT("text")].AsString();
    thirdDayMaxWind = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("maxwind_") + speedUnit].AsString() + ' ' + wxGetTranslation(speedUnit);
    thirdDayChanceOfRain = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("daily_chance_of_rain")].AsString() + '%';
    thirdDayChanceOfSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("daily_chance_of_snow")].AsString() + '%';
    thirdDayTotalPrecipitation = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("totalprecip_") + precipitationUnit].AsString() + ' ' + wxGetTranslation(precipitationUnit);
    thirdDayTotalSnow = jsonRoot[wxT("forecast")][wxT("forecastday")][2][wxT("day")][wxT("totalsnow_cm")].AsString() + wxT(" cm");

    locationStatus = _("Data for: ") + location + wxT(" (") + latitude + ' ' + longitude + _("). Last updated: ") + lastUpdated + '.';
}

wxString Weather95_20Frame::PrintWeatherDetails()
{
    wxString weatherDetails = wxString::Format(wxT("**** Weather 95+20 – %s ****\r\n"), _("WEATHER DETAILS"));
    weatherDetails += wxString::Format(wxT("**** %s ****\r\n"), _("Powered by WeatherAPI.com"));
    weatherDetails += wxString::Format(wxT("\r\n%s %s\r\n"), _("As of:"), lastUpdated.c_str());
    weatherDetails += wxString::Format(wxT("\r\n** %s **\r\n\r\n"), _("LOCATION"));
    if(!country.IsEmpty())
        weatherDetails += wxString::Format(_("City: %s"), city.c_str());
    if(!region.IsEmpty())
    {
        weatherDetails += wxT("\r\n");
        weatherDetails += wxString::Format(_("Region: %s"), region.c_str());
    }
    if(!country.IsEmpty())
    {
        weatherDetails += wxT("\r\n");
        weatherDetails += wxString::Format(_("Country: %s"), country.c_str());
    }
    else
        weatherDetails += wxString::Format(_("Place: %s"), city.c_str());
    weatherDetails += wxT("\r\n\r\n");
    weatherDetails += wxString::Format(_("Latitude: %s"), latitude.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Longitude: %s"), longitude.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n** %s **\r\n"), _("CURRENT CONDITIONS"));
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), TemperatureStaticText->GetLabel().Upper().c_str());
    weatherDetails += currentTemperature + wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), _("CONDITION"));
    weatherDetails += currentCondition + wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), WindStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Direction: %s"), windDirection.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Speed: %s"), windSpeed.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Gust: %s"), windGust.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), AtmosphereStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Pressure: %s"), pressure.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Precipitation: %s"), precipitation.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Humidity: %s"), humidity.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Cloud cover: %s"), cloudCover.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Visibility: %s"), visibility.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), AstronomyStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Sunrise: %s"), sunrise.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Sunset: %s"), sunset.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Moon phase: %s"), moonPhase.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), IndexStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Feels like: %s"), feelsLike.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Wind chill: %s"), windChill.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Heat index: %s"), heatIndex.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Dew point: %s"), dewPoint.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("UV index: %s"), uvIndex.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n** %s **\r\n"), _("WEATHER FORECAST"));
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), TodayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), todayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), todayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), todayCondition.c_str());
    weatherDetails += wxT("\r\n\r\n");
    weatherDetails += wxString::Format(_("Maximum wind: %s"), todayMaxWind.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of rain: %s"), todayChanceOfRain.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of snow: %s"), todayChanceOfSnow.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total precipitation: %s"), todayTotalPrecipitation.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total snow: %s"), todayTotalSnow.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), TomorrowStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), tomorrowTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), tomorrowTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), tomorrowCondition.c_str());
    weatherDetails += wxT("\r\n\r\n");
    weatherDetails += wxString::Format(_("Maximum wind: %s"), tomorrowMaxWind.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of rain: %s"), tomorrowChanceOfRain.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of snow: %s"), tomorrowChanceOfSnow.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total precipitation: %s"), tomorrowTotalPrecipitation.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total snow: %s"), tomorrowTotalSnow.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), ThirdDayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), thirdDayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), thirdDayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), thirdDayCondition.c_str());
    weatherDetails += wxT("\r\n\r\n");
    weatherDetails += wxString::Format(_("Maximum wind: %s"), thirdDayMaxWind.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of rain: %s"), thirdDayChanceOfRain.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Chance of snow: %s"), thirdDayChanceOfSnow.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total precipitation: %s"), thirdDayTotalPrecipitation.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Total snow: %s"), thirdDayTotalSnow.c_str());
    weatherDetails += wxT("\r\n");

    return weatherDetails;
}

void Weather95_20Frame::UpdateFrameWithReceivedData()
{
    this->Freeze();

    CurrentTemperatureStaticText->SetLabel(currentTemperature);
    CurrentTemperatureStaticText->Fit();
    CurrentWeatherConditionStaticText->SetLabel(currentCondition);
    CurrentWeatherConditionStaticText->Fit();
    DirectionStaticText->SetLabel(wxString::Format(_("Direction: %s"), windDirection.c_str()));
    DirectionStaticText->Fit();
    SpeedStaticText->SetLabel(wxString::Format(_("Speed: %s"), windSpeed.c_str()));
    SpeedStaticText->Fit();
    GustStaticText->SetLabel(wxString::Format(_("Gust: %s"), windGust.c_str()));
    GustStaticText->Fit();
    PressureStaticText->SetLabel(wxString::Format(_("Pressure: %s"), pressure.c_str()));
    PressureStaticText->Fit();
    PrecipitationStaticText->SetLabel(wxString::Format(_("Precipitation: %s"), precipitation.c_str()));
    PrecipitationStaticText->Fit();
    HumidityStaticText->SetLabel(wxString::Format(_("Humidity: %s"), humidity.c_str()));
    HumidityStaticText->Fit();
    CloudCoverStaticText->SetLabel(wxString::Format(_("Cloud cover: %s"), cloudCover.c_str()));
    CloudCoverStaticText->Fit();
    VisibilityStaticText->SetLabel(wxString::Format(_("Visibility: %s"), visibility.c_str()));
    VisibilityStaticText->Fit();
    SunriseStaticText->SetLabel(wxString::Format(_("Sunrise: %s"), sunrise.c_str()));
    SunriseStaticText->Fit();
    SunsetStaticText->SetLabel(wxString::Format(_("Sunset: %s"), sunset.c_str()));
    SunsetStaticText->Fit();
    MoonPhaseStaticText->SetLabel(wxString::Format(_("Moon phase:\n%s"), moonPhase.c_str()));
    MoonPhaseStaticText->Fit();
    FeelsLikeStaticText->SetLabel(wxString::Format(_("Feels like: %s"), feelsLike.c_str()));
    FeelsLikeStaticText->Fit();
    WindChillStaticText->SetLabel(wxString::Format(_("Wind chill: %s"), windChill.c_str()));
    WindChillStaticText->Fit();
    HeatIndexStaticText->SetLabel(wxString::Format(_("Heat index: %s"), heatIndex.c_str()));
    HeatIndexStaticText->Fit();
    DewPointStaticText->SetLabel(wxString::Format(_("Dew point: %s"), dewPoint.c_str()));
    DewPointStaticText->Fit();
    UvIndexStaticText->SetLabel(wxString::Format(_("UV index: %s"), uvIndex.c_str()));
    UvIndexStaticText->Fit();

    TodayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("Today"), todayWeekDay.c_str()));
    TodayStaticText->Fit();
    TomorrowStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("Tomorrow"), tomorrowWeekDay.c_str()));
    TomorrowStaticText->Fit();
    ThirdDayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("3rd Day"), thirdDayWeekDay.c_str()));
    ThirdDayStaticText->Fit();

    CurrentMinTempStaticText1->SetLabel(todayTempMin);
    CurrentMinTempStaticText1->Fit();
    CurrentMaxTempStaticText1->SetLabel(todayTempMax);
    CurrentMaxTempStaticText1->Fit();
    WeatherConditionStaticText1->SetLabel(todayCondition);
    WeatherConditionStaticText1->Fit();
    MaxWindStaticText1->SetLabel(wxString::Format(_("Maximum wind: %s"), todayMaxWind.c_str()));
    MaxWindStaticText1->Fit();
    ChanceOfRainStaticText1->SetLabel(wxString::Format(_("Chance of rain: %s"), todayChanceOfRain.c_str()));
    ChanceOfRainStaticText1->Fit();
    ChanceOfSnowStaticText1->SetLabel(wxString::Format(_("Chance of snow: %s"), todayChanceOfSnow.c_str()));
    ChanceOfSnowStaticText1->Fit();
    TotalPrecipitationStaticText1->SetLabel(wxString::Format(_("Total precipitation: %s"), todayTotalPrecipitation.c_str()));
    TotalPrecipitationStaticText1->Fit();
    TotalSnowStaticText1->SetLabel(wxString::Format(_("Total snow: %s"), todayTotalSnow.c_str()));
    TotalSnowStaticText1->Fit();

    CurrentMinTempStaticText2->SetLabel(tomorrowTempMin);
    CurrentMinTempStaticText2->Fit();
    CurrentMaxTempStaticText2->SetLabel(tomorrowTempMax);
    CurrentMaxTempStaticText2->Fit();
    WeatherConditionStaticText2->SetLabel(tomorrowCondition);
    WeatherConditionStaticText2->Fit();
    MaxWindStaticText2->SetLabel(wxString::Format(_("Maximum wind: %s"), tomorrowMaxWind.c_str()));
    MaxWindStaticText2->Fit();
    ChanceOfRainStaticText2->SetLabel(wxString::Format(_("Chance of rain: %s"), tomorrowChanceOfRain.c_str()));
    ChanceOfRainStaticText2->Fit();
    ChanceOfSnowStaticText2->SetLabel(wxString::Format(_("Chance of snow: %s"), tomorrowChanceOfSnow.c_str()));
    ChanceOfSnowStaticText2->Fit();
    TotalPrecipitationStaticText2->SetLabel(wxString::Format(_("Total precipitation: %s"), tomorrowTotalPrecipitation.c_str()));
    TotalPrecipitationStaticText2->Fit();
    TotalSnowStaticText2->SetLabel(wxString::Format(_("Total snow: %s"), tomorrowTotalSnow.c_str()));
    TotalSnowStaticText2->Fit();

    CurrentMinTempStaticText3->SetLabel(thirdDayTempMin);
    CurrentMinTempStaticText3->Fit();
    CurrentMaxTempStaticText3->SetLabel(thirdDayTempMax);
    CurrentMaxTempStaticText3->Fit();
    WeatherConditionStaticText3->SetLabel(thirdDayCondition);
    WeatherConditionStaticText3->Fit();
    MaxWindStaticText3->SetLabel(wxString::Format(_("Maximum wind: %s"), thirdDayMaxWind.c_str()));
    MaxWindStaticText3->Fit();
    ChanceOfRainStaticText3->SetLabel(wxString::Format(_("Chance of rain: %s"), thirdDayChanceOfRain.c_str()));
    ChanceOfRainStaticText3->Fit();
    ChanceOfSnowStaticText3->SetLabel(wxString::Format(_("Chance of snow: %s"), thirdDayChanceOfSnow.c_str()));
    ChanceOfSnowStaticText3->Fit();
    TotalPrecipitationStaticText3->SetLabel(wxString::Format(_("Total precipitation: %s"), thirdDayTotalPrecipitation.c_str()));
    TotalPrecipitationStaticText3->Fit();
    TotalSnowStaticText3->SetLabel(wxString::Format(_("Total snow: %s"), thirdDayTotalSnow.c_str()));
    TotalSnowStaticText3->Fit();

    GetSizer()->Fit(this);
    wxSize windowSize = GetBestVirtualSize();
    int bestWidth = windowSize.GetWidth();
    int bestHeight = windowSize.GetHeight();
    SetSize(bestWidth - 1, bestHeight - 1);
    SetSize(bestWidth, bestHeight);

    this->Thaw();
}
