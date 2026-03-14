class Node:
    def __init__(self, data:any, next:Node = None):
        self.data = data
        self.next = next

class LinkedList:
    def __init__(self, head):
        self.head = head

def main():
    a = Node(10)
    b = Node(20)
    a.next = b
    c = Node(30)
    b.next = c
    head = c

    while head is not None:
        print(head.data)
        head = head.next

if __name__ == "__main__":
    main()
    