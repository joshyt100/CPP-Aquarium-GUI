
/**
 * @file FishCatfish.cpp
 * @author Josh Thomas
 */

#include "FishCatfish.h"
#include "Aquarium.h"
#include <cstdlib> // for rand()
#include <cmath>   // for fabs()

/**
 * @var FishCatfishImageName
 * @brief varible for catfish image
 */
const std::wstring FishCatfishImageName = L"images/catfish.png";

/**
 * fishcatfish constructor
 * @param aquarium
 */
FishCatfish::FishCatfish(Aquarium* aquarium) : Fish(aquarium, FishCatfishImageName)
{
    // Set initial speed for Catfish, generally faster than Carp
    SetRandomSpeed(20.0, 35.0);
}

/**
 * Update function for movement
 * @param elapsed
 */
void FishCatfish::Update(double elapsed)
{
    // Occasionally, the fish will dart quickly for a short time
    if (!mIsDarting && rand() % 100 < 3)  // 3% chance to start darting
    {
        mIsDarting = true;
        mDartDuration = 0.5;  // Dart for half a second
        SetSpeedX(GetSpeedX() * 2.0);  // Double the speed for the dart
    }

    // If the fish is darting, decrement the dart duration
    if (mIsDarting)
    {
        mDartDuration -= elapsed;
        if (mDartDuration <= 0)
        {
            // Darting is finished, slow back down
            mIsDarting = false;
            SetSpeedX(GetSpeedX() / 2.0);  // Return to normal speed
        }
    }

    // Boundary check: prevent the fish from going out of the top or bottom of the screen
    double screenHeight = GetAquarium()->GetHeight();
    double fishHalfHeight = GetFishBitmap()->GetHeight() / 2;
    double edgeBuffer = 10;  // Allow a buffer from the edge

    double newY = GetY();  // Get the current Y position

    // Ensure the fish stays within vertical bounds
    if (newY - fishHalfHeight < edgeBuffer)
    {
        newY = edgeBuffer + fishHalfHeight;  // Correct to avoid going out of bounds at the top
        SetSpeedY(fabs(GetSpeedY()));  // Reverse direction if necessary
    }
    else if (newY + fishHalfHeight > screenHeight - edgeBuffer)
    {
        newY = screenHeight - fishHalfHeight - edgeBuffer;  // Correct to avoid going out of bounds at the bottom
        SetSpeedY(-fabs(GetSpeedY()));  // Reverse direction if necessary
    }

    // Update the Y position after boundary checks
    SetLocation(GetX(), newY);

    // Call the base class update for general movement
    Fish::Update(elapsed);
}

/**
 * Loads xml from fish class
 * @param node
 */
void FishCatfish::XmlLoad(wxXmlNode* node)
{
    Fish::XmlLoad(node);  // Call the base class to load common attributes
}
