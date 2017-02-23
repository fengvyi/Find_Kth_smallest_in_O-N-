#include<iostream>
#include<time.h>
using namespace std;
int *median_array;
clock_t start, finish;
double run_time;

int partition(int* A, int p, int r) {
    int x = A[r];    //pivot
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
		}

	}
	swap(A[i + 1], A[r]);
	return i + 1;
}

int partition_using_m(int* A, int p, int r, int m) {
	int x = m;    //pivot
	int i = p - 1;
	for (int j = p; j <= r - 1; j++) {
		if (A[j] <= x) {
			i++;
			swap(A[i], A[j]);
		}

	}
	if (A[r] <= m) {
		swap(A[i + 1], A[r]);
		return i + 1+1;
	}
	else
		return i + 1;


}

void quicksort(int* A, int p, int r) {

	if (p < r) {
		int q = partition(A, p, r);
		quicksort(A, p, q - 1);
		quicksort(A, q + 1, r);

	}

}

int find_median_of_medians(int* A, int left, int right) {
	//Divide array into grup of 5, return median of medians
	int n = (right - left) / 5;
	int remain = (right - left) - 5 * n;
	if (remain != 0) n++;

	median_array = new int[n];

	if (left == right) return median_array[0] = A[left];

	//Find median of each group, put into median_array
	for (int a = 0; a < n; a++) {
		int p = a * 5+left;
		int r;
		if (right - left <= 5) 
			r = right - left - 1+left;
		else if ((remain != 0) && (a == n - 1))
			r = a * 5 + ((right - left) - 5 * (n - 1) - 1)+left;
		else
			r = a * 5 + 4+left;

		quicksort(A, p, r);

		if ((r - p) % 2 == 0) 
			median_array[a] = A[(p + r) / 2];
		else 
			median_array[a] = (A[(p + r - 1) / 2] + A[(p + r + 1) / 2]) / 2;
	}

	if (n == 1) 
		return median_array[0];
	else 
		return find_median_of_medians(median_array, 0, n);

}

int Find_Kth_smallest(int* A, int left, int right, int k) {
	//Find partition point m using find_median_of_medians()
	//Partition array A to subarray L and R according to m, r=sizeof(L)+1
	// If k=r, then return m.
	//If k<r, then return k th smallest of the set L.
	//If k>r, then return k-r th smallest of the set R.
	int m = find_median_of_medians(A, left, right);
	//find the rank of value m
	int r = partition_using_m(A, left, right - 1,m );
	r = r - left;
	
	if (k == r) 
		return m;
	else if (k < r) 
		return Find_Kth_smallest(A, left, r+left, k);
	else 
		return Find_Kth_smallest(A, r+left, right, k - r);
}

void main() {
	//Test case
	for (int i = 10000; i <= 500000; i+=10000) {
		int n = i;
		int* array;
		array = new int[n];
		for (int j = 0; j < n; j++) array[j] = n-j;
		start = clock();
		int result = Find_Kth_smallest(array, 0, n,n/2);
		finish = clock();
		run_time = (double)(finish - start) / CLK_TCK;
		cout << n<<"," << result <<","<<run_time<< endl;
	}

	system("pause");
}