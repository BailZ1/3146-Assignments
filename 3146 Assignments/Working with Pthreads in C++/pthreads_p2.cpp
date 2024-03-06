#include <pthread.h>
#include <iostream>

using namespace std;

// This is the array that contains the integer values,
// that will be used fore the functions,
// countNegative, average, and reverse. 
int arr[10];

// This function is used to count negatives within the data array. 
// The function has a return type of void and the parameter is a void pointer. 
void *countNegatives(void *arg)
{ 
   int total = 0;

   for (int index = 0; index < 10; index++)
   {
      if (arr[index] < 0)
         total++;
   }
   
   cout << "Total negative numbers: "<< total << endl << endl;
   
   pthread_exit(0);
}

// This function is used to calculate the average value of the data array. 
// The function has a return type of void and the parameter is a void pointer. 
void *average(void *arg)
{
   double total = 0.0;
   
   for (int index = 0; index < 10; index++)
   {
      total += arr[index];
   }
   
   cout << "Average: "<< total / 10.0 << endl << endl;
   
   pthread_exit(0);
}

// This function is used to print the data array in reverse. 
// The function has a return type of void and the parameter is a void pointer.
void *reverse(void *arg)
{
   cout << "The numbers in reverse: " << endl;
   
   for (int index = 9; index >=0; index--)
   {
      cout << arr[index] << endl ;
   }
   
   pthread_exit(0);
}



int main()
{   
   // TODO:
   // Add necessary variable declarations. 

   pthread_t threadCountNegatives, threadAverage, threadReverse;


   // TODO:
   // Add code to perform any needed initialization
   // or to process user input
   cout << "Enter 10 numbers: " << endl;
   for(int i = 0; i < 10; i++){
      cout << "Input number: ";
      cin >> arr[i];
   }
   
   // TODO: Modify according to assignment requirements
   // Create thread(s) that will execute the functions of countNegative, average, and reverse
   // and check for the return values for errors.  

   int rc1, rc2, rc3;

    // Create threads
    rc1 = pthread_create(&threadCountNegatives, NULL, countNegatives, NULL);
    rc2 = pthread_create(&threadAverage, NULL, average, NULL);
    rc3 = pthread_create(&threadReverse, NULL, reverse, NULL);

    // Check for errors
    if (rc1 || rc2 || rc3)
    {
        cerr << "Error creating threads." << endl;
        return -1;
    }

    // Wait for threads to finish
    pthread_join(threadCountNegatives, NULL);
    pthread_join(threadAverage, NULL);
    pthread_join(threadReverse, NULL);

    // NOTE: Using exit here will immediately end execution of all threads
    pthread_exit(NULL);
}
