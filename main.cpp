#include <bits/stdc++.h>

#include "BTree.h"

int main()
{   
    BTree cosa(4);

  /*  cosa.insert(1);
    cosa.insert(4);
    cosa.insert(7);
    cosa.insert(10);
    cosa.insert(17);
    cosa.insert(21);
    cosa.insert(31);
    cosa.insert(25);
    cosa.insert(19);
    cosa.insert(20);
    cosa.insert(28);
    cosa.insert(42);*/

    cosa.insert(10);
    cosa.insert(27);
    cosa.insert(29);
    cosa.insert(17);
    cosa.insert(25);
    cosa.insert(21);
    cosa.insert(15);
    cosa.insert(31);
    cosa.insert(13);
    cosa.insert(51);
    cosa.insert(20);
    cosa.insert(24);
    cosa.insert(48);
    cosa.insert(19);
    cosa.insert(60);
    cosa.insert(35);
    cosa.insert(66);
    cosa.insert(67);
    cosa.insert(68);
    cosa.insert(69);
    cosa.insert(70);
    cosa.insert(71);






    /*
            12
    6    10           14     
3 5   6 8  10 11   12 13 14 15
*/
    cosa.print_to_console();

    return 0;
}