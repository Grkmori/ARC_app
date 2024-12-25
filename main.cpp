
#include <iostream>
#include <exception>
#include <fstream>
#include <csignal>

#include "utilities/utils.hpp"
#include "settings.hpp"
#include "app.hpp"
//#include "utilities/algorithm.hpp"

using namespace std;


int main() {
    //setDPIAware(); // Make the app DPI-aware

    try {
        cout << "\033[1;46mSetting up signal handlers...\033[0m" << endl;
        signal(SIGINT, signalHandler);
        signal(SIGTERM, signalHandler);

        Application app(WINDOWW, WINDOWH, windowTi);
        app.runMain();

        cout << "\033[1;46mApplication terminated normally.\033[0m" << endl;
    } catch (const bad_alloc& e) {
        cerr << "\033[1;41mMemory allocation failed: \033[0m" << e.what() << endl;
        return 1;
    } catch (const exception& e) {
        cerr << "\033[1;41mError: \033[0m" << e.what() << endl;
        return 1;
    } catch (...) {
        cerr << "\033[1;41mUnknown error occurred! \033[0m" << endl;
        return 2;
    }

    return 0;
}
