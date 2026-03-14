#ifndef WEATHERFORECASTREQUESTTHREAD_H
#define WEATHERFORECASTREQUESTTHREAD_H

#include "../Weather95_20App.h"
#include "../Weather95_20Main.h"
#include <wx/thread.h>
#include <wx/txtstrm.h>

class WeatherForecastRequestThread: public wxThread
{
    public:
        WeatherForecastRequestThread(wxString location);
        virtual ~WeatherForecastRequestThread();
        void *Entry();
        Weather95_20Frame *mainFrame;
    protected:
    private:
        wxString ParsePhraseForURL(wxString phrase);
        wxString requestedLocation = wxT("");
        wxJSONValue finalJsonRoot = NULL;
        wxString errorMessage = wxT("");
};

#endif // WEATHERFORECASTREQUESTTHREAD_H
