/**
 * @file MainFrame.h
 * @author Josh Thomas
 *
 *
 */

#ifndef MAINFRAME_H
#define MAINFRAME_H
/**
 * @class MainFrame
 * @brief The main application window frame.
 *
 * The MainFrame class manages the main window of the application,
 * including the event handling for closing the application and
 * displaying the About dialog.
 */
class MainFrame : public wxFrame
{
private:
    void OnExit(wxCommandEvent& event);
    void OnAbout(wxCommandEvent& event);

public:
    void Initialize();
};


#endif //MAINFRAME_H
