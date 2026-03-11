#include <iostream>
using namespace std;

typedef struct Node {
    string data;
    Node* next;
};

void addWord(Node*& head, string word) {
    Node *wordNode = new Node;
    wordNode->data = word;
    wordNode->next = NULL;

    if (head == NULL) {
        head = wordNode;
        return;
    }

    Node* temp = head;

    while (temp->next != NULL) {
        temp = temp->next;s
    }

    temp->next = wordNode;
}

void undoWord(Node*& head) {

    if (head == NULL) {
        cout << "Silecek kelime yok\n";
        return;
    }

    if (head->next == NULL) {
        delete head;
        head = NULL;
        return;
    }

    Node* temp = head;

    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    delete temp->next;
    temp->next = NULL;
}

void displayList(Node*& head) {

    Node* temp = head;

    while (temp != NULL) {
        cout << "[" << temp->data << "] -> ";
        temp = temp->next;
    }

    cout << "NULL" << endl;
}

int main() {

    Node* head = NULL;
    string input;

    while (true) {

        cout << "Kelime giriniz. (UNDO / EXIT): ";
        cin >> input;

        if (input == "EXIT" ) {
            break;
        }
        else if (input == "UNDO") {
            undoWord(head);
        }
        else {
            addWord(head, input);
        }

        displayList(head);
    }

    return 0;
}