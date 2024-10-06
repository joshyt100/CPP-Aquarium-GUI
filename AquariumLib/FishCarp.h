
/**
 * @file FishCarp.h
 * @author Josh Thomas
 *
 */

#ifndef FISHCARP_H
#define FISHCARP_H

#include "Fish.h"

/**
 * @class FishCarp
 * @brief Class representing a Carp in the aquarium.
 */
class FishCarp : public Fish
{
public:
    /// Constructor
    FishCarp(Aquarium* aquarium);

    /**
     * type getter for fish
     * @return wstring with type
     */
    std::wstring GetType() const override { return L"carp"; }

    /// Load Carp fish from XML
    void XmlLoad(wxXmlNode* node) override;

    /// Update the fish state (movement, direction changes, etc.)
    void Update(double elapsed) override;

private:
    /**
     * double for zigzag time
     */
    double mZigZagTime = 0.0;  // Keeps track of the zig-zag timing
};

#endif // FISHCARP_H
