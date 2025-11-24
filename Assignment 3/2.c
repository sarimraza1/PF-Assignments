#include <stdio.h>

void calculateFuel(int fuel, int consumption, int recharge, int solarBonus, int planet, int totalPlanets)
{
    if (planet > totalPlanets)
    {
        printf("Mission Complete: All planets visited successfully.\n");
        return;
    }
    fuel -= consumption;
    fuel += recharge;
    if (planet % 4 == 0)
    {
        fuel += solarBonus;
        printf("[Solar Boost Applied] ");
    }
    if (fuel <= 0)
    {
        printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
        printf("Mission Failed: Out of fuel.\n");
        return;
    }
    printf("Planet %d: Fuel Remaining = %d\n", planet, fuel);
    calculateFuel(fuel, consumption, recharge, solarBonus, planet + 1, totalPlanets);
}

int main()
{
    int initialFuel = 100;
    int fuelConsumption = 20;
    int gravitationalRecharge = 5;
    int solarRecharge = 30;
    int startingPlanet = 1;
    int totalPlanets = 10;
    printf("--- Spacecraft Fuel Simulation ---\n");
    calculateFuel(initialFuel, fuelConsumption, gravitationalRecharge, solarRecharge, startingPlanet, totalPlanets);
    return 0;
}