#include "../Application/SimApp/SimApp.h"



int main()
{
    MTManager& Manager = MTManager::getInstance();
    MTLogger& Logger = Manager.GetLogger();

    SimApp* app = new SimApp();

    
            if (app->startup())
            {
                while (!app->shutdownState())
                {
                  app->update();
                  app->draw();
                }
                app->shutdown();
            }
       

    delete app;
    return 0;
}
