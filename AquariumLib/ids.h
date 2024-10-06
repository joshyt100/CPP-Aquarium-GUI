/**
* @file ids.h
 * @author Joshua Thomas
 *
 * ID values for our program.
 */

#ifndef AQUARIUM_IDS_H
#define AQUARIUM_IDS_H
/**
 * @enum IDs
 * @brief Enumeration of unique identifiers for menu items.
 *
 * These ID values are used to distinguish between different actions
 * in the program's menu, such as adding specific types of fish to the aquarium.
 */
enum IDs {
    IDM_ADDFISHBETA = wxID_HIGHEST + 1,
    IDM_ADDFISHNEMO,
    IDM_ADDFISHCATFISH,
    IDM_ADDFISHANGEL,
    IDM_ADDFISHCARP,
    IDM_ADDDECORCASTLE,
};

#endif //AQUARIUM_IDS_H