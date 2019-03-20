#include<bits/stdc++.h>
using namespace std;
typedef complex<double> node; 

vector<node> fft(vector<node>& eq) 
{ 
	int n = eq.size();

	if (n == 1) 
		return vector<node>(1, eq[0]); 

	vector<node> comp_root(n/2); 
	for (int i = 0; i < n/2; i++) 
    { 
		double omega = 2 * M_PI * i / n; 
		comp_root[i] = node(cos(omega), sin(omega));
	}

	vector<node> even(n / 2), odd(n / 2); 
	for (int i = 0; i < n / 2; i++) 
    { 
		even[i] = eq[i * 2];  
		odd[i] = eq[(i * 2) + 1];
	}

	vector<node> r_even = fft(even); 
	vector<node> r_odd = fft(odd);

	vector<node> result(n); 

	for (int i = 0; i < n / 2; i++) { 
		result[i] = r_even[i] + comp_root[i] * r_odd[i]; 
		result[i + n / 2] = r_even[i] - comp_root[i] * r_odd[i];
	} 

	return result; 
} 

int main() 
{ 
    int n;
    cout << "Enter degree of polynomial: ";
    cin >> n;
    n += 1;
    vector<node> eq_1(n);
    cout << "Enter coefficients: ";
    for (int i = 0; i < n; i++)
        cin >> eq_1[i];
	vector<node> p_eq_1 = fft(eq_1);

	for (int i = 0; i < n; i++) 
		cout << p_eq_1[i] << endl; 

} 
// Sample Input(Class Example): 2, 4, 5, 6
// Output: 17, -3 - 2i, -3, -3 + 2i
