#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <wx/intl.h>
#include <wx/string.h>
#include <wx/fileconf.h>


class ConfigFile
{
    public:
        ConfigFile();
        void SaveConfiguration();
        void SaveConfiguration(short languageID, wxString temperatureUnit, bool twentyFourHourTimeFormat, short dateFormatVariant, bool useUTF8);
        void LoadConfiguration();
        virtual ~ConfigFile();
        const wxString configFileName = wxT("config.ini");
    protected:
    private:
        wxFileConfig *m_Config;
};

#endif // CONFIGFILE_H
