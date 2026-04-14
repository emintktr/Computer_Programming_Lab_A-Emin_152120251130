#include <iostream>
using namespace std;

#define MAX 100

// --- STACK IMPLEMENTATION (DO NOT MODIFY) ---
struct Stack {
    int arr[MAX];
    int top;
};

void initStack(Stack* s) { s->top = -1; }
bool isStackEmpty(Stack* s) { return s->top == -1; }
void push(Stack* s, int val) {
    if (s->top < MAX - 1) {
        s->arr[++(s->top)] = val;
    }
}
int pop(Stack* s) {
    if (!isStackEmpty(s)) {
        return s->arr[(s->top)--];
    }
    return -1; // Error or Empty
}

// --- QUEUE IMPLEMENTATION (DO NOT MODIFY) ---
struct Queue {
    int arr[MAX];
    int front;
    int rear;
};

void initQueue(Queue* q) { q->front = -1; q->rear = -1; }
bool isQueueEmpty(Queue* q) { return q->front == -1 || q->front > q->rear; }
void enqueue(Queue* q, int val) {
    if (q->rear < MAX - 1) {
        if (q->front == -1) q->front = 0;
        q->arr[++(q->rear)] = val;
    }
}
int dequeue(Queue* q) {
    if (!isQueueEmpty(q)) {
        return q->arr[(q->front)++];
    }
    return -1; // Error or Empty
}
void printQueue(Queue* q) {
    if (isQueueEmpty(q)) {
        cout << "Queue is empty." << endl;
        return;
    }
    for (int i = q->front; i <= q->rear; i++) {
        cout << q->arr[i] << " ";
    }
    cout << endl;
}

// ==========================================
// LAB TASK: IMPLEMENT THIS FUNCTION
// ==========================================
void reverseQueue(Queue* q) {
    // TODO: Create a temporary Stack here.
    // Use the push, pop, enqueue, and dequeue functions 
    // to reverse the elements inside the Queue 'q'.
    Stack tempStack;
    initStack(&tempStack);

    while (!isQueueEmpty(q)) {
        push(&tempStack, dequeue(q));
    }

    while (!isStackEmpty(&tempStack)) {
        enqueue(q, pop(&tempStack));
    }
}
// ==========================================

int main() {
    Queue myQueue;
    initQueue(&myQueue);

    cout << "Please enter 5 integers:" << endl;
    for(int i = 0; i < 5; i++) {
        int val;
        cin >> val;
        enqueue(&myQueue, val);
    }

    cout << "\nOriginal Queue: ";
    printQueue(&myQueue);

    // Call your function
    reverseQueue(&myQueue);

    cout << "Reversed Queue: ";
    printQueue(&myQueue);

    return 0;
}