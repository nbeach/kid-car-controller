#include <gtest/gtest.h>
#include "../../../kid-car-controller/src/selection/SettingSelector.h"

TEST(SettingSelectorTest, StartsAtTheDefaultIndex) {
    int count = 3;
    int* values = new int[count] { 50, 100, 150 };
    int defaultIndex = 1;
    SettingSelector<int> selector = SettingSelector<int>(values, count, defaultIndex);

    EXPECT_EQ(selector.currentSetting(), 100);
}

TEST(SettingSelectorTest, IncreasesTheSetting) {
    int count = 3;
    int* values = new int[count] { 50, 100, 150 };
    int defaultIndex = 1;
    SettingSelector<int> selector = SettingSelector<int>(values, count, defaultIndex);

    selector.increase();

    EXPECT_EQ(selector.currentSetting(), 150);
}

TEST(SettingSelectorTest, DecreasesTheSetting) {
    int count = 3;
    int* values = new int[count] { 50, 100, 150 };
    int defaultIndex = 1;
    SettingSelector<int> selector = SettingSelector<int>(values, count, defaultIndex);

    selector.decrease();

    EXPECT_EQ(selector.currentSetting(), 50);
}

int newValue;
TEST(SettingSelectorTest, CallsACallbackOnSettingChanges) {
    newValue = -1;
    int count = 3;
    int* values = new int[count] { 50, 100, 150 };
    int defaultIndex = 1;
    SettingSelector<int> selector = SettingSelector<int>(values, count, defaultIndex);

    selector.onChange([](int value) { newValue = value; });
    selector.increase();

    EXPECT_EQ(newValue, 150);
}