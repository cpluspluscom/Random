#include "Units.hpp"

int UNIT::Id = 0;


void UNIT::Set(float X, float Y)
{   
    Pos.x = X;
    Pos.y = Y;
    
    Right = Pos.x + (25 * scale);
    Bottom = Pos.y + (50 * scale);
    
    RB.x = Right;
    RB.y = Bottom;
    
    Sprite.SetPosition(Pos);   
}


inline void UNIT::Die()
{
    Alive = false;
    Selected = false;
    Id--;
    //std::cout << "Unit " << ID << " Has Died\n";
}


void UNIT::Update()
{   
    switch(Mode)
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
        
        default:
        break;
    }
    
    if((Pos.x == Dest.x) && (Pos.y == Dest.y))
    {   
        NewDest();
    }

    return;
}

inline void UNIT::NewDest()
{
    Dest.x = rand() % WIDTH;
    Dest.y = rand() % HEIGHT;
}

void UNIT::Move()
{
    if(!Alive)
    {
        return;
    }

    if(Dest.x > Pos.x)
    {
        Pos.x += Speed;
    }
    
    if(Dest.x < Pos.x)
    {
        Pos.x -= Speed;
    }
    
    
    if(Dest.y > Pos.y)
    {
        Pos.y += Speed;
    }
    
    if(Dest.y < Pos.y)
    {
        Pos.y -= Speed;
    }
    
    if(Pos.x < 0) 
    {
        Pos.x += Speed;
        Dest.x = WIDTH;
    }
    if(Right > WIDTH)
    {
        Pos.x -= Speed;
        Dest.x = 0;
    }
    
    if(Pos.y < 0)
    {
        Pos.y += Speed;
        Dest.y = HEIGHT;
    }
    if(Bottom > HEIGHT)
    {
        Pos.y -= Speed;
        Dest.y = 0;
    }
    
    Right = Pos.x + (25 * scale);
    Bottom = Pos.y + (50 * scale);
    
    RB.x = Right;
    RB.y = Bottom;
    
    Sprite.SetPosition(Pos);
    
    return;
}


inline void UNIT::Zombify(sf::Image* zimg)
{
    
}


void UNIT::Click(float X, float Y, bool Shift)
{   
    if(X >= Pos.x && X <= Right && Y >= Pos.y && Y <= Bottom)
    {
        //std::cout << LID << std::endl;
        Selected = true;
    }
    else
    {
        if(!Shift)
        {
            Selected = false;
        }
    }
    return;
}


inline bool UNIT::RightClick(float X, float Y)
{

}


inline void UNIT::Go(float X, float Y)
{
    
}


inline void UNIT::Hit()
{

}


bool UNIT::Chase(UNIT* Unit)
{
    if(Unit->Type == Type) //If Units Are Of The Same Type Return False
    {
        return false;
    }
    if(!Unit->Alive) //If Target Is Dead Return False
    {
        Target = -1;
        Mode = NORMAL;
        return false;
    }
    
    Dest = Unit->Pos;
    
    Mode = CHASE; //Unit Is Chasing
        
    return true;
}


void UNIT::MoveAway(UNIT* Unit)
{
    float NewRange = fabs(sqrt(pow(Unit->Pos.y, 2) + pow(Unit->Pos.x, 2)) - sqrt(pow(Pos.x, 2) + pow(Pos.y, 2)));
    
    //std::cout << PID << " Move Away From " << Unit->PID << std::endl;
    
    if(Test(Pos, Unit->Pos, RB, Unit->RB))
    {
        if(Pos.x > Unit->Pos.x)
        {
            Dest.x = Pos.x + Speed;
        }
        if(Right < Unit->Right)
        {
            Dest.x = Pos.x - Speed;
        }
    
        if(Pos.y > Unit->Pos.y)
        {
            Dest.y = Pos.y + Speed;
        }
        if(Bottom < Unit->Bottom)
        {
            Dest.y = Pos.y + Speed;
        }
    }
    
    Right = Pos.x + (25 * scale);
    Bottom = Pos.y + (50 * scale);
    
    RB.x = Right;
    RB.y = Bottom;
}


int UNIT::Attack(UNIT* Unit) {std::cout << "Do Nothing" << std::endl;}
/*{
    if(!Alive)
    {
        return 0;
    }
    
    /*if(!Unit->Alive)
    {
        return 0;
    }
    
    float XRange = fabs(Pos.x - Unit->Pos.x);
    float YRange = fabs(Pos.y - Unit->Pos.y);
    
    if(Target == -1)
    {
        Target = Unit->PID;
    }
    
    /*if(Unit->PID == Target)
    {
        if(!Unit->Alive)
        {
            Target = -1;
        }
        if(Target == Unit->PID) //Chase Target
        {
            Dest = Unit->Pos;
        }
    }
    
    if(Test(Pos, Unit->Pos, RB, Unit->RB)) //Test(...) Inherited From BASE Struct
    {
        if(Type == Unit->Type)
        {
            MoveAway(Unit);           
            return 0;
        }
            
        //std::cout << ID << " Hit " << Unit->ID << "\n";
        int Roll = rand() % 3;
            
        switch(Roll)
        {
            case 1: 
                Unit->Die(); 
                Kills++; 
                std::cout << "\nHuman Killed: " << Unit->PID << "\n";
                Target = -1;
            return 1;
                
            case 2:
                std::cout << "\nZombifying " << PID << "\n";
                Target = -1;
            return 3;
                    
            default:
                std::cout << Unit->PID << " Got Away From " << PID << std::endl;
            break;
        }
    return 1;
    }
    
    return 0;
}*/
