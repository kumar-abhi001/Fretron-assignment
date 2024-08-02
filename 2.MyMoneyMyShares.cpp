#include<bits/stdc++.h>

using namespace std;

//distribution of apples among shares
void distributeAppple(vector<vector<int>> &appleQuantity, vector<int> appleWeight, vector<int> shares, vector<int> sharesWeight) {  
    for(int i = 0; i < appleWeight.size(); i++) {
        int minIndex = 0;
        for(int j = 1; j < shares.size(); j++) {
            if(sharesWeight[j] < sharesWeight[minIndex]) {
                minIndex = j;
            }
        }
        sharesWeight[minIndex] += appleWeight[i];
        appleQuantity[minIndex].push_back(appleWeight[i]);
    }

    for(int i = 0; i < shares.size(); i++) {
        cout << "Share " << i + 1 << " : ";
        for(int j = 0; j < appleQuantity[i].size(); j++) {
            cout << appleQuantity[i][j] << " ";
        }
        cout << endl;
    }
}
int main() {
    vector<int> appleWeight;

    //taking input of apple weight
    cout << "Enter the weight of apples: ";
    while(true) {
        int weight;
        cin >> weight;
        if(weight == -1) {
            break;
        }
        appleWeight.push_back(weight);
    }

    //array of shares
    vector<int> shares = {50, 30, 20};
    vector<int> sharesWeight = {0, 0, 0};

    vector<vector<int>> appleQuantity(3);

    distributeAppple(appleQuantity, appleWeight, shares, sharesWeight);

    vector<string> names = {"Ram", "sham", "rahim"};

    //printing the distribution of apples among shares
    for (int i = 0; i < shares.size(); i++) {
        cout << names[i] << " : ";
        for (int j = 0; j < appleQuantity[i].size(); j++) {
            cout << appleQuantity[i][j] << " ";
        }
        cout << endl;
    }
}