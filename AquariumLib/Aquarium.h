/**
 * @file Aquarium.h
 * @author Josh Thomas
 * @brief Header file for the Aquarium Class
 *
 */
#ifndef AQUARIUM_H
#define AQUARIUM_H
#include <memory>
#include <random>
#include "Item.h"

/**
 * @class Aquarium
 * @brief Manages the background image and drawing operations for the aquarium.
 *
 * The Aquarium class encapsulates a background image and provides functionality
 * to draw this image onto a device context (wxDC). It uses a unique pointer
 * to manage the lifetime of the background image.
 */

class Aquarium
{
private:
    std::unique_ptr<wxBitmap> mBackground; ///< Background image to use
    std::vector<std::shared_ptr<Item>> mItems; ///< All the items in the aquarium
    void XmlItem(wxXmlNode* node);
    /// Random number generator
    std::mt19937 mRandom;

public:
    Aquarium();

    /**
     * @brief Draws the aquarium's background image onto the device context.
     * @param dc Pointer to the wxDC object where the image will be drawn.
     */
    void OnDraw(wxDC* dc);

    /**
     * @brief Adds a new item to the aquarium.
     * @param item The new item to add.
     */
    void Add(std::shared_ptr<Item> item);

    /**
     * @brief Tests if an x,y position is clicking on an item.
     * @param x The x-coordinate to test.
     * @param y The y-coordinate to test.
     * @returns The item clicked on or nullptr if none.
     */
    std::shared_ptr<Item> HitTest(int x, int y);

    /**
     * @brief Moves an item to the end of the list to bring it to the front when rendered.
     * @param item The item to move to the end.
     */
    void MoveToEnd(std::shared_ptr<Item> item);

    /**
     * @brief Moves other fish towards the given Magnemo fish when active.
     * @param fish The Magnemo fish to move others towards.
     * @param distance The distance to pull other fish.
     */
    void PullFishTowards(Item* fish, double distance);
    void Save(const wxString& filename);
    void Load(const wxString& filename);
    void Clear();
    void Update(double elapsed);
    /**
   * Get the random number generator
   * @return Pointer to the random number generator
   */
    std::mt19937& GetRandom() { return mRandom; }
    /**
    * Get the width of the aquarium
    * @return Aquarium width in pixels
    */
    int GetWidth() const { return mBackground->GetWidth(); }

    /**
     * Get the height of the aquarium
     * @return Aquarium height in pixels
     */
    int GetHeight() const { return mBackground->GetHeight(); }
};

#endif //AQUARIUM_H
