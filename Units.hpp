#ifndef __UNITS__UNITS
    #define __UNITS__UNITS

#include <iostream>
#include <vector>
#include <sstream>
#include <ctime>
#include <cmath>

#include <SFML/Graphics.hpp>

#define WIDTH 600
#define HEIGHT 400

#define SCALE .75


enum MODE{NORMAL, WAIT, CHASE, ATTACK, RUN};
enum TYPE{HUMAN, ZOMBIE, TER};

struct BASE
{
    private:
        
    public:
        BASE() {}
    
    virtual sf::Sprite* draw();
    bool Hit(BASE* Obj);
    std::string TYPE();
    bool Test(sf::Vector2f A, sf::Vector2f B, sf::Vector2f RBA, sf::Vector2f RBB);
    virtual std::string GetData();
    
    int Type;
    int LID;  //Vector ID For Deletion And Looping
    int PID; //Permanent ID
    
    sf::Image* Img;
    
    sf::Sprite Sprite;   //Sprite Frame 1
    sf::Sprite Sprite2;  //Sprite Frame 2
        
    sf::Vector2f Pos; //Position Of The Sprite
    sf::Vector2f RB;  //Right Bottom Of The Sprite
    
    float Right;
    float Bottom;
    float Speed;
    float scale;
    
    MODE Mode;
    
    bool Selected;
};
  
struct UNIT: BASE
{
    private:
        
    public:
        UNIT(): Alive(true) {}
        
        UNIT(sf::Image* img, int Z): Kills(0)
        {   
            scale = SCALE;
            
            LID = Id; //Id Is A Static Data Member
            PID = Id;
            Id++;   //Increament Id Everytime Constructor Is Called
            Alive = true;
            Selected = false;
            Mode = NORMAL;
            Speed = 1;
            
            Pos = sf::Vector2f(0,0);
            
            Img = img; //Inherited From Base Class 
            Type = Z; //Inherited From Base Class
            
            Time.Reset();
            
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

            
            Sprite.SetPosition(Pos);
            Sprite2.SetPosition(Pos);
            
            Dest = Pos;
        }
    
    void Set(float X, float Y);
    
    
    int Hit(UNIT* Unit);
    
    virtual void Die();
    virtual void Update();
    virtual int Attack(UNIT* Unit);
    virtual void Click(float X, float Y, bool Shift);
    virtual void Go(float X, float Y);
    virtual void Zombify(sf::Image* zimg);
    virtual bool RightClick(float X, float Y);
    virtual void Hit();
    
    bool Chase(UNIT* Unit);
    void Move();
    void MoveAway(UNIT* Unit);
    void NewDest();
    
    sf::Image* Health;
    
    static int Id;
    
    sf::Vector2f Dest;
    sf::Vector2f TargetLoc;
    
    sf::Shape TargetLine;

    int Kills;
    int Target;
    int HP;
    
    bool Alive;
    
    float TRange;
    
    sf::Clock Time;
};

    
    
    
    
#endif
