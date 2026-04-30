#include "Module.h"
#include <iostream>
#include <string>

string Module::showFormatDate(string dd, string mm, string yyyy) {
    return dd + "/" + mm + "/" + yyyy;
}

string Module::showFormatTime(string h, string m, string t) {
    return h + ":" + m + " " + t;
}