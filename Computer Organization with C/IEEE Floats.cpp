// Name Surname : Emin Salih AÇIKGÖZ
// Student ID   : 22050111032

#include <stdio.h>
#include <limits>

using namespace std;

#define k           8
#define f           23
#define bias        ((1 << (k-1)) - 1)
#define expMask     ((1 << k) - 1)
#define fracMask    ((1 << f) - 1)

struct FloatValue {
private:
    unsigned char signBit;
    unsigned char expValue;
    unsigned int fracValue;

public:
    FloatValue(float value) {
        unsigned int intValue = *(unsigned int*)(&value);
        signBit = (intValue >> (k+f)) & 1;
        expValue = (intValue >> f) & expMask;
        fracValue = intValue & fracMask;
    }

    FloatValue(int sign, int exp, int frac) {
        //We use bitmasks of 1s to ensure that the correct parts get extracted
        signBit = static_cast<unsigned char>(sign & 1);
        expValue = static_cast<unsigned char>(exp & expMask);
        fracValue = static_cast<unsigned int>(frac & fracMask);
    }

    unsigned char getSignBit() {
        return signBit;
    }

    unsigned char getExpValue() {
        return expValue;
    }

    int getE() {
        return expValue - bias;
    }

    unsigned int getFracValue() {
        return fracValue;
    }

    // (a) Zero and (b) Equispaced numbers closest to zero
    // Subnormal values have a exp consisting of all zeros and
    // a fraction that is not all zeros
    // their common point is that they have an exp value of zero
    bool isDenormalized() {
        return expValue == 0;
    }

    bool isZero() {
        return expValue == 0 && fracValue == 0;
    }

    // (a) Infinity or (b) NaN
    bool isSpecial() {
        return isInf() || isNaN();
    }

    bool isInf() {
        // Check if the exponent has all bits set to 1 and the fraction is zero
        return expValue == expMask && fracValue == 0;
    }


    bool isNaN() {
        // Check if the exponent has all bits set to 1 and the fraction is NOT zero
        return expValue == expMask && fracValue != 0;
    }
    

    float value() {
        // Reverse the process by shifting the bits in place and adding them together
        // I tried to directly use the values to obtain a float but precision errors
        // caused the resulting numbers to be completely off from the correct value.
        unsigned int intValue = (signBit << (k+f)) | (expValue << f) | fracValue;

        // Reinterpret intValue as a float. I used reinterpretcast here as I did not 
        // want to create a union to convert the literal bit value into a float
        float value = *reinterpret_cast<float*>(&intValue);

        return value;
    }





};


int main()
{
    // Special
    //struct FloatValue number(-1.0f / 0.0f);
    //struct FloatValue number(1.0f / 0.0f);
    struct FloatValue number(numeric_limits<float>::quiet_NaN());
    //struct FloatValue number(0.0f / 0.0f);
    //struct FloatValue number(-0.0f / 0.0f);

    // Denormalized
    //struct FloatValue number(0.0f);
    //struct FloatValue number(-0.0f);
    //struct FloatValue number(0, 0, 0);
    //struct FloatValue number(0, 0, 0b00000000000000000000001);
    //struct FloatValue number(0, 0, 0b1);

    // Normalized
    //struct FloatValue number(0, 1, 0b0);
    //struct FloatValue number(0, 1, 0b00000000000000000000001);
    //struct FloatValue number(0, 2, 0b00000000000000000000001);
    //struct FloatValue number(15213.0);
    //struct FloatValue number(0, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(-15213.0);
    //struct FloatValue number(1, 13 + bias, 0b11011011011010000000000);
    //struct FloatValue number(15213.239258);
    //struct FloatValue number(-15213.239258);
    //struct FloatValue number(0.239258);
    //struct FloatValue number(3.402823466e38);

    printf("Float Value: %.50f \n", number.value());
    printf("Float Value: %e \n", number.value());
    printf("sign=%d, exp=%d (E=%d), frac=%d \n", number.getSignBit(), number.getExpValue(), number.getE(), number.getFracValue());
    printf("Is Denormalized : %d \t (Is Zero : %d) \n", number.isDenormalized(), number.isZero());
    printf("Is Infinity : %d \t (Is Special : %d) \n", number.isInf(), number.isSpecial());
    printf("Is NaN :  %d \t\t (Is Special : %d) ", number.isNaN(), number.isSpecial());

    return 0;
}
