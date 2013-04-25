#include "Units.hpp"

#ifndef __BUILDING__BUILDING
    #define __BUILDING__BUILDING

struct BUILDING: BASE
{
    private:

    public:
        BUILDING(sf::Image* img, float X, float Y)
        {
            Img = img;
            Type = 3;
            
            Pos.x = X;
            Pos.y = Y;
            
            Right = Img->GetWidth();
            Bottom = Img->GetHeight();
            
            RB.x = Right;
            RB.y = Bottom;
            
            
            Sprite.SetImage(*Img);
            
            //std::cout << "X: " << Pos.x << " Y: " << Pos.y << " Right: " << Right << " Bottom: " << Bottom << "\n";
            Sprite.SetPosition(Pos);
        }
        
        //bool Hit(sf::Vector2f Pos);
    
};




#endif
