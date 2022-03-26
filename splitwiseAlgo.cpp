/*
   Splitwise Algorithm or Minimize Cash Flow Algorithm
*/
#include<iostream>
#include<map>
#include<string>
#include<set>
#include<vector>
using namespace std;

// Comparator class to sort the accoding to there value of credit and debit
class compare {

public:
    bool operator()(pair<string, int>p1, pair<string, int>p2)
    {
        return p1.second < p2.second;
    }

};
class Transection {

private:
    map<string, int>cashFlow;
public:
    multiset<pair<string, int>, compare>info;
    void add_details(string to, string from, int amount)
    {
        // flow is (to->form)
        cashFlow[to] -= amount;
        cashFlow[from] += amount;
    }
    void add_info(string, int);
    // getting the details of pending transection
    vector<pair<string, int>> get_cashflow()
    {
        vector<pair<string, int>>temp;
        for (auto i : cashFlow)
        {
            if (i.second != 0)
            {
                temp.push_back({i.first, i.second});
            }
        }
        return temp;
    }
    vector<string> settlement();

};

void Transection::add_info(string s, int data)
{
    info.insert(make_pair(s, data));
}
// function to settle the transection

vector<string> Transection::settlement()
{
    //taking two pointer left and right to store the max debit and credit information
    vector<string>final;
    while (!info.empty())
    {
        //getting the max absolute amount which needs to be transfered
        auto left = info.begin();
        auto right = prev(info.end());
        // now need to delete the data from set
        info.erase(left);
        info.erase(right);

        //debit and credit amount
        int debit = left->second;
        int credit = right->second;
        //debit is in negative need to take absolute value
        int settlement_amount = min(-debit, credit);
        // eirher debit or credit will be zero
        debit += settlement_amount;
        credit -= settlement_amount;

        // now info of who will pay to who
        string s = left->first + " will pay " + to_string(settlement_amount) + " to " + right->first;
        final.push_back(s);

        // now need to insert th remaining amount
        if (debit != 0) info.insert({left->first, debit});
        if (credit != 0) info.insert({right->first, credit});



    }

    return final;

}
int main()
{
    // creating object to store the transection
    Transection T;

    int total_transection;
    cin >> total_transection;

    string s1, s2;
    int amount;
    while (total_transection--)
    {
        cin >> s1 >> s2 >> amount;
        T.add_details(s1, s2, amount);

    }
    //details of all the pending transection
    vector<pair<string, int>>temp = T.get_cashflow();
    for (auto i : temp)
    {
        string name = i.first;
        int amount = i.second;
        // add the value in heap or multiset in this case
        T.add_info(name, amount);

    }

    //now our heap is ready and we have to pick highest credit and settle it with highest debit to minimize the cash flow

    vector<string>min_transection = T.settlement();

    cout << "Minimum no of transection is: " << min_transection.size() << endl;

    // now print the details of the transection

    for (auto i : min_transection)
    {
        cout << i << endl;
    }

    /*
      Thank You
      regards- PP
    */

    return 0;
}
