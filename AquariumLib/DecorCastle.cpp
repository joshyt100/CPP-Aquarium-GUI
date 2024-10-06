/**
 * @file DecorCastle.cpp
 * @author Josh Thomas
 */
#include "pch.h"
#include "DecorCastle.h"
#include "Aquarium.h"
#include <string>
using namespace std;
/**
 * Constructor
 * @param aquarium Aquarium this fish is a member of
 */
/// Fish filename
const wstring DecorCastleImageName = L"images/castle.png";

DecorCastle::DecorCastle(Aquarium* aquarium) : Item(aquarium, DecorCastleImageName)
{
}

void DecorCastle::XmlLoad(wxXmlNode* node)
{
 // Call the base class to load common attributes (x, y)
 Item::XmlLoad(node);
 // If DecorCastle has specific attributes, load them here
}
