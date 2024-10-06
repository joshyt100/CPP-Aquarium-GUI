/**
 * @file AquariumView.h
 * @author Josh Thomas
 * @brief Header file for the AquariumView class.
 *
 * Defines the AquariumView class that is responsible for rendering the aquarium and handling
 * user interactions using wxWidgets.
 */

#ifndef AQUARIUMVIEW_H
#define AQUARIUMVIEW_H
#include <wx/wx.h>
#include "Aquarium.h"

/**
 * @class AquariumView
 * @brief View class to manage and render the aquarium using wxWidgets.
 *
 * Manages rendering of the aquarium and its components. Handles user interactions such as
 * adding fish and dragging items using wxWidgets' event handling.
 */
class AquariumView : public wxWindow
{
private:
    /**
     * @brief Handles the paint event.
     * @param event wxPaintEvent object for the paint event.
     *
     * Called when the window needs to be repainted. This draws the aquarium's contents.
     */
    void OnPaint(wxPaintEvent& event);

    /// Aquarium object managing the aquarium state.
    Aquarium mAquarium;

    /// Currently grabbed item for dragging.
    std::shared_ptr<Item> mGrabbedItem;
    /// The timer that allows for animation
    wxTimer mTimer;
    /// Stopwatch used to measure elapsed time
    wxStopWatch mStopWatch;

    /// The last stopwatch time
    long mTime = 0;

public:
    /**
     * @brief Initializes the AquariumView.
     * @param parent Parent wxFrame object.
     *
     * Initializes the view and binds the necessary event handlers.
     */
    void Initialize(wxFrame* parent);

    /**
     * @brief Handles adding a Beta Fish to the aquarium.
     * @param event wxCommandEvent object for the event.
     */
    void OnAddFishBetaFish(wxCommandEvent& event);

    /**
     * @brief Handles adding a Carp Fish to the aquarium.
     * @param event wxCommandEvent object for the event.
     */
    void OnAddFishCarp(wxCommandEvent& event);

    /**
     * @brief Handles adding a Catfish to the aquarium.
     * @param event wxCommandEvent object for the event.
     */
    void OnAddFishCatFish(wxCommandEvent& event);
    /**
     * @brief event for adding Decor Castle
     * @param event
     */
    void OnAddDecorCastle(wxCommandEvent& event);
    /**
     * @brief handles event for saving file
     * @param event
     */
    void OnFileSaveAs(wxCommandEvent& event);
    /**
     * @brief handlesevent for file opening
     * @param event
     */
    void OnFileOpen(wxCommandEvent& event);


    /**
     * @brief Handles the left mouse button down event.
     * @param event wxMouseEvent object for the event.
     */
    void OnLeftDown(wxMouseEvent& event);

    /**
     * @brief Handles the left mouse button up event.
     * @param event wxMouseEvent object for the event.
     */
    void OnLeftUp(wxMouseEvent& event);

    /**
     * @brief Handles the mouse move event.
     * @param event wxMouseEvent object for the event.
     */
    void OnMouseMove(wxMouseEvent& event);

    /**
     * @brief Handles the left mouse double-click event.
     * @param event wxMouseEvent object for the event.
     */
    void OnLeftDClick(wxMouseEvent& event);
    /**
     * @brief Handles the timer even
     * @param event wxMouseEvent object for the event.
     */
    void OnTimerEvent(wxTimerEvent& event);
};

#endif // AQUARIUMVIEW_H
