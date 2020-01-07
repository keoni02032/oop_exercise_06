#include <iostream>
#include <ostream>
#include <algorithm>
#include <map>

#include "rhombus.hpp"
#include "containers/queue.hpp"
#include "allocators/allocator.hpp"

int main() {
    int posision;
    containers::queue<rhombus<int>, all::my_allocator<rhombus<int>, 300>> q;

    std::map<int, int, std::less<>, all::my_allocator<std::pair<const int, int>, 1000>> mp;
            for (int i = 0; i < 8; i++) {
                mp[i] = i * i;
            }
            std::for_each(mp.begin(), mp.end(), [](std::pair<int, int> X) {std::cout << X.first << " " << X.second << ", ";});
            std::cout << std::endl;

    std::cout << "1 - push\n"
              << "2 - top\n"
              << "3 - pop\n"
              << "4 - erase_to_num\n"
              << "5 - for_each\n"
              << "6 - map\n"
              << "7 - insert_to_num"
              << "0 - exit\n";

    for (;;) {
        int command;
        std::cin >> command;
        if (command == 1) {
            rhombus<int> rhomb(std::cin);
            q.push(rhomb);
        } else if (command == 2) {
            q.top().print();
        } else if (command == 3) {
            q.pop();
        } else if (command == 4) {
            std::cin >> posision;
            q.erase_to_num(posision);
        } else if (command == 5) {
            std::for_each(q.begin(), q.end(), [](rhombus<int> &rhomb) { return rhomb.print(); });
        } else if (command == 0) {
            break;
        } else if (command == 6) {

            std::map<int, int, std::less<>, all::my_allocator<std::pair<const int, int>, 1000>> mp;
            for (int i = 0; i < 6; i++) {
                mp[i] = i * i;
            }
            std::for_each(mp.begin(), mp.end(), [](std::pair<int, int> X) {std::cout << X.first << " " << X.second << ", ";});
            std::cout << std::endl;
        } else if (command == 7) {
            // int posision;
            // std::cin >> posision;
            // rhombus<int> rhomb(std::cin);
            // auto it = posision;
            // q.insert_to_num(it, rhomb);
            int r;
            std::cin >>r;
            rhombus<int> rhomb(std::cin);
            q.insert_to_num(r, rhomb);
        } else {
            std::cout << "ERROR" << std::endl;
            continue;
        }
    }

    return 0;
}