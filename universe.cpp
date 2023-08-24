#include "universe.hpp"


#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>




#include <cassert>
#include <numeric>
#include <algorithm>


U::Universe::Universe(G::Newton const &newton) : newton_{newton} {}
int U::Universe::size() const { return galaxy_.size(); }


void U::Universe::push_back(G::PlanetState const &ps) { galaxy_.push_back(ps); }


void U::Universe::remove(G::PlanetState const &ps) {
auto it =std::find(galaxy_.begin(),galaxy_.end(),ps);
if(it!=galaxy_.end()){galaxy_.erase(it);}




}












G::PlanetState& U::Universe::operator[](unsigned int index){
 assert(index<galaxy_.size());
 return galaxy_[index];
}
const G::PlanetState& U::Universe::operator[](unsigned int index) const{
 assert(index<galaxy_.size());
 return galaxy_[index];






}




























void U::Universe::evolve(double delta_t) {
 assert(galaxy_.size() >= 1);
 copy_ = galaxy_;
 assert(copy_.size() == galaxy_.size());
 for (auto it = copy_.begin(); it < copy_.end(); ++it) {
   int idx = std::distance(copy_.begin(), it);


   std::pair<double, double> forza = std::accumulate(
       copy_.begin(), copy_.end(), std::make_pair(0.0, 0.0),
       [this, it](std::pair<double, double> sums, const G::PlanetState &ci) {
         newton_(*it, ci);
         sums.first += newton_.f_x;
         sums.second += newton_.f_y;
         return sums;
       });


   galaxy_[idx] = solve(*it, forza.first, forza.second, delta_t);
 }
//galaxy_[0].x+=1000;
}






std::vector<G::PlanetState> const &U::Universe::state() const {
 return galaxy_;
}
G::PlanetState U::Universe::solve(G::PlanetState const &ps, double fx,
                                 double fy, double delta_t) const {
 double ax = fx / ps.m;
 double vx = ps.v_x + ax * delta_t;
 double x = ps.x + ps.v_x * delta_t + 0.5 * ax * delta_t * delta_t;


 double ay = fy / ps.m;
 double vy = ps.v_y + ay * delta_t;
 double y = ps.y + ps.v_y * delta_t + 0.5 * ay * delta_t * delta_t;


 G::PlanetState r{ps.m, x, y, vx, vy};
 return r;
}
























