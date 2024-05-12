

class RampingSelector {
    private:
    int rampingRateCount = 5;
    double rampingRates[5] = { 0.0001, 0.0005, 0.001, 0.002, 0.003 };
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
