/**
 * @file AquariumApp.h
 * @author Josh Thomas
 *
 *
 */

#ifndef AQUARIUMAPP_H
#define AQUARIUMAPP_H

#include <wx/wx.h>

/**
 * @class AquariumApp
 * @brief The main application class for the Aquarium application.
 *
 * The AquariumApp class is derived from wxApp and manages the initialization
 * and execution of the Aquarium application. It sets up the necessary application
 * components and handles the main event loop.
 */


class AquariumApp : public wxApp {
public:
 /**
 * @brief Initializes the Aquarium application.
 * @return True if initialization is successful, false otherwise.
 *
 * This method is called when the Aquarium application starts. It initializes
 * the application by setting up the main frame and any necessary resources.
 */
 bool OnInit() override;

};



#endif //AQUARIUMAPP_H
