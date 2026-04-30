#include <cstdlib>
#include <string>

int main() {
    std::string title = "AirBlue";
    std::string country = "Pakistan";
    std::string code = "ABL";

    // Build the command to call Python script with arguments
    std::string command = "python createAirlineInfo.py " + title + " " + country + " " + code;

    // Execute the Python script
    system(command.c_str());

    return 0;
}
