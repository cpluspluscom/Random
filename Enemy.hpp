#include "Units.hpp"

struct ENEMY : UNIT
{
    private:
        
    public:
        ENEMY(sf::Image* img, int Z): Targeted(false)
        {   
            scale = SCALE;
            
            Enemy++;
            
            HP = 2;
            
            LID = Id; //Id Is A Static Data Member
            PID = Id;
            Id++;   //Increament Id Everytime Constructor Is Called
            Alive = true;
            Selected = false;
            Mode = NORMAL;
            Speed = .5;
            
            Kills = 0;
            
            Pos = sf::Vector2f(0,0);
            
            Img = img; //Inherited From Base Class 
            Type = Z; //Inherited From Base Class
            
            Time.Reset();
            Target = -1;
            
            /////*Generate Units Position Until It Is Within The Bounds Of The Screen*/////
            do
            {
                Pos.x = rand() % 200; //Start Somewhere between 0 and 200
                Right = Pos.x + (25 * scale);
            }while(Pos.x < 0 || Right > WIDTH);
            
            do
            {
                Pos.y = rand() % HEIGHT;
                Bottom = Pos.y + (50 * scale);
            }while(Pos.y < 0 || Bottom > HEIGHT);
            
            RB.x = Right;
            RB.y = Bottom;
            
            Sprite.SetImage(*Img);
                Sprite.SetScale(scale, scale);
                Sprite.SetSubRect(sf::IntRect(0, 0, 24, 50));
            
            Sprite2.SetImage(*Img);
                Sprite2.SetScale(scale, scale);
                Sprite2.SetSubRect(sf::IntRect(25, 0, 50, 50));
                
            Sprite3.SetImage(*Img);
                Sprite3.SetScale(scale, scale);
                Sprite3.SetSubRect(sf::IntRect(51, 0, 75, 50));

            
            Sprite.SetPosition(Pos);
            Sprite2.SetPosition(Pos);
            Sprite3.SetPosition(Pos);
            
            Dest = Pos;
        }
    
    sf::Sprite* draw();
    std::string GetData();
    bool RightClick(float X, float Y);
    int Attack(UNIT* Unit);
    void Hit();
    void Die();
    
    bool Targeted;
    sf::Sprite Sprite3;
    
    static int Enemy;
};
