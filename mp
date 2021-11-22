// Random_Data 용
#include<cstdlib>
#include<ctime>

void Random_Data();
void Data::Random_Data() { 
  srand((unsigned int)time(NULL));
  
  for(int i=0; i<SIZE; i++){
    data[i] = rand()%4;
    if(data[i] == 0) break;
  }
  return;
}
data.Random_Data();