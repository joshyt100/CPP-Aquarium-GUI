/**
* @file FishBeta.h
 * @author Josh Thomas
 *
 */

#ifndef FISHBETA_H
#define FISHBETA_H

#include "Fish.h"

/**
 * @class FishBeta
 * @brief Class representing a Beta fish in the aquarium.
 */
class FishBeta : public Fish
{
public:
    /// Constructor
    FishBeta(Aquarium* aquarium);

    /**
     * returns type of fish
     * @return wstring
     */
    std::wstring GetType() const override { return L"beta"; }

    /// Load Beta fish from XML
    void XmlLoad(wxXmlNode* node) override;

    /// Update the fish state (movement, direction changes, etc.)
    void Update(double elapsed) override;
};

#endif // FISHBETA_H
