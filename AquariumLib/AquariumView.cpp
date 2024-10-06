/**
 * @file AquariumView.cpp
 * @author Josh Thomas
 */
#include "pch.h"
#include "AquariumView.h"
#include <wx/dcbuffer.h>
#include "Aquarium.h"
#include "FishBeta.h"
#include "ids.h"
#include <algorithm>
#include "FishCarp.h"
#include "FishCatfish.h"
#include "DecorCastle.h"

using namespace std;

/// Frame duration in milliseconds
const int FrameDuration = 30;

void AquariumView::Initialize(wxFrame* parent)
{
    mTimer.SetOwner(this);
    mTimer.Start(FrameDuration);
    Create(parent, wxID_ANY);
    SetBackgroundStyle(wxBG_STYLE_PAINT);
    Bind(wxEVT_PAINT, &AquariumView::OnPaint, this);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishBetaFish, this, IDM_ADDFISHBETA);
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishCarp, this, IDM_ADDFISHCARP);  // New binding for Carp
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddFishCatFish, this, IDM_ADDFISHCATFISH);  // New binding for Catfish
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnAddDecorCastle, this, IDM_ADDDECORCASTLE);  // Binding for Castle
    parent->Bind(wxEVT_COMMAND_MENU_SELECTED, &AquariumView::OnFileSaveAs, this,wxID_SAVEAS);  // Binding for Castle
    Bind(wxEVT_LEFT_DCLICK, &AquariumView::OnLeftDClick, this); // Bind the double-click event

    Bind(wxEVT_LEFT_DOWN, &AquariumView::OnLeftDown, this);
    Bind(wxEVT_LEFT_UP, &AquariumView::OnLeftUp, this);
    Bind(wxEVT_MOTION, &AquariumView::OnMouseMove, this);
    Bind(wxEVT_TIMER, &AquariumView::OnTimerEvent, this);
    mStopWatch.Start();
}

void AquariumView::OnPaint(wxPaintEvent& event)
{
    // Compute the time that has elapsed
    // since the last call to OnPaint.
    auto newTime = mStopWatch.Time();
    auto elapsed = (double)(newTime - mTime) * 0.001;
    mTime = newTime;
    mAquarium.Update(elapsed);
    wxAutoBufferedPaintDC dc(this);

    wxBrush background(*wxWHITE);
    dc.SetBackground(background);
    dc.Clear();

    mAquarium.OnDraw(&dc);
}

void AquariumView::OnAddFishBetaFish(wxCommandEvent& event)
{
    auto fish = make_shared<FishBeta>(&mAquarium);
    mAquarium.Add(fish);
    Refresh();
}

void AquariumView::OnAddFishCarp(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishCarp>(&mAquarium);  // Create the new carp fish
    mAquarium.Add(fish);  // Add to the aquarium
    Refresh();  // Redraw the view
}

void AquariumView::OnAddFishCatFish(wxCommandEvent& event)
{
    auto fish = std::make_shared<FishCatfish>(&mAquarium);  // Create the new catfish
    mAquarium.Add(fish);  // Add to the aquarium
    Refresh();  // Redraw the view
}
void AquariumView::OnAddDecorCastle(wxCommandEvent& event)
{
    auto castle = std::make_shared<DecorCastle>(&mAquarium);  // Create the new castle
    mAquarium.Add(castle);  // Add to the aquarium
    Refresh();  // Redraw the view
}

void AquariumView::OnFileSaveAs(wxCommandEvent& event)
{
    wxFileDialog saveFileDialog(this, L"Save Aquarium file", L"", L"",
        L"Aquarium Files (*.aqua)|*.aqua", wxFD_SAVE|wxFD_OVERWRITE_PROMPT);
    if (saveFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = saveFileDialog.GetPath();
    mAquarium.Save(filename);
}
void AquariumView::OnFileOpen(wxCommandEvent& event)
{
    wxFileDialog loadFileDialog(this, L"Load Aquarium file", L"", L"",
            L"Aquarium Files (*.aqua)|*.aqua", wxFD_OPEN);
    if (loadFileDialog.ShowModal() == wxID_CANCEL)
    {
        return;
    }

    auto filename = loadFileDialog.GetPath();
    mAquarium.Load(filename);
    Refresh();

}



void AquariumView::OnLeftDown(wxMouseEvent& event)
{
    mGrabbedItem = mAquarium.HitTest(event.GetX(), event.GetY());

    if (mGrabbedItem != nullptr)
    {
        // Move the grabbed item to the end of the list
        mAquarium.MoveToEnd(mGrabbedItem);
    }
}

void AquariumView::OnLeftUp(wxMouseEvent& event)
{
    auto clickedItem = mAquarium.HitTest(event.GetX(), event.GetY());

    if (clickedItem != nullptr) {
        // Use polymorphism to call IsActive and ToggleState
        if (clickedItem->IsActive()) {
            clickedItem->ToggleState();  // Set back to dormant state on single click
            Refresh();  // Redraw the view
        }
    }
}

void AquariumView::OnMouseMove(wxMouseEvent& event)
{
    // See if an item is currently being moved by the mouse
    if (mGrabbedItem != nullptr)
    {
        // If an item is being moved, we only continue to move it while the left button is down.
        if (event.LeftIsDown())
        {
            mGrabbedItem->SetLocation(event.GetX(), event.GetY());
        }
        else
        {
            // When the left button is released, we release the item.
            mGrabbedItem = nullptr;
        }

        // Force the screen to redraw
        Refresh();
    }
}

void AquariumView::OnLeftDClick(wxMouseEvent& event)
{
    auto clickedItem = mAquarium.HitTest(event.GetX(), event.GetY());

    if (clickedItem != nullptr)
    {
        // Call the virtual ToggleState method on the clicked item
        clickedItem->ToggleState();

        // Redraw the view after the state is toggled (if necessary)
        Refresh();  // Ensure the screen refreshes to display the new state
    }
}

void AquariumView::OnTimerEvent(wxTimerEvent& event)
{
    Refresh();
}
