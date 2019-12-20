/***********
* Raviv Haham
* 208387951
* 01
* ass3
***********/

#include <stdio.h>
#include <math.h>
//counter is a global variable
int counter = 0;

/******************
* Function Name: recEffiPow
* Input: double number X, int number Y
* Output: the function return the result of number x in possession of number y
* Function Operation: this is a recursion function that return the result of number x in possession of number y by 
           the by the effective method of 𝑥^𝑦 = 𝑥^(𝑦/2) ∙ 𝑥^(𝑦/2) 
******************/
double recEffiPow(double x, int y) {
	// we want to add 1 to the global variable- counter so we could check how effective the function is
    counter++;
	//result is a temporary variable that calculate the result of 𝑥^(𝑦/2)
	double result = 1;
	int y2 = y;
	// if y=0 or x=1 the result should be 1 acording to the math pows rules
	if (y == 0 || x == 1)
	{
		return 1;
	}
	/** if x=0 the result should be 0 if the pow is zero or more than zero and if the pow is negative the result should be 
	   infinity acording to the math pows rules
    **/
	else if (x == 0)
	{
		if (y >= 0)
		{
			return 0;
		}
		else
		{
			return 1.0/0.0;
			
		}
	}
	//stop condition- if y is one the result of x in possession of 1 is x
	else if (y == 1)
	{
		return x;
	}
	//if y is negative we want to calculat the result as it was a positive number and to return the result of 1 divide the outcome
	else if (y < 0)
	{
		y = -1 * y;
	}
	if (y2 < 0)
	{
		//if the pow is odd we want to make it even so it's like x*(x^y-1)
		if (y%2==1)
		{
			return 1 / (x * (recEffiPow(x, y - 1)));
		}
		//return the result of what the recursion function bring of x and y/2
		else
		{
			result = recEffiPow(x, y / 2);
			return 1 / (result*result);
		}
		
	}
	else
	{
		//if the pow is odd we want to make it even so it's like x*(x^y-1)
		if (y % 2 == 1)
		{
			return (x * (recEffiPow(x, y - 1)));
		}
		//return the result of what the recursion function bring of x and y/2
		else
		{
			result = recEffiPow(x, y / 2);
			return  (result * result);
		}
		
	}



}

/******************
* Function Name: recPow
* Input: double number X, int number Y
* Output: the function return the result of number x in possession of number y
* Function Operation: this is a recursion function that return the result of number x in possession of number y by
		   the by the method of 𝑥^𝑦 = x*(𝑥^(𝑦-1))
******************/
double recPow(double x, int y) {
	// we want to add 1 to the global variable- counter so we could check how effective the function is
    counter++;
	int y2 = y;
	// if y=0 or x=1 the result should be 1 acording to the math pows rules
	if (y == 0 || x==1)
	{
		return 1;
	}
	/** if x=0 the result should be 0 if the pow is zero or more than zero and if the pow is negative the result should be
	   infinity acording to the math pows rules
	**/
	else if (x == 0)
	{
		if (y >= 0)
		{
			return 0;
		}
		else
		{
			return  1.0 / 0.0;
			
		}
	}
	//stop condition- if y is one the result of x in possession of 1 is x
	else if (y==1)
	{
		return x;
	}
	//if y is negative we want to calculat the result as it was a positive number and to return the result of 1 divide the outcome
	else if (y<0)
	{
		//return 1 divide the result of x dual what the recursion function bring of x and y-1
		y = -1 * y;
	}
	if (y2<0)
	{
		return 1/(x * (recPow(x, y - 1)));
	}
	//return the result of x dual what the recursion function bring of x and y-1
	else
	{
		return (x * (recPow(x, y - 1)));
	}
	
}

/******************
* Function Name: iterPow
* Input: double number X, int number Y
* Output: the function return the result of number x in possession of number y
* Function Operation: this function return the result of number x in possession of number y by
		   the by the method of 𝑥^𝑦 = x dual x ,y times
******************/
double iterPow(double x, int y) {
    // in every loop
    // counter++;
	//result will be the result so we start this value with the value x to make the function more effective
	double result = x;
	int y2 = y;
	// if y=0 or x=1 the result should be 1 acording to the math pows rules
	if (y == 0 || x == 1)
	{
		return 1;
	}
	/** if x=0 the result should be 0 if the pow is zero or more than zero and if the pow is negative the result should be
	   infinity acording to the math pows rules
	**/
	else if (x == 0) 
	{
		if (y >= 0)
		{
			return 0;
		}
		else
		{
			return 1.0 / 0.0;
		}		
	}
	//if y is one the result of x in possession of 1 is x
	else if (y==1)
	{
		return x;
	}
	/**
	  if y is negative we want to calculat the result as it was a positive number and to return the result of 1 divide the
	   outcome
    **/
	else if (y<0)
	{
		y = -1 * y;
	}
	//by this for loop we want to calculate the dual of x with x, y-1 times (because result start with the value x)
	for (int i=0;i<(y-1);i++) 
	{
		// we want to add 1 to the global variable-counter in every loop so we could check how effective the function is
		counter++;
		result = result * x;
	}
	//return 1 divide the result of x dual what the loop bring
	if (y2<0)
	{
		return (1 / result);
	}
	//return the dual of x with x, y times
	else
	{
		return result;
	}

}

/******************
* Function Name: isPermutation
* Input: int arr1[],int arr2[],int size1,int size2
* Output: the function return 1 if one array is permutation of the other array and zero if it's not a permutation of the other array
* Function Operation: the function return if one array is permutation of the other array
******************/
int isPermutation(int arr1[], int size1, int arr2[], int size2) {
	//Auxiliary array that save the values of arr2 array
	int arrSame2[MAX];
	//value that check how many values in arr1 are similar to values in arr2
	int count = 0;
	//value that save the lowest value from arr1
	int lowest = 0;
	//copy the values of arr2 to an auxiliary array that save the values
	for (int i = 0; i < size2; i++)
	{
		arrSame2[i] = arr2[i];
	}
	//if the size of arr1 is diferent from the size of arr2 we want to return 0 because it's false
	if (size1 != size2)
	{
		return 0;
	}
	//for loop who check what number is the lowest and save it in the value lowest
	for (int i = 0; i < size1; i++)
	{
		if (arr1[i]<=lowest)
		{
			lowest = arr1[i];
		}
	}
	//we Subtract 1 from the value lowest so by this way lowest couldn't be a value in the array arr1
	lowest = lowest - 1;
	//for every value of the array arr1 we want to to check if he is similar to the value in  the array arr2
	for (int i = 0; i < size1; i++)
	{
		for (int j = 0; j < size2; j++)
		{
			if (arr1[i] == arrSame2[j])
			{
				/**
				   if the value of the array arr1 is similar to the value in the array arrSame2 (that similar to arr2) we want  
				   to add 1 to the count and to change the value in this location in arrSame2 to lowest value and by this way
				   we can know that we allready check this value
				**/
				count++;
				arrSame2[j] = lowest;
				//we want to go to the next index of i so by this way we will get off the loop of j
				j = size2;
			}
		}
	}
	/**
	  if count is equal to the lengh of arr1 it means that all the values of the array arr1 are similar to the values in  the 
	  array arr2, so we want to return 1
	**/
		if (count == size1)
		{
			return 1;
		}
		/**
	     if count is not equal to the lengh of arr1 it means that not all the values of the array arr1 are similar to the 
		 values in  the array arr2, so we want to return zero
	    **/
		else
		{
			return 0;
		}
	}

/******************
* Function Name: printArr2D
* Input: int arr[],int rows,int columns
* Output: the function  The function print the values in the array with zeros in their left side until they 
          have same number of digits that there are in the longest number in the array
* Function Operation: The function add zeros to the values in the array until they have same number of digits that there
                      are in the longest number in the array, and print it
******************/
void printArr2D(int arr[][MAX], int rows, int columns) {
	//value that save the number of the digits that there are in the number with the most number of the digits
	int longest = 0;
	//value that check how many digits there are in the number
	int num = 0;
	//value that check how many digits there are in the number (in the second time)
	int num2 = 0;
	//for loop that runs on all the values in the array
	//all rows
	for (int i = 0; i < rows; i++)
	{
		//all columns
		for (int j = 0; j < columns; j++)
		{
			num = arr[i][j];
			//we check how many digits there are in the number and save it in the value num;
			num = log10(num) +1;
			//save the number of the digits that there are in the number with the most number of the digits at longest value
			if (num > longest)
			{
				longest = num;
			}
			//after we check we want num to be zero so we could use it again next time
			num = 0;
		}
	}
	//for every value of the array we want to to check his length and to compere it to longest value
	for (int i = 0; i < rows; i++)
	{
		for (int j = 0; j < columns; j++)
		{
			num2 = arr[i][j];
			//we check how many digits there are in the number and save it in the value num 2;
			num2 = log10 (num2) +1;
			/**
			   if the size of the current value is smaller than longest we want to print it with zeros 
			   in it's left side until it will have same number of digits that there are in the longest number in the array
		    **/
		    if (longest > num2)
			{
					printf("%0*d", longest, arr[i][j]);
					//space between number to  number
					printf(" ");
			}
			/**
			   if the size of the current value is equal to the size of the longest we want to print the number as it is
			**/
			else
			{
					printf("%d", arr[i][j]);
					//space between number to  number
					printf(" ");			
			}
			//after we check we want num2 to be zero so we could use it again next time
			num2 = 0;
		}
		//to skip lines after every line
		printf("\n");
	}
}
