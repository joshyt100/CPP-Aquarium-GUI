/**
 * @file DecorCastle.h
 * @author Josh Thomas
 *
 *
 */
#include "Item.h"
#ifndef DECORCASTLE_H
#define DECORCASTLE_H
/**
 * @class DecorCastle
 * @author Josh Thomas
 *@brief class for castle
 *
 */


class DecorCastle : public Item
{
    /// Default constructor (disabled)
public:
    DecorCastle() = delete;

    /// Copy constructor (disabled)
    DecorCastle(const DecorCastle&) = delete;

    /// Assignment operator
    void operator=(const DecorCastle&) = delete;
    /**
     * @brief Constructs a FishBeta object with a reference to the aquarium.
     * @param aquarium Pointer to the aquarium that contains the fish.
     */
    DecorCastle(Aquarium* aquarium);
    /**
     *
     * @return L"castle" which is the type assigned to castle
     */
    std::wstring GetType() const override { return L"castle"; }
    /**
     * 
     * @param node
     */
    virtual void XmlLoad(wxXmlNode* node) override;
};


#endif //DECORCASTLE_H
