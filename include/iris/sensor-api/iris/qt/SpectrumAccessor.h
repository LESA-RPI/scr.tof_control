#ifndef SPECTRUMACCESSOR_H
#define SPECTRUMACCESSOR_H

namespace iris {

namespace qt {

typedef unsigned char (*spectrumPtr)[4096][3];
typedef unsigned char (*spectrumRgbPtr)[3];

class SpectrumAccessor
{
public:
    explicit SpectrumAccessor(spectrumPtr);
    ~SpectrumAccessor();
    
    void setSpectrumPointer(spectrumPtr);
    
    /*
     * Defines a non-linear curve
     * \param thresholdIndex defines the x-value where curve starts to become nonlinear
     * \param maxY defines the asymptote of the nonlinear curve
     */
    void setCurve(unsigned int thresholdIndex, unsigned int duration, unsigned int maxY);
    
    void setSlope(unsigned int thresholdIndex, unsigned int duration, unsigned int maxY);
    
    unsigned int getConversionTableValue(unsigned int index) const;
    
    spectrumRgbPtr getLinear(unsigned int x);
    spectrumRgbPtr getNonlinear(unsigned int x);
    
private:
    spectrumPtr m_spectrumPtr;
    int m_thresholdNonlinear;
    int m_maxY;
    int m_conversionTable[4096];// holds lookup-table for index conversion
    
    void setLinearConversion();
};

}

}

#endif // SPECTRUMACCESSOR_H
