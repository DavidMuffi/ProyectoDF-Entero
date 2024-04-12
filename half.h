#ifndef HALF_H
#define HALF_H


class half
{
private:
    float floatVal; 

public:

    half() {
        floatVal = 0;
    }

    half(float a) {
        floatVal = a;
    }

    void operator = (half b) {
        floatVal = b.floatVal;
    }

    void operator = (float b) {
        floatVal = b;
    }

    float toFloat() { return floatVal; }

    unsigned short getBitPattern(){
        unsigned int* pt;
        unsigned short sh, s, mant;
        int exp; 
        pt = (unsigned int*)(&floatVal);
        if (*pt == 0)
            return 0;
        s = (*pt) >> 31;
        exp = ((*pt) >> 23) & 0xff; 
        mant = ((*pt) >> 13) & 0x3ff;     // espero que convierta a short al terminar 
        exp = exp + 15 - 127;
        sh = (s << 15) | (exp << 10) | mant; 
        return sh;
    }


    void operator = (unsigned short b) { // convertir un bitstream literal de 16-bits a half

        unsigned int u, s, exp, mant;
        float* f;

        f = (float*)(&u);

        if (b == 0)
            u = 0;
        else {
            s = (b & 0x8000) << 16;
            exp = (b >> 10) & 0x1f;
            exp += (127 - 15);
            exp <<= 23;
            mant = (b & 0x3ff) << 13;
            u = s | exp | mant;
        }
        floatVal = *f; 
    }

    half operator + (half b) {
        half res; 
        res.floatVal = floatVal + b.floatVal; 
        return res; 
    }

    half operator * (half b) {
        half res;
        res.floatVal = floatVal * b.floatVal;
        return res;
    }

    half operator - (half b) {
        half res;
        res.floatVal = floatVal - b.floatVal;
        return res;
    }

    half operator / (half b) {
        half res;
        res.floatVal = floatVal / b.floatVal;
        return res;
    }


    half operator + (float b) {
        half res;
        res.floatVal = floatVal + b;
        return res;
    }

    half operator * (float b) {
        half res;
        res.floatVal = floatVal * b;
        return res;
    }

    half operator - (float b) {
        half res;
        res.floatVal = floatVal - b;
        return res;
    }

    half operator / (float b) {
        half res;
        res.floatVal = floatVal / b;
        return res;
    }





    void operator += (half b) {
        floatVal += b.floatVal;
    }

    void operator *= (half b) {
        floatVal *= b.floatVal;
    }

    void operator -= (half b) {
        floatVal -= b.floatVal;
    }

    void operator /= (half b) {
        floatVal /= b.floatVal;
    }

    

};

#endif // __HALF_H__
