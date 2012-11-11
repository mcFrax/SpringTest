#ifndef SPRING_SOLVING_H
#define SPRING_SOLVING_H

#include <set>
#include <cmath>
#include "spring.h"

struct event_t
{
    ::step step;
    const ::spring& spring;
    event_t(const ::step& step, const ::spring& spring)
        : step(step), spring(spring)
    {
    }
    bool operator < (const event_t& e) const
    {
        if (step.trigger_strength != e.step.trigger_strength)
            return step.trigger_strength > e.step.trigger_strength;
        return &(spring) < &(e.spring);
    }
};

template <class SpringList>
strength_t solve_internal(const SpringList& springs, length_t desired_len)
{
    std::set<event_t> event_queue;
    strength_t strength = INFINITY;

    funkcja_liniowa summary_len;

    for (auto i = springs.begin(); i != springs.end(); ++i){
        event_queue.insert(event_t(i->next_step_after(strength), *i));
        summary_len += i->func_for(strength);
    }

    while (!event_queue.empty() && event_queue.begin()->step.trigger_strength > -INFINITY){
        if (summary_len(event_queue.begin()->step.trigger_strength) <= desired_len){
            strength = summary_len.arg_for(desired_len);
            break;
        }
        spring event_trigger = event_queue.begin()->spring;

        summary_len -= event_trigger.func_for(strength);
        strength = event_queue.begin()->step.trigger_strength;

        summary_len += event_trigger.func_for(strength);
        event_queue.erase(event_queue.begin());
        event_queue.insert(event_t(event_trigger.next_step_after(strength), event_trigger));
    }

    return strength;
}

template <class SpringList>
std::vector<length_t> solve(const SpringList& springs_arg, length_t desired_len)
{
    SpringList springs = springs_arg;

    strength_t strength = solve_internal(/*columns, */springs, desired_len);

    std::vector<length_t> result;

    for (auto i = springs.begin(); i != springs.end(); ++i){
        result.push_back(i->length(strength));
    }

    return result;
}

#endif // SPRING_SOLVING_H
