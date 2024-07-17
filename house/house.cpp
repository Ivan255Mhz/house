
#include <iostream>
#include <string>

using namespace std;

int LimitPerson(int val);
int FlorFactory();
int RoomONumFactory();
double SquareFactory(int val);



class Person {
    char* FIO;
    int age;
   

public:

    Person() : age{ 0 }, FIO{ new char [1] {} } {}

    Person(const char * FIO) : age{0}, FIO{new char [strlen(FIO)+1]}{
        
        strcpy_s(this->FIO, strlen(FIO) + 1, FIO);
            
    }

    Person(const char* FIO, int age) : Person(FIO) {
        this->age = age;
    }

    Person(const Person& obj) : Person(obj.FIO, obj.age) {
        strcpy_s(this->FIO, strlen(obj.FIO) + 1, obj.FIO);
    }

    Person(Person&& obj) : age{ obj.age }, FIO{ obj.FIO } {
        obj.FIO = nullptr;
        obj.age = 0;
    }

    ~Person() { 
        delete[] FIO; 
    }

    Person& operator= (const Person& obj) {

        if (this == &obj)
            return *this;
        age = obj.age;
        delete[] FIO;
        FIO = new char[strlen(obj.FIO) + 1];
        strcpy_s(FIO, strlen(obj.FIO) + 1, obj.FIO);

         return *this;
    }

    Person& operator=(Person&& obj) {
        delete[] FIO;
        age = obj.age;
        FIO = obj.FIO;
        obj.FIO = nullptr;
        obj.age = 0;

        return *this;
    }

    int  getAge() const {
        return age;
    }

    void setAge(int age) {
        this->age = age;
    }

    void setFIO(const char* FIO) {
        delete[] this->FIO;
        this->FIO = new char[strlen(FIO) + 1];
        strcpy_s(this->FIO, strlen(FIO) + 1, FIO);
    }

    char* getFIO() const {
        return FIO;
    }

};




class Flat {
    int size;
    Person* ResidentsPerson;
    const int ApartmentNumber;//номер квартиры 
    const int NumberOfRooms;// кол-во комнат
    const int flor;// этаж
    const double Square;// прлощадь 
    static int InitializationAparNum;
    int RegisteredPersons=0;

    friend int  FlorFactory();
    friend ostream& operator<<(ostream& out, const Flat& obj);

public:

    Flat(int size = 5) :size{LimitPerson(size)}, ApartmentNumber{++InitializationAparNum}, NumberOfRooms{RoomONumFactory()}, flor{FlorFactory()}, Square{SquareFactory(NumberOfRooms)}, ResidentsPerson{new Person[size]} {}

    Flat(const Flat& obj) : Flat(obj.size) {
        for (int i{}; i < obj.size; ++i) {
            ResidentsPerson[i] = obj.ResidentsPerson[i];
       }
    }
    
    ~Flat() {
        delete[] ResidentsPerson;
    }

    Flat& operator= (const Flat& obj) {
        delete[] ResidentsPerson;
        ResidentsPerson = new Person [obj.size];
        for (int i{}; i < obj.size; ++i) {
            ResidentsPerson[i] = obj.ResidentsPerson[i];
        }
        
        return *this;
    }

    Person& operator[] (int i) {
        return ResidentsPerson[i];
    }

   

    int getApartmentNumber() const {
        return ApartmentNumber;
    }

    int getNumberOfRooms() const {
        return NumberOfRooms;
    }

    int getFlor() const {
        return flor;
    }

    double getSquare() const {
        return Square;
    }

    int getSize() const {
        return size;
    }

    void RegisterPerson() { // прописать персону
        if (RegisteredPersons > size) {
            cout << "Неверный доступ по индексу." << endl;
            return;
        }
        cout << "Введите Ф.И.О. : ";
        char FIO[100]{};
        cin.ignore();
        cin.getline(FIO, 100);
        ResidentsPerson[RegisteredPersons] = Person(FIO); // Создаем объект Person с ФИО
        int age{};
        cout << "Введите возраст : ";
        cin >> age;
        ResidentsPerson[RegisteredPersons].setAge(age); // Устанавливаем возраст
        ++RegisteredPersons;
    }

    void ExpelPerson(int i) { // выписать персону
        if (i > size) {
            cout << "Неверный доступ по индексу." << endl;
            return;
        }

        ResidentsPerson[i].setFIO("\0");
        ResidentsPerson[i].setAge(0);
        --RegisteredPersons;
    }


};

ostream& operator<<(ostream& out, const Flat& obj) {
    out << "Прописанные персоны : " << endl;
    for (int i{}; i < obj.size; ++i) {
        out << "Ф.И.О - " << obj.ResidentsPerson[i].getFIO() << " " << " Возраст - " << obj.ResidentsPerson[i].getAge() << endl;
    }
    out << "Номер квартиры - " << obj.ApartmentNumber << endl;
    out << "Этаж - " << obj.flor << endl;
    out << "Комнат в квартире - " << obj.NumberOfRooms << endl;
    out << "Площадь квартиры - " << obj.Square << endl;

    return out;

}

int Flat::InitializationAparNum = 0;

class House {
    int  NumberOfApartments = 20;
    Flat Apartment[20];
    const int  HouseNumber;
    char* Street;
    int flor = 4;
    int RegisteredPersons = 0;

public:

    House(int HouseNum, const char* Street) : HouseNumber{ HouseNum }, Street{ new char[100] } {
        strcpy_s(this->Street, 100, Street);
    }

    House(const House& obj) = delete;

    House(House&& obj) = delete;

    ~House() {
        delete[] Street;
    }

    House& operator=(const House& obj) = delete;
    House& operator=(House&& obj) = delete;

    void InfoOFHouse() const {
        cout << "Адрес - " << Street << " - " << HouseNumber << endl;
        cout << "Квартир в доме - " << NumberOfApartments << endl;
        cout << "Этажей доме - " << flor << endl;
        cout << "Прописано персон - " << RegisteredPersons << endl;

    }

    int getNumberOfApartments() const {
        return NumberOfApartments;
    }

    void  getApartInfo(int i) const {
        cout << Apartment[i];
    }

    void RegisteredControl(bool val) {
        if (val == true)
            ++RegisteredPersons;
        else
            --RegisteredPersons;
    }
   

    Flat& operator[](int i) {
        return Apartment[i];
    }

    
};


int LimitPerson(int val) { // прописка максимум 5 челове на квартиру 
    if (val > 5)
        return 5;
    return val;
}

int FlorFactory() {  // фабрика этажей
    if (Flat::InitializationAparNum == 20) // лемит 20 квартир на дом
        Flat::InitializationAparNum = 0;

    if (Flat::InitializationAparNum <= 5)
    {
        return 1;
    }
    else if (Flat::InitializationAparNum <= 10)
    {
        return 2;
    }
    else if (Flat::InitializationAparNum <= 15)
    {
        return 3;
    }
    else
    {
        return 4;
    }
}

int RoomONumFactory() { // фабрика кол-во комнат
    int val = rand() % 4 + 1;
    return val;
}

double SquareFactory(int val) { // фабрика площади квартиры 
    if (val == 1) {
        return 38.5;
    }
    else if (val == 2) {
        return 55.2;
    }
    else if (val == 3) {
        return 67.3;
    }
    else {
        return 84.8;
    }
}


int main()
{
    srand(time(0));
    setlocale(LC_ALL, "RU");

    House a(34, " ул. Пятилеток");
    int choice{};
    do {
        cout << "1.Вывести информацию о доме" << endl;
        cout << "2.Вывести информацию по квартире" << endl;
        cout << "3.Прописать персону" << endl;
        cout << "4.Выписать персону" << endl;
        cout << "5.Выход" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            system("cls");
            a.InfoOFHouse();
            system("pause");
            system("cls");
        }break;

        case 2:
        {
            system("cls");
            int NumApart{};
            cout << "Введите номер квартиры : ";
            cin >> NumApart;
            if (NumApart - 1 >= a.getNumberOfApartments()) {
                cout << "В это доме нет квартиры с данным номером" << endl;
                
            }
            else {
                a.getApartInfo(NumApart-1);
            }
            system("pause");
            system("cls");

        }break;

        case 3:
        {
            system("cls");
            int NumApart{};
            cout << "Введите номер квартиры : ";
            cin >> NumApart;
            if (NumApart - 1 >= a.getNumberOfApartments()) {
                cout << "В это доме нет квартиры с данным номером" << endl;

            }
            else
            {
                system("cls");
                a[NumApart-1].RegisterPerson();
                a.RegisteredControl(true);
                system("pause");
                system("cls");
            }

        }break;

        case 4:
        {
            system("cls");
            int NumApart{};
            cout << "Введите номер квартиры : ";
            cin >> NumApart;
            if (NumApart - 1 >= a.getNumberOfApartments()) {
                cout << "В это доме нет квартиры с данным номером" << endl;

            }
            else
            {
                int index{};
                cout << "Введите индекс списка происки : ";
                cin >> index;
                system("cls");
                a[NumApart - 1].ExpelPerson(index);
                a.RegisteredControl(false);
                system("pause");
                system("cls");
            }

        } break;

        case 5:
        {
            return 0;
        }break;
        
        default:
        {
            cout << "Ошибка выбора меню" << endl;
        }break;

            
        }
            




    } while (choice);
    

    
   

    return 0;
}

