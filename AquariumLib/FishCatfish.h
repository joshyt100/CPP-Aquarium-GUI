
/**
 * @file FishCatfish.h
 * @author Josh Thomas
 *
 */

#ifndef FISHCATFISH_H
#define FISHCATFISH_H

#include "Fish.h"

/**
 * @class FishCatfish
 * @brief Class representing a Catfish in the aquarium.
 */
class FishCatfish : public Fish
{
public:
    /// Constructor
    FishCatfish(Aquarium* aquarium);
    /**
     *gets type
     * @return wstring type
     */
    std::wstring GetType() const override { return L"catfish"; }

    /// Load Catfish fish from XML
    void XmlLoad(wxXmlNode* node) override;

    /// Update the fish state (movement, direction changes, etc.)
    void Update(double elapsed) override;

private:
    /**
     * member variable for if it is darting
     */
    bool mIsDarting = false;  // Whether the fish is darting or not
    /**
     * member variable for duration
     */
    double mDartDuration = 0.0;  // How long the darting lasts
};

#endif // FISHCATFISH_H
