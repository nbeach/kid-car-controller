#ifndef SpeedRamper_h
#define SpeedRamper_h

class SpeedRamper {
    private:
    double decelerationRampingRate;
    int currentSpeed = 0;
    int targetSpeed = 0;
    int timeCurrentSpeedSet = 0;

    public:
    SpeedRamper(double decelerationRampingRate);
    void setTargetSpeed(int speed);
    void setCurrentSpeed(int speed);
    int getCurrentSpeed();
    void setDecelerationRate(double rate);
    void tick();
};

#endif