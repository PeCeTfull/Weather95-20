/***************************************************************
 * Name:      Weather95_20Main.h
 * Purpose:   Defines Application Frame
 * Author:    PeCeT_full (me@pecetfull.pl)
 * Created:   2015-07-19
 * Copyright: PeCeT_full (http://www.pecetfull.pl/)
 * Licence:   The MIT License
 **************************************************************/

#ifndef WEATHER95_20MAIN_H
#define WEATHER95_20MAIN_H

#include "include/wx/jsonreader.h"
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
        void ProcessResultFromWeatherForecastRequestThread(wxJSONValue jsonRoot);
        void ShowErrorMessageFromWeatherForecastRequestThread(wxString errorMessage);

    private:

        void OnCheck(wxCommandEvent& event);
        void OnSaveAsFile(wxCommandEvent& event);
        void OnSaveToClipboard(wxCommandEvent& event);
        void OnImperial(wxCommandEvent& event);
        void OnMetric(wxCommandEvent& event);
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

        void ConvertLastUpdatedDate();
        void DetermineMeasuringUnits();
        void EnableSave();
        void EnsureTimeFormatForSunriseAndSunset();
        void ParseCurrentConditions(wxJSONValue& jsonRoot);
        void ParseLocationDetails(wxJSONValue& jsonRoot);
        void ParseWeatherForecast(wxJSONValue& jsonRoot);
        wxString PrintWeatherDetails();
        void UpdateFrameWithReceivedData();

        wxMenu *fileMenu;
        wxClipboard *systemClipboard = new wxClipboard();
        wxString locationStatus = _("Please type the location and hit Enter.");

        // header
        wxString city;
        wxString country;
        wxString region;
        wxString location; // "[city_name], [country_name]"
        wxString latitude;
        wxString longitude;
        wxString lastUpdated;

        // weather units
        wxString temperatureUnit;
        wxString speedUnit;
        wxString pressureUnit;
        wxString precipitationUnit;
        wxString distanceUnit;

        // current conditions
        wxString currentTemperature;
        wxString currentCondition;
        wxString windDirection;
        wxString windSpeed;
        wxString windGust;
        wxString pressure;
        wxString precipitation;
        wxString humidity;
        wxString cloudCover;
        wxString visibility;
        wxString sunrise;
        wxString sunset;
        wxString moonPhase;
        wxString feelsLike;
        wxString windChill;
        wxString heatIndex;
        wxString dewPoint;
        wxString uvIndex;

        // weather forecast
        wxString todayWeekDay;
        wxString todayTempMin;
        wxString todayTempMax;
        wxString todayCondition;
        wxString todayMaxWind;
        wxString todayChanceOfRain;
        wxString todayChanceOfSnow;
        wxString todayTotalPrecipitation;
        wxString todayTotalSnow;

        wxString tomorrowWeekDay;
        wxString tomorrowTempMin;
        wxString tomorrowTempMax;
        wxString tomorrowCondition;
        wxString tomorrowMaxWind;
        wxString tomorrowChanceOfRain;
        wxString tomorrowChanceOfSnow;
        wxString tomorrowTotalPrecipitation;
        wxString tomorrowTotalSnow;

        wxString thirdDayWeekDay;
        wxString thirdDayTempMin;
        wxString thirdDayTempMax;
        wxString thirdDayCondition;
        wxString thirdDayMaxWind;
        wxString thirdDayChanceOfRain;
        wxString thirdDayChanceOfSnow;
        wxString thirdDayTotalPrecipitation;
        wxString thirdDayTotalSnow;

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
        static const long ID_DIRECTIONSTATICTEXT;
        static const long ID_SPEEDSTATICTEXT;
        static const long ID_GUSTSTATICTEXT;
        static const long ID_ATMOSPHERESTATICTEXT;
        static const long ID_PRESSURESTATICTEXT;
        static const long ID_PRECIPITATIONSTATICTEXT;
        static const long ID_HUMIDITYSTATICTEXT;
        static const long ID_CLOUDCOVERSTATICTEXT;
        static const long ID_VISIBILITYSTATICTEXT;
        static const long ID_ASTRONOMYSTATICTEXT;
        static const long ID_SUNRISESTATICTEXT;
        static const long ID_SUNSETSTATICTEXT;
        static const long ID_MOONPHASESTATICTEXT;
        static const long ID_INDEXSTATICTEXT;
        static const long ID_FEELSLIKESTATICTEXT;
        static const long ID_WINDCHILLSTATICTEXT;
        static const long ID_HEATINDEXSTATICTEXT;
        static const long ID_DEWPOINTSTATICTEXT;
        static const long ID_UVINDEXSTATICTEXT;
        static const long ID_TODAYSTATICTEXT;
        static const long ID_CURRENTMINTEMPSTATICTEXT1;
        static const long ID_DASHSTATICTEXT1;
        static const long ID_CURRENTMAXTEMPSTATICTEXT1;
        static const long ID_WEATHERCONDITIONSTATICTEXT1;
        static const long ID_MAXWINDSTATICTEXT1;
        static const long ID_CHANCEOFRAINSTATICTEXT1;
        static const long ID_CHANCEOFSNOWSTATICTEXT1;
        static const long ID_TOTALPRECIPITATIONSTATICTEXT1;
        static const long ID_TOTALSNOWSTATICTEXT1;
        static const long ID_TOMORROWSTATICTEXT;
        static const long ID_CURRENTMINTEMPSTATICTEXT2;
        static const long ID_DASHSTATICTEXT2;
        static const long ID_CURRENTMAXTEMPSTATICTEXT2;
        static const long ID_WEATHERCONDITIONSTATICTEXT2;
        static const long ID_MAXWINDSTATICTEXT2;
        static const long ID_CHANCEOFRAINSTATICTEXT2;
        static const long ID_CHANCEOFSNOWSTATICTEXT2;
        static const long ID_TOTALPRECIPITATIONSTATICTEXT2;
        static const long ID_TOTALSNOWSTATICTEXT2;
        static const long ID_THIRDDAYSTATICTEXT;
        static const long ID_CURRENTMINTEMPSTATICTEXT3;
        static const long ID_DASHSTATICTEXT3;
        static const long ID_CURRENTMAXTEMPSTATICTEXT3;
        static const long ID_WEATHERCONDITIONSTATICTEXT3;
        static const long ID_MAXWINDSTATICTEXT3;
        static const long ID_CHANCEOFRAINSTATICTEXT3;
        static const long ID_CHANCEOFSNOWSTATICTEXT3;
        static const long ID_TOTALPRECIPITATIONSTATICTEXT3;
        static const long ID_TOTALSNOWSTATICTEXT3;
        static const long idMenuCheck;
        static const long idMenuAsFile;
        static const long idMenuToClipboard;
        static const long idMenuSave;
        static const long idMenuQuit;
        static const long idMenuImperial;
        static const long idMenuMetric;
        static const long idMenuMeasuringUnits;
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
        static const long ID_MAINSTATUSBAR;
        //*)

        //(*Declarations(Weather95_20Frame)
        wxStatusBar* MainStatusBar;
        wxStaticText* CurrentMaxTempStaticText1;
        wxMenu* MeasuringUnitsMenuItem;
        wxStaticText* MaxWindStaticText1;
        wxStaticText* MoonPhaseStaticText;
        wxMenuItem* TwentyFourHourMenuItem;
        wxStaticText* ChanceOfRainStaticText3;
        wxStaticText* DirectionStaticText;
        wxStaticText* TomorrowStaticText;
        wxPanel* LogoPanel;
        wxMenuItem* DateFormat11MenuItem;
        wxMenu* TargetFileEncodingMenuItem;
        wxStaticText* CurrentMinTempStaticText2;
        wxStaticText* PrecipitationStaticText;
        wxStaticText* CurrentMaxTempStaticText2;
        wxStaticText* FeelsLikeStaticText;
        wxStaticText* HumidityStaticText;
        wxStaticText* TotalPrecipitationStaticText3;
        wxStaticText* ChanceOfSnowStaticText3;
        wxStaticText* DewPointStaticText;
        wxStaticText* CurrentMaxTempStaticText3;
        wxStaticText* AtmosphereStaticText;
        wxStaticText* WindStaticText;
        wxMenuItem* UTF8MenuItem;
        wxStaticText* ChanceOfRainStaticText1;
        wxMenuItem* DateFormat6MenuItem;
        wxMenu* OptionsMenu;
        wxStaticText* MaxWindStaticText3;
        wxStaticText* TotalSnowStaticText2;
        wxMenuItem* ANSIMenuItem;
        wxMenuItem* DateFormat9MenuItem;
        wxStaticText* MaxWindStaticText2;
        wxStaticText* ChanceOfRainStaticText2;
        wxStaticText* DashStaticText3;
        wxStaticText* CurrentMinTempStaticText3;
        wxMenuItem* MetricMenuItem;
        wxMenuItem* ImperialMenuItem;
        wxStaticText* TemperatureStaticText;
        wxMenuItem* DateFormat10MenuItem;
        wxStaticText* TotalPrecipitationStaticText1;
        wxStaticText* CurrentMinTempStaticText1;
        wxMenuItem* TwelveHourClockMenuItem;
        wxMenu* DateFormatMenuItem;
        wxStaticText* CloudCoverStaticText;
        wxMenu* TimeFormatMenuItem;
        wxStaticText* TotalSnowStaticText3;
        wxMenuItem* CheckMenuItem;
        wxStaticText* SpeedStaticText;
        wxMenuItem* DateFormat4MenuItem;
        wxStaticText* DashStaticText2;
        wxStaticText* ChanceOfSnowStaticText2;
        wxStaticText* WeatherConditionStaticText2;
        wxMenuItem* DateFormat7MenuItem;
        wxStaticText* WeatherConditionStaticText3;
        wxStaticText* ChanceOfSnowStaticText1;
        wxStaticText* PressureStaticText;
        wxMenuItem* AsFileMenuItem;
        wxStaticText* HeatIndexStaticText;
        wxStaticText* UvIndexStaticText;
        wxMenuItem* ChangeLanguageMenuItem;
        wxMenuItem* ToClipboardMenuItem;
        wxStaticText* GustStaticText;
        wxStaticText* DashStaticText1;
        wxStaticText* TotalSnowStaticText1;
        wxStaticText* ThirdDayStaticText;
        wxMenuItem* DateFormat12MenuItem;
        wxStaticText* SunsetStaticText;
        wxStaticText* CurrentWeatherConditionStaticText;
        wxStaticText* TotalPrecipitationStaticText2;
        wxMenuItem* DateFormat1MenuItem;
        wxStaticText* VisibilityStaticText;
        wxStaticText* CurrentTemperatureStaticText;
        wxMenuItem* DateFormat8MenuItem;
        wxMenuItem* DateFormat2MenuItem;
        wxStaticText* LocationStaticText;
        wxStaticText* SunriseStaticText;
        wxStaticText* WindChillStaticText;
        wxMenuItem* DateFormat5MenuItem;
        wxStaticText* WeatherConditionStaticText1;
        wxStaticText* TodayStaticText;
        wxMenuItem* SaveSettingsMenuItem;
        wxMenuItem* DateFormat3MenuItem;
        wxStaticText* IndexStaticText;
        wxStaticText* AstronomyStaticText;
        wxTextCtrl* LocationTextCtrl;
        wxMenu* SaveMenuItem;
        //*)

        DECLARE_EVENT_TABLE()
};

#endif // WEATHER95_20MAIN_H
