//#include "dlist.h"
//#include <iostream>
//#include <string>
//
//
//using namespace std;
//
//enum STATUS
//{
//    PLATINUM, GOLD, SILVER, REGULAR,UNKNOWN
//};
//
//const char *STATUS_STR[] = {"platinum", "gold", "silver", "regular"};
//
//struct Customer
//{
//    int timestamp;
//    string name;
//    int duration;
//};
//
//STATUS getStatus(string str)
//{
//    for (int i = 0; i < 4; i++)
//    {
//        if (str == STATUS_STR[i])
//        {
//            return STATUS(i);
//        }
//    }
//    return UNKNOWN;
//}
//
//void processCall(Dlist<Customer>* customer, int& end, int time)
//{
//    for (int i = 0; i < 4; i++)
//    {
//        try
//        {
//            auto temp = customer[i].removeFront();
//            if (temp->timestamp <= time)
//            {
//                cout << "Answering call from " << temp->name << endl;
//                end += temp->duration;
//                delete temp;
//                break;
//            }
//            else
//            {
//                customer[i].insertFront(temp);
//            }
//        }
//        catch (emptyList)
//        {
//            continue;
//        }
//    }
//}
//void processInput(Dlist<Customer>* customer, int& num, int& time_next, int time)
//{
//    while (time == time_next && num >= 0)
//    {
//        auto temp = new Customer;
//        temp->timestamp = time_next;
//        cin >> temp->name;
//        string str;
//        cin >> str;
//        auto status = getStatus(str);
//        cin >> temp->duration;
//        if (status != UNKNOWN) {
//            customer[status].insertBack(temp);
//            cout << "Call from " << temp->name << " a " << STATUS_STR[status] << " member" << endl;
//        }
//        num--;
//        if (num >= 0)
//        {
//            cin >> time_next;
//        }
//    }
//}
//
//
//int main()
//{
//    int num, time_next = 0;
//    auto customer = new Dlist<Customer>[4];
//    cin >> num;
//    if (num > 0)
//    {
//        num--;
//        cin >> time_next;
//    }
//    else
//    {
//        time_next = -1;
//    }
//    int time = 0, end = 0;
//    while (true)
//    {
//        cout << "Starting tick #" << time << endl;
//        processInput(customer, num, time_next, time);
//        if (end > time)
//        {
//            time++;
//            continue;
//        }
//        processCall(customer, end, time);
//        if (time == end)
//        {
//            break;
//        }
//        time++;
//    }
//    delete[] customer;
//    return 0;
//}

