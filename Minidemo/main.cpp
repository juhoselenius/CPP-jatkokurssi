#include <iostream>
#include <memory>
#include "Application.h"

const int SCREEN_WIDTH = 480;
const int SCREEN_HEIGHT = 640;

const double DELTA_TIME = 1.0 / 60.0;

/*!
 * \brief main function of Miniprojekti.
 * \param argc number of the commands in argv.
 * \param argv commands from windows OS.
 * \return The application exit code.
 */
int main(int argc, char** argv)
{
    std::unique_ptr<Application> app(new Application(SCREEN_WIDTH, SCREEN_HEIGHT, DELTA_TIME));

    while (!app->m_bQuit)
    {
        app->Loop();

        if (app->m_bRestart)
        {
            app.reset(new Application(SCREEN_WIDTH, SCREEN_HEIGHT, DELTA_TIME));
		}
    }

    return 0;
}