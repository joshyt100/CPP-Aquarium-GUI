/**
 * @file Fish.cpp
 * @author Josh Thomas
 */
#include "pch.h"
#include "Fish.h"
#include "Aquarium.h"
#include <random>
#include <iomanip>
/**
 * Constructor
 * @param aquarium The aquarium we are in
 * @param filename Filename for the image we use
 */
/// Maximum speed in the X direction in
/// in pixels per second
const double MaxSpeedX = 50;

/// Minimum speed in the X direction in
/// pixels per second
const double MinSpeedX = 20;
Fish::Fish(Aquarium *aquarium, const std::wstring &filename) :
    Item(aquarium, filename)
{
    std::uniform_real_distribution<> distribution(MinSpeedX, MaxSpeedX);
    mSpeedX = distribution(aquarium->GetRandom());
    mSpeedY = 0;
}

void Fish::SetRandomSpeed(double minSpeed, double maxSpeed)
{
    std::uniform_real_distribution<> distribution(minSpeed, maxSpeed);
    mSpeedX = distribution(GetAquarium()->GetRandom());
    mSpeedY = distribution(GetAquarium()->GetRandom());
}

void Fish::Update(double elapsed)
{
    // Horizontal movement and boundary checking
    double screenWidth = GetAquarium()->GetWidth();
    double fishHalfWidth = GetFishBitmap()->GetWidth() / 2;
    double edgeBuffer = 10;

    if (GetX() - fishHalfWidth < edgeBuffer) { // Check left boundary
        mSpeedX = fabs(mSpeedX); // Ensure speed is positive, moving right
    } else if (GetX() + fishHalfWidth > screenWidth - edgeBuffer) { // Check right boundary
        mSpeedX = -fabs(mSpeedX); // Ensure speed is negative, moving left
    }

    // Vertical movement with natural fluctuation
    double screenHeight = GetAquarium()->GetHeight();
    double fishHalfHeight = GetFishBitmap()->GetHeight() / 2;
    mSpeedY = 10 * sin(GetX() * 0.01); // Sine wave for vertical movement

    // Prevent fish from moving out of the top and bottom of the screen
    if (GetY() - fishHalfHeight < edgeBuffer || GetY() + fishHalfHeight > screenHeight - edgeBuffer) {
        mSpeedY = -mSpeedY; // Reverse vertical direction if hitting top or bottom
    }

    // Update position
    SetLocation(GetX() + mSpeedX * elapsed, GetY() + mSpeedY * elapsed);

    // Mirror image if direction changes
    SetMirror(mSpeedX < 0);
}

wxXmlNode* Fish::XmlSave(wxXmlNode* node)
{
    // Call base class XmlSave to save common attributes like type, x, y
    auto itemNode = Item::XmlSave(node);

    // Save the speed attributes
    itemNode->AddAttribute(L"speedx", wxString::Format(L"%.6f", mSpeedX)); // consistent precision
    itemNode->AddAttribute(L"speedy", wxString::Format(L"%.6f", mSpeedY));

    return itemNode;
}

void Fish::XmlLoad(wxXmlNode* node)
{
    // Load common attributes from Item
    Item::XmlLoad(node);
    double speedX, speedY;
    node->GetAttribute(L"speedx", L"0").ToDouble(&speedX);
    node->GetAttribute(L"speedy",L"0").ToDouble(&speedY);
    SetSpeedX(speedX);
    SetSpeedY(speedY);


}
