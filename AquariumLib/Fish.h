/**
 * @file Fish.h
 * @author Josh Thomas
 *
 *
 */

#ifndef FISH_H
#define FISH_H

#include "Item.h"

/**
 * @class Fish
 * @brief Fish class inherits from Item class and extends
 * functionality
 */
class Fish : public Item
{
protected:
    /**
     *protected constructor for fish
     * @param aquarium
     * @param filename
     */
    Fish(Aquarium* aquarium, const std::wstring& filename);

private:
    /// Fish speed in the X direction
    /// in pixels per second
    double mSpeedX;

    /// Fish speed in the Y direction
    /// in pixels per second
    double mSpeedY;

public:
    // Getters and Setters for Speed
    /**
     * sets the random speed
     * @param minSpeed
     * @param maxSpeed

     */

    void SetRandomSpeed(double minSpeed, double maxSpeed);
    /**
     * gets speed of x
     * @return mSpeedX
     */
    double GetSpeedX() const { return mSpeedX; }
    /**
     * gets speed of y
     * @return speed of y
     */
    double GetSpeedY() const { return mSpeedY; }
    /**
     * sets speed of x
     * @param speedX
     */
    void SetSpeedX(double speedX) { mSpeedX = speedX; }
    /**
     * sets speed of y
     * @param speedY
     */
    void SetSpeedY(double speedY) { mSpeedY = speedY; }
    /// Default constructor (disabled)
    Fish() = delete;

    /// Copy constructor (disabled)
    Fish(const Fish&) = delete;

    /// Assignment operator
    void operator=(const Fish&) = delete;
    /**
     * updates position
     * @param elapsed
     */
    void Update(double elapsed) override;
    /**
     * saves xml
     * @param node
     * @return
     */
    wxXmlNode* XmlSave(wxXmlNode* node) override;
    /**
     * Loads xml
     * @param node
     */
    void XmlLoad(wxXmlNode* node) override;
};


#endif //FISH_H
