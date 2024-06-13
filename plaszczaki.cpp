#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

class plaszczak
{
    int id;
    int energy;
    bool urlop;

public:

    plaszczak(int id, int energy, bool urlop)
    {
        this->id = id;
        this->energy = energy;
        this->urlop = urlop;
    }

    int getId()
    {
        return id;
    }

    int getEnergy() const
    {
        return energy;
    }

    bool getUrlop()
    {
        return urlop;
    }

    int minimizeRests(vector<int> fence)
    {
        int restAmount = 0;
        if((int)fence.size() - energy <= 0)
        {
            return 0;
        }

        for(int i = 0; i < fence.size() - energy; i++)
        {
            bool isResting = true;
            int index = i + energy;

            //jezeli w zakresie energii znajdzie miejsce gdzie warunek jest spelniony to po petli przejdzie do tego miejsca
            //w przeciwnym wypaku przejdzie do najdalszego dostepnego miejsca i tam odslucha melodie
            for(int k = i; k < i + energy; k++)
            {
                if(fence[k + 1] < fence[k])
                {
                    index = k + 1;
                    isResting = false;
                }
            }
            if(isResting)
            {
                restAmount++;
            }
            i = index - 1;
        }
        return restAmount;
    }
};



int main()
{
    vector<int> fence = {1, 2, 3, 3, 5, 3, 2, 8, 4, 2, 2, 5, 3}; //zawiera wysokosci punktow w plocie
    vector<plaszczak> plaszczaki;

    ifstream input("plaszczaki.txt");
    if(!input.good())
    {
        cerr << "blad otwarcia pliku!";
        exit(-1);
    }

    while(!input.eof())
    {
        int id, energy;
        bool urlop;
        input >> id >> energy >> urlop;

        plaszczak temp(id, energy, urlop);
        if(!temp.getUrlop()) //jak plaszczak wzial urlop to go nie dodajemy na liste
        {
            plaszczaki.push_back(temp);
        }
    }

    if(plaszczaki.size() < 7)
    {
        cout << "Dostarczyles za malo plaszczakow, lub zbyt wielu wzielu urlop. Znajdz wiecej i wroc.";
        exit(0);
    }

    //sortujemy plaszczaki po energii
    sort(plaszczaki.begin(), plaszczaki.end(), [](const plaszczak& a, const plaszczak& b) {
        return a.getEnergy() > b.getEnergy();
    });

    cout << "Heretyk wybral plaszczakow o numerach: ";
    for(int i = 0; i < 7; i++)
    {
        cout << plaszczaki[i].getId() << ", ";
    }
    cout << plaszczaki[6].getEnergy() << endl << endl;

    //obliczamy plaszczakom minimalna ilosc odsluchan
    for(int i = 0; i < 7; i++)
    {
        cout << "Minimalna ilosc dla plaszczaka " << plaszczaki[i].getId() << ": " << plaszczaki[i].minimizeRests(fence) << endl;
    }

    return 0;
}
