#include <stdio.h>
#define MAX_SIZE 10 

// global variables
int queue[MAX_SIZE]; 
int front = -1,rear=-1;
//
//int stack_full() {
//    if(top >= MAX_SIZE - 1)
//        return 1;
//    return 0; // return 0 only if the above condition is false
//}
//
//int stack_empty() {
//    if(top == -1)
//        return 1;
//    return 0; // return 0 only if the above condition is false
//}
//
//void push(int x) {
//    top++;
//    stack[top] = x;
//}
//
//int pop() {
//    int temp = stack[top];
//    top--;
//    return temp;
//}
//
//// helper function: print the current stack
//void print_stack() {
//    printf("stack = ");
//    for(int i=0; i<=top; i++) 
//        printf(" %d", stack[i]);
//    printf(" (top=%d)\n", top);
//}
//
//// helper function: run a series of pushes
//// input arguments: int arr[] <- an array from which input values are taken
//// input arguments: int num <- total number of elements to push
//void run_pushes(int arr[], int num) {
//    for(int i=0; i<num; i++) {
//        printf("push(%d) , ", arr[i]);
//        if(!stack_full()) { // if stack is not full (!1 = 0)
//            push(arr[i]);
//        }
//       else {
//            printf("stack full! ");
//       }
//       print_stack();
//    }
//}
//
//// helper function: run a series of pops
//// input argument: int num <- total number of elements to pop
//void run_pops(int num) {
//    int value;
//    for(int i=0; i<num; i++) {
//        printf("pop() ");
//        if(!stack_empty()) { // if stack is not empty (!1 = 0)
//            value = pop();
//            printf("-> %d , ", value);
//        }
//        else {
//            printf("stack empty! ");
//        }
//        print_stack();
//    }
//}
void print_queue()
{
	printf("queue = ");
    for(int i=front; i<=rear; i++) 
        printf(" %d", queue[i]);
    printf(" (front=%d, rear=%d)\n", front,rear);
}
void enqueue(int x)
{
	if(front==-1&&rear==-1)
		front++;
	
	rear++;		
	queue[rear]=x;
}
int dequeue()
{
	front++;
	return queue[front-1];
}
int queue_full()
{
	if(rear>=MAX_SIZE-1)
		return 1;
	return 0;
}
int queue_empty()
{
	if(front>rear)
		return 1;
	return 0;
}
void run_enqueue(int arr[],int num)
{
	for(int i=0;i<num;i++)
	{
		printf("push(%d) , ", arr[i]);
		if(queue_full())
			printf("queue full! ");
		else
			enqueue(arr[i]);
		print_queue();
	}
}
void run_dequeue(int num)
{
	for(int i=0;i<num;i++)
	{
		printf("pop() ");
		if(queue_empty())
			printf("queue empty! ");
		else
		{
			int value=dequeue();	
			printf("-> %d , ", value);
		}
		print_queue();
	}
}
int main() {
    int numbers[] = {3, 9, 4, 5, 2, 1, 6, 8, 7, 5, 8};
	
	print_queue();
//    print_stack();
    run_enqueue(numbers, 5);
    run_dequeue(3);
    run_enqueue(numbers, 10);
    run_dequeue(11);
}
