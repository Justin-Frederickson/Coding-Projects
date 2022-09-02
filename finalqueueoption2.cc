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

class Queue1 {
 public:
  int size, totalWaitTime, totalServiceTime, totalQueueLength, averageWaitTime,
      averageServiceTime, averageQueueLength, totalSize;
  Customer *head;
  Customer *tail;
  Queue1() {
    head = tail = NULL;
    size = 0;
    totalSize = 0;
    totalWaitTime = 0;
    totalServiceTime = 0;
    totalQueueLength = 0;
    averageWaitTime = 0;
    averageServiceTime = 0;
    averageQueueLength = 0;
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
    totalSize++;
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
    size--;
  }

  void check() {
    if (head == NULL) {
      return;
    }
    if (head->ordertime == 0) {
      totalWaitTime += head->waitTime;
      totalServiceTime += (head->waitTime + head->copyOfOrdertime);
      dequeue();
      return;
    }
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
      cout << "Size: " << size << endl;
    }
  }

  void makeStats() {
    averageWaitTime = (totalWaitTime / totalSize);
    averageServiceTime = (totalServiceTime / totalSize);
    averageQueueLength = (totalQueueLength / 1020);
  }
};
class Queue2 {
 public:
  int size, totalWaitTime, totalServiceTime, totalQueueLength, averageWaitTime,
      averageServiceTime, averageQueueLength, totalSize;
  Customer *head;
  Customer *tail;
  Queue2() {
    head = tail = NULL;
    size = 0;
    totalSize = 0;
    totalWaitTime = 0;
    totalServiceTime = 0;
    totalQueueLength = 0;
    averageWaitTime = 0;
    averageServiceTime = 0;
    averageQueueLength = 0;
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
    totalSize++;
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
    size--;
  }

  void check() {
    if (head == NULL) {
      return;
    }
    if (head->ordertime == 0) {
      totalWaitTime += head->waitTime;
      totalServiceTime += (head->waitTime + head->copyOfOrdertime);
      dequeue();
      return;
    }
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
      cout << "Size: " << size << endl;
    }
  }

  void makeStats() {
    averageWaitTime = (totalWaitTime / totalSize);
    averageServiceTime = (totalServiceTime / totalSize);
    averageQueueLength = (totalQueueLength / 1020);
  }
};

int main() {
  Queue1 Q1;
  Queue2 Q2;
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
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }
        customer_count++;
      }
    } else if (TIME > 120 && TIME <= 210) {  // 10 am - 11:30am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }

        customer_count++;
      }
    } else if (TIME > 210 && TIME <= 330) {  // 11:30am - 1:30pm
      generator = rand() % 100 + 1;
      if (generator <= 40) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }

        customer_count++;
      }
    } else if (TIME > 330 && TIME <= 570) {  // 1:30pm - 5:30pm
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }

        customer_count++;
      }
    } else if (TIME > 570 && TIME <= 720) {  // 5:30pm - 8pm
      generator = rand() % 100 + 1;
      if (generator <= 25) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }

        customer_count++;
      }
    } else if (TIME > 720 && TIME <= 900) {  // 8pm - 11pm
      generator = rand() % 100 + 1;
      if (generator <= 20) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        if (Q1.size < Q2.size) {
          Q1.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 1"
               << endl;
        } else {
          Q2.enqueue(TIME, generator);
          cout << "\nCustomer No. " << customer_count << " joined queue # 2"
               << endl;
        }

        customer_count++;
      }
    } else if (TIME > 900 && TIME <= 1020) {  // 11pm - 1am
      generator = rand() % 100 + 1;
      if (generator <= 10) {
        generator = rand() % 6 + 1;
        cout << "New customer arrived at time: " << TIME
             << " with an order time of: " << generator
             << " Customer No.: " << customer_count << endl;
        // SPECIAL CASE: Order would be fulfilled AFTER restaurant closes.
        // Solution: customer turned away.
        // NOTE: They can still arrive at the restaurant, but their order just
        // won't be fulfilled
        if ((TIME + generator) < 1020) {
          if (Q1.size < Q2.size) {
            Q1.enqueue(TIME, generator);
            cout << "\nCustomer No. " << customer_count << " joined queue # 1"
                 << endl;
          } else {
            Q2.enqueue(TIME, generator);
            cout << "\nCustomer No. " << customer_count << " joined queue # 2"
                 << endl;
          }

          customer_count++;
        }
      }
    }

    Q1.check();
    Q2.check();

    // Q1.printContents();
    // Q2.printContents();
    TIME++;  // granularity of 1 min
  }

  Q1.printContents();
  Q2.printContents();

  Q1.makeStats();
  Q2.makeStats();

  // Print stats
  cout << "\nAverage Wait Time: "
       << (Q1.averageWaitTime + Q2.averageWaitTime) / 2 << endl;

  cout << "\nAverage Service Time: "
       << (Q1.averageServiceTime + Q2.averageServiceTime) / 2 << endl;

  cout << "\nAverage Queue Length: "
       << (Q1.averageQueueLength + Q2.averageQueueLength) / 2 << endl;

  return 0;
}
