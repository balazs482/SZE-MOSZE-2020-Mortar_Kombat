# SZE-MOSZE-2020-Mortar_Kombat

This program simulates a turn based fight between a hero and a some monsters.  
  
## Input instructions  
### Argument  
Use an argument when running the compiled executable. The argument should be a path to a .json file describing a scenario.  
There must be a "hero" and a "monsters" key with paths to all the entities' .json files.  
```   
{
    "hero" : "Dark_Wanderer.json",
    "monsters" : " Fallen.json  Fallen.json  Zombie.json  Fallen.json  Blood_Raven.json "
} 
```  
### Entities  
All entities' .json files must contain the following keys:
- "name"
- "hp" (hit points)
- "dmg" (damage points)
- "as" (attack speed)  
```   
{  
    "name" : "Kakarott",  
    "hp" : 380,  
    "dmg" : 20,  
    "as" : 1.9  
}  
```  
  
## Simulation  
### Fight
The characters fight in turns back and forth repeatedly.  
By every attack, the attacked character's hit points reduce by the attacker character's damage points.   
For every damage point the hero inflicts it gains an experience point.   
100 experience points cause the player to level up resulting in:
- 10% more maximum hit points (rounded)   
- 10% more damage points   
- 10% less attack speed
- instant hit point regeneration   
The simulation ends when one reaches 0 hit points.  
## Scenario  
The hero fights throught all the monsters one by one. 
Every turn the name, level and hit points of the hero, as well as the name of the monster is printed.  
If either non of the monster or the hero has any hit points left, the simulation ends.  
The hero's condition is printed, and then the program exits.   
  
Documentation: https://teaching-projects.github.io/SZE-MOSZE-2020-Mortar_Kombat/   
