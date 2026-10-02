#include <iostream>
#include "LinkedList.h"

int main() {
    std::cout << "Default constructor\n";
    LinkedList list_default;
    std::cout << "Is the list empty? " << (list_default.empty() ? "Yes" : "No") << "\n";

    std::cout << "\npush_tail (add element to tail)\n";
    list_default.push_tail(10);
    list_default.push_tail(20);
    list_default.push_tail(30);
    std::cout << "List content: " << list_default << "\n";

    std::cout << "\npush_head (add element to head)\n";
    list_default.push_head(5);
    std::cout << "After push_head(5): " << list_default << "\n";

    std::cout << "\nConstructor with random values\n";
    LinkedList list_random(5, 10, 50);
    std::cout << "Random list: " << list_random << "\n";

    std::cout << "\nCopy constructor\n";
    LinkedList list_copy(list_random);
    std::cout << "Copied list: " << list_copy << "\n";

    std::cout << "\nAssignment operator\n";
    LinkedList list_assign;
    list_assign = list_default;
    std::cout << "List after assignment: " << list_assign << "\n";

    std::cout << "\npush_tail with another list\n";
    list_default.push_tail(list_random);
    std::cout << "After adding another list to tail: " << list_default << "\n";

    std::cout << "\npush_head with another list\n";
    list_default.push_head(list_copy);
    std::cout << "After adding another list to head: " << list_default << "\n";

    std::cout << "\npop_head (remove from head)\n";
    list_default.pop_head();
    std::cout << "After pop_head: " << list_default << "\n";

    std::cout << "\npop_tail (remove from tail)\n";
    list_default.pop_tail();
    std::cout << "After pop_tail: " << list_default << "\n";

    std::cout << "\ndelete_node (remove all elements with a value)\n";
    list_default.delete_node(20);
    std::cout << "After delete_node(20): " << list_default << "\n";

    std::cout << "\nIndex operator\n";
    if (!list_default.empty()) {
        std::cout << "First element (read): " << list_default[0] << "\n";
        list_default[0] = 999;
        std::cout << "First element after writing 999: " << list_default[0] << "\n";
    }

    std::cout << "\nDestructor demonstration\n";
    {
        LinkedList temp_list(3, 1, 3);
        std::cout << "Temporary list: " << temp_list << "\n";
    }
    std::cout << "Destructor called when temp_list goes out of scope.\n";

    LinkedList bigList;
    for (int i = 1; i <= 2000; ++i) {
        bigList.push_tail(i);
    }
    std::cout << "List in reverse:\n" << bigList << "\n";

    return 0;
}