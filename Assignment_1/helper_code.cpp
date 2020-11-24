/**** This is a helper/skeleton code for the assignment     ****/
/**** Author: Sarbojit Das                                  ****/
/**** Compile using command g++ simple_thread.cpp -lpthread ****/

#include<iostream>
#include<thread>

#include"adt_set.cpp"

using namespace std;

ADT_Set adt_set = ADT_Set();

void worker_func(int num, operation test_case[]){
  cout<<"Worker "<<num<<endl;
}

void monitor_func(operation test_case[]){
  //blah blah blah
  cout<<"Monitor"<<endl;
}

int main(){
  int N_Threads = 3;
  
  thread *worker= new thread[N_Threads];
  operation test_case[100];
  //fill test_case with your sequence of operations
  thread monitor = thread(monitor_func,test_case);

  for (int i=0;i<N_Threads;i++){
    worker[i]=thread(worker_func,i,test_case);		
  }

  for (int i=0;i<N_Threads;i++){
    worker[i].join();	
  }

  monitor.join();	
  return 0;
}