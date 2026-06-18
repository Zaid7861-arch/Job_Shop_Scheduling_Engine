#pragma once
#include <vector>
#include <functional>
#include<algorithm>
// 1. Include your actual files instead of forward declaring
#include "treasure.cpp"
#include "heap.cpp"
#include "crewmate.cpp"

class StrawHatTreasury {
private:
    Heap<CrewMate*>* crewmate_heap;
    std::vector<Treasure*> all_treasures;
    std::vector<CrewMate*>roster;

public:
    /*
    Time Complexity: O(m)
    */
    StrawHatTreasury(int m) {
        // 1. Define how we compare CrewMates (Min-Heap based on current_load)
        std::function<bool(CrewMate* const&, CrewMate* const&)> comp = 
            [](CrewMate* const& a, CrewMate* const& b) {
                // In case of a tie, the assignment says any can be chosen, 
                // but it's good practice to have a stable tie-breaker (like memory address or an ID if they had one)
                return a->end_time < b->end_time; 
            };

        // 2. Create m CrewMates and store them in a temporary array
        std::vector<CrewMate*> initial_crew;
        for (int i = 0; i < m; i++) {
            CrewMate*new_mate = new CrewMate();
            initial_crew.push_back(new_mate);
            roster.push_back(new_mate);

        }

        // 3. Initialize the heap using your O(m) constructor
        crewmate_heap = new Heap<CrewMate*>(comp, initial_crew);
    }

    ~StrawHatTreasury() {
        // We have to delete the crewmates from the heap array to prevent memory leaks
        // Since we can't easily iterate the internal heap array, you might want to 
        // store a separate vector of CrewMate* just for cleanup, or implement a 
        // cleanup method in your heap. For now, we will just delete the heap.
        delete crewmate_heap;
    }

    /*
    Time Complexity: O(log m + log n)
    */
    void add_treasure(Treasure* treasure) {
        // 1. Save to our master record
        all_treasures.push_back(treasure);

        // 2. Get the crewmate with the least current load O(log m)
        CrewMate* best_mate = crewmate_heap->extract();

        // 3. Assign the treasure to them O(log n)
        best_mate->assign_treasure(treasure);

        // 4. Push them back into the heap with their newly updated load O(log m)
        crewmate_heap->insert(best_mate);
    }

    std::vector<Treasure*> get_completion_time() {
      for (CrewMate* mate : roster) {
            
            // To avoid destroying the real queue, we make a shallow copy of the heap.
            // (Make sure your Heap class has a copy constructor, or you can copy its internal vector)
            Heap<Treasure*> virtual_queue = *(mate->treasure_queue); 
            
            // Set the virtual clock for this specific crewmate
            long long virtual_time = mate->last_update_time;

            // Process every treasure in their queue
            while (!virtual_queue.is_empty()) {
                Treasure* current_treasure = virtual_queue.extract();
                
                // If the crewmate is idle, the clock jumps forward to when the treasure arrives
                if (virtual_time < current_treasure->arrival_time) {
                    virtual_time = current_treasure->arrival_time;
                }
                
                // Process the treasure (add its remaining size to the clock)
                virtual_time += current_treasure->remaining_size;
                
                // Record the final completion time onto the actual treasure object
                current_treasure->completion_time = virtual_time;
            }
        }
        
        // 2. Sort the master list of treasures by their ID
        // The assignment explicitly allows using the built-in sort function here
        std::sort(all_treasures.begin(), all_treasures.end(), 
            [](Treasure* a, Treasure* b) {
                return a->id < b->id;
            }
        );
        
        // 3. Return the sorted list
        return all_treasures;
        
    }
};