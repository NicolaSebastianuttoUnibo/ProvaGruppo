
#ifndef UNIVERSE_HPP
#define UNIVERSE_HPP
#include <vector>








#include "newton.hpp"
namespace U {
class Universe;///forward declaration
struct Newton {
// la forza è espressa in megaNewton (10^6)N
double f_x{};  // force x
double f_y{};  // force y
void operator()(G::PlanetState const& a, G::PlanetState const& b);
double d_2(G::PlanetState const& a, G::PlanetState const& b);
double r_2(G::PlanetState const& a, G::PlanetState const& b);


const double G_{6.67430e-29*3600*3600};  /// costante G (MN*Mm^2/kg^2) our G = usual G*10^-18
};
















class Universe {
Newton newton_;
std::vector<G::PlanetState> galaxy_;
std::vector<G::PlanetState> copy_;
G::PlanetState solve(G::PlanetState const &ps, double fx, double fy,
                    double delta_t) const;
std::vector<G::PlanetState> importantplanet_;
void check_Collision();


public:
double mechanic_energy_;
const double initial_energy_;
double lost_energy_;
double total_energy_;
double calculateenergy();
void findimportantplanet();




Universe(Newton const &newton);
void push_back(G::PlanetState const &ps);
void remove(G::PlanetState const &ps);
int size() const;
void evolve(double delta_t);
std::vector<G::PlanetState> const &state() const;






};
































}  // namespace U
#endif




