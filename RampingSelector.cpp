class RampingSelector {
    private:
    int rampingRateCount = 5;
    double rampingRates[5] = { 0.25, 0.375, 0.5, 1.0, 256.0 };
    int currentRampingRateIndex = 2;

    public:
    double increase() {
        if(currentRampingRateIndex < (rampingRateCount - 1)) currentRampingRateIndex++;
        return currentRate();
    }

    double decrease() {
        if(currentRampingRateIndex > 0) currentRampingRateIndex--;
        return currentRate();
    }
    
    double currentRate() {
        return rampingRates[currentRampingRateIndex];
    }
};
