#include <string>

using namespace std;

class ILoggable
{
    public:
        virtual string StringToLog() = 0;
};