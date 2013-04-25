#include "Enemy.hpp"

int ENEMY::Enemy = 0;

sf::Sprite* ENEMY::draw()
{
    if(Selected)
    {
        Sprite2.SetPosition(Pos);
        return &Sprite2;
    }
    
    return &Sprite;
}


std::string ENEMY::GetData()
{
    if(!Alive)
    {
        return "DEAD";
    }
    
    std::ostringstream Stream;
    Stream << "LID: " << LID << "\nHit Points: " << HP << "\nTarget: " << Target;
    
    return Stream.str();
}


bool ENEMY::RightClick(float X, float Y)
{
    if(X >= Pos.x && X <= Right && Y >= Pos.y && Y <= Bottom)
    {
        Targeted = true;
        return true;
    }
    else
    {
        Targeted = false;
        return false;
    }
}



int ENEMY::Attack(UNIT* Unit)
{
    if(!Alive)
    {
        return 0;
    }
    
    if(!Unit->Alive)
    {
        if(Unit->LID == Target)
        {
            Target = -1;
        }
        
        return 0;
    }
    
    float NewRange = fabs(sqrt(pow(Unit->Pos.y, 2) + pow(Unit->Pos.x, 2)) - sqrt(pow(Pos.x, 2) + pow(Pos.y, 2)));
    TRange = fabs(sqrt((pow(TargetLoc.y, 2) + pow(TargetLoc.x, 2))) - sqrt(pow(Pos.x, 2) + pow(Pos.y, 2)));
    
    if(Unit->Type == HUMAN)
    {
        if(Target == -1 && Unit->Alive == true) //If Enemy Has No Target AND The Unit Being Looked At Is Alive
        {
            Target = Unit->LID;
        }
        
        if(Unit->LID == Target) //Chase Target
        {
            Dest = Unit->Pos;
            TargetLoc = Unit->Pos;
        }
    }
        
    if(Test(Pos, Unit->Pos, RB, Unit->RB)) //Test For Impact With Target
    {
        if(Unit->Type == ZOMBIE)
        {
            MoveAway(Unit);
            return 0;
        }
        
        std::cout << LID << " Is Attacking " << Unit->LID << std::endl;
        
        int Roll = rand() % 4;
        switch(Roll)
        {
            case 1: 
                Unit->Hit(); 
                Kills++; 
                std::cout << LID << " Hit: " << Unit->LID << "\n";
                
                //Target = -1;
            return 1;
                
            case 2:
                //std::cout << "\nZombifying " << Id << "\n";
                //Target = -1;
            return 3;
                    
            default:
                //std::cout << Unit->ID << " Got Away From " << Id << std::endl;
            break;
        }
    }
    
    return 0;
}


void ENEMY::Hit()
{
    HP--;
    
    if(HP <= 0)
    {
        Die();
    }
}


void ENEMY::Die()
{
    Alive = false;
    Selected = false;
    Id--;
    Enemy--;
}
