#include <iostream>
#include <flatbuffers/flatbuffers.h>
#include <flatbuffers/idl.h>
#include <flatbuffers/util.h>
#include "monster_generated.h"

#include <string>

using namespace std;
using namespace MyGame::Sample;

int main(int argc, char *argv[])
{
    flatbuffers::FlatBufferBuilder builder;

    auto weapon_one_name = builder.CreateString("Sword");
    short weapon_one_damage = 3;
    auto weapon_two_name = builder.CreateString("Axe");
    short weapon_two_damage = 5;
    // Use the `CreateWeapon` shortcut to create Weapons with all the fields set.
    auto sword = CreateWeapon(builder, weapon_one_name, weapon_one_damage);
    auto axe = CreateWeapon(builder, weapon_two_name, weapon_two_damage);

    // Serialize a name for our monster, called "Orc".
    auto name = builder.CreateString("Orc");
    // Create a `vector` representing the inventory of the Orc. Each number
    // could correspond to an item that can be claimed after he is slain.
    unsigned char treasure[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    auto inventory = builder.CreateVector(treasure, 10);

    // Place the weapons into a `std::vector`, then convert that into a FlatBuffer `vector`.
    std::vector<flatbuffers::Offset<Weapon>> weapons_vector;
    weapons_vector.push_back(sword);
    weapons_vector.push_back(axe);
    auto weapons = builder.CreateVector(weapons_vector);

    // Create a `Vec3`, representing the Orc's position in 3-D space.
    auto pos = Vec3(1.0f, 2.0f, 3.0f);


    // Set his hit points to 300 and his mana to 150.
    int hp = 300;
    int mana = 150;
    // Finally, create the monster using the `CreateMonster` helper function
    // to set all fields.
    auto orc = CreateMonster(builder, &pos, mana, hp, name, inventory, Color_Red,
                             weapons, Equipment_Weapon, axe.Union());
    builder.Finish(orc);

    string fileName("save_test.bin");

    flatbuffers::SaveFile(fileName.c_str(), (char*)builder.GetBufferPointer(), builder.GetSize(), true);


    string monsterOut;

    flatbuffers::LoadFile(fileName.c_str(), true, &monsterOut);


    cout << "Hello World! from monster: " << monsterOut << endl;
    return 0;
}
