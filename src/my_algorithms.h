/* Ryan Koven, 2012. my_algorithms.h: c++ header file defines templated functions that implement sorting and searching algorithms and other useful functionality, 
like partitioning an array around a pivot element. */


#ifndef MY_ALGORITHMS_H_
#define MY_ALGORITHMS_H_

#include<cmath>
#include<cstdlib>
#include<iostream>

namespace algo{

/* partition: An input array A is partitioned around the template value in the first element of the array. 
That is, the value in position zero in the array will be placed in its "proper place" in any sorted version of the array. */
template<typename T>
void partition(T* A, int length){
	
	int i = 1;
	T temp;
	for (int j = 1; j < length; j++){
		if (A[j] < A[0]){
			temp = A[i];
			A[i++] = A[j];
			A[j] = temp;
			
						 }
	                                }
	temp = A[i - 1];
	A[i - 1] = A[0];
	A[0] = temp;

}

/* partition_index: returns the index of the pivot (the first element of the array, before the partitioning) after partitioning.   */
template<typename T>
int partition_index(T* A, int length){
	
	int i = 1;
	T temp;

	for (int j = 1; j < length; j++){
		if (A[j] < A[0]){
			temp = A[i];
			A[i++] = A[j];
			A[j] = temp;
			
						 }
	                                }
	temp = A[i - 1];
	A[i - 1] = A[0];
	A[0] = temp;

	return i - 1; //index of pivot
}

/* Implementation of the classic randomized quicksort. Places the input array A in sorted order. */
template<typename T>
void quicksort(T* A, int length){
	
	T temp;

	if (length < 2) return;
	else{

	int pivot = rand()%length;
	
	temp = A[0];
	A[0] = A[pivot];
	A[pivot] = temp;
	int pivot_index = partition_index(A, length);
	
	quicksort(&A[0], pivot_index);
	quicksort(&A[pivot_index+1], length - pivot_index - 1);
	
	}
}

/* quicksort_comparisons: counts the number of comparisons of primitive data types that an implementation 
   of randomized quicksort uses to sort the input array A */
template <typename T>
int quicksort_comparisons(T* A, int length){
	
	T temp;
	int comparisons = 0;

	if (length < 2) return 0;

	else{
 
	int pivot = rand()%length;

	temp = A[0];
	A[0] = A[pivot];
	A[pivot] = temp;
	int pivot_index = partition_index(A, length);
	comparisons += length - 1;
	comparisons += quicksort_comparisons(&A[0], pivot_index);
	comparisons += quicksort_comparisons(&A[pivot_index+1], length - pivot_index - 1);
	return comparisons;
	}
}

/* merge_sort: implementation of the merge sort algorithm. Sorts the input array A. */
template<typename T>
T* merge_sort(T* input_array, int length){
	T* pointer = (T*)malloc(5*length+1);
	
	if (input_array == NULL)
		pointer = NULL;
		
	else if (length == 1)
		pointer = input_array;
	
	else{
		
		

		T* sorted_left_side = merge_sort( &input_array[0], length/2);
		T* sorted_right_side = merge_sort(&input_array[length/2], length-(length/2));
		
		
		int i = 0;
		int j = 0;
		int k = 1;
		if (sorted_left_side[0] < sorted_right_side[0]){
			*pointer = sorted_left_side[0];
			i++;
		}
		else{
			*pointer = sorted_right_side[0];
			j++;
		}
		while(k < length){
			if (sorted_left_side[i] < sorted_right_side[j] && i < length/2){
				pointer[k] = sorted_left_side[i];
				i++;
															}
			else if (sorted_left_side[i] > sorted_right_side[j] && j < (length-length/2)) {
				pointer[k] = sorted_right_side[j];
				j++;
			}
			else if (i<length/2){
				pointer[k] = sorted_left_side[i];
				i++;
			}

			else
			{
				pointer[k] = sorted_right_side[j];
				j++;
			
			}

			k++;
		
		}

	}

	return pointer;
}

/* count_inversions: Returns the number of "inversions" in an input array A.  
   An inversion is a pair (A[i], A[j]) of array elements with A[i] > A[j] and i < j.  
   This version has been tested on arrays with as many as 100000 entries. */
template<typename T>
int count_inversions(T* input_array, int length){
		int left_inversions = 0;
		int right_inversions = 0;
		int split_inversions = 0;
	
	
		if (length > 1){
			 left_inversions = count_inversions(&input_array[0], length/2);
			 right_inversions = count_inversions(&input_array[length/2], length-(length/2));
			

			T* sorted_left_side = merge_sort( &input_array[0], length/2);
			T* sorted_right_side = merge_sort(&input_array[length/2], length-(length/2));
		
		
			int i = 0;
			int j = 0;
			int k = 1;
			if (sorted_left_side[0] < sorted_right_side[0]){
				i++;
		}
			else{
				split_inversions += length/2;
				j++;
		}
			while(k < length){
				if (sorted_left_side[i] < sorted_right_side[j] && i < length/2){
					i++;
															}
				else if (sorted_left_side[i] > sorted_right_side[j] && j < (length-length/2)) {
					split_inversions += (length/2 - i);
					j++;
			}
		

			k++;
		
		}

	}


	
	return right_inversions+left_inversions+split_inversions;
}

/* print_inversions: prints inversions in an input array A as pairs (A[i], A[j]), with A[i] > A[j] and i < j. */
template<typename T>
void print_inversions(T* input_array, int length){
		
	
		if (length > 1){
			  print_inversions(&input_array[0], length/2);
			  print_inversions(&input_array[length/2], length-(length/2));
			

			T* sorted_left_side = merge_sort( &input_array[0], length/2);
			T* sorted_right_side = merge_sort(&input_array[length/2], length-(length/2));
		
		
			int i = 0;
			int j = 0;
			int k = 1;
			if (sorted_left_side[0] < sorted_right_side[0]){
				i++;
		}
			else{
					for(int l = i; l < length/2; l++)	
						cout<<"("<<sorted_left_side[l]<<", "<<sorted_right_side[j]<<")\n";
					j++;
		}
			while(k < length){
				if (sorted_left_side[i] < sorted_right_side[j] && i < length/2){
					i++;
															}
				else if (sorted_left_side[i] > sorted_right_side[j] && j < (length-length/2)) {
					for(int l = i; l<length/2; l++)	
						cout<<"("<<sorted_left_side[l]<<", "<<sorted_right_side[j]<<")\n";
					j++;
					
					
			}
		

			k++;
		
		}

	}

}

/* Rselect: implementation of a randomized selection algorithm. Returns the value of the nth greatest 
   (specified by index) value in the array A, counting from 0 (i.e. index 0 is the smallest element, 
   index 1 is the second smallest element, etc. */
template<typename T>
T Rselect(T* A, int length, int index){

	int value = 0;

	if (length < 2)
		return A[0];
	else {
		int a;
		T temp;
		
		int pivot = rand()%length;

		temp = A[0];
		A[0] = A[pivot];
		A[pivot] = temp;

		if ((a = partition_index(A, length)) == index)
			return A[a];
		else if (index < a)
			return Rselect(&A[0], a, index);
		else
			return Rselect(&A[a + 1], length - a - 1, index - a - 1);
	}

	
}

}

#endif