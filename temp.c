// temp.c
// to understand how to go about command line args
 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

float SRRIP(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int valid;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
		//printf("%d %d\n",i,ways_filled[index]);
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].valid=0;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].valid=3;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].valid=0;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].valid==3)
                     {
                        set[index][i].tag=iter;
                        set[index][i].valid=2;
                        i=0;
                        break;
                     }
                  }
                  if(i==ways)
                  {
                     for(j=0;j<ways;j++)
                        set[index][j].valid++;
                  }
               }
            }
            flag=0;
         }
      }
   fclose(fptr);
	return (float)(hit)/(hit+miss);
}

float fifo(long long sets,int ways)
{
   int ti=0;
   struct data
   {
      long long tag;
      int time;
   }set[sets][ways];
   int flag=0,i,j=0;
   long long hit=0,miss=0,index=0;
   int ways_filled[sets];
   FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
         index=iter;
         flag=1;
         }
         else if(flag==1)
         {
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].time=ti;
                  ways_filled[index]++;
               }
            }
            else
            {
               int minti=1e99;
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  //so basically this loop finds maximum time , just change it to minimum time and you should be sett
                  for(i=0;i<ways;i++)
                  {
                     if(minti>=set[index][i].time)
                     {
                        minti=set[index][i].time;
                     }
                  }
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].time==minti)
                     {
                        set[index][i].tag=iter;
                        set[index][i].time=ti;
                        i=0;
                        break;
                     }
                  }
               }
            }
            flag=0;
         }
         ti++;
      }
   fclose(fptr);
   printf("no of hits=%lld\t no of misses=%lld\n",hit,miss);
   float hitr;
   hitr=(float)hit/(float)(hit+miss);
   hitr=hitr*100;
   //printf("Hitratio : %f\n",hitr);
   return hitr;
}

float lifo(long long sets,int ways)
{
   int ti=0;
   struct data
   {
      long long tag;
      int time;
   }set[sets][ways];
   int flag=0,i,j=0;
   long long hit=0,miss=0,index=0;
   int ways_filled[sets];
   FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
         index=iter;
         flag=1;
         }
         else if(flag==1)
         {
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].time=ti;
                  ways_filled[index]++;
               }
            }
            else 
            {
               int maxti=0;
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].time=ti;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
                  for(i=0;i<ways;i++)
                  {
                     if(maxti<set[index][i].time)
                     {
                        maxti=set[index][i].time;
                     }
                  }
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].time==maxti)
                     {
                        set[index][i].tag=iter;
                        set[index][i].time=ti;
                        i=0;
                        break;
                     }
                  }
               }
            }
            flag=0;
         }
         ti++;
      }
   fclose(fptr);
   float hitr;
   hitr=(float)hit/(float)(hit+miss);
   hitr=hitr*100;
   return hitr;
}

float LRU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int lastUsedTime;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0,time=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
		time++;
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].lastUsedTime=time;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].lastUsedTime=time;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].lastUsedTime=time;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int min=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].lastUsedTime<set[index][min].lastUsedTime)
                     {
                        min=i;
                     }
                  }
                  set[index][min].tag=iter;
                        set[index][min].lastUsedTime=time;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}

float LFU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int frequency;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].frequency++;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].frequency=0;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].frequency++;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int min=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].frequency<set[index][min].frequency)
                     {
                        min=i;
                     }
                  }
                  set[index][min].tag=iter;
                        set[index][min].frequency=0;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}


float MFU(long long sets,int ways)
{
   struct data
   {
      long long tag;
      int frequency;
   }set[sets][ways];

   // creating a FILE variable
  int flag=0,i,j=0;
  long long hit=0,miss=0,index=0;
  int ways_filled[sets];

  FILE* fptr = fopen("d1-final.txt", "r");
   long long iter = 0;
   for(; fscanf(fptr, "%lld", &iter) && !feof(fptr);)
      {
         if(flag==0)
         {
       //printf("index=%lld\n", iter);
       index=iter;
       flag=1;
         }
         else if(flag==1)
         {
            //printf("tag=%lld\n", iter);
            if(ways_filled[index]<ways)
            {
               for(i=0;i<ways_filled[index];i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
		//printf("hit = %lld\n",hit);
                     set[index][i].frequency++;
                     break;
                  }
               }
               if((i==ways_filled[index] && ways_filled[index]!=0) || ways_filled[index]==0)
               {
                  miss++;
                  set[index][ways_filled[index]].tag=iter;
                  set[index][ways_filled[index]].frequency=0;
                  ways_filled[index]++;
               }
            }
            else 
            {
               for(i=0;i<ways;i++)
               {
                  if(set[index][i].tag==iter)
                  {
                     hit++;
                     set[index][i].frequency++;
                     break;
                  }
               }
               while(i==ways)
               {
                  miss++;
		  int max=0;
                  for(i=0;i<ways;i++)
                  {
                     if(set[index][i].frequency>set[index][max].frequency)
                     {
                        max=i;
                     }
                  }
                  set[index][max].tag=iter;
                        set[index][max].frequency=0;
		i=0;
               }
            }
            flag=0;
         }
      }
   fclose(fptr);	
	printf("Hit-ratio=%f\tMiss-ratio=%f\n",((float)hit/(hit+miss)*100),((float)miss/(miss+hit)*100));
	return (float)(hit)/(hit+miss);
}

int main(int argc, char *argv[]) {
	
	//declaring hit-ratio variable for each algorithm
	float hit-ratio_srrip,hit-ratio_lifo,hit-ratio_fifo,hit-ratio_lfu,hit-ratio_lru,hit-ratio_mfu;

	// ensure correct number of command line args
	if (argc != 5) {
		printf("usage: ./executable policy sets ways blocksize\n");
		exit(1);
	}

	// // DEBUG to display the 5 command line args
	// printf("argc: %d\n", argc);
	// for(int i = 0; i < 5; i++) {
	// 	printf("argv[%d]: %s \n", i, argv[i]);
	// }

	// to convert character array to int
	// for easy arguement passing to policy function
	int sets, ways, blocksize;
	sets = atoi(argv[2]);
	ways = atoi(argv[3]);
	blocksize = atoi(argv[4]);
	printf("%d %d %d\n", sets, ways, blocksize);

	// how policy will be called
	if (!strcmp(argv[1], "lru")) {
		printf("call LRU()\n");
		LRU(sets, ways, blocksize);
	}
	
	//calling all the replacement algorithm
	hit-ratio_srrip=SRRIP(sets,ways);
	hit-ratio_lifo=lifo(sets,ways);
	hit-ratio_fifo=fifo(sets,ways);
	hit-ratio_lru=LFU(sets,ways);
	hit-ratio_lfu=LFU(sets,ways);
	hit-ratio_mfu=MFU(sets,ways);

	return 0;
}

