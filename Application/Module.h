#ifndef MODULE_H
#define MODULE_H

#include <string>
#include <windows.h>

class Module {
public:
    virtual void create() = 0;
    virtual void readByID() = 0;
    virtual void display() = 0;

    // Format date as "dd/mm/yyyy"
    std::string showFormatDate(const std::string& dd, const std::string& mm, const std::string& yyyy) {
        return dd + "/" + mm + "/" + yyyy;
    }

    // Format time as "hh:mm t" (t = AM/PM)
    std::string showFormatTime(const std::string& h, const std::string& m, const std::string& t) {
        return h + ":" + m + " " + t;
    }

    virtual ~Module() = default;  // Always good to have a virtual destructor
};

#endif