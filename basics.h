#ifndef BASICS_H
#define BASICS_H

typedef double length_t;
typedef double strength_t;
typedef double strength_factor_t;

struct funkcja_liniowa
{
    double a;
    double b;
    explicit funkcja_liniowa(double a = 0, double b = 0) : a(a), b(b) {}
    funkcja_liniowa& operator += (const funkcja_liniowa &f)
    {
        a+=f.a;
        b+=f.b;
        return *this;
    }
    funkcja_liniowa& operator -= (const funkcja_liniowa &f)
    {
        a-=f.a;
        b-=f.b;
        return *this;
    }
    funkcja_liniowa& operator += (const double &d)
    {
        b+=d;
        return *this;
    }
    funkcja_liniowa& operator *= (const double &d)
    {
        a*=d;
        b*=d;
        return *this;
    }
    double operator()(const double &arg) const
    {
        return a*arg + b;
    }
    double arg_for(const double &val) const
    {
        return (val-b)/a;
    }
};

static inline funkcja_liniowa operator + (const funkcja_liniowa &f1, const funkcja_liniowa &f2)
{
    return funkcja_liniowa(f1.a+f2.a, f1.b+f2.b);
}

static inline funkcja_liniowa operator + (const funkcja_liniowa &f1, const double &d)
{
    return funkcja_liniowa(f1.a, f1.b+d);
}

static inline funkcja_liniowa operator + (const double &d, const funkcja_liniowa &f1)
{
    return f1+d;
}

static inline funkcja_liniowa operator * (const funkcja_liniowa &f1, const double &d)
{
    return funkcja_liniowa(f1.a*d, f1.b*d);
}

static inline funkcja_liniowa operator * (const double &d, const funkcja_liniowa &f1)
{
    return f1*d;
}

#endif // BASICS_H
