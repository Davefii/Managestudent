#include <iostream>
#include "clsloginScreen.h"
using namespace std;
int main()
{
    while (true)
    {
        if (!clsLoginScreen::ShowLoginScreen())
        {
            break;
        }
    }
    return 0;
}