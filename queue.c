#include "queue.h"
#include "tile_game.h"
#include <stdlib.h>

void enqueue(struct queue *q, struct game_state state) {
    //encode
    uint64_t encoded; //stored serialized game state
    //serialize
    encoded = serialize(state);
    //insert
    insert_at_head(&q->data, encoded); //void function
}

struct game_state dequeue(struct queue *q) {
    struct game_state state;
    //deserialize
    state = deserialize(remove_from_tail(&(q->data))); 
    return state;
}
///////////////////////////////////////////////////
/* my own function
    inputs: struct queue q
            uint64_t encoded
    outputs: int 1 if encoded is in q
            int 0 if not
*//////////////////////////////////////////////////
int repetition (struct queue q, uint64_t encoded){
    struct list_node * n = q.data.head;
    while (n!=NULL){
        if(encoded==n->value){return 1;}
        n = n->next;
    }
    return 0;
}

int number_of_moves(struct game_state start) { 
    struct queue q = { .data.head = NULL };
    struct game_state curr = start;
    enqueue(&q, start);

    while (q.data.head!=NULL){
        curr = dequeue(&q);
        //successful?
        int success = 0;
        if(curr.empty_row == 3 && curr.empty_col == 3){
            // printf("checking for success\n");
            int correct = 1;
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(curr.tiles[i][j]==correct){
                        success++;
                        if(success==15){
                            // printf("correct!\n");
                            free_list(q.data);
                            return curr.num_steps;
                        }
                        correct++;
                    }
                }
            }
        }
        if(curr.empty_row > 0){
            // printf("moving down\n");
            struct game_state copy = curr;
            move_down(&copy);
            //check if it's already in the queue
            if(!repetition(q,serialize(copy))){enqueue(&q,copy);}
        }
        if(curr.empty_row < 3){     
            // printf("moving up\n");
            struct game_state copy = curr;
            move_up(&copy);
            if(!repetition(q,serialize(copy))){enqueue(&q,copy);}
        }
        if (curr.empty_col > 0){
            // printf("moving right\n");
            struct game_state copy = curr;
            move_right(&copy);
            if(!repetition(q,serialize(copy))){enqueue(&q,copy);}
        }
        if(curr.empty_col < 3){     
            // printf("moving left\n");
            struct game_state copy = curr;
            move_left(&copy);
            if(!repetition(q,serialize(copy))){enqueue(&q,copy);}
        }
        
    }
    return 0; 
}
