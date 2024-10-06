/**
* @file Aquarium.cpp
 * @author Joshua Thomas
 *
 *
 */
#include "pch.h"
#include "Aquarium.h"
#include "FishBeta.h"
#include "DecorCastle.h"
#include "FishCatfish.h"
#include "FishCarp.h"
#include <cmath>


using namespace std;

Aquarium::Aquarium()
{
    mBackground = std::make_unique<wxBitmap>(L"images/background1.png", wxBITMAP_TYPE_ANY);
    // We use the constant here to indicate how
    // many rows we want to create
    // Seed the random number generator
    std::random_device rd;
    mRandom.seed(rd());
}

void Aquarium::OnDraw(wxDC* dc)
{
    dc->DrawBitmap(*mBackground, 0, 0);
    for (const auto& item : mItems)
    {
        item->Draw(dc);
    }
}

void Aquarium::Add(std::shared_ptr<Item> item)
{
    mItems.push_back(item);
}

std::shared_ptr<Item> Aquarium::HitTest(int x, int y)
{
    for (auto i = mItems.rbegin(); i != mItems.rend(); ++i)
    {
        if ((*i)->HitTest(x, y))
        {
            return *i;
        }
    }
    return nullptr;
}

void Aquarium::MoveToEnd(std::shared_ptr<Item> item)
{
    auto loc = std::find(mItems.begin(), mItems.end(), item);
    if (loc != mItems.end())
    {
        mItems.erase(loc);
        mItems.push_back(item);
    }
}

void Aquarium::PullFishTowards(Item* magnemo, double distance)
{
    for (const auto& item : mItems)
    {
        if (item.get() != magnemo)
        {
            double dx = item->GetX() - magnemo->GetX();
            double dy = item->GetY() - magnemo->GetY();
            double dist = std::sqrt(dx * dx + dy * dy);

            if (dist > 0)
            {
                double moveDistance = std::min(distance, dist);
                item->SetLocation(item->GetX() - (dx * moveDistance / dist), item->GetY() - (dy * moveDistance / dist));
            }
        }
    }
}

/**
 * Save the aquarium as a .aqua XML file.
 *
 * Open an XML file and stream the aquarium data to it.
 *
 * @param filename The filename of the file to save the aquarium to
 */
void Aquarium::Save(const wxString& filename)
{
    wxXmlDocument xmlDoc;

    auto root = new wxXmlNode(wxXML_ELEMENT_NODE, L"aqua");
    xmlDoc.SetRoot(root);
    // Iterate over all items and save them
    for (auto item : mItems)
    {
        item->XmlSave(root);
    }
    if (!xmlDoc.Save(filename, wxXML_NO_INDENTATION))
    {
        wxMessageBox(L"Write to XML failed");
        return;
    }
}

/**
 * Load the aquarium from a .aqua XML file.
 *
 * Opens the XML file and reads the nodes, creating items as appropriate.
 *
 * @param filename The filename of the file to load the aquarium from.
 */
void Aquarium::Load(const wxString& filename)
{
    wxXmlDocument xmlDoc;
    if (!xmlDoc.Load(filename))
    {
        wxMessageBox(L"Unable to load Aquarium file");
        return;
    }

    Clear();
    // Get the XML document root node
    auto root = xmlDoc.GetRoot();

    //
    // Traverse the children of the root
    // node of the XML document in memory!!!!
    //
    auto child = root->GetChildren();
    for (; child; child = child->GetNext())
    {
        auto name = child->GetName();
        if (name == L"item")
        {
            XmlItem(child);
        }
    }
}

/**
 * Handle a node of type item.
 * @param node XML node
 */
void Aquarium::XmlItem(wxXmlNode* node)
{
    // A pointer for the item we are loading
    shared_ptr<Item> item;

    // We have an item. What type?
    auto type = node->GetAttribute(L"type");
    if (type == L"beta")
    {
        item = make_shared<FishBeta>(this);
    }
    else if (type == L"carp")
    {
        item = make_shared<FishCarp>(this);
    }
    else if (type == L"catfish")
    {
        item = make_shared<FishCatfish>(this);
    }
    else if (type == L"castle")
    {
        item = make_shared<DecorCastle>(this);
    }


    if (item != nullptr)
    {
        Add(item);
        item->XmlLoad(node);
    }
}

/**
 * Clears out mItems
 */
void Aquarium::Clear()
{
    mItems.clear();
}

/**
 * Handle updates for animation
 * @param elapsed The time since the last update
 */
void Aquarium::Update(double elapsed)
{
    for (auto item : mItems)
    {
        item->Update(elapsed);
    }

}
