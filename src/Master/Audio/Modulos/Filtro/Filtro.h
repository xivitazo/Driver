#ifndef FILTRO_H
#define FILTRO_H
enum FilterMode {
    FILTER_MODE_LOWPASS = 0,
    FILTER_MODE_HIGHPASS,
    FILTER_MODE_BANDPASS,
    kNumFilterModes
};

class Filter {
public:

    Filter() :
    cutoff(0.99),
    resonance(0.0),
    mode(FILTER_MODE_LOWPASS),
    buf0(0.0),
    buf1(0.0)
    {
        calculateFeedbackAmount();
    };
    double process(double inputValue)
    {
        buf0 += cutoff * (inputValue - buf0);
        buf1 += cutoff * (buf0 - buf1);
        switch (mode) {
            case FILTER_MODE_LOWPASS:
                return buf1;
            case FILTER_MODE_HIGHPASS:
                return inputValue - buf0;
            case FILTER_MODE_BANDPASS:
                return buf0 - buf1;
            default:
                return 0.0;
        }
    }
    inline void setCutoff(double newCutoff) { cutoff = newCutoff; calculateFeedbackAmount(); };
    inline void setResonance(double newResonance) { resonance = newResonance; calculateFeedbackAmount(); };
    inline void setFilterMode(FilterMode newMode) { mode = newMode; }
private:
    double cutoff;
    double resonance;
    FilterMode mode;
    double feedbackAmount;
    inline void calculateFeedbackAmount() { feedbackAmount = resonance + resonance/(1.0 - cutoff); }
    double buf0;
    double buf1;
};

#endif // FILTRO_H
