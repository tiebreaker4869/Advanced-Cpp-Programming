#include <iostream>

using namespace std;

int main(){
    int sumOfMale = 0, sumOfFemale = 0;
    int n, age;
    cin >> n;
    string name, gender;
    while(n -- ){
        cin >> age >> gender >> name;
        if(gender == "m")sumOfMale += age;
        else sumOfFemale += age;
    }
    
    cout << "f: " << sumOfFemale << endl;
    cout << "m: " <<sumOfMale << endl;
    
    return 0;
}