#include <iostream>

#include <SFML/Graphics.hpp>

#include "ZEvent.hpp"
#include "Units.hpp"
#include "Fighter.hpp"
#include "Enemy.hpp"
#include "Building.hpp"
#include "Portrait.hpp"

void pause() __attribute__((destructor)); //This Is A GCC\Mingw Specific Function Attribute, I Have No Idea How To Do It Using "cl.exe" SOMEONE PLEASE TELL ME!!!

void pause()
{
    std::cin.sync();
    std::cin.ignore();
}


int main(int argc, char *argv[])
{   
    sf::RenderWindow App(sf::VideoMode(WIDTH, HEIGHT, 32), "SFML Zombies");
        App.SetFramerateLimit(90);
        
    std::vector<UNIT*> UVec;
        
    srand(time(NULL));
    
    std::string TEXT = "HELLO";
    
    sf::Clock Clock;
    sf::Font Font;
        if(!Font.LoadFromFile("cour.ttf"))
        {
            std::cout << "FONT FAILED TO LOAD\n";
        }
    sf::String Msg(TEXT, Font, 15);
        Msg.Move(0, 0);
        Msg.SetColor(sf::Color::Black);
        
    const sf::Input& Input = App.GetInput();
    sf::Event Event;
    
    float MX = 0;
    float MY = 0;
    
    sf::Image HealthBar;
        //HealthBar.LoadFromFile("C:\\Program Files\\Dev-Cpp\\SFML_Projects\\Sprites\\HealthBar.PNG");
        HealthBar.LoadFromFile("Sprites\\HealthBar.PNG");
    
    sf::Image PortraitImg;
        //PortraitImg.LoadFromFile("C:\\Program Files\\Dev-Cpp\\SFML_Projects\\Sprites\\Portrait.PNG");
        PortraitImg.LoadFromFile("Sprites\\Portrait.PNG");
    
    sf::Image BaseImage; //Image That Workers Are Derived From
        //BaseImage.LoadFromFile("C:\\Program Files\\Dev-Cpp\\SFML_Projects\\Sprites\\Fighter2.PNG");
        BaseImage.LoadFromFile("Sprites\\Fighter2.PNG");
    
    sf::Image DWImg(BaseImage); //Default Worker Image
        DWImg.CreateMaskFromColor(DWImg.GetPixel(3,3), 0); // Make The Color At This Point In The Image Transparent
        DWImg.CreateMaskFromColor(DWImg.GetPixel(25,0), 0); //Hide The Pink Divider Between Frames
        
    sf::Image SWImg(BaseImage); //Currently Selected Worker Image
        SWImg.CreateMaskFromColor(SWImg.GetPixel(3,3), 0);
    
    sf::Image ZImg;
        //ZImg.LoadFromFile("C:\\Program Files\\Dev-Cpp\\SFML_Projects\\Sprites\\Zombie2.PNG");
        ZImg.LoadFromFile("Sprites\\Zombie2.PNG");
        ZImg.CreateMaskFromColor(ZImg.GetPixel(1,1), 0);
        ZImg.CreateMaskFromColor(ZImg.GetPixel(25,0), 0);
        
    sf::Image HImg;
        //HImg.LoadFromFile("C:\\Program Files\\Dev-Cpp\\SFML_Projects\\Sprites\\Home.PNG");
        HImg.LoadFromFile("Sprites\\Home.PNG");
        HImg.CreateMaskFromColor(HImg.GetPixel(1,1), 0);
        
    PORTRAIT Portrait(&PortraitImg, &HealthBar);
        
    BUILDING Home(&HImg, 10, 200);
    
    int FNum = 10; //Number of Fighters
    int ZNum = 10; //Number of Zombies
    
    int Case = 0;
    
///////*CREATING THE UNITS*///////
    
    for(int i = 0; i < FNum; i++)
    {
        FIGHTER* Fighter = new FIGHTER(&DWImg, &HealthBar, HUMAN);
    
        UVec.push_back(Fighter);
    }
    
    for(int i = 0; i < ZNum; i++)
    {
        ENEMY* Zombie = new ENEMY(&ZImg, ZOMBIE);
        
        UVec.push_back(Zombie);
    }
    
///////*THE RUNNING LOOP*///////
    
    while(App.IsOpened())
    {
        MX = Input.GetMouseX();
        MY = Input.GetMouseY();
        
        App.Clear(sf::Color::White);
        
        while(App.GetEvent(Event))
        {
            ZEvent(Event, &App);
        }
        
        App.Draw(Home.Sprite); //Draw Buildings
        
        //Portrait.Update(1); //Portrait Is A Work In Progress
        
        for(int i = 0; i < UVec.size(); i++) //Update The Screen
        {
            UVec[i]->LID = i;
            UVec[i]->Update();
            
            if(UVec[i]->Selected)
            {
                Portrait.Update(UVec[i]);
                Msg.SetText(UVec[i]->GetData());
            }
            
            if(Home.Hit(UVec[i])) // If Unit Would Hit Any Building In The Vector
            {                         // 
                //UVec[i]->MoveAway(&Home);// Avoid The Building
            }               
            
            for(int j = 0; j < UVec.size(); j++)
            {   
                if(UVec[i]->Attack(UVec[j]) == 3)
                {
                    //UVec[i]->Zombify(&ZImg); //Not Implemented Yet
                }
            
                if(Input.IsMouseButtonDown(sf::Mouse::Right))
                {   
                    if(UVec[i]->Selected)
                    {
                        if(UVec[j]->RightClick(MX, MY))
                        {
                            UVec[i]->Mode = CHASE;
                            UVec[i]->Target = UVec[j]->PID;
                        }
                    }
                }
            }
                
            if(Input.IsMouseButtonDown(sf::Mouse::Left))
            {
                UVec[i]->Click(MX, MY, Input.IsKeyDown(sf::Key::LShift));
            }
            
            if(UVec[i]->Alive)
            {   
                App.Draw(*UVec[i]->draw());
            }
            else
            {
                //UVec.erase(UVec.begin() + UVec[i]->LID); //Not Worrying About This Right Now
            }
        }
        
        App.Draw(Msg);
        //App.Draw(Portrait.Sprite);
        App.Display();
    }
    
    UVec.erase(UVec.begin(), UVec.end()); //Hopefully Calling The Destructors Of The Objects In The Vector
    
    return EXIT_SUCCESS;
}
