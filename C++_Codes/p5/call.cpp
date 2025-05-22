#include "dlist.h"
#include <iostream>
#include <string>

using namespace std;

struct member {
    int timestamp;
    string name;
    string status;
    int duration;
};

struct CallQueues {
    Dlist<member> platinum;
    Dlist<member> gold;
    Dlist<member> silver;
    Dlist<member> regular;
};

int main() {
    CallQueues queues;

    int totalCalls, stamp = -1; // 默认设置time_next为-1
    cin >> totalCalls;

    if (totalCalls > 0) {
        cin >> stamp;
    }

    int currentTime = 0, endingTime = 0;
    while (true) {
        cout << "Starting tick #" << currentTime << endl;

        // 当前时间等于或超过了下一个电话时间，并且还有电话未处理
        while (currentTime >= stamp && totalCalls > 0) {
            auto temp = new member;
            temp->timestamp = stamp;
            cin >> temp->name >> temp->status >> temp->duration;

            if (temp->status == "platinum") {
                queues.platinum.insertBack(temp);
            } else if (temp->status == "gold") {
                queues.gold.insertBack(temp);
            } else if (temp->status == "silver") {
                queues.silver.insertBack(temp);
            } else if (temp->status == "regular") {
                queues.regular.insertBack(temp);
            }

            cout << "Call from " << temp->name << " a " << temp->status << " member" << endl;
            totalCalls--;

            if (totalCalls > 0) {
                cin >> stamp;
            } else {
                stamp = -1; // 所有电话都已读入
            }
        }

        if (endingTime > currentTime) {
            currentTime++;
            continue;
        }

        bool callHandled = false;
        for (auto& queue : {&queues.platinum, &queues.gold, &queues.silver, &queues.regular}) {
            if (!queue->isEmpty()) {
                auto temp = queue->removeFront();
                if (temp->timestamp <= currentTime) {
                    cout << "Answering call from " << temp->name << endl;
                    endingTime = max(endingTime, currentTime + temp->duration);
                    delete temp;
                    callHandled = true;
                    break;
                } else {
                    queue->insertFront(temp);
                }
            }
        }

        if (!callHandled && totalCalls == 0 && currentTime >= endingTime) {
            break; // 没有电话处理且所有电话已读入，且当前时间超过处理时间
        }

        currentTime++;
    }

    return 0;
}
