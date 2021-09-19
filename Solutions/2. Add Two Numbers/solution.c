/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 19 September 2021
 * @brief A C-based solution to LeetCode question 2
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief Supplied node format of the singly linked list derived from
 * LeetCode question. Nodes have two attribute members, the first being the
 * <code>int</code> representing one of the digits in the greater link number
 * and the second being a pointer to the next node in the list. 
 */
struct ListNode {
  int val;                  /**< Digit of number associated with node */ 
  struct ListNode * next;   /**< Next node in list */
};

/**
 * @brief The author's initial approach to solving this problem involved the
 * boneheaded parsing of the entire linked list nodes' associated values into
 * one <code>int</code>, the addition of both lists' resultant numbers, and the
 * translation of the result back into a linked list. However, as some input
 * cannot be expressed within the numeric confines of a <code>long long
 * int</code>, the author abandoned this ineffective approach in favor of the
 * more obvious adding of linked list nodes together one by one, as seen in this
 * revised implementation.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 95% of all C implementations with a runtime of 8 ms and more efficient
 * in terms of memory usage than 88% of C implementations with a memory usage
 * of 7.6 MB.
 *
 * @param l1 struct ListNode* A pointer to the first node of the first list
 * @param l2 struct ListNode* A pointer to the first node of the second list
 * @return head struct ListNode* A pointer to the first node of the sum list
 */
struct ListNode * addTwoNumbers(struct ListNode * l1, struct ListNode * l2) {

  // Declarations
  unsigned char sum, carry;
  struct ListNode * head, * current, * previous;

  // Definitions
  sum = 0;
  carry = 0;
  head = NULL;
  previous = NULL;

  while (l1 != NULL || l2 != NULL || carry > 0) {
    sum = 0;

    // Check if there are remaining nodes in first list
    if (l1 != NULL) {
      sum += l1->val;
      l1 = l1->next;
    }

    // Check if there are remaining nodes in second list
    if (l2 != NULL) {
      sum += l2->val;
      l2 = l2->next;
    }

    // Ensure carry is added to sum if exists
    sum += carry;

    // Should be a check of NULL after malloc, but, you know, LeetCode
    current = malloc(sizeof(struct ListNode));
    current->next = NULL;

    // Faster approach than using sum / 10 or sum % 10
    if (sum >= 10) {
      current->val = sum - 10;
      carry = 1;
    } else {
      current->val = sum;
      carry = 0;
    }

    // Keep track of head node for return from function
    if (head == NULL) {
      head = current;
    }

    if (previous != NULL) {
      previous->next = current;
    }

    previous = current;
  }

  return head;
}

/**
 * @brief The first of two helper functions employed by <code>main</code> to
 * set up the test harness and feed the <code>addTwoNumbers</code> function
 * wellformed test cases, this method is responsible for translating the input
 * array of <code>int</code>s into a linked list. The array's contents are
 * treated as the values of each node, and provided a <code>next</code> attibute
 * to allow an indeterminate number of nodes to be strung together.
 * 
 * @param values int* A pointer to the array's first element
 * @param size int The size of the array in question
 * @return head struct ListNode* A pointer to the first node in the list
 */
struct ListNode * translateArrayToList(int * values, int size) {

  // Declarations
  unsigned char i;
  struct ListNode * head, * current, * previous;

  // Definitions for nodes
  previous = NULL;
  head = NULL;
  current = NULL;

  for (i = 0; i < size; i++) {
    current = malloc(sizeof(struct ListNode));
    if (current == NULL) {
      return NULL;
    }

    // Set int array element as val
    current->val = values[i];
    current->next = NULL;

    // Keep track of head for return from function
    if (head == NULL) {
      head = current;
    }

    if (previous != NULL) {
      previous->next = current;
    }

    previous = current;
  }

  return head;
}

/**
 * @brief The second of two helper functions employed by <code>main</code> to
 * set up the test harness and feed the <code>addTwoNumbers</code> function
 * wellformed test cases, this method is responsible for deallocating all
 * previously allocated heap memory space to ensure there are no memory leaks.
 * It simply iterates along the list until the end is reached, freeing the space
 * for each node accordingly.
 *
 * @param current struct ListNode* The head node of the linked list
 * @return void
 */
void deallocate(struct ListNode * current) {

  struct ListNode * next;

  next = NULL;
  while (current != NULL) {
    next = current->next;
    free(current);
    current = next;
  }
}

/**
 * @brief <code>main</code> serves as the example driver for the exercise and
 * runs a few of the test cases supplied on the LeetCode website to permit the
 * solution to be tested offsite. In order to set up the test harness in such a
 * way as to permit the testing of the <code>addTwoNumbers</code> function,
 * <code>main</code> makes use of a pair of helper functions found immediately
 * above.
 *
 * @param argc int The number of command line args
 * @param argv char** The command line args in string form
 * @return int A status <code>int</code>
 */
int main(int argc, char ** argv) {

  // Declarations
  unsigned char i;
  struct ListNode * sum, * current, * op1, * op2, * operands[8];

  // Test cases
  int arr1[3] =  {2,4,3},
      arr2[3] =  {5,6,4},
      arr3[7] =  {9,9,9,9,9,9,9},
      arr4[4] =  {9,9,9,9},
      arr5[1] =  {0},
      arr6[1] =  {0},
      arr7[1] =  {9},
      arr8[10] = {1,9,9,9,9,9,9,9,9,9};

  // Convert int arrays to linked lists formatted in accordance with question
  operands[0] = translateArrayToList(arr1, sizeof(arr1) / sizeof(int)); 
  operands[1] = translateArrayToList(arr2, sizeof(arr2) / sizeof(int));
  operands[2] = translateArrayToList(arr3, sizeof(arr3) / sizeof(int));
  operands[3] = translateArrayToList(arr4, sizeof(arr4) / sizeof(int));
  operands[4] = translateArrayToList(arr5, sizeof(arr5) / sizeof(int));
  operands[5] = translateArrayToList(arr6, sizeof(arr6) / sizeof(int));
  operands[6] = translateArrayToList(arr7, sizeof(arr7) / sizeof(int));
  operands[7] = translateArrayToList(arr8, sizeof(arr8) / sizeof(int));

  for (i = 0; i < 4; i++) {
    op1 = operands[2 * i];
    op2 = operands[2 * i + 1];

    sum = addTwoNumbers(op1, op2);
    current = sum;

    while (current != NULL) {
      printf("%d,", current->val);
      current = current->next;
    }
    printf("\n");

    // Free all previously allocated heap memory
    deallocate(sum);
    deallocate(op1);
    deallocate(op2);
  }

  return 0;
}
