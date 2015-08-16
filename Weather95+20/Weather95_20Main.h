/***************************************************************
 * Name:      Weather95_20Main.h
 * Purpose:   Defines Application Frame
 * Author:    PeCeT_full (pecetfull@komputermania.pl.eu.org)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.komputermania.pl.eu.org/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef WEATHER95_20MAIN_H
#define WEATHER95_20MAIN_H

#include <wx/clipbrd.h>

//(*Headers(Weather95_20Frame)
#include <wx/sizer.h>
#include <wx/stattext.h>
#include <wx/menu.h>
#include <wx/textctrl.h>
#include <wx/panel.h>
#include <wx/frame.h>
#include <wx/statusbr.h>
//*)

class Weather95_20Frame: public wxFrame
{
    public:

        Weather95_20Frame(wxWindow* parent,wxWindowID id = -1);
        virtual ~Weather95_20Frame();

    private:

        void OnCheck(wxCommandEvent& event);
        wxString PrintWeatherDetails();
        void OnSaveAsFile(wxCommandEvent& event);
        void OnSaveToClipboard(wxCommandEvent& event);
        void OnCelsius(wxCommandEvent& event);
        void OnFahrenheit(wxCommandEvent& event);
        void OnANSI(wxCommandEvent& event);
        void OnUTF8(wxCommandEvent& event);
        void On12HourClock(wxCommandEvent& event);
        void On24HourClock(wxCommandEvent& event);
        void OnYearHyphenMonthHyphenDay(wxCommandEvent& event);
        void OnDayHyphenMonthHyphenYear(wxCommandEvent& event);
        void OnYearHyphenDayHyphenMonth(wxCommandEvent& event);
        void OnMonthHyphenDayHyphenYear(wxCommandEvent& event);
        void OnYearDotMonthDotDay(wxCommandEvent& event);
        void OnDayDotMonthDotYear(wxCommandEvent& event);
        void OnYearDotDayDotMonth(wxCommandEvent& event);
        void OnMonthDotDayDotYear(wxCommandEvent& event);
        void OnYearSlashMonthSlashDay(wxCommandEvent& event);
        void OnDaySlashMonthSlashYear(wxCommandEvent& event);
        void OnYearSlashDaySlashMonth(wxCommandEvent& event);
        void OnMonthSlashDaySlashYear(wxCommandEvent& event);
        void OnSaveSettings(wxCommandEvent& event);
        void OnChangeLanguage(wxCommandEvent& event);
        void OnLeftDown(wxMouseEvent& event);
        void OnLogoPanelLeftDown(wxMouseEvent& event);
        wxMenu *mainMenu;
        wxClipboard *systemClipboard = new wxClipboard();
        wxString locationStatus = _("Please type the location and hit Enter.");

        // header
        wxString city;
        wxString country;
        wxString region;
        wxString location; // "[city_name], [country_name]"
        wxString latitude;
        wxString longitude;
        wxString lastBuildDate;

        // weather units
        wxString temperatureUnit;
        wxString distanceUnit;
        wxString pressureUnit;
        wxString speedUnit;

        // current conditions
        wxString currentTemperature;
        wxString currentCondition;
        wxString windChill;
        wxString windDirection;
        wxString windSpeed;
        wxString humidity;
        wxString pressure;
        wxString rising;
        wxString visibility;

        // astronomy stuff
        wxString sunrise;
        wxString sunset;

        // weather forecast
        wxString todayWeekDay;
        wxString todayTempMin;
        wxString todayTempMax;
        wxString todayCondition;
        wxString tomorrowWeekDay;
        wxString tomorrowTempMin;
        wxString tomorrowTempMax;
        wxString tomorrowCondition;
        wxString thirdDayWeekDay;
        wxString thirdDayTempMin;
        wxString thirdDayTempMax;
        wxString thirdDayCondition;
        wxString fourthDayWeekDay;
        wxString fourthDayTempMin;
        wxString fourthDayTempMax;
        wxString fourthDayCondition;
        wxString fifthDayWeekDay;
        wxString fifthDayTempMin;
        wxString fifthDayTempMax;
        wxString fifthDayCondition;

        //(*Handlers(Weather95_20Frame)
        void OnQuit(wxCommandEvent& event);
        void OnAbout(wxCommandEvent& event);
        void OnKeyUpAndDown(wxKeyEvent& event);
        void OnSetAndKillFocus(wxFocusEvent& event);
        void OnMouseMove(wxMouseEvent& event);
        //*)

        //(*Identifiers(Weather95_20Frame)
        static const long ID_LOCATIONSTATICTEXT;
        static const long ID_LOCATIONTEXTCTRL;
        static const long ID_LOGOPANEL;
        static const long ID_TEMPERATURESTATICTEXT;
        static const long ID_CURRENTTEMPERATURESTATICTEXT;
        static const long ID_CURRENTWEATHERCONDITIONSTATICTEXT;
        static const long ID_WINDSTATICTEXT;
        static const long ID_CHILLSTATICTEXT;
        static const long ID_DIRECTIONSTATICTEXT;
        static const long ID_SPEEDSTATICTEXT;
        static const long ID_ATMOSPHERESTATICTEXT;
        static const long ID_HUMIDITYSTATICTEXT;
        static const long ID_VISIBILITYSTATICTEXT;
        static const long ID_PRESSURESTATICTEXT;
        static const long ID_RISINGSTATICTEXT;
        static const long ID_ASTRONOMYSTATICTEXT;
        static const long ID_SUNRISESTATICTEXT;
        static const long ID_SUNSETSTATICTEXT;
        static const long ID_TODAYSTATICTEXT;
        static const long ID_MAXTEMPSTATICTEXT1;
        static const long ID_CURRENTMAXTEMPSTATICTEXT1;
        static const long ID_MINTEMPSTATICTEXT1;
        static const long ID_CURRENTMINTEMPSTATICTEXT1;
        static const long ID_WEATHERCONDITIONSTATICTEXT1;
        static const long ID_TOMORROWSTATICTEXT;
        static const long IID_MAXTEMPSTATICTEXT2;
        static const long ID_CURRENTMAXTEMPSTATICTEXT2;
        static const long ID_MINTEMPSTATICTEXT2;
        static const long ID_CURRENTMINTEMPSTATICTEXT2;
        static const long ID_WEATHERCONDITIONSTATICTEXT2;
        static const long ID_THIRDDAYSTATICTEXT;
        static const long ID_MAXTEMPSTATICTEXT3;
        static const long ID_CURRENTMAXTEMPSTATICTEXT3;
        static const long ID_MINTEMPSTATICTEXT3;
        static const long ID_CURRENTMINTEMPSTATICTEXT3;
        static const long ID_WEATHERCONDITIONSTATICTEXT3;
        static const long ID_FOURTHDAYSTATICTEXT;
        static const long ID_MAXTEMPSTATICTEXT4;
        static const long ID_CURRENTMAXTEMPSTATICTEXT4;
        static const long ID_MINTEMPSTATICTEXT4;
        static const long ID_CURRENTMINTEMPSTATICTEXT4;
        static const long ID_WEATHERCONDITIONSTATICTEXT4;
        static const long ID_FIFTHTHDAYSTATICTEXT;
        static const long ID_MAXTEMPSTATICTEXT5;
        static const long ID_CURRENTMAXTEMPSTATICTEXT5;
        static const long ID_MINTEMPSTATICTEXT5;
        static const long ID_CURRENTMINTEMPSTATICTEXT5;
        static const long ID_WEATHERCONDITIONSTATICTEXT5;
        static const long idMenuCheck;
        static const long idMenuAsFile;
        static const long idMenuToClipboard;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuCelsius;
        static const long idMenuFahrenheit;
        static const long idMenuTemperatureUnit;
        static const long idMenu12HourClock;
        static const long idMenu24HourClock;
        static const long idMenuTimeFormat;
        static const long idMenuYearHyphenMonthHyphenDay;
        static const long idMenuDayHyphenMonthHyphenYear;
        static const long idMenuYearHyphenDayHyphenMonth;
        static const long idMenuMonthHyphenDayHyphenYear;
        static const long idMenuYearDotMonthDotDay;
        static const long idMenuDayDotMonthDotYear;
        static const long idMenuYearDotDayDotMonth;
        static const long idMenuMonthDotDayDotYear;
        static const long idMenuYearSlashMonthSlashDay;
        static const long idMenuDaySlashMonthSlashYear;
        static const long idMenuYearSlashDaySlashMonth;
        static const long idMenuMonthSlashDaySlashYear;
        static const long idMenuDateFormat;
        static const long idMenuANSI;
        static const long idMenuUTF8;
        static const long idMenuTargetFileEncoding;
        static const long idMenuChangeLanguage;
        static const long idMenuSaveSettings;
        static const long idMenuAbout;
        static const long ID_STATUSBAR1;
        //*)

        //(*Declarations(Weather95_20Frame)
        wxStaticText* MaxTempStaticText5;
        wxStaticText* CurrentMaxTempStaticText1;
        wxMenuItem* MenuItem8;
        wxStaticText* CurrentMaxTempStaticText5;
        wxStaticText* CurrentMinTempStaticText4;
        wxStaticText* DirectionStaticText;
        wxMenuItem* MenuItem26;
        wxStaticText* TomorrowStaticText;
        wxPanel* LogoPanel;
        wxMenuItem* MenuItem25;
        wxStaticText* CurrentMinTempStaticText2;
        wxStaticText* CurrentMaxTempStaticText2;
        wxStaticText* HumidityStaticText;
        wxMenuItem* MenuItem5;
        wxStaticText* CurrentMaxTempStaticText4;
        wxMenu* MenuItem15;
        wxStaticText* CurrentMaxTempStaticText3;
        wxStaticText* AtmosphereStaticText;
        wxMenu* Menu3;
        wxStaticText* WindStaticText;
        wxStaticText* MinTempStaticText3;
        wxMenuItem* MenuItem14;
        wxMenuItem* MenuItem11;
        wxStaticText* MinTempStaticText4;
        wxMenuItem* MenuItem29;
        wxMenu* MenuItem4;
        wxStaticText* CurrentMinTempStaticText3;
        wxMenu* MenuItem10;
        wxMenuItem* MenuItem22;
        wxStaticText* TemperatureStaticText;
        wxMenuItem* MenuItem17;
        wxStaticText* CurrentMinTempStaticText1;
        wxMenuItem* MenuItem13;
        wxStaticText* FifthDayStaticText;
        wxStaticText* MinTempStaticText5;
        wxStaticText* MaxTempStaticText4;
        wxMenu* MenuItem7;
        wxMenuItem* MenuItem12;
        wxMenuItem* MenuItem24;
        wxMenuItem* MenuItem27;
        wxStaticText* SpeedStaticText;
        wxMenuItem* MenuItem3;
        wxMenuItem* MenuItem20;
        wxStaticText* WeatherConditionStaticText2;
        wxMenuItem* MenuItem28;
        wxStaticText* WeatherConditionStaticText3;
        wxStaticText* PressureStaticText;
        wxStaticText* ChillStaticText;
        wxStaticText* WeatherConditionStaticText5;
        wxStatusBar* StatusBar1;
        wxStaticText* MaxTempStaticText3;
        wxMenuItem* MenuItem6;
        wxStaticText* MinTempStaticText2;
        wxMenuItem* MenuItem23;
        wxStaticText* ThirdDayStaticText;
        wxStaticText* RisingStaticText;
        wxStaticText* SunsetStaticText;
        wxStaticText* CurrentWeatherConditionStaticText;
        wxStaticText* CurrentMinTempStaticText5;
        wxStaticText* FourthDayStaticText;
        wxStaticText* VisibilityStaticText;
        wxMenuItem* MenuItem21;
        wxStaticText* CurrentTemperatureStaticText;
        wxStaticText* MaxTempStaticText2;
        wxMenuItem* MenuItem16;
        wxStaticText* MinTempStaticText1;
        wxMenuItem* MenuItem9;
        wxStaticText* LocationStaticText;
        wxMenu* MenuItem18;
        wxStaticText* WeatherConditionStaticText4;
        wxStaticText* SunriseStaticText;
        wxMenuItem* MenuItem30;
        wxStaticText* WeatherConditionStaticText1;
        wxStaticText* TodayStaticText;
        wxStaticText* AstronomyStaticText;
        wxTextCtrl* LocationTextCtrl;
        wxStaticText* MaxTempStaticText1;
        wxMenuItem* MenuItem19;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WEATHER95_20MAIN_H
