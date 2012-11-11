#ifndef SPRING_H
#define SPRING_H

#include <list>
#include <cmath>
#include "basics.h"

struct step
{
    strength_t trigger_strength;
    funkcja_liniowa next_len_func;
    step(strength_t trigger_strength, funkcja_liniowa next_len_func = funkcja_liniowa())
        : trigger_strength(trigger_strength),
          next_len_func(next_len_func)
    {
    }
};

typedef std::list<step> step_list_t;

class spring
{
private:
    length_t opt_len_val;
    length_t min_len_val;
    length_t min_len_good_looking_val;
    step_list_t func_steps_val;
    void make_steps();
    static const step no_step;
public:
    spring(length_t opt_len = 0, length_t min_len = 0, length_t min_len_good_looking = -INFINITY);
    length_t length(strength_t strength) const; //inefficient, & that ain't gonna change
    strength_t strength(length_t length) const; //even more inefficient, & that ain't gonna change too
    strength_factor_t strength_factor(length_t length) const;
    //const step& next_step(strength_t strength);
    //const step& next_step(length_t length);
    const step& next_step_after(strength_t strength);
    //const step& next_step_after(length_t length);
    const step_list_t& func_steps() const;
    const funkcja_liniowa& func_for(strength_t strength) const;

    const length_t& min_len_good_looking() const;
    void set_min_len_good_looking(const length_t& new_val);
    const length_t& min_len() const;
    void set_min_len(const length_t& new_val);
    const length_t& opt_len() const;
    void set_opt_len(const length_t& new_val);
};

#endif // SPRING_H
