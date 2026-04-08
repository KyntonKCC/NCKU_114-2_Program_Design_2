#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>
using namespace std;

double applyEnvironmentalPressure(double G, double P){
    return pow(G, 1.1) + sqrt(P);
}

double calculateFinalG(double baseG, double decayRate = 0.6, double prevG = 0.0, double act = 1.0){
    return baseG + (decayRate * act * prevG);
}

int main(){
    vector<double> baseG;
    vector<int> noG;
    double P, T;

    double tempG;
    while(cin >> tempG && tempG != -1)
        baseG.push_back(tempG);
    int tempN;
    while(cin >> tempN && tempN != -1)
        noG.push_back(tempN);
    cin >> P >> T;

    int n = baseG.size();
    vector<bool> isOrange(n + 1, true);
    for(int i = 0; i < noG.size(); i++)
        if(1 <= noG[i] && noG[i] <= n)
            isOrange[noG[i]] = false;

    vector<double> finalG(n);
    bool trigger = false;
    bool effect = false;
    for(int i = 0; i < n; i++){
        double adjBase = applyEnvironmentalPressure(baseG[i], P);
        double decayRate = (i == 0) ? 0.0 : (isOrange[i] ? 0.6 : 0.3);
        double prevG = (i == 0 ? 0.0 : finalG[i - 1]);
        double currAct = effect ? 0.8 : 1.0;
        finalG[i] = calculateFinalG(adjBase, decayRate, prevG, currAct);
        if(!effect && finalG[i] > T){
            trigger = true;
            effect = true;
        }
    }

    cout << fixed << setprecision(2);
    cout << "Last Generation Gene: " << finalG.back() << endl;
    cout << "All Adjusted Genes:" << endl;
    for(int i = 0; i < n; i++)
        cout << setw(8) << finalG[i];
    cout << endl;
    cout << "Gene Fatigue: " << (trigger ? "YES" : "NO") << endl;
    return 0;
}