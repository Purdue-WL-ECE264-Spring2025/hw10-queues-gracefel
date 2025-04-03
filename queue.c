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

int number_of_moves(struct game_state start) { 


    struct queue q = { .data.head = NULL }; // = malloc(sizeof(struct queue));
    //enqueue
    struct game_state curr = start;
    enqueue(&q, start);
    // I don't know where to put all of these
    // these need to go in the queue but I'm not sure how
    while (q.data.head!=NULL){
        curr = dequeue(&q);
        if(start.empty_row > 0){
            move_up(&curr);
            enqueue(&q,curr);
        }
        if(curr.empty_row < 3){
            move_down(&curr);
            enqueue(&q,curr);
        }
        if(curr.empty_col > 0){
            move_left(&curr);
            enqueue(&q,curr);
        }
        if(curr.empty_col < 3){      
            move_right(&curr);
            enqueue(&q,curr);
        }
        //successful?
        if(curr.empty_row == 3 && curr.empty_col == 3){
            int correct = 1;
            for(int i = 0; i < 4; i++){
                for(int j = 0; j < 4; j++){
                    if(curr.tiles[i][j]==correct){
                        if(correct==15){
                            return curr.num_steps;
                        }
                        correct++;
                    }
                }
            }
        }
    }
    return 0; 
}
