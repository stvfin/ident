// ident.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.

#include <iostream>
#include <string>

using namespace std;

//A1-B2-C3-E4-H5-I6-K7-L8-N9-O1
const char not_case[] = {'D','F','G','J','M','Q','V'};
const int l_lits = 19;
const char lits[] = { 'A','B','C','E','H','I','K','L','N','O','P','R','S','T','U','W','X','Y','Z' };
const int l_nums = 9;
const char nums[] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
const int max_num = l_lits * l_nums;

class MyIdent {
public:
  MyIdent();
  void SetIdent(string s) {
    ident = s;
  }
  string GetIdent() {
    return ident;
  }
  void IncIdent();

private:
  string ident;
};

MyIdent::MyIdent() {
  ident = "A0";
}

//A1-B2-C3-E4-H5-I6-K7-L8-N9-O1  - образец
void MyIdent::IncIdent() {
  string s = ident;
  int l = s.length();                     //Количество символов
  int lg;                                 //Количество групп
  if (l > 2) lg = (l+1) / 3; else lg = 1;
  int tg = 1;                             //Текущая группа (1-10)
                        //Оцифровка
  int data[10]={0,0,0,0,0,0,0,0,0,0};     //Оцифровка 0-старший, от 9 - младший
  while (tg<=lg) {                        //Слева направо (слева старшие)
    int k;                                //начало группы
    if (tg == 1) k = 0;else k = (tg - 1) * 3;     
    char sl = s[k];                       //Первый символ в группе  lits
    char sn = s[k + 1];                   //Второй                  nums
    int t_lit = 0;
    while (sl != lits[t_lit]) t_lit++;    //Поиск буквы в lits
    int t_num = 0;
    while (sn != nums[t_num]) t_num++;    //Поиск цифры в lits

    data[tg-lg+9] = t_lit * l_nums + t_num + 1;  //1 как флаг разряда
    tg++;
  }
                        //инкремент
  data[9]++;                              //младший разряд
                        //Перенос
  for (int i = 9; i >=0; i--) {
    if (data[i] == 0) break;
    if (data[i] > max_num) {              //переполнение
      if (i == 0)                         //переполнение в старшем разряде
        for (int k = 0; k < 10; k++) {    //после максимума A1
          if (k == 9) data[k] = 1; 
          else data[k] = 0; 
        }
      else {                              //переполнение в младших разрядах
        data[i] = 1;
        data[i - 1]++;
      }
    }
  }
                        //Символизация
  s = "";
  for (int i = 0; i < 10; i++) {
    int d = data[i];
    if (d == 0) continue;
    int dl = (d-1) / l_nums;
    int dn = (d-1) % l_nums;
    if (s.length() == 0) {
      s += "  ";
      s[0] = lits[dl];
      s[1] = nums[dn];
    }
    else {
      s += "-  ";
      s[s.length() - 2] = lits[dl];;
      s[s.length() - 1] = nums[dn];;
    }
  }
  ident = s;      //Результат
}

int main(int argc, char** argv)
{
  setlocale(LC_ALL, "Rus");
  std::cout << "main()\n";
  MyIdent mi;
  if (argc != 2) {
    cout << "Для проверки введите как аргумент строки запуска Идентификатор\n";
    cout << "Формат по заданию A1-Z9... (не проверяется на соответствие)\n";
    mi.SetIdent("Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9-Z9");
    cout << mi.GetIdent() << endl;
    mi.IncIdent();
    cout << "after increment " << mi.GetIdent() << endl;
    mi.SetIdent("A9");
    cout << mi.GetIdent() << endl;
    mi.IncIdent();
    cout << "after increment " << mi.GetIdent() << endl;
    mi.SetIdent("Z9");
    cout << mi.GetIdent() << endl;
    mi.IncIdent();
    cout << "after increment " << mi.GetIdent() << endl;
    mi.SetIdent("A1-Z9");
    cout << mi.GetIdent() << endl;
    mi.IncIdent();
    cout << "after increment " << mi.GetIdent() << endl;
  }
  else {
    string s = argv[1];
    mi.SetIdent(s);
    cout << "Начальный идентификатор: " << mi.GetIdent() << endl;
    mi.IncIdent();
    cout << "after increment: " << mi.GetIdent() << endl;
  }
  return 0;
}

