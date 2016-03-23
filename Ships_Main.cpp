#include<assert.h>
#include"Ships.hpp"
#include"Ship.hpp"
#include <iostream>
#include"Ship_Type_Enum.hpp"
#include<forward_list>
#include<fstream>

int P_PROB = 40;
int CAR_PROB = 50;
int E_PROB = 25;
int num_x = 35;
int num_y=20;

int main()
{
    std::cout << "Pirate: "<<Ship_Type::Pirate<<std::endl;
    std::cout << "Escort:: "<<Ship_Type::Escort<<std::endl;
    std::cout << "Captured: "<<Ship_Type::Captured<<std::endl;
    std::cout << "Cargo: "<<Ship_Type::Cargo<<std::endl;

    std::ofstream out_file;
    out_file.open("test.txt");
    assert(out_file.is_open());

    Ships p_ships(Ship_Type::Pirate, 40, 50, 25);
    Ships car_ships(Ship_Type::Cargo, 40, 50, 25);
    Ships e_ships{Ship_Type::Escort, 40, 50, 25};
    Ships cap_ships = Ships(Ship_Type::Captured, 40, 50, 25);

    for (int i =0; i < 10; i++)
    {
        p_ships.AddPirateShip(i, num_y - 1);
        car_ships.AddCargoShip(0, i);
        e_ships.AddEscortShip(num_x - 1, i);
        cap_ships.AddCapturedShip(i, num_y);
    }     
    
    std::cout<<"Pirate Ships"<<std::endl;
    p_ships.PrintList();
    /*
    std::cout<< "Cargo Ships"<<std::endl;
    car_ships.PrintList();
    std::cout<<"Escort Ships"<<std::endl;
    e_ships.PrintList();
    std::cout<<"Captured Ships"<<std::endl;
*/
    std::cout<<"======================Sort Lists===================="<<std::endl;
    p_ships.RemoveCaptured();
    std::cout<<"Pirate Ships"<<std::endl;
    p_ships.PrintList();
/*
    std::cout<< "Cargo Ships"<<std::endl;
    car_ships.PrintList();
    std::cout<<"Escort Ships"<<std::endl;
    e_ships.PrintList();
    std::cout<<"Captured Ships"<<std::endl;
*/

    out_file << "Print out all pirate ship (x, y)" << std::endl;

    for (int j=1; j < 10; j+=2)
    {
        p_ships.RemoveShip(j);
    }
    p_ships.RemoveShip(9); 
    std::forward_list<Ship>::iterator p_list_begin = p_ships.Begin();
    std::forward_list<Ship>::iterator p_list_end = p_ships.End();
    std::forward_list<Ship>::iterator car_list_begin = car_ships.Begin();
    std::forward_list<Ship>::iterator car_list_end = car_ships.End();
    std::forward_list<Ship>::iterator e_list_begin = e_ships.Begin();
    std::forward_list<Ship>::iterator e_list_end = e_ships.End();

    std::forward_list<Ship>::iterator cap_list_begin = cap_ships.Begin();
    std::forward_list<Ship>::iterator cap_list_end = cap_ships.End();

    int i = 1;
    out_file << "Remove odd value ships." << std::endl;
    for ( ; p_list_begin != p_list_end; p_list_begin++)
    {
         Ship ship = *p_list_begin;
        out_file  <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

       
    
/*
    int i = 1;
    out_file << "Pirate Ships: "<< std::endl;
    std::cout<< "Pirate Ships == 0"<<std::endl;
    for ( ; p_list_begin != p_list_end; p_list_begin++)
    {
        Ship ship = *p_list_begin;
        out_file  <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

    p_ships.Move();

    out_file << "Move the pirate ships and print again." << std::endl;

    i = 1;
    out_file << "Pirate Ships: "<< std::endl;
    p_list_begin = p_ships.Begin();
    for ( ; p_list_begin != p_list_end; p_list_begin++)
    {
        Ship ship = *p_list_begin;
        out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

    out_file << "Gen() Test==================================" << std::endl;
    for (int j =0; j < 30; j++)
    {
        out_file << "Calling Move() and Gen()" << std::endl;
        p_ships.Move();
        p_ships.Gen();
        p_list_begin = p_ships.Begin();
        p_list_end = p_ships.End();
        
        int i = 1;
        for ( ; p_list_begin != p_list_end; p_list_begin++)
        {
            Ship ship = *p_list_begin;
            out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
            //out_file<<i<<"\t"<<ship.Type()<<std::endl;
            i++;
        }
    }
    out_file << "Cargo Ships: "<< std::endl;
    std::cout<< "Cargo Ships == 1"<< std::endl;
    for ( ; car_list_begin != car_list_end; car_list_begin++)
    {
        Ship ship = *car_list_begin;
        out_file  <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

    car_ships.Move();

    out_file << "Move the cargo ships and print again." << std::endl;

    i = 1;
    out_file << "Cargo Ships: "<< std::endl;
    car_list_begin = car_ships.Begin();
    for ( ; car_list_begin != car_list_end; car_list_begin++)
    {
        Ship ship = *car_list_begin;
        out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" <<"\t\t\t"<<ship.Value()<< std::endl;
        i++;
    }

    out_file << "Gen() Test==================================" << std::endl;
    for (int j =0; j < 30; j++)
    {
        out_file << "Calling Move() and Gen()" << std::endl;
        car_ships.Move();
        car_ships.Gen();
        car_list_begin = car_ships.Begin();
        car_list_end = car_ships.End();
        
        int i = 1;
        for ( ; car_list_begin != car_list_end; car_list_begin++)
        {
            Ship ship = *car_list_begin;
            out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
            //out_file<<i<<"\t"<<ship.Type()<<std::endl;
            i++;
        }
    }
    out_file << "Escort Ships: "<< std::endl;
    std::cout<<"Escort Ships == 2"<<std::endl;
    for ( ; e_list_begin != e_list_end; e_list_begin++)
    {
        Ship ship = *e_list_begin;
        out_file  <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

    e_ships.Move();

    out_file << "Move the escort ships and print again." << std::endl;

    i = 1;
    out_file << "Escort Ships: "<< std::endl;
    e_list_begin = e_ships.Begin();
    for ( ; e_list_begin != e_list_end; e_list_begin++)
    {
        Ship ship = *e_list_begin;
        out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
        i++;
    }

    out_file << "Gen() Test==================================" << std::endl;
    for (int j =0; j < 30; j++)
    {
        out_file << "Calling Move() and Gen()" << std::endl;
        e_ships.Move();
        e_ships.Gen();
        e_list_begin = e_ships.Begin();
        e_list_end = e_ships.End();
        
        int i = 1;
        for ( ; e_list_begin != e_list_end; e_list_begin++)
        { 
            Ship ship = *e_list_begin;
            out_file <<i<< "\t("  << ship.Xpos() << ", "<< ship.Ypos()<<")" << "\t\t\t"<<ship.Value()<<std::endl;
            //out_file<<i<<"\t"<<ship.Type()<<std::endl;
            i++;
        }
    }

*/

    out_file.close();
    return 0;
}
