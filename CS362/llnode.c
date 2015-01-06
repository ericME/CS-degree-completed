  struct node 
  { 
     int value; 
     struct node *next; 
  }; 
  typedef struct node snode; 
  snode* create_node(int); 
  void insert_node_first(int value); 
  void insert_node_last(int value); 
  void insert_node_pos(int position, int value); 
  void delete_pos(); 
  void search(int value); 
  void display(); 
  snode *newnode, *ptr, *prev, *temp; 
  snode *first = NULL, *last = NULL; 
  void insert_node_pos(int pos, int val) 
  { 
            int  cnt = 0, i; 
   
      
            newnode = create_node(val); 
      
            ptr = first; 
            while (ptr != NULL) 
            { 
               ptr = ptr->next; 
               cnt++; 
            } 
            if (pos == 1) 
            { 
               if (first == last && first == NULL) 
               { 
                       first = last = newnode; 
                       first->next = NULL; 
                       last->next = NULL; 
               } 
               else 
               { 
                       temp = first; 
                       first = newnode; 
                       first->next = temp; 
               } 
               printf("\nInserted"); 
            } 
            else if (pos>1 && pos<=cnt) 
            { 
               ptr = first; 
               for (i = 1;i < pos;i++) 
               { 
                       prev = ptr; 
                       ptr = ptr->next; 
               } 
               prev->next = newnode; 
               newnode->next = ptr; 
               printf("\n----INSERTED----"); 
            } 
            else 
            { 
               printf("Position is out of range"); 
            } 
  } 