#ifndef __ZEvent__ZEvent
    #define __ZEvent__ZEvent
    
void ZEvent(sf::Event Event, sf::RenderWindow* APP)
{   
    const sf::Input& Input = APP->GetInput();
    
    if(Event.Key.Code == sf::Key::Escape)
    {
        if(Input.IsKeyDown(sf::Key::Escape))
        {
            std::cout << "\nESCAPE PRESSED\n";
            APP->Close();
        }
    }
}
    
#endif
