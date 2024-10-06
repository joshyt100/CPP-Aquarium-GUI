/**
* @file FishBeta.cpp
 * @author Josh Thomas
 * @brief Implementation of the FishBeta class.
 *
 * This file defines the behavior specific to the FishBeta class. FishBeta is a type of fish in the aquarium
 * with specific behaviors defined herein, particularly how it updates its movement and handles XML loading.
 */

#include "FishBeta.h"
#include "Aquarium.h"

/**
 * Path to the image file used for FishBeta.
 */
const std::wstring FishBetaImageName = L"images/beta.png";

/**
 * Constructs a FishBeta instance with initial settings.
 * @param aquarium The aquarium this FishBeta belongs to.
 */
FishBeta::FishBeta(Aquarium* aquarium) : Fish(aquarium, FishBetaImageName) {
    SetRandomSpeed(50, 75);  // Set horizontal speed in a given range.
}

/**
 * Update the state of FishBeta over time.
 * @param elapsed The time elapsed since the last update call.
 */
void FishBeta::Update(double elapsed) {
 if (rand() % 100 < 5) {
  SetSpeedX(-GetSpeedX());  // Occasionally reverse horizontal direction.
 }

 // Vertical movement constraints
 double screenHeight = GetAquarium()->GetHeight();
 double fishHalfHeight = GetFishBitmap()->GetHeight() / 2;
 double edgeBuffer = 10;  // Distance from the edge of the aquarium

 // Check if the fish is too close to the top or bottom of the aquarium
 if (GetY() - fishHalfHeight < edgeBuffer) {
  SetSpeedY(fabs(GetSpeedY()));  // Ensure speed is positive, moving down
 } else if (GetY() + fishHalfHeight > screenHeight - edgeBuffer) {
  SetSpeedY(-fabs(GetSpeedY()));  // Ensure speed is negative, moving up
 }

 SetLocation(GetX() + GetSpeedX() * elapsed, GetY() + GetSpeedY() * elapsed);

 SetMirror(GetSpeedX() < 0);

 Fish::Update(elapsed);
}

/**
 * Load FishBeta properties from an XML node.
 * @param node XML node containing fish attributes.
 */
void FishBeta::XmlLoad(wxXmlNode* node) {
    Fish::XmlLoad(node);  // Load common fish properties.
}
