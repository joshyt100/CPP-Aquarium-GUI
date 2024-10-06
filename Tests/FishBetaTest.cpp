
/**
 * @file FishBetaTest.cpp
 * @author Josh Thomas
 */
#include <pch.h>
#include <gtest/gtest.h>
#include <Aquarium.h>
#include <FishBeta.h>

using namespace std;


TEST(FishBetaTest, HitTestNoImage) {
    Aquarium aquarium;

    // Testing a point where no fish is located
    ASSERT_EQ(aquarium.HitTest(344, 300), nullptr) <<
        L"Testing point with no image";
}