#include "Building.hpp"


sf::Sprite* BASE::draw()
{
    if(Selected)
    {
        Sprite2.SetPosition(Pos);
        return &Sprite2;
    }
    
    Sprite.SetPosition(Pos);
    return &Sprite;
}



bool BASE::Hit(BASE* Obj)
{
    if(Test(Pos, Obj->Pos, RB, Obj->RB))
    {
        return true;
    }
    
    return false;
}


bool BASE::Test(sf::Vector2f A, sf::Vector2f B, sf::Vector2f RBA, sf::Vector2f RBB)
{
    if((A.x > B.x) && (A.x < RBB.x) && (A.y > B.y) && (A.y < RBB.y))
    {
        /* if(A.x > B.x)
        {
            std::cout << " A.x Greater Then B.x\n";
        }
        if(A.x < RBB.x)
        {
            std::cout << " A.x Less Then RBB.x\n";
        }
        
        if(A.y > B.y)
        {
            std::cout << " A.y Greater Then B.y\n";
        }
        if(A.y < RBB.y)
        {
            std::cout << " A.y Less Then RBB.y\n";
        } */

        
        return true;
    }
    
    if((RBA.x > B.x) && (RBA.x < RBB.x) && (RBA.y > B.y) && (RBA.y < RBB.y))
    {
        /* if(RBA.x > B.x)
        {
            std::cout << " RBA.x Greter Then B.x\n";
        }
        if(RBA.x < RBB.x)
        {
            std::cout << " RBA.x Less Then RBB.x\n";
        }
        
        if(RBA.y > B.y)
        {
            std::cout << " RBA.y Greater Then B.y\n";
        }
        if(RBA.y < RBB.y)
        {
            std::cout << " RBA.y Less Then RBB.y\n";
        } */

        
        return true;
    }

    return false;
}


std::string BASE::GetData()
{
    return "Hello";
}


std::string BASE::TYPE()
{
    switch(Type)
    {
        case HUMAN:
            return " Human ";
        case ZOMBIE:
            return " Zombie ";
        case TER:
            return " Building ";
        default:
            return " NULL ";
    }
}
