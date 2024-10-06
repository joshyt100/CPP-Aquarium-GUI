/**
 * @file Item.h
 * @author Josh Thomas
 *
 *
 */

#ifndef ITEM_H
#define ITEM_H

/**
 * @class Item
 * @brief Represents an item in the aquarium.
 *
 * The Item class is responsible for managing the position of an item within an
 * aquarium. It provides methods to get and set the item's location and manages
 * its association with the aquarium.
 */
class Aquarium;

class Item
{
protected:
    Item(Aquarium* aquarium, const std::wstring& filename);

private:
    /// The underlying fish image
    std::unique_ptr<wxImage> mItemImage;
    /// The mirrored bitmap we can display for this fish
    std::unique_ptr<wxBitmap> mFishBitmapMirror;

    /// The aquarium this item is contained in
    Aquarium* mAquarium;
    /// The bitmap we can display for this fish

    // Item location in the aquarium
    /**
     * member variable for x
     */
    double mX = 0;
    /**
     * member variable for y
     */
    double mY = 0;
    /**
     * member variable for mirror
     */
    bool mMirror = false;
    /**
     * member variable for bitmap
     */
    std::unique_ptr<wxBitmap> mFishBitmap;

public:
    /// Default constructor (disabled)
    Item() = delete;

    /// Copy constructor (disabled)
    Item(const Item&) = delete;

    /// Assignment operator
    void operator=(const Item&) = delete;

    /**
     * Gets aquarium object and makes it callable outside item
     * @return mAquarium object
     */
    /// Get the aquarium this item belongs to
    Aquarium* GetAquarium() { return mAquarium; }
    /**
     * The x location of the item
     * @return x location in pixels
     */
    double GetX() const { return mX; }
    /**
     * gets fishbitmap
     * @return mFishBitmap.get()
     */
    wxBitmap* GetFishBitmap() const { return mFishBitmap.get(); }

    /**
     * The Y location of the item
     * @return Y location in pixels
     */
    double GetY() const { return mY; }


    /**
     * Set the item location
     * @param x X location in pixels
     * @param y Y location in pixels
     */
    void SetLocation(double x, double y)
    {
        mX = x;
        mY = y;
    }


    /**
 * Draw this item
 * @param dc Device context to draw on
 */
    void Draw(wxDC* dc);

    /**
    * @brief Checks if the item is currently active.
    * @return Always returns false, can be overridden in derived classes.
    */
    virtual bool IsActive() const { return false; }
    bool HitTest(int x, int y);

    /**
     * Toggle state whether it is active or not
     */
    virtual void ToggleState()
    {
    }

    /**
     * gets the type
     * @return type
     */
    virtual std::wstring GetType() const = 0;

    virtual wxXmlNode* XmlSave(wxXmlNode* node);
    virtual void XmlLoad(wxXmlNode* node);
    /**
   * Handle updates for animation
   * @param elapsed The time since the last update
   */
    virtual void Update(double elapsed)
    {
    }

    void SetMirror(bool m);
    /**
     * virtual destructor
     */
    virtual ~Item();
};


#endif //ITEM_H
