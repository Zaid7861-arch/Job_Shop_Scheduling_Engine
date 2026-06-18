#include <iostream>
#include <vector>

// Include your main treasury file (which already includes the others)
// Adjust this filename if you named it differently
#include "straw_hat.cpp" 

int main() {
    std::cout << "--- Starting Straw Hat Treasury Simulation ---" << std::endl;

    // 1. Initialize the treasury with 3 CrewMates (as per the example)
    StrawHatTreasury treasury(3);

    // 2. Create the treasures from the example
    // Treasure(id, size, arrival_time)
    Treasure* t1 = new Treasure(1, 8, 1);
    Treasure* t2 = new Treasure(2, 7, 2);
    Treasure* t3 = new Treasure(3, 4, 4);
    Treasure* t4 = new Treasure(4, 1, 5);

    // 3. Add them to the treasury
    treasury.add_treasure(t1);
    treasury.add_treasure(t2);
    treasury.add_treasure(t3);
    treasury.add_treasure(t4);

    // 4. Run the simulation to get the completion times
    std::vector<Treasure*> results = treasury.get_completion_time();

    // 5. Print the results
    std::cout << "\nResults (Sorted by ID):" << std::endl;
    for (Treasure* t : results) {
        std::cout << "Treasure ID: " << t->id 
                  << " | Completion Time: " << t->completion_time << std::endl;
    }

    std::cout << "----------------------------------------------" << std::endl;

    return 0;
}