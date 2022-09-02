//I pledge my honor that I have abided by the Stevens Honor System - Justin Frederickson, Shady Kamel
#include <stdlib.h>
#include <time.h>

#include <iostream>
using namespace std;

class Customer {
 public:
  int in_time;
  int out_time;
  int ordertime;
  int waitTime;
  int copyOfOrdertime;
  Customer *next;

  Customer() {
    next = NULL;
    in_time = -1;
    out_time = -1;
    ordertime = -1;
    waitTime = 0;
  }
};

class Queue {
 public:
  int size, totalWaitTime, totalServiceTime, totalQueueLength;
  int longestWaitTime = 0;
  int shortestWaitTime = 2000;
  int timeForLongestWaitTime = -1;
  int timeForShortestWaitTime = -1;
  //
  int longestServiceTime = 0;
  int shortestServiceTime = 2000;
  int timeForLongestServiceTime = -1;
  int timeForShortestServiceTime = -1;
  //
  int longestQueueLength = 0;
  int shortestQueueLength = 2000;
  int timeForLongestQueueLength = -1;
  int timeForShortestQueueLength = -1;
  Customer *head;
  Customer *tail;
  Queue() {
    head = tail = NULL;
    size = 0;
    totalWaitTime = 0;
    totalServiceTime = 0;
    totalQueueLength = 0;
  }

  void enqueue(int in_time, int ordertime) {
    Customer *temp = new Customer;
    temp->ordertime = ordertime;
    temp->in_time = in_time;
    temp->out_time = in_time + ordertime;
    temp->copyOfOrdertime = ordertime;

    if (head == NULL) {
      head = temp;
      tail = temp;
    } else {
      tail->next = temp;
      tail = temp;
    }
    size++;
  }

  void dequeue() {
    Customer *temp;
    if (head == NULL) {
    } else if (head->next == NULL) {
      delete head;
      head = NULL;
    } else {
      temp = head;
      head = head->next;
      delete temp;
    }
  }

  void check(int TIME) {
    if (head == NULL) {
      return;
    }
    if (head->ordertime == 0) {
      totalWaitTime += head->waitTime;
      totalServiceTime += (head->waitTime + head->copyOfOrdertime);
      // best and worst case scenarios {waittime}:

      if (head->waitTime > longestWaitTime) {
        longestWaitTime = head->waitTime;
        timeForLongestWaitTime = TIME;
      }
      if (head->waitTime < shortestWaitTime) {
        shortestWaitTime = head->waitTime;
        timeForShortestWaitTime = TIME;
      }
      // best and worst case scenarios {servicetime}:
      if ((head->waitTime + head->copyOfOrdertime) > longestServiceTime) {
        longestServiceTime = (head->waitTime + head->copyOfOrdertime);
        timeForLongestServiceTime = TIME;
      }
      if ((head->waitTime + head->copyOfOrdertime) < shortestServiceTime) {
        shortestServiceTime = (head->waitTime + head->copyOfOrdertime);
        timeForShortestServiceTime = TIME;
      }

      // dequeue
      dequeue();
      return;
    }
    // decrement ordertime (simulate order being processed)
    head->ordertime = (head->ordertime - 1);

    if (head->next != NULL) {
      // increment wait time for all other orders
      Customer *allNodes;
      allNodes = head->next;
      while (allNodes->next != NULL) {
        allNodes->waitTime = (allNodes->waitTime + 1);
        allNodes = allNodes->next;
      }
      allNodes->waitTime = (allNodes->waitTime + 1);
    }

    //
    //
    //
    // Calculate number of people in line every minute
    int countThisMinute = 0;
    Customer *visitAllInLine;
    visitAllInLine = head;
    while (visitAllInLine != NULL) {
      countThisMinute++;
      visitAllInLine = visitAllInLine->next;
    }
    totalQueueLength += countThisMinute;

    if (countThisMinute > longestQueueLength) {
      longestQueueLength = countThisMinute;
      timeForLongestQueueLength = TIME;
    }
    if (countThisMinute < shortestQueueLength) {
      shortestQueueLength = countThisMinute;
      timeForShortestQueueLength = TIME;
    }
  }

  void printContents() {
    if (head == NULL) {
      cout << "Empty queue" << endl;
      return;
    } else {
      Customer *temp;
      temp = head;
      cout << "---" << endl;
      while (temp != NULL) {
        cout << temp->ordertime << " --> ";
        temp = temp->next;
      }
      cout << "NULL" << endl;
      cout << "---" << endl;
      cout << "Tail: " << tail->ordertime << endl;
      cout << "Head: " << head->ordertime << endl;
    }
  }
  void printStats() {
    cout << "Size of Queue overall: " << size << endl;
    cout << "\nAverage Wait Time: " << (totalWaitTime / size) << endl;
    cout << "Longest wait time: " << longestWaitTime
         << " Occurred at time (in minutes): " << timeForLongestWaitTime
         << endl;
    cout << "Shortest wait time: " << shortestWaitTime
         << " Occurred at time (in minutes): " << timeForShortestWaitTime
         << endl;
    cout << "\nAverage Service Time: " << (totalServiceTime / size) << endl;
    cout << "Longest service time: " << longestServiceTime
         << " Occurred at time (in minutes): " << timeForLongestServiceTime
         << endl;
    cout << "Shortest service time: " << shortestServiceTime
         << " Occurred at time (in minutes): " << timeForShortestServiceTime
         << endl;
    cout << "\nAverage Queue Length: " << (totalQueueLength / 1020) << endl;
    cout << "Longest queue length: " << longestQueueLength
         << " Occurred at time (in minutes): " << timeForLongestQueueLength
         << endl;
    cout << "Shortest queue length: " << shortestQueueLength
         << " Occurred at time (in minutes): " << timeForShortestQueueLength
         << endl;
  }
};

int main() {
  Queue Q;
  int TIME = 0, generator;
  int cumulative_time = 0;
  int customer_count = 1;
  // as many variables as you need

  srand(time(NULL));

  // store hours, every minute of that day
  while (TIME <= 1020) {  // amount of TIME in problem in total
    // 1. should we add a new customer to the Q at this minute?
    if (TIME >= 0 && TIME <= 120) {  // 8am - 10am
      generator = rand() % 100 + 1;
      if (generator <= 30) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 120 && TIME <= 210) {  // 10 am - 11:30am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 210 && TIME <= 330) {  // 11:30am - 1:30pm
      generator = rand() % 100 + 1;
      if (generator <= 40) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 330 && TIME <= 570) {  // 1:30pm - 5:30pm
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 570 && TIME <= 720) {  // 5:30pm - 8pm
      generator = rand() % 100 + 1;
      if (generator <= 25) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 720 && TIME <= 900) {  // 8pm - 11pm
      generator = rand() % 100 + 1;
      if (generator <= 20) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        Q.enqueue(TIME, generator);
      }
    } else if (TIME > 900 && TIME <= 1020) {  // 11pm - 1am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count++ << endl;
        // SPECIAL CASE: Order would be fulfilled AFTER restaurant closes.
        // Solution: customer turned away.
        // NOTE: They can still arrive at the restaurant, but their order just
        // won't be fulfilled
        if ((TIME + generator) < 1020) {
          Q.enqueue(TIME, generator);
        }
      }
    }

    Q.check(TIME);
    TIME++;  // granularity of 1 min
  }

  Q.printContents();
  Q.printStats();

  return 0;
}
