#include "SimApp.h"


int main()
{
    MTManager* Manager = new MTManager(100);

    SimApp* app = new SimApp();

    
            if (app->startup(Manager))
            {
                while (!app->shutdownState())
                {
                  app->update(Manager);
                  app->draw();
                }
                app->shutdown();
            }
       

    delete Manager;
    delete app;
    return 0;
}
