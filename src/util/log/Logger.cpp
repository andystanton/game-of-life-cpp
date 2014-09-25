#include "util/log/Logger.hpp"

const string Logger::messageOk = string(" ... \033[1;32mOK\033[0m");
const string Logger::messageFail = string(" ... \033[1;31mFail\033[0m");

const regex Logger::colourPattern = regex("\\\033\\[\\d+\\;?\\d*m");

Logger::Logger(string loggerName, bool noColour)
        : loggerName(loggerName)
        , logEntry()
        , noColour(noColour)
{
}

Logger::~Logger()
{
}

Logger & Logger::operator<<(const string & message)
{
    // If there's nothing in the stringstream yet, prepend with the logger name
    if (logEntry.str().empty())
    {
        logEntry << "[" << loggerName << "] ";
    }

    // Output log message, stripping colours using regex replace if required.
    logEntry << (noColour ? regex_replace(message, colourPattern, string("")) : message);

    return * this;
}

Logger & Logger::operator<<(const LoggerMode mode)
{
    switch (mode)
    {
        case endl:
            cout << logEntry.str() << std::endl;
            logEntry.clear();
            logEntry.str(string(""));
            break;
        case ok:
            * this << messageOk;
            break;
        case fail:
            * this << messageFail;
            break;
        default:
            break;
    }

    return * this;
}

