#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#define unt unsigned int
using namespace std;

unt filasSS;
unt columnasSS;
vector<vector<unt>> SS;
vector<vector<string>> SScin;
vector<string> formulas;

unt getColumn(const string& column) {
    unt columnToInt = 0;
    for (char c : column) columnToInt = 26 * columnToInt + c - 65 + 1;
    return columnToInt - 1;
}

vector<string> CellFormula(string cell) {
    cell.erase(remove(cell.begin(), cell.end(), '='), cell.end());
    stringstream ss(cell);
    string token;
    vector<string> splitCell;
    while(getline(ss, token, '+')) splitCell.push_back(token);
    return splitCell;
}

pair<int, int> cellPosition(const string& cell) {
    string row, column;
    for (char c : cell) isalpha(c) ? column += c : row += c;
    return make_pair(stoi(row) - 1, getColumn(column));
}

bool solve(string &form){
    unt temp = 0;
    for(unt i=0; i < CellFormula(form).size(); i++){
        pair<int, int> currentCellPosition = cellPosition(CellFormula(form)[i]);
        if(SS[currentCellPosition.second][currentCellPosition.first] != 0){
            temp+=SS[currentCellPosition.second][currentCellPosition.first];
        }
        else{
            return false;
        }
    }
    for(unt i=0; i<filasSS; i++)
        for(unt j=0; j<columnasSS; j++){
            if(SScin[i][j] == form){
                SS[i][j]=temp;
            }
        }
    return true;
}

void formulaToNum(unt formul){
    if(formul >= formulas.size() or formul< 0){
        if(solve(formulas[formul])) formulaToNum(formul+1);
        else formulaToNum(formul-1);
    }
}

int main() {
    unt numberOfSS;
    cin>>numberOfSS;

    while(numberOfSS>0){
        cin>>columnasSS;
        cin>>filasSS;

        for(unt i=0; i<filasSS; i++){
            vector<unt> a;
            SS.push_back(a);
            for(unt j=0; j<columnasSS; j++){
                SS[i].push_back(0);
            }
        }

        string x;
        for(unt i=0; i<filasSS; i++){
            vector<string> b;
            SScin.push_back(b);
            for(unt j=0; j<columnasSS; j++){
                cin>>x;
                SScin[i].push_back(x);
            }
        }

        for(unt i=0; i<filasSS; i++)
            for(unt j=0; j<columnasSS; j++){
                if(SScin[i][j][0]!='='){
                    stringstream num(SScin[i][j]);
                    num >> SS[i][j];
                }
            }

        for(unt i=0; i<filasSS; i++)
            for(unt j=0; j<columnasSS; j++){
                if(SScin[i][j][0]=='='){
                    formulas.push_back(SScin[i][j]);
                }
            }

        formulaToNum(formulas.size()-1);

        for(unt i=0; i<filasSS; i++) {
            cout << '\n';
            for (unt j = 0; j < columnasSS; j++)
                cout << SS[i][j] << " ";
        }

        --numberOfSS;
    }

    return EXIT_SUCCESS;
}