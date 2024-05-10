class SpeedLimitSelector {
private:
    int speedLimitCount = 5;
    int speedLimits[5] = { 64, 88, 112, 184, 256 };
    int currentSpeedLimitIndex = 2;

public:
    int increase() {
        if(currentSpeedLimitIndex < (speedLimitCount - 1)) currentSpeedLimitIndex++;
        return currentLimit();
    }

    int decrease() {
        if(currentSpeedLimitIndex > 0) currentSpeedLimitIndex--;
        return currentLimit();
    }

    int currentLimit() {
        return speedLimits[currentSpeedLimitIndex];
    }
};
