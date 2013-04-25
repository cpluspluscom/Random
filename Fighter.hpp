#include "Units.hpp"

struct FIGHTER : public UNIT
{
    private:
        
    public:
        FIGHTER(sf::Image* img, sf::Image* HealthBar, int Z): Ammo(10), Loaded(true), Range(75), Firing(false)
        {
            scale = SCALE;
            
            Fighters++;
            
            Health = HealthBar;
            HP = 5;
            LID = Id; //Id Is A Static Data Member
            PID = Id;
            Id++;   //Increament Id Everytime Constructor Is Called
            Alive = true;
            Selected = false;
            Mode = NORMAL;
            Speed = 1;
            
            Img = img; //Inherited From Base Class 
            Type = Z; //Inherited From Base Class
            Target = -1;
            
            Time.Reset(); //Start Timer At Zero
            
            /////*Generate Units Position Until It Is Within The Bounds Of The Screen*/////
            do
            {
                Pos.x = 400 + (rand() % 200);
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
                
            Sprite4.SetImage(*Img);
                Sprite4.SetScale(scale, scale);
                Sprite4.SetSubRect(sf::IntRect(76, 0, 103, 50));
            
            Sprite5.SetImage(*Img);
                Sprite5.SetScale(scale, scale);
                Sprite5.SetSubRect(sf::IntRect(0,51, 25, 100));
            
            Sprite6.SetImage(*Img);
                Sprite6.SetScale(scale, scale);
                Sprite6.SetSubRect(sf::IntRect(52, 51, 76, 100));
            
            Sprite.SetPosition(Pos);
            Sprite2.SetPosition(Pos);
            
            Dest = Pos;
        }
    
    void Update();
    //void MoveAway(sf::Vector2f Obj);
    
    sf::Sprite* draw();
    int Attack(UNIT* Unit);
    std::string GetData();
    void Zombify(sf::Image* zimg);
    void Hit();
    void Die();
    
    void HealthImg();
    
    bool RightClick(float X, float Y);
    
    float Range;
    int Ammo;
    bool Loaded;
    bool Firing;
    
    static int Fighters;
    
    sf::Sprite Sprite3;
    sf::Sprite Sprite4;
    
    sf::Sprite Sprite5;
    sf::Sprite Sprite6;
};
