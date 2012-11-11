#ifndef SPRING_SOLVING_H
#define SPRING_SOLVING_H

#include <set>
#include <cmath>
#include <iostream>
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
    std::cerr << "\n\nsolve_internal()\n";
    std::set<event_t> event_queue;
    strength_t strength = INFINITY;

    funkcja_liniowa summary_len;

    for (auto i = springs.begin(); i != springs.end(); ++i){
        event_queue.insert(event_t(i->next_step_after(strength), *i));
        summary_len += i->func_for(strength);
    }

    while (!event_queue.empty() && event_queue.begin()->step.trigger_strength > -INFINITY){
        std::cerr << "plof " << summary_len(event_queue.begin()->step.trigger_strength) << '\n';
        if (summary_len(event_queue.begin()->step.trigger_strength) <= desired_len){
            strength = summary_len.arg_for(desired_len);
            std::cerr << "breaking: " << desired_len << ' ' << summary_len(event_queue.begin()->step.trigger_strength)
                      << ' ' << event_queue.begin()->step.trigger_strength << ' ' << strength << ' ' << summary_len.a
                      << ',' << summary_len.b << '\n';
            break;
        }
        const spring& event_trigger = event_queue.begin()->spring;

        int spring_num = -1;
        int iii = 0;
        for (auto i = springs.begin(); i != springs.end(); ++i){
            if (&(*i) == &(event_queue.begin()->spring)) spring_num = iii;
            ++iii;
        }

        summary_len -= event_queue.begin()->step.prev_len_func;
        strength = event_queue.begin()->step.trigger_strength;

//        std::cerr << "summary_len["<< summary_len.a <<", "<< summary_len.b <<"] += event_trigger.func_for("<<strength<<")["
//                  << event_trigger.func_for(strength).a <<", "<< event_trigger.func_for(strength).b <<"];\n";
        summary_len += event_queue.begin()->step.next_len_func;
        event_queue.erase(event_queue.begin());
        event_queue.insert(event_t(event_trigger.next_step_after(strength), event_trigger));
    }

    return strength;
}

template <class SpringList>
std::vector<length_t> solve(const SpringList& springs_arg, length_t desired_len, strength_t *used_strength = 0)
{
    SpringList springs = springs_arg;

    strength_t strength = solve_internal(/*columns, */springs, desired_len);

    std::vector<length_t> result;

    for (auto i = springs.begin(); i != springs.end(); ++i){
        result.push_back(i->length(strength));
    }

    if (used_strength) *used_strength = strength;

    return result;
}

#endif // SPRING_SOLVING_H
