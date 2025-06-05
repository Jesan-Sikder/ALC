#include <bits/stdc++.h>
using namespace std;

int main()
{
    int t, a, b;
    cin >> t;

    for (int i = 1; i <= t; i++)
    {

        cin >> a >> b;
        if (a < b || a==b)
        {
            int result = (((b - a) * 4) + 19 + ((a - 0) * 4));

            cout << "Case " << i << ": " << result << endl;
        }
        else if (a > b)
        {
            int resultx = (((a - b) * 4) + 19 + ((a - 0) * 4));

            cout << "Case " << i << ": " << resultx << endl;
        }
    }
}