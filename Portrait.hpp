#include "Units.hpp"


struct PORTRAIT
{
    private:
        
    public:
        PORTRAIT(sf::Image* img, sf::Image* health): Img(img), Health(health)
        {
            Img->Copy(*Health, 0, 0, sf::IntRect(0, 20, 24, 23));
            
            Sprite.SetImage(*Img);
            Sprite.SetPosition(0, 0);    
        }        
    
    void Update(int Arg);
    void Update(UNIT* Unit);
    
    sf::Image* Img;
    sf::Image* Health;
    
    sf::Sprite Sprite;
        
        
};
