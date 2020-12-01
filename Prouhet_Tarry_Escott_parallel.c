#include<stdio.h>
#include<string.h>
#include<mpi.h>
#include<stdbool.h>

const int MAX =25;
const int n=12;

/*
 * Function declaration to generate numbers that satisfy the problem criteria
 */
int  num_generator(int digit_start, int digit_end);

/*
 *main function - the start of program execution
 */
int main(void){

	// total processes
	int comm_sz;

	// particular process rank
	int my_rank;
	int local_start, local_end;
	int local;

	//variables to keep track  of time
	double starttime, endtime;

	//printf("Initializing MPI to find PTE numbers for n=6 and k=2");
	MPI_Init(NULL, NULL);
	starttime = MPI_Wtime();
	MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	//calculating start and end for process, basically each process is assigned two start numbers in bruteforce attack
	local_end=(my_rank*2) - 1;
	local_start=local_end-1;

	//Find number with given criteria and do MPI_Send
	if(my_rank !=0)
	{
		local= num_generator(local_start,local_end);
	       	MPI_Send(&local, 1,MPI_INT,0,0,MPI_COMM_WORLD);
		   if(local == 1){
			  endtime = MPI_Wtime();
			  printf("This execution took %f seconds\n",endtime-starttime);
                          printf("Solution Found! Exiting..");
                          return 0;
                   }	
	}
	//Process 0 scenario - receive the local value
	else{
	       for(int q=1; q < comm_sz; q++){
                  MPI_Recv(&local,1, MPI_INT, q,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
	       }	       
	}
	MPI_Finalize();
	return 0;

}


/**
 *Num generator function to perform brute force attack
 */
int  num_generator(int digit_start, int digit_end){
   for(int a=digit_start; a<=digit_end; a++){
     for(int b=0;  b<=MAX; b++){
	 for(int c=0; c<=MAX; c++){
	   for(int d=0; d<=MAX; d++){
	     for(int e=0; e<=MAX; e++){
	      for(int f=0; f<=MAX; f++){
		for(int g=0; g<=MAX; g++){
	 	 for(int h=0; h<=MAX; h++){
		   for(int i=0; i<=MAX; i++){
		     for(int j=0; j<=MAX; j++){
		       for(int k=0; k<=MAX; k++){
	                for(int l=0; l<=MAX; l++){

			//variables to keep track of sum and square sum			
			int arr1_sum=0, arr2_sum=0, arr1_square_sum=0, arr2_square_sum=0;
			arr1_sum = (a+b+c+d+e+f);
               		arr1_square_sum = (a*a)+(b*b)+(c*c)+(d*d)+(e*e)+(f*f);
               		arr2_sum = (g+h+i+j+k+l);
               		arr2_square_sum = (g*g)+(h*h)+(i*i)+(j*j)+(k*k)+(l*l);

			//verification if the sets are disjoint
			bool jointCheck = true;
				
			 int p, q;
       			 int arr1[6];
      			 int arr2[6];
      			 arr1[0]=a; 
			 arr1[1]=b;
       			 arr1[2]=c;
			 arr1[3]=d;
			 arr1[4]=e;
			 arr1[5]=f;
       			 arr2[0]=g;
       			 arr2[1]=h;
       		   	 arr2[2]=i;
			 arr2[3]=j;
			 arr2[4]=k;
			 arr2[5]=l;
       			 for(p=0; p<6; p++){
               		   for(q=0;q<6; q++){
                       	     if(arr1[p]==arr2[q]){
                                 jointCheck = false;
			         break;
                       	      }
               		    }
		        }
			 if((arr1_sum == arr2_sum) && (arr1_square_sum == arr2_square_sum) && (jointCheck == true)){
				 printf("(%d)^2 + (%d)^2 + (%d)^2 + (%d)^2 + (%d)^2 + (%d)^2   =    (%d)^2 + (%d)^2 + (%d)^2 + (%d)^2 + (%d)^2 + (%d)^2 \n",a,b,c,d,e,f,g,h,i,j,k,l);
				 return 1;
       			 }

		   }	
		   }
		   }
		  }
		}	
	      }	      
    	    }}  	  
    	   }}
     }}		 
	
   
return 0;	
}	
