#include <iostream>
#define DATA_SIZE 10  // 데이터 배열 크기
#define MENU 3  // 품목 종류
using namespace std;

//---- 입력 클래스----
class Data {
  private:
    int data[DATA_SIZE] = { 0 };  // 데이터 배열
  public:
    void Insert_Data(); // 데이터를 집어넣는 홤수
    int* getData() { return data; } // 멤버 변수 data의 포인터 반환
    void printData(); // 현재 데이터의 상태를 출력하는 함수.
};

// 데이터 객체 내의 배열(data)에 입력 받은 데이터(tmp)를 저장하는 용도.
void Data::Insert_Data() {
  for(int i=0; i<DATA_SIZE; i++) {
    int tmp;
    cout << "데이터를 입력하시오.(A:1, B:2, C:3, END: 0)>> ";
    cin >> tmp;
    if(tmp == 0) break; // 0은 더이상 입력할 것이 없음을 의미. break.
    data[i] = tmp;  // tmp의 값을 data배열에 저장. (i번째 칸에 저장.)
  }
  return;
}

// 현재 객체 내에 있는 데이터 배열의 상태를 출력. (확인용.)
void Data::printData() {
  for(int i=0; i<DATA_SIZE; i++){
    cout << i << ": " << data[i] << endl;
  }
  return;
}

//---- 라멘 -----
class Ramen {
  int ramen;
public:
  virtual int getPrice() {return ramen;} ; // 가상 함수 원형
};

// 차슈: charsiu에 팔린 개수를 저장, 가상함수 getPrice로 차슈 품목의 매출 반환.
class Charsiu : public Ramen {
  int charsiu;
public:
  Charsiu(int charsiu) { this->charsiu = charsiu; };
  virtual int getPrice() { return 1000 * charsiu; };
};

// 차슈와 똑같음.
class Donko : public Ramen {
  int donko;
public:
  Donko(int donko) { this->donko = donko; };
  virtual int getPrice() { return 2000 * donko; };
};

// 차슈와 똑같음.
class Tantan : public Ramen {
   int tantan;
public:
   Tantan(int tantan) { this->tantan = tantan; };
   virtual int getPrice() { return 3000 * tantan; };
};

//----Calc----
class Calc : public Ramen {
private:
   int total_price;       // 총합
   int count[MENU] = {0}; // 여기에 품목별 팔린 개수를 저장.
public:
   // 데이터 클래스에서 데이터 배열을 외부로 넘기는 역할을 하는 getData함수 friend선언.
   friend int* getData(); 
   void counting(int* p);
   int sum(int* p);
   // 이하의 함수는 진행 상황 확인용.
   void printCount();
   void printPrice(Ramen *r[]);
};

// 몇개씩 팔렸는지 알고 싶을 때.
void Calc::printCount() { 
  cout << "printCount함수 실행>>" << endl;
  for(int i=0; i<MENU; i++) {
    // count 배열에 저장된 팔린 개수들을 출력.
    cout << i+1 << ": " << count[i] << "개 판매" << endl;
  }
  return;
}

// 품목별 매출을 확인용.
void Calc::printPrice(Ramen *r[]) { // 라멘 객체 배열을 입력으로 받음.
  cout << "printPrice함수 실행>>" << endl;  
  for(int i=0; i<MENU; i++)
    // 각각의 라면 객체에서 가상함수 getPrice를 실행하며 품목별 매출을 출력. (저장은 X)
    cout << (i+1) << ": " << r[i]->getPrice() << "원" << endl;
  return;
}

// 입력받은 데이터 배열을 읽으며 count배열에 팔린 개수를 하나씩 카운팅하는 함수.
void Calc::counting(int *p2) { // p는 getdata()로 받은 데이터 배열
  for(int i=0; i < DATA_SIZE; i++) {
    int tmp = *(p2+i);
    if(tmp == 1 )  // 차슈 
      count[0]++;
    else if(tmp == 2) // 돈코
      count[1]++;
    else if(tmp == 3) // 탄탄
      count[2]++;
    else  // 더이상 팔린게 없음.
      break;
  }
  return;
}

int Calc::sum(int* p1) {
  counting(p1); // 입력된 데이터배열에서 몇개씩 팔렸는지 카운팅
  printCount(); // 카운팅 확인

  Ramen *r[MENU];  // 라면 클래스 3개 생성.
  // 업캐스팅.
  r[0] = new Charsiu(count[0]); // 차슈가 팔린 개수를 입력받아 charsiu에 저장. 
  r[1] = new Donko(count[1]);   // 돈코 "
  r[2] = new Tantan(count[2]);  // 탄탄 "

  printPrice(r);  // 각 품목별 getPrice()값을 확인용.

  for(int i=0; i<3; i++) {
    total_price += r[i]->getPrice();  // 품목별 매출을 총합에 모두 다 더함.
  }

  cout << "총합: " << total_price << "원 입니다." << endl;  // 총합 출력.

  for(int i=0; i<3; i++) delete r[i]; // 필요없어진 라면 객체 메모리 모두 해제.
  return total_price;
}

//-----메인------
int main() {
  Data data;  // Data 객체 생성
  Calc c; // Calc 객체 생성
  
  // 생성된 데이터 객체의 초기 상태 배열을 확인용. 모두다 0으로(0은 빈 상태)
  //cout << "초기 데이터배열" << endl;
  //data.printData(); // 데이터 배열 출력함수.

  cout << "데이터배열의 크기: " << DATA_SIZE << endl;
  cout << "메뉴 종류 개수: " << MENU << endl;
  // 데이터 배열에 입력을 하나씩 받아 저장하는 함수.
  data.Insert_Data(); 
  
  // 입력후 데이터배열 상태 확인용.
  //cout << "입력후 데이터배열" << endl;
  //data.printData();
  
  //int *p = data.getData();  // 데이터 배열 포인터
  //c.sum(p); // 합을 계산
  
  // 위의 두 코드를 한 문장으로 축약.
  c.sum(data.getData());
  return 0;
}