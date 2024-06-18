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
    vector<int> fence;// = {1, 2, 3, 3, 5, 3, 2, 8, 4, 2, 2, 5, 3}; //zawiera wysokosci punktow w plocie
    vector<plaszczak> plaszczaki;
    int n;

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
        if(energy == 0)
        {
            cout << "Plaszczak nie moze miec 0 energii";
            input.close();
            exit(0);
        }

        plaszczak temp(id, energy, urlop);
        if(!temp.getUrlop()) //jak plaszczak wzial urlop to go nie dodajemy na liste
        {
            plaszczaki.push_back(temp);
        }
    }
    input.close();

    if(plaszczaki.size() < 7)
    {
        cout << "Dostarczyles za malo plaszczakow, lub zbyt wielu wzielu urlop. Znajdz wiecej i wroc.";
        exit(0);
    }

    cout << "Podaj ilosc punktow plotu: ";
    cin >> n;
    if(n == 0)
    {
        cout << "Plot nie moze miec dlugosci 0...";
        exit(0);
    }

    cout << "Podaj jasnosci: ";
    for(int i = 0; i < n; i++)
    {
        int bright;
        cin >> bright;
        fence.push_back(bright);
    }

    //sortujemy plaszczaki po energii
    sort(plaszczaki.begin(), plaszczaki.end(), [](const plaszczak& a, const plaszczak& b) {
        return a.getEnergy() > b.getEnergy();
    });

    cout << "Heretyk wybral plaszczakow o numerach: ";
    for(int i = 0; i < 7; i++)
    {
        cout << plaszczaki[i].getId() << " ";
    }
    cout << endl << endl;

    //obliczamy plaszczakom ounkt startu oraz minimalna ilosc odsluchan melodii
    for(int i = 0; i < 7; i++)
    {
        vector<int> temp = fence; //pomocniczy wektor w ktorym bedziemy zmieniac pozycje startu
        vector<pair<int, int>> rests; //<punkt startu, ilosc odsluchan>

        rests.push_back(make_pair(0, plaszczaki[i].minimizeRests(temp))); //start z punktu 0 dla i-tego straznika

        //punkt 0 przesuwamy na koniec a reszte przesuwamy 1 miejsce do przodu, czynnosc powtarzamy n - 1 razy
        //w ten dla kazdego punktu startu z plotu obliczamy minimalna liczbe odsluchan meldii po czym wrzucamy do wektora
        for(int j = 0; j < n - 1; j++)
        {
            int temp2 = temp[0]; //zmienna pomocnicza na punkt 0
            for(int k = 1; k < n; k++) //punkty od 1 do konca przesuwamy do przodu o 1 miejsce
            {
                temp[k - 1] = temp[k];
            }
            temp[n - 1] = temp2; //nasz punkt 0 wrzucamy na koniec wektora

            //dodajemy do wektora punkt startu i ilosc odsluchan
            rests.push_back(make_pair(j + 1, plaszczaki[i].minimizeRests(temp)));
        }

        //szukamy minimalna ilosc odsluchan i ja wypisujemy razem z punktem startowym i-tego straznika
        auto mini = min_element(rests.begin(), rests.end(),
                                           [](const pair<int, int>& a, const pair<int, int>& b) {
                                               return a.second < b.second;
                                           });
        cout << "Plaszczak nr " << plaszczaki[i].getId() << " startuje z punktu nr " << mini->first;
        cout << " oraz odsluchuje melodie " << mini->second << " razy" << endl;
    }

    return 0;
}
