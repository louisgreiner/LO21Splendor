#ifndef RESOURCES_H
#define RESOURCES_H

#include <iostream>

class Resources{
    private:
        // Attributes
        int diamond;
        int sapphire;
        int emerald;
        int ruby;
        int onyx;
        int gold;
    public:
        // Constructors
        Resources(); // DONE
        Resources(int d, int s, int e, int r, int o, int g); // DONE
        Resources& operator=(const Resources& res) = default;
        Resources* FactoryMethod() const{
            return new Resources(*this);
        }
        // Getters
        int getDiamond(); // DONE
        int getSapphire(); // DONE
        int getEmerald(); // DONE
        int getRuby(); // DONE
        int getOnyx(); // DONE
        int getGold(); // DONE
        int getSum(); // DONE // except gold
        void getInformations(std::ostream& f= std::cout) const; // DONE
        // Setters
        void setDiamond(int d); // DONE
        void setSapphire(int s); // DONE
        void setEmerald(int e); // DONE
        void setRuby(int r); // DONE
        void setOnyx(int o); // DONE
        void setGold(int g); // DONE
        // Destructors
        ~Resources() = default;
};

std::ostream& operator<<(std::ostream& f, const Resources& res); // DONE

#endif // RESOURCES_H
