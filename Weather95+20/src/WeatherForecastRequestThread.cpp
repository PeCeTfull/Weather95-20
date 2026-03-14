#include "WeatherForecastRequestThread.h"
#include "../include/curl/curl.h"
#include "../include/wx/jsonreader.h"
#include <wx/url.h>

//helper functions
static size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp)
{
    ((std::string*)userp)->append((char*)contents, size* nmemb);
    return size* nmemb;
}

WeatherForecastRequestThread::WeatherForecastRequestThread(wxString location)
{
    //ctor

    requestedLocation = location;
}

WeatherForecastRequestThread::~WeatherForecastRequestThread()
{
    //dtor

    curl_global_cleanup();

    if(&finalJsonRoot != NULL)
    {
        if(mainFrame != NULL) mainFrame->ProcessResultFromWeatherForecastRequestThread(finalJsonRoot);
    }
    else
    {
        if(mainFrame != NULL) mainFrame->ShowErrorMessageFromWeatherForecastRequestThread(errorMessage);
    }
}

void *WeatherForecastRequestThread::Entry()
{
    CURL *curl;
    CURLcode res;
    std::string readBuffer;

    curl_global_init(CURL_GLOBAL_DEFAULT);

    curl = curl_easy_init();
    if(curl)
    {
        wxString formattedLocation = ParsePhraseForURL(requestedLocation);
        formattedLocation.Replace(wxT(" "), wxT("%20"));

        wxString apiURL = wxT("http://api.weatherapi.com/v1/forecast.json?q=") + formattedLocation + wxT("&days=5&aqi=no&alerts=no&lang=") + _("en") + wxT("&key=") + wxT(API_SERVICE_KEY);
        wxURI apiURI(apiURL);
        wxString encodedApiURL = apiURI.BuildURI();
        std::string apiDest = std::string(encodedApiURL.mb_str(wxConvUTF8));
        curl_easy_setopt(curl, CURLOPT_URL, apiDest.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);

        res = curl_easy_perform(curl);
        if(res != CURLE_OK)
            errorMessage = wxString::Format(_("Could not successfully establish the connection due to the following reason: %s."), wxGetTranslation(wxString::FromUTF8(curl_easy_strerror(res))));
        else
        {
            curl_easy_cleanup(curl);

            wxString apiResult(readBuffer.c_str(), wxConvUTF8);

            wxJSONValue jsonRoot;
            wxJSONReader jsonReader;

            int numErrors = jsonReader.Parse(apiResult, &jsonRoot);
            if(numErrors > 0)
            {
                errorMessage = _("The received data is corrupt. Enter another search phrase or try again later.");
                #if defined(__DEBUG__)
                const wxArrayString& errors = jsonReader.GetErrors();
                errorMessage += wxT("\n\n__DEBUG__: ") + errors[0];
                #endif
            }
            else
                finalJsonRoot = jsonRoot;
        }
    }
}

wxString WeatherForecastRequestThread::ParsePhraseForURL(wxString phrase)
{
    return wxString(phrase.mb_str(wxConvUTF8), wxConvISO8859_1);
}
