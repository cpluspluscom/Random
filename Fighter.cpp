#include "Fighter.hpp"

int FIGHTER::Fighters = 0;

int FIGHTER::Attack(UNIT* Unit)
{
    if(!Alive) //If You're Dead You Don't Get To Attack
    {
        return 0;
    }
    
    if(Unit->LID == LID) //Don't Attack Yourself
    {
        return 0;
    }
    
    if(Ammo <= 0) //If You're Out Of Ammo Run Away
    {
        Mode = RUN;
        MoveAway(Unit);
        return 0;
    }
    
    if(Unit->Type == HUMAN) //If UNIT Is A Human Don't Shoot It
    {
        MoveAway(Unit);
        return 0;
    }
    
    if(!Unit->Alive) //If What You're Evaluating Is Not Alive Don't Shoot It
    {
        return 0;
    }
    
    if(Target == -1 && Unit->Alive && Unit->Type == ZOMBIE) //If You Have No Target, Choose A New One
    {
        //std::cout << "Targeting " << Unit->PID << std::endl;
        Target = Unit->LID;
        TargetLoc = Unit->Pos;
    }
    
    float NewRange = fabs(sqrt(pow(Unit->Pos.y, 2) + pow(Unit->Pos.x, 2)) - sqrt(pow(Pos.x, 2) + pow(Pos.y, 2)));
    TRange = fabs(sqrt((pow(TargetLoc.y, 2) + pow(TargetLoc.x, 2))) - sqrt(pow(Pos.x, 2) + pow(Pos.y, 2)));
    
    if(NewRange < TRange)
    {
        Target = Unit->LID;
        TargetLoc = Unit->Pos;
        TRange = NewRange;
    }
    
    if(!Loaded) //If Your Weapon Not Loaded Run Away
    {
        Mode = RUN;
        MoveAway(Unit);
        return 0;
    }

    if(Unit->LID == Target) //If UNIT Is Your Current Target
    {
        if(!Unit->Alive)
        {
            Target = -1;
            return 0;
        }
        
        if(TRange >= Range) //If UNIT Is Out Of 'Range' Left Or Right Approach Target
        {
            Dest = Unit->Pos;
            TargetLoc = Unit->Pos;
        
            return 0;
        }
    
        int Hit = rand() % 4; //If All Criteria Passed Then Fire

        std::cout << LID << " Is Shooting At A " << Unit->TYPE() << " At " << TRange << std::endl;
        
        Ammo--;
        Time.Reset();
        Loaded = false;
        Firing = true;
    
        switch(Hit)
        {
            case 1: 
                Unit->Hit();
                
                //Target = -1; //One Hit Used To Kill The Opponent
            return 1;
        
            default:   
            return 1;
        }
    }
    
    return 1;    
}


std::string FIGHTER::GetData()
{
    if(!Alive)
    {
        return "DEAD";
    }
    
    std::ostringstream String;
    
    String << "LID: " << LID << "\nHit Points: " << HP << "\nTarget: " << Target << "\nAmmo " << Ammo;
    
    return String.str();
}


void FIGHTER::Update()
{
    switch(Mode) //This Will Probably Be Eliminated
    {
        case WAIT: //If Unit Is Waiting Then Return To Normal Mode
            Mode = NORMAL;
        return;
        
        case CHASE: //If Unit Is In CHASE Mode They Will Not Choose A New Destination
            Move();
        break;
        
        case NORMAL:
            Move();
        break;
        
        case RUN:
            Move();
        break;
        
        default:
        break;
    }
    
    if((Pos.x == Dest.x) && (Pos.y == Dest.y))
    {   
        NewDest();
    }
    
    if(Time.GetElapsedTime() >= 1) //Reload Timer NOTE: This Should NOT Be A Constant, SFML 2.0 Is Moving To Miliseconds
    {
        if(Ammo > 0)
        {
            Mode = NORMAL;
            Loaded = true;
            Time.Reset();
        }
    }
}

sf::Sprite* FIGHTER::draw()
{
    if(!Selected && Loaded)
    {
        Sprite.SetPosition(Pos);
        return &Sprite;
    }
    
    if(!Selected && Firing)
    {
        Firing = false;
        Sprite2.SetPosition(Pos);
        return &Sprite2;
    }
    
    if(Selected && !Firing)
    {
        Sprite3.SetPosition(Pos);
        return &Sprite3;
    }
    
    if(Selected && Firing)
    {
        Firing = false;
        Sprite4.SetPosition(Pos);
        return &Sprite4;
    }
    
    if(!Selected && !Loaded)
    {
        Sprite5.SetPosition(Pos);
        return &Sprite5;
    }
    
    if(Selected && !Loaded)
    {
        Sprite6.SetPosition(Pos);
        return &Sprite6;
    }
}

inline bool FIGHTER::RightClick(float X, float Y)
{
    if(Selected)
    {
        Dest.x = X;
        Dest.y = Y;
        
        return true;
    }
    
    return false;
}

void FIGHTER::Zombify(sf::Image* zimg) //Broken, This Function Not In Use
{
    std::cout << LID << " Zombified\n";
    
    Type = ZOMBIE;
    
    Img = zimg;   
    Sprite.SetImage(*Img);
}

void FIGHTER::Hit()
{
    HP--;
    if(HP <= 0)
    {
        Die();
    }
}


void FIGHTER::Die()
{
    Alive = false;
    Selected = false;
    Id--;
    Fighters--;
}


/* void FIGHTER::MoveAway(sf::Vector2f Obj)
{
    if(Obj.x > Pos.x)
    {
        Dest.x -= 1;
    }
    if(Obj.x < Pos.x)
    {
        Dest.x += 1;
    }
    
    if(Obj.y > Pos.y)
    {
        Dest.y -= 1;
    }
    if(Obj.y < Pos.y)
    {
        Dest.y += 1;
    }
} */
