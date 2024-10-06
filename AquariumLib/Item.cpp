/**
 * @file Item.cpp
 * @author Josh Thomas
 */

#include "pch.h"
#include "Item.h"
#include "Aquarium.h"
using namespace std;

/**
 * Constructor for item
 * @param aquarium
 * @param filename
 */
Item::Item(Aquarium* aquarium, const std::wstring& filename) : mAquarium(aquarium)
{
    mItemImage = std::make_unique<wxImage>(filename, wxBITMAP_TYPE_ANY);
    mFishBitmap = std::make_unique<wxBitmap>(*mItemImage);

    // Create a mirrored image
    wxImage mirroredImage = mItemImage->Mirror();
    mFishBitmapMirror = std::make_unique<wxBitmap>(mirroredImage);
}

void Item::Draw(wxDC* dc)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();
    int x = int(GetX() - wid / 2);
    int y = int(GetY() - hit / 2);

    if (mMirror)
    {
        dc->DrawBitmap(*mFishBitmapMirror, x, y, true);
    }
    else
    {
        dc->DrawBitmap(*mFishBitmap, x, y, true);
    }
}

/**
 * Test to see if we hit this object with a mouse.
 * @param x X position to test
 * @param y Y position to test
 * @return true if hit.
 */
bool Item::HitTest(int x, int y)
{
    double wid = mFishBitmap->GetWidth();
    double hit = mFishBitmap->GetHeight();

    double testX = x - GetX() + wid / 2;
    double testY = y - GetY() + hit / 2;

    if (mMirror)
    {
        testX = wid - testX;
    }

    if (testX < 0 || testY < 0 || testX >= wid || testY >= hit)
    {
        return false;
    }

    return !mItemImage->IsTransparent((int)testX, (int)testY);
}

/**
 * Save this item to an XML node
 * @param node The parent node we are going to be a child of
 * @return wxXmlNode that we saved the item into
 */
wxXmlNode* Item::XmlSave(wxXmlNode* node)
{
    // Create a new node for this item
    auto itemNode = new wxXmlNode(wxXML_ELEMENT_NODE, L"item");

    // Set position attributes
    itemNode->AddAttribute(L"x", wxString::Format(L"%.6f", mX));
    itemNode->AddAttribute(L"y", wxString::Format(L"%.6f", mY));

    // Add the 'type' attribute using GetType() from the derived class
    itemNode->AddAttribute(L"type", GetType()); // Only add 'type' here

    // Attach the node to the parent node
    node->AddChild(itemNode);

    return itemNode;
}

/**
 * Load the attributes for an item node.
 *
 * This is the  base class version that loads the attributes
 * common to all items. Override this to load custom attributes
 * for specific items.
 *
 * @param node The Xml node we are loading the item from
 */
void Item::XmlLoad(wxXmlNode* node)
{
    node->GetAttribute(L"x", L"0").ToDouble(&mX);
    node->GetAttribute(L"y", L"0").ToDouble(&mY);
    wxString typeAttr = node->GetAttribute(L"type", L"unknown");
}

/**
 * Set the mirror status
 * @param m New mirror flag
 */
void Item::SetMirror(bool m)
{
    if (m != mMirror)
    {
        // This code only executes if the mirror state changes
        mMirror = m;
    }
}

/**
 * Destructor
 */
Item::~Item()
{
}
