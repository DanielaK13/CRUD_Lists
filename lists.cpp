#include <iostream>
#include <list>
#include <fstream>
#include <algorithm>
#include <string>
#include <istream>
#include <iterator>

using namespace std;

struct filme{

    int cont, cod;
    float preco, novo_preco, copias;
    string nome, gen;

};

bool carregarArquivo (list<filme> &l);
bool adicionarFilme(list<filme> &l);
bool buscarFilme(list<filme> &l);
bool alterarFilme(list<filme> &l);
bool excluirFilme(list<filme> &l);
void mostrarFilme(list<filme> &l);
void mostrarGeneroFilme(list<filme> &l);
bool comparaLista (list<filme>&l);
bool exportarArquivo(list<filme> &l, int tipo);


int main(){

    int menu;

    list<filme> l;

    setlocale(0, "portuguese");

    carregarArquivo(l);

    cout << endl << endl;
    cout << "| ******* MOVIES ******* |" << endl;
    do
    {
        cout << endl << "========= MENU =========" << endl << endl;

        cout << "[1] - Add movie..." << endl;
        cout << "[2] - Search movie..." << endl;
        cout << "[3] - Modify movie..." << endl;
        cout << "[4] - Delete movie..." << endl;
        cout << "[5] - Show list..." << endl;
        cout << "[6] - Show by genre..." << endl;
        cout << "[7] - Export file... " << endl;
        cout << "[8] - Exit..." << endl << endl;

        cout << "Type your option: ";
        cin  >> menu; cin.ignore();

        switch(menu){

              case 1 :
                  adicionarFilme(l);
                  continue;

              case 2 :
                  buscarFilme(l);
                  continue;

              case 3 :
                  alterarFilme (l);
                  continue;

              case 4 :
                  excluirFilme(l);
                  continue;

              case 5 :
                  mostrarFilme(l);
                  continue;

              case 6 :
                  mostrarGeneroFilme(l);
                  continue;

              case 7 :
                exportarArquivo(l, 1);
                continue;
        }

    }

    while(menu != 8); // fim

    return 0;
}

bool carregarArquivo(list<filme>& l){
    ifstream arq;
    arq.open("movies.txt");

    filme f;

    if(!arq){ // problema ao ler arquivo
        cout << "Couldn't open file.";
        return 2;
    }

    return true;
}

bool adicionarFilme(list<filme>& l){

    filme f;
    int cont = 0;

    cout << endl;
    cout << "--- Add Film --- \n" << endl;

    cout << "Code: ";
        cin >> f.cod; cin.ignore();

    cout << "Name: ";
        getline(cin, f.nome);

    cout << "Genre: "<< endl;
        cout << "\t [C] - Comedy" << endl;
        cout << "\t [D] - Drama"<< endl;
        cout << "\t [S] - Science fiction" << endl;
        cout << "\t [W] - War"<<endl;
        cout << "\t [M] - Musical"<<endl;
        cout << "\t [R] - Romance"<<endl;
        cout << "\t [T] - Thriller"<<endl;
        cout << "\t [H] - Horror"<<endl;
        getline(cin, f.gen);

    cout << "Price: $ ";
        cin >> f.preco; cin.ignore();

    cout << "Copies sold: ";
        cin >> f.copias; cin.ignore();

    cout << "\nSUCCESSFUL INCLUSION! \n";

    if(l.empty() || f.cod > l.back().cod){
        l.push_back(f);
    }
    else {
        for(auto c: l){
            if(f.cod == c.cod){
                cout << "\nThis film is already registered! \n";
                return false;
            }
            continue;
        }
    }
    for (auto it=l.begin(); it!=l.end(); ++it){
        if (f.cod == it->cod){
                it->cont ++;
                break;
        }
        if(it->cod > f.cod){
            l.insert(it, f);
            break;
        }
    }
    return 0;
}

void mostrarFilme(list<filme>& l){

    filme f;
    auto it = l.begin();
    if(!l.empty()){
        cout << endl;
        cout << "--- List of Films --- " << endl;
        for (; it!=l.end(); ++it){
            cout << endl;
            cout << "Code: " << it->cod << endl;
            cout << "Name: " << it->nome << endl;
            cout << "Genre: " << it->gen << endl;
            cout << "Price: $ " << it->preco << ".00" << endl;
            cout << "Copies sold: " << it->copias << endl;
        }
        cout << "-----------------------" << endl;
    }
    else{
        cout << "\nMovie list is empty!" << endl;
    }

}

bool excluirFilme(list<filme> &l){

    filme f;
    if(l.size()==0){
        cout<<"\nThere is no film registered!"<<endl;
        return false;
    }
    cout << " \nEnter the CODE you want to delete: ";
    cin >> f.cod;
    for(auto it=l.begin(); it!=l.end(); ++it){
            if(f.cod==it->cod){
                l.erase(it);
                cout<<"\nSuccessfully deleted!\n";
                return true;
            }
    }
    cout<<"\nThere are no movies in the list.\n";
    return false;
}

bool exportarArquivo(list<filme> &l, int tipo){

    if(tipo == 1){

        ofstream saida;
        saida.open("MovieList.html", ios::ate);

        if(!saida){
            cout << "\nError exporting movie list! \n";

            return 2;
        }

        saida<<"LIST OF MOVIES </br>";
        saida << endl;

        int i = 1;

        for(auto it=l.begin(); it!=l.end(); ++it){

            saida << i << "° Movie</br>";
            saida << "Code: " << it->cod << "</br>";
            saida << "Name: " << it->nome << "</br>";
            saida << "Genre: " << it->gen << "</br>";
            saida << "Price: $ " << it->preco << ".00" << "</br>";
            saida << "Copies sold: " << it->copias << "</br>";
            saida << "</br>";
            i++;
        }

        cout<<"\nThe list of films was successfully exported! \n"<<endl;

    }else if(tipo == 2){

        ofstream saida;

        saida.open("moviesList.txt", ios::ate);

        if(!saida){
            cout << "\nError saving movie list! \n";
            return 2;
        }

        for(auto it = l.begin(); it != l.end(); ++it){

            saida << "Code: " << it->cod << "</br>";
            saida << "Name: " << it->nome << "</br>";
            saida << "Genre: " << it->gen << "</br>";
            saida << "Price: $ " << it->preco << "</br>";
            saida << "Copies sold: " << it->copias << "</br>";
        }
    }
}

bool buscarFilme(list<filme>&l){
    filme f;
    auto it = l.begin();
    string buscarCod;

    cout << endl;
    cout << "Enter the CODE you want to search: ";
    getline(cin, buscarCod);

    for (; it!=l.end(); ++it){

        cout << "\nCode: " << it->cod << endl;
        cout << "Name: " << it->nome << endl;
        cout << "Genre: " << it->gen << endl;
        cout << "Price: $ " << it->preco << ".00" << endl;
        cout << "Copies sold: " << it->copias << endl;
    }
    return 0;
}

bool alterarFilme(list<filme>& l){
    filme f;
    buscarFilme(l);
    float preco_novo;

    if(!l.empty()){
        cout << "\nNew price: "; cin.ignore();
        cin >> preco_novo;
        f.preco = preco_novo;
    }
    else{
        cout << "\nEmpty movie list!" << endl;
    }
}

void mostrarGeneroFilme(list<filme> &l){
    auto it = l.begin();
    char gen;
    cout << "List by Genre: "<< endl;
        cout << "\t [C] - Comedy" << endl;
        cout << "\t [D] - Drama"<< endl;
        cout << "\t [S] - Science fiction" << endl;
        cout << "\t [w] - War"<<endl;
        cout << "\t [M] - Musical"<<endl;
        cout << "\t [R] - Romance"<<endl;
        cout << "\t [T] - Thriller"<<endl;
        cout << "\t [H] - Horror"<<endl;
    cin >> gen;
    switch(gen){
            case 1: 'R'; break; //romance
            case 2: 'W'; break; //guerra
            case 3: 'T'; break; // suspense
            case 4: 'H'; break; //terror
            case 5: 'D'; break;//drama
            case 6: 'C'; break;//comedia
            case 7: 'S'; break;//ficcao cientifica
            case 8: 'M'; break;//musical
        }
    cout << "\nList by Genre:" << " " << gen << endl;
    for (; it!=l.end(); ++it){
        cout << endl;
        cout << "Code: " << it->cod << endl;
        cout << "Name: " << it->nome << endl;
        cout << "Genre: " << it->gen << endl;
        cout << "Price: $ " << it->preco << ".00" << endl;
        cout << "Copies sold: " << it->copias << endl;
    }
}

