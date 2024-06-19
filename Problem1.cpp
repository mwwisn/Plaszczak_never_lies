#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdlib>
#include <ctime>
#include <climits>
#include <cfloat>
#include <cmath>

using namespace std;

struct PunktOrientacyjny {
    int x;
    int y;
};

struct Sciezka {
    int punktOrientacyjny;
    double dlugoscDrogi;
};

int orientacja(PunktOrientacyjny p, PunktOrientacyjny q, PunktOrientacyjny r) {
    int wartosc = (q.y - p.y) * (r.x - q.x) - (q.x - p.x) * (r.y - q.y);
    if (wartosc == 0) return 0; // punkty sa wspolniliowe
    else if (wartosc > 0) return 1; // prawoskretne
    else return 2; // lewoskretne
}

vector<int> znajdzOtoczkeWypukla(vector<PunktOrientacyjny>& punktyOrientacyjne) {
    int n = punktyOrientacyjne.size();
    if (n < 3) return {}; // mniej ni¿ 3 punkty nie tworz¹ otoczki

    vector<int> otoczkaWypukla;
    int p = 0, q, lewy = 0;
    do {
        otoczkaWypukla.push_back(p);
        q = (p + 1) % n;
        for (int i = 0; i < n; i++) {
            if (orientacja(punktyOrientacyjne[p], punktyOrientacyjne[i], punktyOrientacyjne[q]) == 2) {
                q = i;
            }
        }
        p = q;
    } while(p != lewy);

    return otoczkaWypukla;
}

vector<double> dijkstra(int liczbaWierzcholkow, int polozenieFabryki, vector<vector<Sciezka>>& sciezki) {
    vector<double> odleglosci(liczbaWierzcholkow, DBL_MAX);
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> kolejka;

    odleglosci[polozenieFabryki] = 0;
    kolejka.push({0, polozenieFabryki});

    while (!kolejka.empty()) {
        double obecnaOdleglosc = kolejka.top().first;
        int obecnyWierzcholek = kolejka.top().second;
        kolejka.pop();

        for (const Sciezka& krawedz : sciezki[obecnyWierzcholek]) {
            int sasiedniWierzcholek = krawedz.punktOrientacyjny;
            double wagaKrawedzi = krawedz.dlugoscDrogi;

            if (odleglosci[obecnyWierzcholek] + wagaKrawedzi < odleglosci[sasiedniWierzcholek]) {
                odleglosci[sasiedniWierzcholek] = odleglosci[obecnyWierzcholek] + wagaKrawedzi;
                kolejka.push({odleglosci[sasiedniWierzcholek], sasiedniWierzcholek});
            }
        }
    }

    return odleglosci;
}

class GrafDwudzielny {
    int liczbaWierzcholkowU, liczbaWierzcholkowV;
    vector<vector<int>> listaSasiedztwa;
    vector<int> para_u, para_v, odleglosc;

    bool bfs() {
        queue<int> kolejka;
        for (int i = 0; i < liczbaWierzcholkowU; ++i) {
            if (para_u[i] == -1) {
                odleglosc[i] = 0;
                kolejka.push(i);
            } else {
                odleglosc[i] = INT_MAX;
            }
        }
        bool znalezionoSciezkePowiekszajaca = false;
        // fragment utworzony przez chat gpt
        while (!kolejka.empty()) {
            int u = kolejka.front();
            kolejka.pop();
            if (odleglosc[u] != INT_MAX) {
                for (int v : listaSasiedztwa[u]) {
                    if (para_v[v - liczbaWierzcholkowU] == -1) {
                        znalezionoSciezkePowiekszajaca = true;
                    } else if (odleglosc[para_v[v - liczbaWierzcholkowU]] == INT_MAX) {
                        odleglosc[para_v[v - liczbaWierzcholkowU]] = odleglosc[u] + 1;
                        kolejka.push(para_v[v - liczbaWierzcholkowU]);
                    }
                }
            }
        }
        // koniec fragmentu
        return znalezionoSciezkePowiekszajaca;
    }

    bool dfs(int u) {
        if (u != -1) {
            for (int v : listaSasiedztwa[u]) {
                if (para_v[v - liczbaWierzcholkowU] == -1 || (odleglosc[para_v[v - liczbaWierzcholkowU]] == odleglosc[u] + 1 && dfs(para_v[v - liczbaWierzcholkowU]))) {
                    para_u[u] = v;
                    para_v[v - liczbaWierzcholkowU] = u;
                    return true;
                }
            }
            odleglosc[u] = INT_MAX;
            return false;
        }
        return true;
    }

public:
    GrafDwudzielny(int _liczbaWierzcholkowU, int _liczbaWierzcholkowV) : liczbaWierzcholkowU(_liczbaWierzcholkowU),
    liczbaWierzcholkowV(_liczbaWierzcholkowV), listaSasiedztwa(_liczbaWierzcholkowU), para_u(_liczbaWierzcholkowU, -1),
    para_v(_liczbaWierzcholkowV, -1), odleglosc(_liczbaWierzcholkowU) {}

    void dodajKrawedz(int u, int v) {
        listaSasiedztwa[u].push_back(v + liczbaWierzcholkowU);
    }

    int hopcroft_karp() {
        int skojarzenia = 0;
        while (bfs()) {
            for (int i = 0; i < liczbaWierzcholkowU; ++i) {
                if (para_u[i] == -1 && dfs(i)) {
                    ++skojarzenia;
                }
            }
        }
        return skojarzenia;
    }

    void wypiszPary() {
        cout << "Pary plaszczkow:" << endl;
        for (int i = 0; i < liczbaWierzcholkowU; ++i) {
            if (para_u[i] != -1) {
                cout << i << " " << para_u[i] - liczbaWierzcholkowU << endl;
            }
        }
    }
};

int kijkiPakowanie(vector<double>& ucieteKijki) {
    sort(ucieteKijki.rbegin(), ucieteKijki.rend()); // Sortowanie malej¹co
    vector<double> duzeKije;

    for (double dlugosc : ucieteKijki) {
        bool umieszczony = false;
        for (double& duzyKij : duzeKije) {
            if (duzyKij + dlugosc <= 1.0) {
                duzyKij += dlugosc;
                umieszczony = true;
                break;
            }
        }
        if (!umieszczony) {
            duzeKije.push_back(dlugosc);
        }
    }
    return duzeKije.size();
}

int main() {
    srand(time(NULL));
    int iloscPunktowOrientacyjnych, iloscSciezek;
    cout << "Podaj liczbe punktow orientacyjnych oraz ilosc sciezek: " << endl;
    cin >> iloscPunktowOrientacyjnych >> iloscSciezek;
    cout << endl;
    vector<PunktOrientacyjny> punktyOrientacyjne(iloscPunktowOrientacyjnych);
    vector<vector<Sciezka>> sciezki(iloscPunktowOrientacyjnych);

    // wczytywanie punktow orientacyjnych
    cout << "Podaj wspolrzedne kazdego z wierzcholkow: " << endl;
    for(int i = 0; i < iloscPunktowOrientacyjnych; ++i) {
        int x, y;
        cin >> x >> y;
        punktyOrientacyjne[i] = {x, y};
    }
    cout << endl;

    // sortuje punkty od lewej do prawej miejsca w tablicy beda uzywane jako id punktu
    sort(punktyOrientacyjne.begin(), punktyOrientacyjne.end(), [](const PunktOrientacyjny& a, const PunktOrientacyjny& b) {
        return a.x < b.x;
    });

    cout << "Posortowane punkty orientacyjne: " << endl;
    for(int i = 0; i < punktyOrientacyjne.size(); ++i){
        cout << punktyOrientacyjne[i].x << " " << punktyOrientacyjne[i].y << endl;
    }
    cout << endl;

    // wczytywanie sciezek
    cout << "Podaj sciezki (punkt 1, puntk 2, dlugosc drogi): " << endl;
    for(int i = 0; i < iloscSciezek; ++i) {
        int punkt1, punkt2;
        double dlugoscDrogi;
        cin >> punkt1 >> punkt2 >> dlugoscDrogi;
        sciezki[punkt1].push_back({punkt2, dlugoscDrogi});
        sciezki[punkt2].push_back({punkt1, dlugoscDrogi}); // jest to graf niezorientowany
    }
    cout << endl;

    vector<int> otoczkaWypukla = znajdzOtoczkeWypukla(punktyOrientacyjne);

    cout << "Otoczka wypukla: " << endl;
    for(int i = 0; i < otoczkaWypukla.size(); ++i){
        cout << otoczkaWypukla[i] << endl;
    }
    cout << endl;

    vector<double> dlugosciPomiedzyPunktamiOtoczki;
    // przypisanie kolejno dlugosciPomiedzyPunktamiOtoczki jezeli juz istnieje sciezka pomiedzy nimi
    // to = dlogosci sciezki a jezeli nie to jest losowana
    for(int i = 0; i < otoczkaWypukla.size(); ++i) {
        bool nieznaleziono = true;
        for(const auto& sciezka : sciezki[otoczkaWypukla[i]]) {
            if(sciezka.punktOrientacyjny == otoczkaWypukla[(i + 1) % otoczkaWypukla.size()]) {
                dlugosciPomiedzyPunktamiOtoczki.push_back(sciezka.dlugoscDrogi);
                nieznaleziono = false;
                break;
            }
        }
        if(nieznaleziono) {
            PunktOrientacyjny punkt1 = punktyOrientacyjne[otoczkaWypukla[i]];
            PunktOrientacyjny punkt2 = punktyOrientacyjne[otoczkaWypukla[i + 1]];
            double y = sqrt(pow(punkt2.x - punkt1.x, 2) + pow(punkt2.y - punkt1.y, 2));
            y = round(y * 100.0) / 100.0;
            dlugosciPomiedzyPunktamiOtoczki.push_back(y);
        }
    }

    cout << "Dlugosci pomiedzy punktami otoczki: " << endl;
    for(int i = 0; i < dlugosciPomiedzyPunktamiOtoczki.size(); ++i) {
        cout << dlugosciPomiedzyPunktamiOtoczki[i] << endl;
    }
    cout << endl;

    int polozenieFabryki;
    cout << "Wybierz punkt orintacyjny w ktorym jest polozona fabryka (od 0 do " << iloscPunktowOrientacyjnych - 1 << "): ";
    cin >> polozenieFabryki;

    vector<double> odleglosciOdFabryki = dijkstra(iloscPunktowOrientacyjnych, polozenieFabryki, sciezki);

    cout << "Odleglosci od fabryki: " << endl;
    for(int i = 0; i < odleglosciOdFabryki.size(); ++i){
        cout << "Punkt " << i << " jest odalony od fabryki o: " << odleglosciOdFabryki[i] << endl;
    }
    cout << endl;

    int liczbaTragarzy, ileTragarzySieWzajemnieLubi;
    cout << "Podaj liczbe tragarzy: " << endl;
    cin >> liczbaTragarzy;
    cout << endl << "Podaj ile tragarzy sie wzajemnie lubi: " << endl;
    cin >> ileTragarzySieWzajemnieLubi;
    GrafDwudzielny graf(liczbaTragarzy, liczbaTragarzy);
    cout << endl << "Podaj po kolei tragarzy ktorzy sie lubia: " << endl;
    for(int i = 0; i < ileTragarzySieWzajemnieLubi; ++i) {
        int tragarz1, tragarz2;
        cin >> tragarz1 >> tragarz2;
        graf.dodajKrawedz(tragarz1, tragarz2);
    }
    int maksymalnaIloscPar = graf.hopcroft_karp();
    cout << endl << "Stworzono lacznie " << maksymalnaIloscPar << " par" << endl;
    graf.wypiszPary();
    cout << endl;

    priority_queue<double, vector<double>, greater<double>> najmniejszyCzas;
    for(int i = 0; i < maksymalnaIloscPar; ++i) {
        najmniejszyCzas.push(0);
    }

    double czas = 0;
    int zuzyteDuzeKije = 0;
    cout << "Czas w jakim plaszczaki stawiaja kolejny kawalek plotu: " << endl;
    for(int i = 0; i < dlugosciPomiedzyPunktamiOtoczki.size(); ++i) {
        while(dlugosciPomiedzyPunktamiOtoczki[i] > 0) {
            czas = najmniejszyCzas.top();
            cout << "czas = " << czas << " + " << odleglosciOdFabryki[otoczkaWypukla[i]] * 10 << endl;
            najmniejszyCzas.pop();
            dlugosciPomiedzyPunktamiOtoczki[i] -= 1;
            czas += (odleglosciOdFabryki[otoczkaWypukla[i]] * 10);
            najmniejszyCzas.push(czas);
            zuzyteDuzeKije++;
        }
    }
    cout << endl;

    vector<double> ucieteKijki;
    for(int i = 0; i < dlugosciPomiedzyPunktamiOtoczki.size(); ++i) {
        if(dlugosciPomiedzyPunktamiOtoczki[i] != 0) {
            ucieteKijki.push_back(1 + dlugosciPomiedzyPunktamiOtoczki[i]);
            zuzyteDuzeKije--;
        }
    }
    int zuzytePocieteKije = kijkiPakowanie(ucieteKijki);
    zuzyteDuzeKije += zuzytePocieteKije;

    cout << "Plaszczaki postawily plot w czasie: " << czas << " minut" << endl;
    cout << "Ilosc zuzytych Kijkow: " << zuzyteDuzeKije << endl;

    return 0;
}
