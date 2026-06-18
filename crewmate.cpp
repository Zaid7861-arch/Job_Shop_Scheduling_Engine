#pragma once

#include <iostream>
#include <vector>
#include <functional>
#include <algorithm>

#include "treasure.cpp" 
#include "heap.cpp"

class CrewMate {
public:
    long long end_time; // Replaces current_load to accurately track when they finish all work
    long long last_update_time; // The true clock for this specific crewmate

    Heap<Treasure*>* treasure_queue;

    CrewMate() {
        end_time = 0;    
        last_update_time = 0;
        
        // BUG FIX: We must use remaining_size here, not original size, 
        // so priorities update dynamically as tasks are processed.
        std::function<bool(Treasure* const& , Treasure*const&)> comp = [](Treasure* const& a , Treasure* const&b){
            long long priority_a = a->arrival_time + a->remaining_size;
            long long priority_b = b->arrival_time + b->remaining_size;
            if(priority_a == priority_b){
                return a->id < b->id;
            }
            return priority_a < priority_b;
        };
        
        std::vector<Treasure*> empty_init;
        treasure_queue = new Heap<Treasure*>(comp, empty_init);
    }

    ~CrewMate(){
        delete treasure_queue;
    }

    // Fast-forwards the simulation for this crewmate up to the new arrival time
    void fast_forward(long long t) {
        if (last_update_time >= t) return;
        
        long long dt = t - last_update_time;
        
        while (dt > 0 && !treasure_queue->is_empty()) {
            Treasure* current = treasure_queue->extract();
            
            if (current->remaining_size <= dt) {
                // Task finishes completely before the new treasure arrives
                dt -= current->remaining_size;
                last_update_time += current->remaining_size;
                current->remaining_size = 0;
                current->completion_time = last_update_time;
            } else {
                // Task is partially processed, gets paused and thrown back in queue
                current->remaining_size -= dt;
                last_update_time += dt; 
                dt = 0;
                treasure_queue->insert(current); 
            }
        }
        // Sync the clock if they were idle
        last_update_time = t; 
    }
     
    void assign_treasure(Treasure* t){
        // 1. Catch the crewmate's clock up to the exact arrival time
        fast_forward(t->arrival_time);
        
        // 2. Give them the new treasure
        treasure_queue->insert(t);
        
        // 3. Update their ultimate finishing time
        end_time = std::max(end_time, t->arrival_time) + t->size;
    }
};