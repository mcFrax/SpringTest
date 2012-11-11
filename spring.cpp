#include "spring.h"
#include <cmath>

using namespace std;

static const double len_factor = 1;

spring::spring(length_t opt_len, length_t min_len, length_t min_len_good_looking)
    : opt_len_val(opt_len), min_len_val(min_len), min_len_good_looking_val(min_len_good_looking)
{
    make_steps();
}

const step spring::no_step = step(-INFINITY);

const funkcja_liniowa &spring::func_for(strength_t strength) const
{
    //brutalnie, lepiej sie pewnie nie da
    for (auto i = func_steps_val.begin();; ++i){
        if (i == func_steps_val.end() || i->trigger_strength < strength)
            return (--i)->next_len_func;
    }
}

const step& spring::next_step_after(strength_t strength) const
{
    for (auto i = func_steps_val.begin(); i != func_steps_val.end(); ++i){
        if (i->trigger_strength < strength)
            return *i;
    }
    return no_step;
}


length_t spring::length(strength_t strength) const
{
    return func_for(strength)(strength);
}

void spring::make_steps()
{
    if (min_len_good_looking_val < min_len_val){
        //That's stupid, let make it sane
        min_len_good_looking_val = min_len_val;
    }

    func_steps_val.clear();
    //funkcja_liniowa opt_func(len_factor, opt_len_val);
    funkcja_liniowa opt_func(opt_len_val, opt_len_val);
    func_steps_val.push_back(step(INFINITY, opt_func));

    length_t mgl = min_len_good_looking_val;

    if (opt_len_val < mgl){
        //funkcja_liniowa squeezing_func(len_factor, mgl);
        funkcja_liniowa squeezing_func(opt_len_val, mgl);
        func_steps_val.push_back(step(opt_func.arg_for(mgl), funkcja_liniowa(0, mgl)));
        func_steps_val.push_back(step(0, squeezing_func));

        func_steps_val.push_back(step(squeezing_func.arg_for(min_len_val), funkcja_liniowa(0, min_len_val)));
    } else {
        func_steps_val.push_back(step(opt_func.arg_for(min_len_val), funkcja_liniowa(0, min_len_val)));
    }

    for (unsigned i = 0; i < func_steps_val.size()-1;){
        if (func_steps_val[i].trigger_strength == func_steps_val[i+1].trigger_strength ){
            func_steps_val.erase(func_steps_val.begin()+i);
        } else {
             ++i;
        }
    }

    func_steps_val[0].prev_len_func = funkcja_liniowa();
    for (unsigned i = 1; i < func_steps_val.size(); ++i)
        func_steps_val[i].prev_len_func = func_steps_val[i-1].next_len_func;

}

const length_t &spring::min_len_good_looking() const
{
    return min_len_good_looking_val;
}

void spring::set_min_len_good_looking(const length_t &new_val)
{
    min_len_good_looking_val = new_val;
    make_steps();
}

const length_t &spring::min_len() const
{
    return min_len_val;
}

void spring::set_min_len(const length_t &new_val)
{
    min_len_val = new_val;
    make_steps();
}

const length_t &spring::opt_len() const
{
    return opt_len_val;
}

void spring::set_opt_len(const length_t &new_val)
{
    opt_len_val = new_val;
    make_steps();
}
