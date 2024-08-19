// filename main.cpp
// description: remove those continous numbers that multpling result is 10 repeatly until no more numbers can be removed.

// testcase: head = [-2,5,-1,-10,1,-1,10,2,2,2,5,5] 
// g++ main.cpp 
// g++ version suggested as g++ (Ubuntu 13.2.0-23ubuntu4) 13.2.0

#include<iostream>
#include<vector>
#include<string>
using namespace std;

struct ListNode {
    int val;
    ListNode * next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    ListNode* removeSublists(ListNode *head);
};


ListNode* Solution::removeSublists(ListNode *head){

    // process
    cout << "start process:" <<endl<<endl;
    bool found_last_time = true;

    int last_time_total_node = 0;
    int num = 0;
    ListNode *leftN = head;
    ListNode *rightN = head;
    ListNode *curr = nullptr;
    ListNode *prev = nullptr;
    ListNode *next = nullptr;

    int result = 1;
    curr = leftN;
    while (leftN != nullptr)
    {

        if(curr->val > 10 || curr->val < -10) {
            // need to re-start from the next node.
            leftN = curr->next;
            prev = curr;
            curr = leftN;
            rightN = curr;
            result = 1;
            continue;
        }

        if ((result < 10) && (result >= -10))
        {
            result *= curr->val;
        }

        rightN = curr->next;

        if (result == 10){

            // do the deletion: from nodes leftN to rightN(included)
            cout << "result(2): " << result <<endl;
            curr = head;
            prev = head;

            // find the first node to be deleted.
            while (curr != leftN){
                prev = curr;
                curr = curr->next;
            }

            while(curr != rightN)
            {
                if(head == curr) {
                    cout << "deleting head node: " << curr->val <<endl;
                    head = curr->next;
                    prev = head;
                    delete curr;
                    curr = head;
                } else {
                    cout << "deleting intermediate node: " << curr->val <<endl;
                    next = curr->next;
                    delete curr;
                    curr = next;
                    prev->next = curr;
                }
            }

            leftN = head;
            result = 1;
            curr = leftN;
            cout<<endl;

            continue;
        }

        if ((result < -10) || (result >10))
        {
            
            result = 1;
            leftN = leftN->next;
            rightN = leftN;
            curr= leftN;
            continue;
        }
        prev = curr;
        curr = curr->next;
        if (curr == nullptr) {
            break;
        }
    }

    return head;
}

int numInList(const ListNode * head)
{
    int i = 0;
    while (nullptr!= head)
    {
        i++;
        head = head->next;
    }
    cout << "list num in total: " << i << endl;
    return i;

}

void printList(const ListNode* head) {
    if(head == nullptr) {
        cout << "Print an empty list." << endl;
        return;
    }

    while (head != nullptr){
        cout<< head->val;
        head = head->next;
        if(head)
            cout<< ", ";
        else
            cout <<endl;
    }
    return;
}

void destroyList(ListNode *head){
    if(nullptr == head)
    {
        cout << "List is empty."<<endl;
        return;
    }

    ListNode *next = nullptr;
    while (head) {
        next = head->next;
        delete head;
        head = next;
    }
    return;
}


int main(){

    vector<int> vecHead {-2,5,-1,-10,1,-1,10,2,2,2,5,5};

    // create the link list 
    ListNode *head = nullptr;

    // print vec data
    cout << endl << "vec data: " <<endl;
    for(auto it = vecHead.begin(); it != vecHead.end(); ++it) {
        cout << *it ;
        if (it + 1 != vecHead.end())
            cout << ", ";
        else
            cout << endl;
    }

    // creat the list
    for(auto it = vecHead.rbegin(); it != vecHead.rend(); ++it) {
        head = new ListNode(*it, head);
    }
    cout << endl;

    // print list
    cout << "Print list before process:" <<endl;
    printList(head);
    cout<<endl;

    Solution sl;
    head = sl.removeSublists(head);

    // print list after the process
    cout << endl << "Print list after process:" << endl;
    printList (head);
    cout << endl;

    destroyList(head);
    head = nullptr;

    return 0;
}
