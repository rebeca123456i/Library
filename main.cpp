#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip> 
#include <algorithm> 

using namespace std;

class Carte {

protected:
    string titlu;
    string autor;
    int anPublicare;
   
    string domeniu;

public:
    // Constructor implicit
    Carte(const string& titlul = "", const string& autorul = "", int an = 0, const string& dom = "")
        : titlu(titlul), autor(autorul), anPublicare(an),domeniu(dom) 
    {}


    // Destructor
    virtual ~Carte() {
        cout << "Destructor Carte: " << titlu << '\n';
    }

    // Funcție virtuală de afișare
    virtual void afiseaza() const {
        cout << "Titlu: " << titlu << ", Autor: " << autor << ", An: " << anPublicare << ", Domeniu: " << domeniu << endl;
    }

    // Getter și setter
    string getTitlu() const 
    { 
        return titlu; 
    }
    void setTitlu(const string& t) 
    {
        titlu = t; 
    }

    string getAutor() const 
    {
        return autor; 
    }
    void setAutor(const string& a)
    { 
        autor = a; 
    }

    int getAn() const 
    { 
        return anPublicare; 
    }
    void setAn(int a) 
    { 
        anPublicare = a; 
    }

    string getDomeniu() const 
    { 
        return domeniu; 
    }
    void setDomeniu(const string& d) 
    { 
        domeniu = d; 
    }


    friend istream& operator>>(istream& in, Carte& c)
    {
        getline(in, c.titlu);
        getline(in, c.autor);
        in >> c.anPublicare;
        in.ignore(); // să "consume" newline-ul
        getline(in, c.domeniu);
        return in;
    }
};



    class CarteCuPDF : public Carte {

        string linkPDF;

    public:
        // Constructor
        CarteCuPDF(const string& t = "", const string& a = "", int an = 0, const string& link = "", const string& dom = "")
            : Carte(t, a, an, dom), linkPDF(link) {
        }


        // Funcția override de afișare
        void afiseaza() const override {
            Carte::afiseaza();
            cout << "Link: " << linkPDF << endl;
        }

        // Getter și setter
        string getLink() const { return linkPDF; }
        void setLink(const string& l) { linkPDF = l; }
    };







    class Biblioteca {
        vector<Carte*> carti;

    public:
        void adaugaCarte(Carte* c) {
            carti.push_back(c);
        }

        void afiseazaToate() const {
            for (const auto& c : carti) {
                c->afiseaza();
                cout << "---------------------------------------------------------------------------------------------------------------------\n";
            }
        }

        bool existaCarte(const string& titlu, const string& autor) const {
            for (const auto& c : carti) {
                if (c->getTitlu() == titlu && c->getAutor() == autor) {
                    return true;
                }
            }
            return false;
        }

        ~Biblioteca() {
            for (auto c : carti) {
                delete c;
            }
        }
        void cautaCartiDupaAutor(const string& autorCautat) const 
        {
            bool gasit = false;  
            cout << '\n';
            cout << "**********************CARTIILE DUPA AUTORUL ALES**********************************************\n\n";
            for (const auto& carte : carti) 
            {
                if (carte->getAutor() == autorCautat)
                { 
                 
                    carte->afiseaza();
                  
                    gasit = true;
                }
            }
            if (!gasit) {
                cout << "Nu s-au gasit carti scrise de autorul \"" << autorCautat << "\".\n";
            }
        }
        void afiseazaCartiDupaDomeniu(const string& domeniuCautat) const 
        {
            bool gasit = false;  
            cout << '\n';
            cout << "**********************CARTIILE DUPA DOMENIUL ALES**********************************************\n\n";
            for (const auto& carte : carti) {
                if (carte->getDomeniu() == domeniuCautat)
                {
                  
                    carte->afiseaza();
                 
                    gasit = true;
                }
            }
            if (!gasit) {
                cout << "Nu s-au gasit carti din domeniul \"" << domeniuCautat << "\".\n";
            }
        }

        void afiseazaCartiDinPerioada(int anStart, int anSfarsit) const 
        {
            bool gasit = false;
            cout << "\n**********************CARTILE PUBLICATE INTRE " << anStart << " SI " << anSfarsit << " **********************\n\n";
            for (const auto& carte : carti) {
                int an = carte->getAn();
                if (an >= anStart && an <= anSfarsit) {
                    carte->afiseaza();
                    gasit = true;
                }
            }
            if (!gasit) {
                cout << "Nu s-au gasit carti publicate in perioada specificata.\n";
            }
        }
        void cautaCartiCuLitera(char litera) const 
        {
            bool gasit = false;
            cout << "\n**********************CARTILE CARE INCEP CU LITERA '" << litera << "'**********************\n\n";

            for (const auto& carte : carti) {
                if (!carte->getTitlu().empty() && toupper(carte->getTitlu()[0]) == toupper(litera)) {
                    carte->afiseaza();
                    gasit = true;
                }
            }

            if (!gasit) {
                cout << "Nu s-au gasit carti care sa inceapa cu litera '" << litera << "'.\n";
            }
        }


        void sorteazaDupaAutor() {
            for (size_t i = 0; i < carti.size(); ++i) {
                for (size_t j = i + 1; j < carti.size(); ++j) {
                    if (carti[i]->getAutor() > carti[j]->getAutor()) {
                        swap(carti[i], carti[j]);
                    }
                }
            }
        }


        void afiseazaNumarExemplare(const string& titlu, const string& autor) const 
        {
            int count = 0;
            for (const auto& carte : carti) {
                if (carte->getTitlu() == titlu && carte->getAutor() == autor) 
                {
                    ++count;
                }
            }
            cout << "Exista " << count << " exemplare ale cartii \"" << titlu << "\" scrisa de " << autor << ".\n";
        }


    };


    void citesteCartiDinFisier(Biblioteca& biblio, const string& fisier) 
    {
    ifstream in("C:\\Users\\andro\\Desktop\\anul 1\\Programarea orientata spre obiect\\proiect_biblioteca\\carti.txt");  // Deschide fișierul
    if (!in) {
        cerr << "Nu s-a putut deschide fișierul!"<<endl;
        return;
    }

    string titlu, autor, domeniu;
    int an;

    while (getline(in, titlu) && getline(in, autor) && in >> an && in.ignore() && getline(in, domeniu)) {
        Carte* c = new Carte(titlu, autor, an, domeniu);
        biblio.adaugaCarte(c);
    }

    in.close();

}
    
    /// Funcția meniu
    void meniu(Biblioteca& biblio)
    {
        int opt = -1;
        while (opt != 0) {
            system("CLS");
            cout << "\t\t M E N I U   B I B L I O T E C A\n";
            cout << "------------------------------------------------------------------\n";
            cout << left << setw(75) << "* 0 - Iesi din meniu" << endl;
            cout << left << setw(75) << "* 1 - Afisarea cartilor din bibloteca" << endl;
            cout << left << setw(75) << "* 2 - Cautarea cartilor dupa autor" << endl;
            cout << left << setw(75) << "* 3 - Afisarea cartilor dintr-un anumit domeniu (literatura, poezier, etc.)" << endl;
            cout << left << setw(75) << "* 4 - Afisarea cartilor publicate intr-o perioada" << endl;
            cout << left << setw(75) << "* 5 - Listarea in ordine alfabetica a autorului" << endl;
            cout << left << setw(75) << "* 6 - Cautarea toate cartiile cu litera data" << endl;
            cout << left << setw(75) << "* 7 - Afisarea numarului de exemplare pentru un titlu de carte, editura si autor" << endl;
            cout << left << setw(75) << "* 8 -Adaugarea unei carti in biblioteca" << endl;
            cout << "------------------------------------------------------------------\n";
            cout << "\nIntroduceti optiunea dorita: ";
            cin >> opt;
            cin.ignore();

            switch (opt) {
            case 1:
            {
                biblio.afiseazaToate();
                break;
            }
            case 2:
            {
                string autor;
                cout << "Introduceti numele autorului: ";
                getline(cin, autor);
                biblio.cautaCartiDupaAutor(autor);
                break;
            }
            case 3:
            {
                string domeniu;
                cout << "Introduceti domeniul: ";
                getline(cin, domeniu);
                biblio.afiseazaCartiDupaDomeniu(domeniu);
                break;
            }
               
            case 4:
            {
                int anStart, anSfarsit;
                cout << "Introduceti anul de inceput: ";
                cin >> anStart;
                cout << "Introduceti anul de sfarsit: ";
                cin >> anSfarsit;
                cin.ignore();
                biblio.afiseazaCartiDinPerioada(anStart, anSfarsit);
               break;
            }
               
            case 5:
            {
                biblio.sorteazaDupaAutor(); // Sortează cărțile după autor
                cout << "Cartile au fost sortate dupa autor:\n";
                biblio.afiseazaToate(); // Afișează cărțile sortate
                break;
            }
               
            case 6:
            {
                char litera;
                cout << "Introduceti litera: ";
                cin >> litera;
                cin.ignore(); // consumă newline
                biblio.cautaCartiCuLitera(litera);

                  break;
            }
              
            case 7:
            {
                string titlu, autor;
                cout << "Titlul cartii: ";
                getline(cin, titlu);
                cout << "Autorul cartii: ";
                getline(cin, autor);
                biblio.afiseazaNumarExemplare(titlu, autor);

             
                break;
            }
            case 8:
            {
                string titlu, autor, link;
                int an;
                cout << "Titlu: ";
                getline(cin, titlu);
                cout << "Autor: ";
                getline(cin, autor);

                if (biblio.existaCarte(titlu, autor)) {
                    cout << "Cartea deja exista in biblioteca!\n";
                }
                else {
                    cout << "An publicare: ";
                    cin >> an;
                    cin.ignore();
                    cout << "Link PDF (sau lasa gol): ";
                    getline(cin, link);

                    if (link.empty()) {
                        biblio.adaugaCarte(new Carte(titlu, autor, an));
                    }
                    else {
                        biblio.adaugaCarte(new CarteCuPDF(titlu, autor, an, link));
                    }
                    cout << "Cartea a fost adaugata cu succes!\n";
                }
                break;
            }
            case 0:
                cout << "Iesire din aplicatie...\n";
                break;
            default:
                cout << "Optiune invalida.\n";
            }

            system("pause");
        }
    }
    int main()
    {



        Biblioteca b;
         citesteCartiDinFisier(b, "C:\\Users\\andro\\Desktop\\anul 1\\Programarea orientata spre obiect\\proiect_biblioteca\\carti.txt");
         meniu(b); 



        return 0;
    
        }
