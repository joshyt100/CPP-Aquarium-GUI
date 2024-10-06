/**
* @file FishCarp.cpp
 * @author Josh Thomas
 */

#include "FishCarp.h"
#include "Aquarium.h"
#include <cmath> // For sin()
/**
 * @var FishCarpImageName
 * @brief Filename for carp image
 */
const std::wstring FishCarpImageName = L"images/carp.png";

/**
 * FishCarp constructor
 * @param aquarium
 */
FishCarp::FishCarp(Aquarium* aquarium) : Fish(aquarium, FishCarpImageName)
{
    // Set speed for Carp fish, with slower gradual movement
    SetRandomSpeed(70, 190);  // Custom speed range for Carp
}

/**
 * Update function of FishCarp updates to zig zag pattern
 * @param elapsed
 */
void FishCarp::Update(double elapsed)
{
    // Increment time for zig-zag movement
    mZigZagTime += elapsed;

    // Zig-zag properties
    double zigzagAmplitude = GetFishBitmap()->GetHeight();  // Amplitude based on fish size
    double zigzagFrequency = 2.0;   // Speed of the zig-zag movement

    // Compute the new Y position with sinusoidal zig-zag
    double newY = GetY() + zigzagAmplitude * sin(mZigZagTime * zigzagFrequency) * elapsed;

    // Ensure the carp stays within the aquarium's vertical bounds
    double screenHeight = GetAquarium()->GetHeight();
    double fishHalfHeight = GetFishBitmap()->GetHeight() / 2;
    double edgeBuffer = 10;  // Add some buffer to avoid hitting the edges

    // Check the top and bottom boundaries
    if (newY - fishHalfHeight < edgeBuffer)
    {
        newY = edgeBuffer + fishHalfHeight;  // Adjust to avoid going out of bounds
    }
    else if (newY + fishHalfHeight > screenHeight - edgeBuffer)
    {
        newY = screenHeight - fishHalfHeight - edgeBuffer;  // Adjust to avoid going out of bounds
    }

    // Update the location with the new Y and current X position
    SetLocation(GetX(), newY);

    // Call the base class update for horizontal movement, mirroring, etc.
    Fish::Update(elapsed);
}

/**
 * loads xml from fish class
 * @param node
 */
void FishCarp::XmlLoad(wxXmlNode* node)
{
    // Call the base class to load common attributes like position, speed, etc.
    Fish::XmlLoad(node);
}
