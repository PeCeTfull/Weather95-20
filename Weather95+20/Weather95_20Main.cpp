/***************************************************************
 * Name:      Weather95_20Main.cpp
 * Purpose:   Code for Application Frame
 * Author:    PeCeT_full (pecetfull@komputermania.pl.eu.org)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.komputermania.pl.eu.org/)
 * Licence:   The MIT License
 **************************************************************/

#include "Weather95_20Main.h"
#include "Weather95_20App.h"
#include "wxImagePanel.h"
#include "YahooLogo.h"
#include "include/curl/curl.h"
#include "include/wx/jsonreader.h"
#include <wx/msgdlg.h>
#include <wx/txtstrm.h>
#include <wx/url.h>
#include <wx/aboutdlg.h>
#include <wx/wfstream.h>
#include <wx/sstream.h>
#include <wx/filedlg.h>
#include <wx/hashmap.h>
#include <wx/mstream.h>
#include <wx/dir.h>
#include <wx/filename.h>

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
const long Weather95_20Frame::ID_CHILLSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_DIRECTIONSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SPEEDSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_ATMOSPHERESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_HUMIDITYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_VISIBILITYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_PRESSURESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_RISINGSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_ASTRONOMYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SUNRISESTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_SUNSETSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_TODAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_MAXTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_MINTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT1 = wxNewId();
const long Weather95_20Frame::ID_TOMORROWSTATICTEXT = wxNewId();
const long Weather95_20Frame::IID_MAXTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_MINTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT2 = wxNewId();
const long Weather95_20Frame::ID_THIRDDAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_MAXTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_MINTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT3 = wxNewId();
const long Weather95_20Frame::ID_FOURTHDAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_MAXTEMPSTATICTEXT4 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT4 = wxNewId();
const long Weather95_20Frame::ID_MINTEMPSTATICTEXT4 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT4 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT4 = wxNewId();
const long Weather95_20Frame::ID_FIFTHTHDAYSTATICTEXT = wxNewId();
const long Weather95_20Frame::ID_MAXTEMPSTATICTEXT5 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMAXTEMPSTATICTEXT5 = wxNewId();
const long Weather95_20Frame::ID_MINTEMPSTATICTEXT5 = wxNewId();
const long Weather95_20Frame::ID_CURRENTMINTEMPSTATICTEXT5 = wxNewId();
const long Weather95_20Frame::ID_WEATHERCONDITIONSTATICTEXT5 = wxNewId();
const long Weather95_20Frame::idMenuCheck = wxNewId();
const long Weather95_20Frame::idMenuAsFile = wxNewId();
const long Weather95_20Frame::idMenuToClipboard = wxNewId();
const long Weather95_20Frame::idMenuSave = wxNewId();
const long Weather95_20Frame::idMenuQuit = wxNewId();
const long Weather95_20Frame::idMenuCelsius = wxNewId();
const long Weather95_20Frame::idMenuFahrenheit = wxNewId();
const long Weather95_20Frame::idMenuTemperatureUnit = wxNewId();
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
const long Weather95_20Frame::ID_STATUSBAR1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(Weather95_20Frame,wxFrame)
EVT_MENU(idMenuCheck, Weather95_20Frame::OnCheck)
EVT_MENU(idMenuAsFile, Weather95_20Frame::OnSaveAsFile)
EVT_MENU(idMenuToClipboard, Weather95_20Frame::OnSaveToClipboard)
EVT_MENU(idMenuCelsius, Weather95_20Frame::OnCelsius)
EVT_MENU(idMenuFahrenheit, Weather95_20Frame::OnFahrenheit)
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

WX_DECLARE_HASH_MAP(int, wxString, wxIntegerHash, wxIntegerEqual, CodeMap);
CodeMap weatherConditions;

Weather95_20Frame::Weather95_20Frame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(Weather95_20Frame)
    wxFlexGridSizer* FlexGridSizer4;
    wxFlexGridSizer* FlexGridSizer16;
    wxFlexGridSizer* FlexGridSizer24;
    wxFlexGridSizer* FlexGridSizer19;
    wxFlexGridSizer* FlexGridSizer23;
    wxMenuItem* MenuItem2;
    wxFlexGridSizer* FlexGridSizer10;
    wxFlexGridSizer* FlexGridSizer3;
    wxMenuItem* MenuItem1;
    wxFlexGridSizer* FlexGridSizer5;
    wxFlexGridSizer* FlexGridSizer22;
    wxFlexGridSizer* FlexGridSizer9;
    wxFlexGridSizer* FlexGridSizer2;
    wxMenu* Menu1;
    wxFlexGridSizer* FlexGridSizer7;
    wxStaticBoxSizer* WeatherForecastStaticBoxSizer;
    wxFlexGridSizer* FlexGridSizer15;
    wxFlexGridSizer* FlexGridSizer18;
    wxFlexGridSizer* FlexGridSizer8;
    wxFlexGridSizer* FlexGridSizer21;
    wxFlexGridSizer* FlexGridSizer14;
    wxFlexGridSizer* FlexGridSizer20;
    wxFlexGridSizer* FlexGridSizer13;
    wxFlexGridSizer* FlexGridSizer12;
    wxMenuBar* MenuBar1;
    wxFlexGridSizer* FlexGridSizer6;
    wxFlexGridSizer* FlexGridSizer1;
    wxFlexGridSizer* FlexGridSizer11;
    wxFlexGridSizer* FlexGridSizer17;
    wxMenu* Menu2;
    wxStaticBoxSizer* CurrentConditionsStaticBoxSizer;

    Create(parent, wxID_ANY, _("Weather 95+20"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE|wxMINIMIZE_BOX, _T("wxID_ANY"));
    SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_BTNFACE));
    FlexGridSizer1 = new wxFlexGridSizer(4, 1, 0, 0);
    FlexGridSizer2 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer2->AddGrowableCol(1);
    LocationStaticText = new wxStaticText(this, ID_LOCATIONSTATICTEXT, _("Location:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_LOCATIONSTATICTEXT"));
    FlexGridSizer2->Add(LocationStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    LocationTextCtrl = new wxTextCtrl(this, ID_LOCATIONTEXTCTRL, wxEmptyString, wxDefaultPosition, wxSize(-1,-1), 0, wxDefaultValidator, _T("ID_LOCATIONTEXTCTRL"));
    FlexGridSizer2->Add(LocationTextCtrl, 1, wxALL|wxEXPAND|wxALIGN_RIGHT|wxALIGN_CENTER_VERTICAL, 5);
    LogoPanel = new wxPanel(this, ID_LOGOPANEL, wxDefaultPosition, wxSize(126,21), wxTAB_TRAVERSAL, _T("ID_LOGOPANEL"));
    FlexGridSizer2->Add(LogoPanel, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(FlexGridSizer2, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentConditionsStaticBoxSizer = new wxStaticBoxSizer(wxHORIZONTAL, this, _("Current conditions"));
    FlexGridSizer19 = new wxFlexGridSizer(1, 4, 0, 0);
    FlexGridSizer23 = new wxFlexGridSizer(3, 1, 0, 0);
    TemperatureStaticText = new wxStaticText(this, ID_TEMPERATURESTATICTEXT, _("Temperature"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TEMPERATURESTATICTEXT"));
    wxFont TemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TemperatureStaticTextFont.Ok() ) TemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TemperatureStaticTextFont.SetWeight(wxBOLD);
    TemperatureStaticText->SetFont(TemperatureStaticTextFont);
    FlexGridSizer23->Add(TemperatureStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentTemperatureStaticText = new wxStaticText(this, ID_CURRENTTEMPERATURESTATICTEXT, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTTEMPERATURESTATICTEXT"));
    wxFont CurrentTemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentTemperatureStaticTextFont.Ok() ) CurrentTemperatureStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentTemperatureStaticTextFont.SetPointSize(37);
    CurrentTemperatureStaticTextFont.SetWeight(wxBOLD);
    CurrentTemperatureStaticText->SetFont(CurrentTemperatureStaticTextFont);
    FlexGridSizer23->Add(CurrentTemperatureStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentWeatherConditionStaticText = new wxStaticText(this, ID_CURRENTWEATHERCONDITIONSTATICTEXT, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTWEATHERCONDITIONSTATICTEXT"));
    FlexGridSizer23->Add(CurrentWeatherConditionStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19->Add(FlexGridSizer23, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer20 = new wxFlexGridSizer(4, 1, 0, 0);
    WindStaticText = new wxStaticText(this, ID_WINDSTATICTEXT, _("Wind"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WINDSTATICTEXT"));
    wxFont WindStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !WindStaticTextFont.Ok() ) WindStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    WindStaticTextFont.SetWeight(wxBOLD);
    WindStaticText->SetFont(WindStaticTextFont);
    FlexGridSizer20->Add(WindStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ChillStaticText = new wxStaticText(this, ID_CHILLSTATICTEXT, _("Chill: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CHILLSTATICTEXT"));
    FlexGridSizer20->Add(ChillStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    DirectionStaticText = new wxStaticText(this, ID_DIRECTIONSTATICTEXT, _("Direction: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_DIRECTIONSTATICTEXT"));
    FlexGridSizer20->Add(DirectionStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SpeedStaticText = new wxStaticText(this, ID_SPEEDSTATICTEXT, _("Speed: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SPEEDSTATICTEXT"));
    FlexGridSizer20->Add(SpeedStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19->Add(FlexGridSizer20, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer21 = new wxFlexGridSizer(5, 1, 0, 0);
    AtmosphereStaticText = new wxStaticText(this, ID_ATMOSPHERESTATICTEXT, _("Atmosphere"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ATMOSPHERESTATICTEXT"));
    wxFont AtmosphereStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !AtmosphereStaticTextFont.Ok() ) AtmosphereStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    AtmosphereStaticTextFont.SetWeight(wxBOLD);
    AtmosphereStaticText->SetFont(AtmosphereStaticTextFont);
    FlexGridSizer21->Add(AtmosphereStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    HumidityStaticText = new wxStaticText(this, ID_HUMIDITYSTATICTEXT, _("Humidity: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_HUMIDITYSTATICTEXT"));
    FlexGridSizer21->Add(HumidityStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    VisibilityStaticText = new wxStaticText(this, ID_VISIBILITYSTATICTEXT, _("Visibility: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_VISIBILITYSTATICTEXT"));
    FlexGridSizer21->Add(VisibilityStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    PressureStaticText = new wxStaticText(this, ID_PRESSURESTATICTEXT, _("Pressure: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_PRESSURESTATICTEXT"));
    FlexGridSizer21->Add(PressureStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    RisingStaticText = new wxStaticText(this, ID_RISINGSTATICTEXT, _("Rising: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_RISINGSTATICTEXT"));
    FlexGridSizer21->Add(RisingStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19->Add(FlexGridSizer21, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    FlexGridSizer22 = new wxFlexGridSizer(3, 1, 0, 0);
    AstronomyStaticText = new wxStaticText(this, ID_ASTRONOMYSTATICTEXT, _("Astronomy"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_ASTRONOMYSTATICTEXT"));
    wxFont AstronomyStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !AstronomyStaticTextFont.Ok() ) AstronomyStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    AstronomyStaticTextFont.SetWeight(wxBOLD);
    AstronomyStaticText->SetFont(AstronomyStaticTextFont);
    FlexGridSizer22->Add(AstronomyStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SunriseStaticText = new wxStaticText(this, ID_SUNRISESTATICTEXT, _("Sunrise: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SUNRISESTATICTEXT"));
    FlexGridSizer22->Add(SunriseStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    SunsetStaticText = new wxStaticText(this, ID_SUNSETSTATICTEXT, _("Sunset: N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_SUNSETSTATICTEXT"));
    FlexGridSizer22->Add(SunsetStaticText, 1, wxALL|wxALIGN_LEFT|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer19->Add(FlexGridSizer22, 1, wxALL|wxALIGN_TOP|wxALIGN_CENTER_HORIZONTAL, 5);
    CurrentConditionsStaticBoxSizer->Add(FlexGridSizer19, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(CurrentConditionsStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastStaticBoxSizer = new wxStaticBoxSizer(wxVERTICAL, this, _("Weather forecast"));
    FlexGridSizer3 = new wxFlexGridSizer(1, 3, 0, 0);
    FlexGridSizer4 = new wxFlexGridSizer(4, 1, 0, 0);
    TodayStaticText = new wxStaticText(this, ID_TODAYSTATICTEXT, _("Today"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TODAYSTATICTEXT"));
    wxFont TodayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TodayStaticTextFont.Ok() ) TodayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TodayStaticTextFont.SetWeight(wxBOLD);
    TodayStaticText->SetFont(TodayStaticTextFont);
    FlexGridSizer4->Add(TodayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer9 = new wxFlexGridSizer(0, 2, 0, 0);
    MaxTempStaticText1 = new wxStaticText(this, ID_MAXTEMPSTATICTEXT1, _("Max. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXTEMPSTATICTEXT1"));
    FlexGridSizer9->Add(MaxTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText1 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT1, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT1"));
    wxFont CurrentMaxTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText1Font.Ok() ) CurrentMaxTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText1Font.SetPointSize(12);
    CurrentMaxTempStaticText1Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText1->SetFont(CurrentMaxTempStaticText1Font);
    FlexGridSizer9->Add(CurrentMaxTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer9, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer10 = new wxFlexGridSizer(0, 2, 0, 0);
    MinTempStaticText1 = new wxStaticText(this, ID_MINTEMPSTATICTEXT1, _("Min. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINTEMPSTATICTEXT1"));
    FlexGridSizer10->Add(MinTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMinTempStaticText1 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT1, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT1"));
    wxFont CurrentMinTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText1Font.Ok() ) CurrentMinTempStaticText1Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText1Font.SetPointSize(12);
    CurrentMinTempStaticText1Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText1->SetFont(CurrentMinTempStaticText1Font);
    FlexGridSizer10->Add(CurrentMinTempStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer4->Add(FlexGridSizer10, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText1 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT1, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT1"));
    FlexGridSizer4->Add(WeatherConditionStaticText1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5 = new wxFlexGridSizer(4, 1, 0, 0);
    TomorrowStaticText = new wxStaticText(this, ID_TOMORROWSTATICTEXT, _("Tomorrow"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_TOMORROWSTATICTEXT"));
    wxFont TomorrowStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !TomorrowStaticTextFont.Ok() ) TomorrowStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    TomorrowStaticTextFont.SetWeight(wxBOLD);
    TomorrowStaticText->SetFont(TomorrowStaticTextFont);
    FlexGridSizer5->Add(TomorrowStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer11 = new wxFlexGridSizer(0, 2, 0, 0);
    MaxTempStaticText2 = new wxStaticText(this, IID_MAXTEMPSTATICTEXT2, _("Max. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("IID_MAXTEMPSTATICTEXT2"));
    FlexGridSizer11->Add(MaxTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText2 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT2, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT2"));
    wxFont CurrentMaxTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText2Font.Ok() ) CurrentMaxTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText2Font.SetPointSize(12);
    CurrentMaxTempStaticText2Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText2->SetFont(CurrentMaxTempStaticText2Font);
    FlexGridSizer11->Add(CurrentMaxTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer11, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer12 = new wxFlexGridSizer(0, 2, 0, 0);
    MinTempStaticText2 = new wxStaticText(this, ID_MINTEMPSTATICTEXT2, _("Min. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINTEMPSTATICTEXT2"));
    FlexGridSizer12->Add(MinTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMinTempStaticText2 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT2, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT2"));
    wxFont CurrentMinTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText2Font.Ok() ) CurrentMinTempStaticText2Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText2Font.SetPointSize(12);
    CurrentMinTempStaticText2Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText2->SetFont(CurrentMinTempStaticText2Font);
    FlexGridSizer12->Add(CurrentMinTempStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer5->Add(FlexGridSizer12, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText2 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT2, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT2"));
    FlexGridSizer5->Add(WeatherConditionStaticText2, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6 = new wxFlexGridSizer(4, 1, 0, 0);
    ThirdDayStaticText = new wxStaticText(this, ID_THIRDDAYSTATICTEXT, _("3rd Day"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_THIRDDAYSTATICTEXT"));
    wxFont ThirdDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !ThirdDayStaticTextFont.Ok() ) ThirdDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    ThirdDayStaticTextFont.SetWeight(wxBOLD);
    ThirdDayStaticText->SetFont(ThirdDayStaticTextFont);
    FlexGridSizer6->Add(ThirdDayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer13 = new wxFlexGridSizer(0, 2, 0, 0);
    MaxTempStaticText3 = new wxStaticText(this, ID_MAXTEMPSTATICTEXT3, _("Max. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXTEMPSTATICTEXT3"));
    FlexGridSizer13->Add(MaxTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText3 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT3, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT3"));
    wxFont CurrentMaxTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText3Font.Ok() ) CurrentMaxTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText3Font.SetPointSize(12);
    CurrentMaxTempStaticText3Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText3->SetFont(CurrentMaxTempStaticText3Font);
    FlexGridSizer13->Add(CurrentMaxTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizer13, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer14 = new wxFlexGridSizer(0, 2, 0, 0);
    MinTempStaticText3 = new wxStaticText(this, ID_MINTEMPSTATICTEXT3, _("Min. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINTEMPSTATICTEXT3"));
    FlexGridSizer14->Add(MinTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMinTempStaticText3 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT3, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT3"));
    wxFont CurrentMinTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText3Font.Ok() ) CurrentMinTempStaticText3Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText3Font.SetPointSize(12);
    CurrentMinTempStaticText3Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText3->SetFont(CurrentMinTempStaticText3Font);
    FlexGridSizer14->Add(CurrentMinTempStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer6->Add(FlexGridSizer14, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText3 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT3, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT3"));
    FlexGridSizer6->Add(WeatherConditionStaticText3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer3->Add(FlexGridSizer6, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastStaticBoxSizer->Add(FlexGridSizer3, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer24 = new wxFlexGridSizer(1, 2, 0, 0);
    FlexGridSizer7 = new wxFlexGridSizer(4, 1, 0, 0);
    FourthDayStaticText = new wxStaticText(this, ID_FOURTHDAYSTATICTEXT, _("4th Day"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_FOURTHDAYSTATICTEXT"));
    wxFont FourthDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !FourthDayStaticTextFont.Ok() ) FourthDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    FourthDayStaticTextFont.SetWeight(wxBOLD);
    FourthDayStaticText->SetFont(FourthDayStaticTextFont);
    FlexGridSizer7->Add(FourthDayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer15 = new wxFlexGridSizer(0, 2, 0, 0);
    MaxTempStaticText4 = new wxStaticText(this, ID_MAXTEMPSTATICTEXT4, _("Max. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXTEMPSTATICTEXT4"));
    FlexGridSizer15->Add(MaxTempStaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText4 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT4, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT4"));
    wxFont CurrentMaxTempStaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText4Font.Ok() ) CurrentMaxTempStaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText4Font.SetPointSize(12);
    CurrentMaxTempStaticText4Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText4->SetFont(CurrentMaxTempStaticText4Font);
    FlexGridSizer15->Add(CurrentMaxTempStaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(FlexGridSizer15, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer16 = new wxFlexGridSizer(0, 2, 0, 0);
    MinTempStaticText4 = new wxStaticText(this, ID_MINTEMPSTATICTEXT4, _("Min. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINTEMPSTATICTEXT4"));
    FlexGridSizer16->Add(MinTempStaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMinTempStaticText4 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT4, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT4"));
    wxFont CurrentMinTempStaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText4Font.Ok() ) CurrentMinTempStaticText4Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText4Font.SetPointSize(12);
    CurrentMinTempStaticText4Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText4->SetFont(CurrentMinTempStaticText4Font);
    FlexGridSizer16->Add(CurrentMinTempStaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer7->Add(FlexGridSizer16, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText4 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT4, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT4"));
    FlexGridSizer7->Add(WeatherConditionStaticText4, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer24->Add(FlexGridSizer7, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8 = new wxFlexGridSizer(4, 1, 0, 0);
    FifthDayStaticText = new wxStaticText(this, ID_FIFTHTHDAYSTATICTEXT, _("5th Day"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_FIFTHTHDAYSTATICTEXT"));
    wxFont FifthDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !FifthDayStaticTextFont.Ok() ) FifthDayStaticTextFont = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    FifthDayStaticTextFont.SetWeight(wxBOLD);
    FifthDayStaticText->SetFont(FifthDayStaticTextFont);
    FlexGridSizer8->Add(FifthDayStaticText, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer17 = new wxFlexGridSizer(0, 2, 0, 0);
    MaxTempStaticText5 = new wxStaticText(this, ID_MAXTEMPSTATICTEXT5, _("Max. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MAXTEMPSTATICTEXT5"));
    FlexGridSizer17->Add(MaxTempStaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMaxTempStaticText5 = new wxStaticText(this, ID_CURRENTMAXTEMPSTATICTEXT5, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMAXTEMPSTATICTEXT5"));
    wxFont CurrentMaxTempStaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMaxTempStaticText5Font.Ok() ) CurrentMaxTempStaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMaxTempStaticText5Font.SetPointSize(12);
    CurrentMaxTempStaticText5Font.SetWeight(wxBOLD);
    CurrentMaxTempStaticText5->SetFont(CurrentMaxTempStaticText5Font);
    FlexGridSizer17->Add(CurrentMaxTempStaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer17, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer18 = new wxFlexGridSizer(0, 2, 0, 0);
    MinTempStaticText5 = new wxStaticText(this, ID_MINTEMPSTATICTEXT5, _("Min. temperature:"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_MINTEMPSTATICTEXT5"));
    FlexGridSizer18->Add(MinTempStaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    CurrentMinTempStaticText5 = new wxStaticText(this, ID_CURRENTMINTEMPSTATICTEXT5, _("N/A"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_CURRENTMINTEMPSTATICTEXT5"));
    wxFont CurrentMinTempStaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    if ( !CurrentMinTempStaticText5Font.Ok() ) CurrentMinTempStaticText5Font = wxSystemSettings::GetFont(wxSYS_DEFAULT_GUI_FONT);
    CurrentMinTempStaticText5Font.SetPointSize(12);
    CurrentMinTempStaticText5Font.SetWeight(wxBOLD);
    CurrentMinTempStaticText5->SetFont(CurrentMinTempStaticText5Font);
    FlexGridSizer18->Add(CurrentMinTempStaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer8->Add(FlexGridSizer18, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherConditionStaticText5 = new wxStaticText(this, ID_WEATHERCONDITIONSTATICTEXT5, _("Weather condition"), wxDefaultPosition, wxDefaultSize, 0, _T("ID_WEATHERCONDITIONSTATICTEXT5"));
    FlexGridSizer8->Add(WeatherConditionStaticText5, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer24->Add(FlexGridSizer8, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    WeatherForecastStaticBoxSizer->Add(FlexGridSizer24, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    FlexGridSizer1->Add(WeatherForecastStaticBoxSizer, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    MenuBar1 = new wxMenuBar();
    Menu1 = new wxMenu();
    MenuItem3 = new wxMenuItem(Menu1, idMenuCheck, _("&Check\tEnter"), _("Checks the weather in the city provided."), wxITEM_NORMAL);
    Menu1->Append(MenuItem3);
    MenuItem7 = new wxMenu();
    MenuItem8 = new wxMenuItem(MenuItem7, idMenuAsFile, _("As &file...\tCtrl+S"), _("Saves the weather details to a specified file."), wxITEM_NORMAL);
    MenuItem7->Append(MenuItem8);
    MenuItem8->Enable(false);
    MenuItem9 = new wxMenuItem(MenuItem7, idMenuToClipboard, _("To &Clipboard\tCtrl+Alt+C"), _("Copies the weather details to the system clipboard."), wxITEM_NORMAL);
    MenuItem7->Append(MenuItem9);
    MenuItem9->Enable(false);
    Menu1->Append(idMenuSave, _("&Save"), MenuItem7, wxEmptyString);
    Menu1->AppendSeparator();
    MenuItem1 = new wxMenuItem(Menu1, idMenuQuit, _("E&xit\tAlt+F4"), _("Quits the application."), wxITEM_NORMAL);
    Menu1->Append(MenuItem1);
    MenuBar1->Append(Menu1, _("&File"));
    Menu3 = new wxMenu();
    MenuItem4 = new wxMenu();
    MenuItem5 = new wxMenuItem(MenuItem4, idMenuCelsius, _("&Celsius"), _("Sets the temperature unit to Celsius along with distance (km), pressure (mb) and wind speed (kph)."), wxITEM_RADIO);
    MenuItem4->Append(MenuItem5);
    MenuItem6 = new wxMenuItem(MenuItem4, idMenuFahrenheit, _("&Fahrenheit"), _("Sets the temperature unit to Fahrenheit along with distance (mi), pressure (in) and wind speed (mph)."), wxITEM_RADIO);
    MenuItem4->Append(MenuItem6);
    Menu3->Append(idMenuTemperatureUnit, _("Temperature &unit"), MenuItem4, wxEmptyString);
    MenuItem15 = new wxMenu();
    MenuItem16 = new wxMenuItem(MenuItem15, idMenu12HourClock, _("&12-hour clock"), _("Sets the time format to 12-hour (AM/PM)."), wxITEM_RADIO);
    MenuItem15->Append(MenuItem16);
    MenuItem17 = new wxMenuItem(MenuItem15, idMenu24HourClock, _("&24-hour clock"), _("Sets the time format to 24-hour."), wxITEM_RADIO);
    MenuItem15->Append(MenuItem17);
    Menu3->Append(idMenuTimeFormat, _("&Time format"), MenuItem15, wxEmptyString);
    MenuItem18 = new wxMenu();
    MenuItem19 = new wxMenuItem(MenuItem18, idMenuYearHyphenMonthHyphenDay, _("YYYY-MM-DD"), _("Sets the date format to YYYY-MM-DD."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem19);
    MenuItem20 = new wxMenuItem(MenuItem18, idMenuDayHyphenMonthHyphenYear, _("DD-MM-YYYY"), _("Sets the date format to DD-MM-YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem20);
    MenuItem21 = new wxMenuItem(MenuItem18, idMenuYearHyphenDayHyphenMonth, _("YYYY-DD-MM"), _("Sets the date format to YYYY-DD-MM."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem21);
    MenuItem22 = new wxMenuItem(MenuItem18, idMenuMonthHyphenDayHyphenYear, _("MM-DD-YYYY"), _("Sets the date format to MM-DD-YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem22);
    MenuItem23 = new wxMenuItem(MenuItem18, idMenuYearDotMonthDotDay, _("YYYY.MM.DD"), _("Sets the date format to YYYY.MM.DD."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem23);
    MenuItem24 = new wxMenuItem(MenuItem18, idMenuDayDotMonthDotYear, _("DD.MM.YYYY"), _("Sets the date format to DD.MM.YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem24);
    MenuItem25 = new wxMenuItem(MenuItem18, idMenuYearDotDayDotMonth, _("YYYY.DD.MM"), _("Sets the date format to YYYY.DD.MM."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem25);
    MenuItem26 = new wxMenuItem(MenuItem18, idMenuMonthDotDayDotYear, _("MM.DD.YYYY"), _("Sets the date format to MM.DD.YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem26);
    MenuItem27 = new wxMenuItem(MenuItem18, idMenuYearSlashMonthSlashDay, _("YYYY/MM/DD"), _("Sets the date format to YYYY/MM/DD."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem27);
    MenuItem28 = new wxMenuItem(MenuItem18, idMenuDaySlashMonthSlashYear, _("DD/MM/YYYY"), _("Sets the date format to DD/MM/YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem28);
    MenuItem29 = new wxMenuItem(MenuItem18, idMenuYearSlashDaySlashMonth, _("YYYY/DD/MM"), _("Sets the date format to YYYY/DD/MM."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem29);
    MenuItem30 = new wxMenuItem(MenuItem18, idMenuMonthSlashDaySlashYear, _("MM/DD/YYYY"), _("Sets the date format to MM/DD/YYYY."), wxITEM_RADIO);
    MenuItem18->Append(MenuItem30);
    Menu3->Append(idMenuDateFormat, _("&Date format"), MenuItem18, wxEmptyString);
    MenuItem10 = new wxMenu();
    MenuItem11 = new wxMenuItem(MenuItem10, idMenuANSI, _("&ANSI"), _("Sets plain text details format to ANSI."), wxITEM_RADIO);
    MenuItem10->Append(MenuItem11);
    MenuItem12 = new wxMenuItem(MenuItem10, idMenuUTF8, _("&UTF-8"), _("Sets plain text details format to Unicode (UTF-8)."), wxITEM_RADIO);
    MenuItem10->Append(MenuItem12);
    Menu3->Append(idMenuTargetFileEncoding, _("Target file &encoding"), MenuItem10, wxEmptyString);
    MenuItem14 = new wxMenuItem(Menu3, idMenuChangeLanguage, _("&Change language"), _("Changes the user interface language."), wxITEM_NORMAL);
    Menu3->Append(MenuItem14);
    Menu3->AppendSeparator();
    MenuItem13 = new wxMenuItem(Menu3, idMenuSaveSettings, _("&Save settings"), _("Saves current settings to the configuration file."), wxITEM_NORMAL);
    Menu3->Append(MenuItem13);
    MenuBar1->Append(Menu3, _("&Options"));
    Menu2 = new wxMenu();
    MenuItem2 = new wxMenuItem(Menu2, idMenuAbout, _("&About...\tF1"), _("Shows info about this application."), wxITEM_NORMAL);
    Menu2->Append(MenuItem2);
    MenuBar1->Append(Menu2, _("&Help"));
    SetMenuBar(MenuBar1);
    StatusBar1 = new wxStatusBar(this, ID_STATUSBAR1, 0, _T("ID_STATUSBAR1"));
    int __wxStatusBarWidths_1[1] = { -1 };
    int __wxStatusBarStyles_1[1] = { wxSB_NORMAL };
    StatusBar1->SetFieldsCount(1,__wxStatusBarWidths_1);
    StatusBar1->SetStatusStyles(1,__wxStatusBarStyles_1);
    SetStatusBar(StatusBar1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
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
    StatusBar1->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Weather95_20Frame::OnLeftDown, NULL, this);

    mainMenu = Menu1;

    if(wxGetApp().userTemperatureUnit == wxT('f'))
        MenuItem6->Check(true);
    if(wxGetApp().user24HourTimeFormat)
        MenuItem17->Check(true);
    if(wxGetApp().userDateFormatVariant == 1)
        MenuItem19->Check(true);
    else if(wxGetApp().userDateFormatVariant == 2)
        MenuItem20->Check(true);
    else if(wxGetApp().userDateFormatVariant == 3)
        MenuItem21->Check(true);
    else if(wxGetApp().userDateFormatVariant == 4)
        MenuItem22->Check(true);
    else if(wxGetApp().userDateFormatVariant == 5)
        MenuItem23->Check(true);
    else if(wxGetApp().userDateFormatVariant == 6)
        MenuItem24->Check(true);
    else if(wxGetApp().userDateFormatVariant == 7)
        MenuItem25->Check(true);
    else if(wxGetApp().userDateFormatVariant == 8)
        MenuItem26->Check(true);
    else if(wxGetApp().userDateFormatVariant == 9)
        MenuItem27->Check(true);
    else if(wxGetApp().userDateFormatVariant == 10)
        MenuItem28->Check(true);
    else if(wxGetApp().userDateFormatVariant == 11)
        MenuItem29->Check(true);
    else if(wxGetApp().userDateFormatVariant == 12)
        MenuItem30->Check(true);
    if(wxGetApp().userUseUTF8)
        MenuItem12->Check(true);

    if(!wxGetApp().DoesLangsFolderExist())
        MenuItem14->Enable(false);

    weatherConditions[0] = _("Tornado");
    weatherConditions[1] = _("Tropical storm");
    weatherConditions[2] = _("Hurricane");
    weatherConditions[3] = _("Severe thunderstorms");
    weatherConditions[4] = _("Thunderstorms");
    weatherConditions[5] = _("Mixed rain and snow");
    weatherConditions[6] = _("Mixed rain and sleet");
    weatherConditions[7] = _("Mixed snow and sleet");
    weatherConditions[8] = _("Freezing drizzle");
    weatherConditions[9] = _("Drizzle");
    weatherConditions[10] = _("Freezing rain");
    weatherConditions[11] = _("Showers");
    weatherConditions[12] = _("Showers");
    weatherConditions[13] = _("Snow flurries");
    weatherConditions[14] = _("Light snow showers");
    weatherConditions[15] = _("Blowing snow");
    weatherConditions[16] = _("Snow");
    weatherConditions[17] = _("Hail");
    weatherConditions[18] = _("Sleet");
    weatherConditions[19] = _("Dust");
    weatherConditions[20] = _("Foggy");
    weatherConditions[21] = _("Haze");
    weatherConditions[22] = _("Smoky");
    weatherConditions[23] = _("Blustery");
    weatherConditions[24] = _("Windy");
    weatherConditions[25] = _("Cold");
    weatherConditions[26] = _("Cloudy");
    weatherConditions[27] = _("Mostly cloudy (night)");
    weatherConditions[28] = _("Mostly cloudy (day)");
    weatherConditions[29] = _("Partly cloudy (night)");
    weatherConditions[30] = _("Partly cloudy (day)");
    weatherConditions[31] = _("Clear (night)");
    weatherConditions[32] = _("Sunny");
    weatherConditions[33] = _("Fair (night)");
    weatherConditions[34] = _("Fair (day)");
    weatherConditions[35] = _("Mixed rain and hail");
    weatherConditions[36] = _("Hot");
    weatherConditions[37] = _("Isolated thunderstorms");
    weatherConditions[38] = _("Scattered thunderstorms");
    weatherConditions[39] = _("Scattered thunderstorms");
    weatherConditions[40] = _("Scattered showers");
    weatherConditions[41] = _("Heavy snow");
    weatherConditions[42] = _("Scattered snow showers");
    weatherConditions[43] = _("Heavy snow");
    weatherConditions[44] = _("Partly cloudy");
    weatherConditions[45] = _("Thundershowers");
    weatherConditions[46] = _("Snow showers");
    weatherConditions[47] = _("Isolated thundershowers");
    weatherConditions[3200] = _("Not available");

    wxMemoryInputStream mInput(yahooLogo, YAHOO_LOGO_SIZE);
    wxImage yahooLogoImage(mInput, wxBITMAP_TYPE_PNG);
    wxPanel *drawPanel = new wxImagePanel(LogoPanel, yahooLogoImage);
    drawPanel->SetSize(134, 29);
    drawPanel->Connect(wxEVT_LEFT_DOWN, (wxObjectEventFunction)&Weather95_20Frame::OnLogoPanelLeftDown, NULL, this);
    drawPanel->SetCursor(wxCURSOR_HAND);
}

Weather95_20Frame::~Weather95_20Frame()
{
    //(*Destroy(Weather95_20Frame)
    //*)
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
    info.SetVersion(wxT("1.0"));
    info.SetCopyright(wxT("Copyright (C) PeCeT_full 2015 <pecetfull@komputermania.pl.eu.org>"));
    info.SetDescription(_("A weather forecast program for both vintage and modern PC workstations. Powered by Yahoo Weather API.\nThis product includes software developed by the OpenSSL Project for use in the OpenSSL Toolkit (http://www.openssl.org/).\n\nBuild info: ") + wxBuildInfo(long_f) + _(".\nBuild date: ") +  __TDATE__ + wxT(", ") __TTIME__ + _(".\n\nCurrent language: ") + currentLanguageName + '.');
    info.SetWebSite(_("http://www.komputermania.pl.eu.org"));
    info.SetLicence(_("This program is published under The MIT License. For more information, please refer to the Licence.txt file included with the application.\n\nThis program also includes libraries that are necessary to launch the software. The licensing information regarding those are located in the Licences directory."));

    wxAboutBox(info);
}

static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size* nmemb);
    return size* nmemb;
}

short ReturnMonthNumber(wxString shortMonthName)
{
    if(shortMonthName == wxT("Jan"))
        return 1;
    else if(shortMonthName == wxT("Feb"))
        return 2;
    else if(shortMonthName == wxT("Mar"))
        return 3;
    else if(shortMonthName == wxT("Apr"))
        return 4;
    else if(shortMonthName == wxT("May"))
        return 5;
    else if(shortMonthName == wxT("Jun"))
        return 6;
    else if(shortMonthName == wxT("Jul"))
        return 7;
    else if(shortMonthName == wxT("Aug"))
        return 8;
    else if(shortMonthName == wxT("Sep"))
        return 9;
    else if(shortMonthName == wxT("Oct"))
        return 10;
    else if(shortMonthName == wxT("Nov"))
        return 11;
    else if(shortMonthName == wxT("Dec"))
        return 12;
    else
        return 0;
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

wxString ConvertToFullWeekdayName(wxString shortWeekdayName)
{
    if(shortWeekdayName == wxT("Mon"))
        return _("Monday");
    else if(shortWeekdayName == wxT("Tue"))
        return _("Tuesday");
    else if(shortWeekdayName == wxT("Wed"))
        return _("Wednesday");
    else if(shortWeekdayName == wxT("Thu"))
        return _("Thursday");
    else if(shortWeekdayName == wxT("Fri"))
        return _("Friday");
    else if(shortWeekdayName == wxT("Sat"))
        return _("Saturday");
    else if(shortWeekdayName == wxT("Sun"))
        return _("Sunday");
    else
        return _("Unknown");
}

void ConvertTo24HourClock(wxString& source12HourClock)
{
    int colonSignPlacement = source12HourClock.Find(wxT(':'));
    short minutes = wxAtoi(source12HourClock.SubString(colonSignPlacement + 1, source12HourClock.Length()));
    short hours = wxAtoi(source12HourClock.SubString(0, colonSignPlacement - 1));
    if(source12HourClock.Contains(wxT("am")))
    {
        if(hours == 12)
            hours = 0;
    }
    else if(source12HourClock.Contains(wxT("pm")))
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

    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl)
    {
        wxString enteredLocationName = LocationTextCtrl->GetLabel();
        enteredLocationName.Replace(wxT(" "), wxT("%20"));

        wxString apiURL = wxT("https://query.yahooapis.com/v1/public/yql?q=select%20*%20from%20weather.forecast%20where%20woeid%20in%20(select%20woeid%20from%20geo.places(1)%20where%20text%3D%22") + enteredLocationName + wxT("%22)%20and%20u%3D'") + wxGetApp().userTemperatureUnit + wxT("'&format=json&env=store%3A%2F%2Fdatatables.org%2Falltableswithkeys");
        std::string apiDest = std::string(apiURL.mb_str(wxConvUTF8));
        curl_easy_setopt(curl, CURLOPT_URL, apiDest.c_str());
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
        {
            wxMessageBox(wxString::Format(_("Could not successfully establish the connection due to the following reason: %s."), wxGetTranslation(wxString::FromUTF8(curl_easy_strerror(res)))), _("Error"), wxICON_HAND);
            return;
        }

        curl_easy_cleanup(curl);

        wxString apiResult(readBuffer.c_str(), wxConvUTF8);

        wxJSONValue jsonRoot;
        wxJSONReader jsonReader;

        int numErrors = jsonReader.Parse(apiResult, &jsonRoot);
        if(numErrors > 0)
        {
            wxMessageBox(_("The target data document is not well-formed. Enter another search phrase or try again later."), _("Error"), wxICON_HAND);
            //const wxArrayString& errors = jsonReader.GetErrors();
            return;
        }

        if(jsonRoot[wxT("query")][wxT("results")].AsString() != wxT("null"))
        {
            if(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("title")].AsString() != wxT("City not found"))
            {
                // header
                city = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("location")][wxT("city")].AsString();
                country = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("location")][wxT("country")].AsString();
                region = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("location")][wxT("region")].AsString();
                if(country != wxT("") && country != city)
                {
                    country = wxGetTranslation(country);
                    location = city + wxT(", ") + country;
                }
                else // if search phrase is the Earth or a country
                {
                    city = wxGetTranslation(city);
                    location = city;
                    country.Empty();
                }
                latitude = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("lat")].AsString();
                longitude = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("long")].AsString();
                lastBuildDate = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("lastBuildDate")].AsString();
                lastBuildDate = lastBuildDate.SubString(5, lastBuildDate.Length()); // cuts the 3-letter week day name
                // time conversion of the time in lastBuildDate from 12 to 24 hour time format (if enabled in options)
                if(wxGetApp().user24HourTimeFormat)
                {
                    wxString timeZone = lastBuildDate.SubString(lastBuildDate.find_last_of(wxT(' ')) + 1, lastBuildDate.Length());
                    lastBuildDate = lastBuildDate.SubString(0, lastBuildDate.find_last_of(wxT(' ')) - 1);
                    wxString noonType = lastBuildDate.SubString(lastBuildDate.find_last_of(wxT(' ')) + 1, lastBuildDate.Length());
                    lastBuildDate = lastBuildDate.SubString(0, lastBuildDate.find_last_of(wxT(' ')) - 1);
                    wxString actualClock = lastBuildDate.SubString(lastBuildDate.find_last_of(wxT(' ')) + 1, lastBuildDate.Length());
                    lastBuildDate = lastBuildDate.SubString(0, lastBuildDate.find_last_of(wxT(' ')) - 1);
                    actualClock += wxT(' ' + noonType);
                    ConvertTo24HourClock(actualClock);
                    lastBuildDate += wxString::Format(wxT(" %s %s"), actualClock.c_str(), timeZone.c_str());
                }
                // month conversion (from English 3-letter month name to its digital counterpart
                int firstSpace = lastBuildDate.Find(wxT(' '));
                int secondSpace = lastBuildDate.SubString(firstSpace + 1, lastBuildDate.Length()).Find(wxT(' ')) + firstSpace;
                wxString monthName = lastBuildDate.SubString(firstSpace + 1, secondSpace);
                short monthNumber = ReturnMonthNumber(monthName);
                lastBuildDate.Replace(wxT(' ') + monthName + wxT(' '), wxString::Format(wxT("-%i-"), monthNumber));
                // general date conversion
                wxString currentLastBuildDateWithoutTime = lastBuildDate.SubString(0, lastBuildDate.Find(wxT(' ')) - 1); // temporary
                int firstHyphen = currentLastBuildDateWithoutTime.Find(wxT('-'));
                int secondHyphen = currentLastBuildDateWithoutTime.SubString(firstHyphen + 1, currentLastBuildDateWithoutTime.Length()).Find(wxT('-')) + firstHyphen;
                short dayNumber = wxAtoi(currentLastBuildDateWithoutTime.SubString(0, firstHyphen - 1));
                short yearNumber = wxAtoi(currentLastBuildDateWithoutTime.SubString(secondHyphen + 2, currentLastBuildDateWithoutTime.Length()));
                lastBuildDate.Replace(currentLastBuildDateWithoutTime, ReturnDateOfSpecifiedFormat(dayNumber, monthNumber, yearNumber));

                // weather units
                temperatureUnit = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("units")][wxT("temperature")].AsString();
                distanceUnit = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("units")][wxT("distance")].AsString();
                pressureUnit = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("units")][wxT("pressure")].AsString();
                // pressure unit conversion (if necessary)
                wxString localisedPressureUnit = _("PRESSURE_MB"); // the 'identifier' of a pressure unit (varies on UI language)
                if(temperatureUnit == wxT('C') && localisedPressureUnit == wxT("PRESSURE_HPA"))
                    pressureUnit = wxT("hPa");
                speedUnit = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("units")][wxT("speed")].AsString();

                // current conditions
                currentTemperature = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("condition")][wxT("temp")].AsString() + wxT(" °") + temperatureUnit;
                currentCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("condition")][wxT("code")].AsString())];
                windChill = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("wind")][wxT("chill")].AsString() + wxT("°");
                windDirection = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("wind")][wxT("direction")].AsString() + wxT("°");
                windSpeed = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("wind")][wxT("speed")].AsString() + ' ' + speedUnit;
                humidity = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("atmosphere")][wxT("humidity")].AsString() + '%';
                pressure = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("atmosphere")][wxT("pressure")].AsString() + ' ' + pressureUnit;
                int risingInt = wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("atmosphere")][wxT("rising")].AsString());
                if(risingInt == 2)
                    rising = _("falling");
                else if(risingInt == 1)
                    rising = _("rising");
                else
                    rising = _("steady");
                visibility = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("atmosphere")][wxT("visibility")].AsString();
                if(visibility == wxT(""))
                    visibility = wxT('?');
                else
                    visibility += ' ' + distanceUnit;

                // astronomy stuff
                sunrise = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("astronomy")][wxT("sunrise")].AsString();
                sunset = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("astronomy")][wxT("sunset")].AsString();
                // time conversion from 12 to 24 hour time format (if enabled in options)
                if(wxGetApp().user24HourTimeFormat)
                {
                    // sunrise
                    ConvertTo24HourClock(sunrise);
                    // sunset
                    ConvertTo24HourClock(sunset);
                }

                // weather forecast
                todayWeekDay = ConvertToFullWeekdayName(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][0][wxT("day")].AsString());
                todayTempMin = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][0][wxT("low")].AsString() + wxT(" °") + temperatureUnit;
                todayTempMax = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][0][wxT("high")].AsString() + wxT(" °") + temperatureUnit;
                todayCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][0][wxT("code")].AsString())];
                tomorrowWeekDay = ConvertToFullWeekdayName(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][1][wxT("day")].AsString());
                tomorrowTempMin = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][1][wxT("low")].AsString() + wxT(" °") + temperatureUnit;
                tomorrowTempMax = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][1][wxT("high")].AsString() + wxT(" °") + temperatureUnit;
                tomorrowCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][1][wxT("code")].AsString())];
                thirdDayWeekDay = ConvertToFullWeekdayName(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][2][wxT("day")].AsString());
                thirdDayTempMin = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][2][wxT("low")].AsString() + wxT(" °") + temperatureUnit;
                thirdDayTempMax = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][2][wxT("high")].AsString() + wxT(" °") + temperatureUnit;
                thirdDayCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][2][wxT("code")].AsString())];
                fourthDayWeekDay = ConvertToFullWeekdayName(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][3][wxT("day")].AsString());
                fourthDayTempMin = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][3][wxT("low")].AsString() + wxT(" °") + temperatureUnit;
                fourthDayTempMax = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][3][wxT("high")].AsString() + wxT(" °") + temperatureUnit;
                fourthDayCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][3][wxT("code")].AsString())];
                fifthDayWeekDay = ConvertToFullWeekdayName(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][4][wxT("day")].AsString());
                fifthDayTempMin = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][4][wxT("low")].AsString() + wxT(" °") + temperatureUnit;
                fifthDayTempMax = jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][4][wxT("high")].AsString() + wxT(" °") + temperatureUnit;
                fifthDayCondition = weatherConditions[wxAtoi(jsonRoot[wxT("query")][wxT("results")][wxT("channel")][wxT("item")][wxT("forecast")][4][wxT("code")].AsString())];

                // decimal fraction character conversion (if necessary)
                wxString decimalFractionChar = _("DEC_FRACTION_DOT"); // the 'identifier' of a decimal fraction character (so it can vary on UI language – dot is default [English])
                if(decimalFractionChar == wxT("DEC_FRACTION_COMMA"))
                {
                    latitude.Replace(wxT("."), wxT(","));
                    longitude.Replace(wxT("."), wxT(","));
                    windSpeed.Replace(wxT("."), wxT(","));
                    pressure.Replace(wxT("."), wxT(","));
                    visibility.Replace(wxT("."), wxT(","));
                }

                locationStatus = _("Data for: ") + location + wxT(" (") + latitude + ' ' + longitude + _("). Last updated: ") + lastBuildDate + '.';

                CurrentTemperatureStaticText->SetLabel(currentTemperature);
                CurrentTemperatureStaticText->Fit();
                CurrentWeatherConditionStaticText->SetLabel(currentCondition);
                CurrentWeatherConditionStaticText->Fit();
                ChillStaticText->SetLabel(wxString::Format(_("Chill: %s"), windChill.c_str()));
                ChillStaticText->Fit();
                DirectionStaticText->SetLabel(wxString::Format(_("Direction: %s"), windDirection.c_str()));
                DirectionStaticText->Fit();
                SpeedStaticText->SetLabel(wxString::Format(_("Speed: %s"), windSpeed.c_str()));
                SpeedStaticText->Fit();
                HumidityStaticText->SetLabel(wxString::Format(_("Humidity: %s"), humidity.c_str()));
                HumidityStaticText->Fit();
                VisibilityStaticText->SetLabel(wxString::Format(_("Visibility: %s"), visibility.c_str()));
                VisibilityStaticText->Fit();
                PressureStaticText->SetLabel(wxString::Format(_("Pressure: %s"), pressure.c_str()));
                PressureStaticText->Fit();
                RisingStaticText->SetLabel(wxString::Format(_("Rising: %s"), rising.c_str()));
                RisingStaticText->Fit();
                SunriseStaticText->SetLabel(wxString::Format(_("Sunrise: %s"), sunrise.c_str()));
                SunriseStaticText->Fit();
                SunsetStaticText->SetLabel(wxString::Format(_("Sunset: %s"), sunset.c_str()));
                SunsetStaticText->Fit();

                TodayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("Today"), todayWeekDay.c_str()));
                TodayStaticText->Fit();
                TomorrowStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("Tomorrow"), tomorrowWeekDay.c_str()));
                TomorrowStaticText->Fit();
                ThirdDayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("3rd Day"), thirdDayWeekDay.c_str()));
                ThirdDayStaticText->Fit();
                FourthDayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("4th Day"), fourthDayWeekDay.c_str()));
                FourthDayStaticText->Fit();
                FifthDayStaticText->SetLabel(wxString::Format(wxT("%s – %s"), _("5th Day"), fifthDayWeekDay.c_str()));
                FifthDayStaticText->Fit();
                CurrentMaxTempStaticText1->SetLabel(todayTempMax);
                CurrentMaxTempStaticText1->Fit();
                CurrentMinTempStaticText1->SetLabel(todayTempMin);
                CurrentMinTempStaticText1->Fit();
                WeatherConditionStaticText1->SetLabel(todayCondition);
                WeatherConditionStaticText1->Fit();
                CurrentMaxTempStaticText2->SetLabel(tomorrowTempMax);
                CurrentMaxTempStaticText2->Fit();
                CurrentMinTempStaticText2->SetLabel(tomorrowTempMin);
                CurrentMinTempStaticText2->Fit();
                WeatherConditionStaticText2->SetLabel(tomorrowCondition);
                WeatherConditionStaticText2->Fit();
                CurrentMaxTempStaticText3->SetLabel(thirdDayTempMax);
                CurrentMaxTempStaticText3->Fit();
                CurrentMinTempStaticText3->SetLabel(thirdDayTempMin);
                CurrentMinTempStaticText3->Fit();
                WeatherConditionStaticText3->SetLabel(thirdDayCondition);
                WeatherConditionStaticText3->Fit();
                CurrentMaxTempStaticText4->SetLabel(fourthDayTempMax);
                CurrentMaxTempStaticText4->Fit();
                CurrentMinTempStaticText4->SetLabel(fourthDayTempMin);
                CurrentMinTempStaticText4->Fit();
                WeatherConditionStaticText4->SetLabel(fourthDayCondition);
                WeatherConditionStaticText4->Fit();
                CurrentMaxTempStaticText5->SetLabel(fifthDayTempMax);
                CurrentMaxTempStaticText5->Fit();
                CurrentMinTempStaticText5->SetLabel(fifthDayTempMin);
                CurrentMinTempStaticText5->Fit();
                WeatherConditionStaticText5->SetLabel(fifthDayCondition);
                WeatherConditionStaticText5->Fit();

                GetSizer()->Fit(this);
                wxSize windowSize = GetBestVirtualSize();
                int bestWidth = windowSize.GetWidth();
                int bestHeight = windowSize.GetHeight();
                SetSize(bestWidth - 1, bestHeight - 1);
                SetSize(bestWidth, bestHeight);
                mainMenu->Enable(idMenuAsFile, true);
                mainMenu->Enable(idMenuToClipboard, true);
            }
            else
                wxMessageBox(_("No data is currently available for the requested location. Please enter another location or try again later."), _("Error"), wxICON_HAND);
        }
        else
            wxMessageBox(_("Could not find the location or any of its counterparts in Yahoo! Weather's database."), _("Error"), wxICON_HAND);
    }

    curl_global_cleanup();
}

wxString Weather95_20Frame::PrintWeatherDetails()
{
    wxString weatherDetails = wxString::Format(wxT("**** Weather 95+20 – %s ****\r\n"), _("WEATHER DETAILS"));
    weatherDetails += wxString::Format(wxT("**** %s ****\r\n"), _("Powered by Yahoo!"));
    weatherDetails += wxString::Format(wxT("\r\n%s %s\r\n"), _("As of:"), lastBuildDate.c_str());
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
    weatherDetails += wxString::Format(_("Chill: %s"), windChill.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Direction: %s"), windDirection.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Speed: %s"), windSpeed.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), AtmosphereStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Humidity: %s"), humidity.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Visibility: %s"), visibility.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Pressure: %s"), pressure.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Rising: %s"), rising.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), AstronomyStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Sunrise: %s"), sunrise.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Sunset: %s"), sunset.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n** %s **\r\n"), _("WEATHER FORECAST"));
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), TodayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), todayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), todayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), todayCondition.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), TomorrowStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), tomorrowTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), tomorrowTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), tomorrowCondition.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), ThirdDayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), thirdDayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), thirdDayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), thirdDayCondition.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), FourthDayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), fourthDayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), fourthDayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), fourthDayCondition.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(wxT("\r\n%s\r\n"), FifthDayStaticText->GetLabel().Upper().c_str());
    weatherDetails += wxString::Format(_("Maximal temperature: %s"), fifthDayTempMax.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Minimal temperature: %s"), fifthDayTempMin.c_str());
    weatherDetails += wxT("\r\n");
    weatherDetails += wxString::Format(_("Condition: %s"), fifthDayCondition.c_str());
    weatherDetails += wxT("\r\n");

    return weatherDetails;
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
            if(wxFileName::GetSize(fileDestinationPath) == 0) // known issue with incompatible diacritics – results in an empty file
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

void Weather95_20Frame::OnCelsius(wxCommandEvent& event)
{
    wxGetApp().userTemperatureUnit = wxT('c');
}

void Weather95_20Frame::OnFahrenheit(wxCommandEvent& event)
{
    wxGetApp().userTemperatureUnit = wxT('f');
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
    wxString *parameters = new wxString[PARAMS_AMOUNT];
    parameters[0] = wxT(FILE_HEADER);
    parameters[1] = wxT(PARAM_1) + wxString::Format(wxT("%d"), wxGetApp().languageID);
    parameters[2] = wxT(PARAM_2) + wxGetApp().userTemperatureUnit.Upper();
    parameters[3] = wxT(PARAM_3) + wxString::Format(wxT("%d"), wxGetApp().user24HourTimeFormat);
    parameters[4] = wxT(PARAM_4) + wxString::Format(wxT("%d"), wxGetApp().userDateFormatVariant);
    parameters[5] = wxT(PARAM_5) + wxString::Format(wxT("%d"), wxGetApp().userUseUTF8);
    ConfigFile *newConfigFile = new ConfigFile();
    newConfigFile->WriteFileContents(parameters);
    wxDELETE(newConfigFile);
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
    StatusBar1->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnSetAndKillFocus(wxFocusEvent& event)
{
    StatusBar1->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnMouseMove(wxMouseEvent& event)
{
    StatusBar1->SetStatusText(locationStatus);
}

void Weather95_20Frame::OnLeftDown(wxMouseEvent& event)
{
    wxMessageBox(locationStatus, _("Location status"));
}

void Weather95_20Frame::OnLogoPanelLeftDown(wxMouseEvent& event)
{
    wxLaunchDefaultBrowser(wxT("https://www.yahoo.com/?ilc=401"));
}
