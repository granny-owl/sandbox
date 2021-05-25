#include <iostream>
#include <vector>

void hanoi(int q, char start, char buff, char end, int& it) {

    if (q == 1) {
        std::cout << "Move disk " << q << " from " << start << " to " << end << '\n';
        it++;
        return;
    }

    hanoi(q - 1, start, end, buff, it);
    std::cout << "Move disk " << q << " from " << start << " to " << end << '\n';
    it++;
    hanoi(q - 1, buff, start, end, it);

}

int main()
{
    int q;
    int i = 0;
    std::cout << "Number of disks: ";
    std::cin >> q;
    std::cout << '\n';
 
    hanoi(q, 'A', 'B', 'C', i);
    std::cout << "Iterations: " << i << '\n';
    std::cout << "Minimum number of steps: " << pow(2, q) - 1;

    return 0;
}
