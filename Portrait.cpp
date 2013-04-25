#include "Portrait.hpp"

void PORTRAIT::Update(int Arg)
{
    switch(Arg)
    {
        case 5: Img->Copy(*Health, 0, 0, sf::IntRect(0, 0, 24, 4)); break;
        case 4: Img->Copy(*Health, 0, 0, sf::IntRect(0, 4, 24, 7)); break;  
        case 3: Img->Copy(*Health, 0, 0, sf::IntRect(0, 8, 24, 11)); break;
        case 2: Img->Copy(*Health, 0, 0, sf::IntRect(0, 12, 24, 15)); break;
        case 1: Img->Copy(*Health, 0, 0, sf::IntRect(0, 16, 24, 19)); break;
        case 0: Img->Copy(*Health, 0, 0, sf::IntRect(0, 20, 24, 23));
    }
}


void PORTRAIT::Update(UNIT* Unit)
{
    Update(Unit->HP);
}
