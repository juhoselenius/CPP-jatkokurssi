#include <iostream>
#include <vector>
#include <algorithm>
#include <thread>
#include <chrono>

/*! \brief Helper function for printing the enemy HP list.
 *
 *  \param hpList The list of enemy HP values.
 */
void printHPList(std::vector<int> hpList)
{
    std::cout << "List of Enemy HP" << std::endl;
    for (int i = 0; i < hpList.size(); i++)
    {
        std::cout << "Furry " << i + 1 << " HP: " << hpList[i] << std::endl;
    }
    std::cout << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(4000));
}

/*! \brief Helper function for simulating casting a spell.
 *
 *  \param spell The name of the spell.
 */
void castSpell(std::string spell)
{
    std::cout << "Player cast a " << spell << " spell\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
}

/*! \brief Function for dealing damage to an enemy.
 *
 *  If enemy's HP is greater than or equal to 100, it decreases by 100; otherwise, it becomes 0.
 *
 *  \param enemyHP Reference to the enemy's HP value.
 */
void dealDamage(int& enemyHP)
{
    if (enemyHP >= 100)
    {
        enemyHP -= 100;
    }
    else
    {
        enemyHP = 0;
    }
}

/*! \brief Functor for dealing damage to an enemy.
 *
 *  If enemy's HP is greater than or equal to 100, it decreases by 100; otherwise, it becomes 0.
 */
class DealDamageFunctor
{
public:
    /*! \brief Operator overload for applying damage to an enemy.
     *
     *  \param enemyHP Reference to the enemy's HP value.
     */
    void operator() (int& enemyHP)
    {
        if (enemyHP >= 100)
        {
            enemyHP -= 100;
        }
        else
        {
            enemyHP = 0;
        }
    }
};

int main()
{
    std::vector<int> enemyHPList;

    // Generating random HP values for enemies
    for (int i = 0; i < 10; i++)
    {
        enemyHPList.emplace_back((rand() % 10 + 1) * 100); // Add integers from 100 to 1000
    }

    std::cout << "A wild pack of furries appeared!\n" << std::endl;
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));

    printHPList(enemyHPList);

    castSpell("function");

    // Assignment A: Standalone function
    st
