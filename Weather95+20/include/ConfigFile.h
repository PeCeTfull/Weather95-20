#ifndef CONFIGFILE_H
#define CONFIGFILE_H

#include <wx/string.h>

#define PARAMS_AMOUNT 6 // 5 + 1 for the header
#define FILE_HEADER "[Weather 95+20]"
#define PARAM_1 "LanguageID=" // default value is wxLANGUAGE_ENGLISH_CANADA
#define PARAM_2 "TemperatureUnit="
#define PARAM_2_DEFAULT_VALUE "C"
#define PARAM_3 "24HourTimeFormat="
#define PARAM_3_DEFAULT_VALUE 1
#define PARAM_4 "DateFormatVariant="
#define PARAM_4_DEFAULT_VALUE 1
#define PARAM_5 "UseUTF8="
#define PARAM_5_DEFAULT_VALUE 0


class ConfigFile
{
    public:
        ConfigFile();
        wxString *ReadFileContents();
        void NewFileContents();
        void WriteFileContents(wxString* paramTable);
        virtual ~ConfigFile();
        const wxString configFileName = wxT("config.ini");
    protected:
    private:
        void SaveFile(wxString& params);
};

#endif // CONFIGFILE_H
