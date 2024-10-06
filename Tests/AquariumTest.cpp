/**
 * @file AquariumTest.cpp
 * @author Josh Thomas
 */
#include <pch.h>
#include "gtest/gtest.h"
#include <Aquarium.h>
#include <FishBeta.h>
#include "FishBeta.h"
#include "FishCatfish.h"
#include "FishCarp.h"
#include "DecorCastle.h"
#include <regex>
#include <string>
#include <fstream>
#include <streambuf>
#include <wx/filename.h>

using namespace std;

const unsigned int RandomSeed = 1238197374;

class AquariumTest : public ::testing::Test
{
protected:
    /**
     * Create a path to a place to put temporary files
     */
    wxString TempPath()
    {
        // Create a temporary filename we can use
        auto path = wxFileName::GetTempDir() + L"/aquarium";
        if (!wxFileName::DirExists(path))
        {
            wxFileName::Mkdir(path);
        }

        return path;
    }

    /**
     * Test to ensure an aquarium .aqua file is empty
     */
    void TestEmpty(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;
        ASSERT_TRUE(regex_search(xml, wregex(L"<\\?xml.*\\?>")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
    }

    /**
     * Read a file into a wstring and return it.
     * @param filename Name of the file to read
     * @return File contents
     */
    wstring ReadFile(const wxString& filename)
    {
        ifstream t(filename.ToStdString());
        wstring str((istreambuf_iterator<char>(t)),
                    istreambuf_iterator<char>());

        return str;
    }
    void TestThreeBetas(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure speed attributes are present (adjusting for floating-point values)
        ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"45\\.000000\" speedy=\"15\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"-35\\.000000\" speedy=\"10\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"55\\.000000\" speedy=\"-20\\.000000\"")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"400\\.000000\" y=\"400\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"600\\.000000\" y=\"100\\.000000\"")));
    }
    void PopulateThreeBetas(Aquarium* aquarium)
    {
        // Explicitly set known values for testing
        auto fish1 = make_shared<FishBeta>(aquarium);
        fish1->SetLocation(100, 200);
        fish1->SetSpeedX(45.0);  // Set exact speed values
        fish1->SetSpeedY(15.0);
        aquarium->Add(fish1);

        auto fish2 = make_shared<FishBeta>(aquarium);
        fish2->SetLocation(400, 400);
        fish2->SetSpeedX(-35.0);  // Set exact speed values
        fish2->SetSpeedY(10.0);
        aquarium->Add(fish2);

        auto fish3 = make_shared<FishBeta>(aquarium);
        fish3->SetLocation(600, 100);
        fish3->SetSpeedX(55.0);  // Set exact speed values
        fish3->SetSpeedY(-20.0);
        aquarium->Add(fish3);
    }



    void TestAllTypes(wxString filename)
    {
        cout << "Temp file: " << filename << endl;

        auto xml = ReadFile(filename);
        cout << xml << endl;

        // Ensure all items are present and speeds are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"beta\".*speedx=\"44\\.695000\".*")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"carp\".*speedx=\"33\\.895000\".*")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"catfish\".*speedx=\"22\\.795000\".*")));
        ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"castle\".*</aqua>")));

        // Ensure the positions are correct
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"300\\.000000\" y=\"400\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"500\\.000000\" y=\"600\\.000000\"")));
        ASSERT_TRUE(regex_search(xml, wregex(L"x=\"700\\.000000\" y=\"800\\.000000\"")));
    }

    void PopulateAllTypes(Aquarium* aquarium)
    {
        auto beta = make_shared<FishBeta>(aquarium);
        beta->SetLocation(100, 200);
        beta->SetSpeedX(44.695);  // Known speed value
        beta->SetSpeedY(0.0);
        aquarium->Add(beta);

        auto carp = make_shared<FishCarp>(aquarium);
        carp->SetLocation(300, 400);
        carp->SetSpeedX(33.895);  // Known speed value
        carp->SetSpeedY(0.0);
        aquarium->Add(carp);

        auto catfish = make_shared<FishCatfish>(aquarium);
        catfish->SetLocation(500, 600);
        catfish->SetSpeedX(22.795);  // Known speed value
        catfish->SetSpeedY(0.0);
        aquarium->Add(catfish);

        auto castle = make_shared<DecorCastle>(aquarium);
        castle->SetLocation(700, 800);
        aquarium->Add(castle);
    }
void TestThreeBetasForSave(wxString filename)
{
    cout << "Temp file (Save Test): " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure speed attributes are correct for the save scenario
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"45\\.000000\" speedy=\"15\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"-35\\.000000\" speedy=\"10\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"55\\.000000\" speedy=\"-20\\.000000\"")));

    // Ensure the positions are correct for the save scenario
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"400\\.000000\" y=\"400\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"600\\.000000\" y=\"100\\.000000\"")));
}

void TestThreeBetasForLoad(wxString filename)
{
    cout << "Temp file (Load Test): " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure speed attributes are correct for the load scenario
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"45\\.000000\" speedy=\"15\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"-35\\.000000\" speedy=\"10\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"speedx=\"55\\.000000\" speedy=\"-20\\.000000\"")));

    // Ensure the positions are correct for the load scenario
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"400\\.000000\" y=\"400\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"600\\.000000\" y=\"100\\.000000\"")));
}

void TestAllTypesForSave(wxString filename)
{
    cout << "Temp file (Save Test): " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure all items are present and speeds are correct for the save test
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"beta\".*speedx=\"44\\.695000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"carp\".*speedx=\"33\\.895000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"catfish\".*speedx=\"22\\.795000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"castle\".*</aqua>")));

    // Ensure the positions are correct for the save test
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"300\\.000000\" y=\"400\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"500\\.000000\" y=\"600\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"700\\.000000\" y=\"800\\.000000\"")));
}

void TestAllTypesForLoad(wxString filename)
{
    cout << "Temp file (Load Test): " << filename << endl;

    auto xml = ReadFile(filename);
    cout << xml << endl;

    // Ensure all items are present and speeds are correct for the load test
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"beta\".*speedx=\"44\\.695000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"carp\".*speedx=\"33\\.895000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"catfish\".*speedx=\"22\\.795000\".*")));
    ASSERT_TRUE(regex_search(xml, wregex(L"<item.*type=\"castle\".*</aqua>")));

    // Ensure the positions are correct for the load test
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"100\\.000000\" y=\"200\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"300\\.000000\" y=\"400\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"500\\.000000\" y=\"600\\.000000\"")));
    ASSERT_TRUE(regex_search(xml, wregex(L"x=\"700\\.000000\" y=\"800\\.000000\"")));
}






};

TEST_F(AquariumTest, Construct)
{
    Aquarium aquarium;
}

TEST_F(AquariumTest, HitTest)
{
    Aquarium aquarium;

    ASSERT_EQ(aquarium.HitTest(100, 200), nullptr) << L"Testing empty aquarium";

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish1) << L"Testing fish at 100, 200";
}

TEST(FishBetaTest, HitTestWithOverlappingFish)
{
    Aquarium aquarium;

    shared_ptr<FishBeta> fish1 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish1);
    fish1->SetLocation(100, 200);

    shared_ptr<FishBeta> fish2 = make_shared<FishBeta>(&aquarium);
    aquarium.Add(fish2);
    fish2->SetLocation(100, 200); // Same location as fish1

    // fish2 is added last, so it should be on top
    ASSERT_TRUE(aquarium.HitTest(100, 200) == fish2) << L"Testing overlapping fish at 100, 200";
}

TEST_F(AquariumTest, Save)
{
    // Create a path to temporary files
    auto path = TempPath();

    // Create an aquarium
    Aquarium aquarium;

    //
    // First test, saving an empty aquarium
    //
    auto file1 = path + L"/test1.aqua";
    aquarium.Save(file1);

    TestEmpty(file1);

    //
    // Now populate the aquarium
    //
    PopulateThreeBetas(&aquarium);

    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);

    TestThreeBetas(file2);

    PopulateAllTypes(&aquarium);

    auto file3 = path + L"/test3.aqua";
    aquarium.Save(file3);

    TestAllTypes(file3);
}

TEST_F(AquariumTest, Clear)
{
    Aquarium aquarium;

    // Populate the aquarium with items
    PopulateThreeBetas(&aquarium);

    // Ensure items are present before clearing
    auto fileBeforeClear = TempPath() + L"/test_before_clear.aqua";
    aquarium.Save(fileBeforeClear);
    TestThreeBetas(fileBeforeClear);

    // Clear the aquarium
    aquarium.Clear();

    // Save and test the file after clearing
    auto fileAfterClear = TempPath() + L"/test_after_clear.aqua";
    aquarium.Save(fileAfterClear);

    auto xml = ReadFile(fileAfterClear);
    cout << xml << endl;
    ASSERT_TRUE(regex_search(xml, wregex(L"<aqua/>")));
}

// TEST_F(AquariumTest, Load)
// {
//     // Create a path to temporary files
//     auto path = TempPath();
//
//     // First, test saving and loading the aquarium with Three Betas
//     Aquarium aquarium;
//     PopulateThreeBetas(&aquarium);  // Use Populate to set up the initial save state
//
//     auto file2 = path + L"/test2.aqua";
//     aquarium.Save(file2);
//     TestThreeBetas(file2);  // Test the save output
//
//     // Now load the saved file into aquarium2
//     Aquarium aquarium2;
//     aquarium2.Load(file2);  // Load the previously saved file
//
//     // Re-test to ensure consistency after load
//     CheckLoadedThreeBetas(&aquarium2);  // Ensure the fish are loaded correctly
//
//     // Now test saving and loading with all types of items
//     Aquarium aquarium3;
//     PopulateAllTypesForSave(&aquarium3);  // Set up the save state
//
//     auto file3 = path + L"/test3.aqua";
//     aquarium3.Save(file3);
//     TestAllTypesForSave(file3);  // Test the save output
//
//     // Load and re-test for consistency
//     aquarium3.Load(file3);
//     CheckLoadedAllTypes(&aquarium3);  // Ensure all types are loaded correctly
// }
TEST_F(AquariumTest, Load)
{
    auto path = TempPath();

    // First, test loading and saving three betas
    Aquarium aquarium;
    PopulateThreeBetas(&aquarium);  // Populate and save first
    auto file2 = path + L"/test2.aqua";
    aquarium.Save(file2);
    TestThreeBetasForSave(file2);  // Test after save

    // Load and re-test to ensure consistency
    Aquarium aquarium2;
    aquarium2.Load(file2);
    aquarium2.Save(file2);
    TestThreeBetasForLoad(file2);  // Test after load

    // Now, test saving and loading all types
    Aquarium aquarium3;
    PopulateAllTypes(&aquarium3);  // Populate and save first
    auto file3 = path + L"/test3.aqua";
    aquarium3.Save(file3);
    TestAllTypesForSave(file3);  // Test after save

    // Load and re-test to ensure consistency
    aquarium3.Load(file3);
    aquarium3.Save(file3);
    TestAllTypesForLoad(file3);  // Test after load
}

