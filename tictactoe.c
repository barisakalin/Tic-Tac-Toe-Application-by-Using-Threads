#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <stdbool.h>

#define N 5
char table[N][N];
int count = 0;
int row,column;

bool check_win(char sign){
    
    //ROW
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(table[i][j] != sign){
                break;
            }
            if(j == N-1){
                return true;
            }
        } 
    }
    //COLUMN
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(table[j][i] != sign){
                break;
            }
            if(j == N-1){
                return true;
            }
        } 
    }
    //DIAGONAL
    for(int i = 0; i<N; i++){
        if(table[i][i] != sign){
            break;
        }
        if(i == N-1){
            return true;
        }
    }

    //DIAGONAL 2
    for(int i = 0; i<N; i++){
        if(table[i][N-i-1] != sign){
            break;
        }
        if(i == N-1){
            return true;
        }
    }
    return false;
}

bool check_full(){
    for(int i=0; i<N; i++){
        for(int j=0; j<N; j++){
            if(table[i][j] == '-'){
                return false;
            }
        }
    }
    
    return true;
}

pthread_mutex_t lock1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t lock3 = PTHREAD_MUTEX_INITIALIZER;

void make_move(char sign){
    printf("Player %c played on (",sign);
    printf("%d,",row);
    printf("%d)\n", column);
    table[row][column] = sign;
}

void* thread_function(void* arg){
    
    int x=0;
    row  = rand() % N;
    column = rand() % N;

    while(!check_win('X') && !check_win('O') && !check_full()){
        
        pthread_mutex_lock(&lock1);
        
        if(pthread_self() == 1 && count == 0){
            
            row  = rand() % N;
            column = rand() % N;
            
            if(table[row][column] == 'O' || table[row][column] == 'X'){}
            
            else{
                make_move('X');
                count++;
            }
        }
       
        if(pthread_self() == 2 && count == 1){
            
            row  = rand() % N;
            column = rand() % N;
            
            if(table[row][column] == 'X' || table[row][column] == 'O'){}
            else{
                make_move('O');
                count--;
            }
        }
        pthread_mutex_unlock(&lock1);
        
        x++;
    }
    
    return NULL;
}

int main(int argc,char* argv[]){

    int r, c;
    for (r=0; r<N; r++){
        for(c=0; c<N; c++){
            table[r][c] = '-';
        }
}
    clock_t start = clock();
    srand (time(NULL));
    pthread_t thread1,thread2;
    
    pthread_create(&thread1,NULL,thread_function,NULL);
    pthread_create(&thread2,NULL,thread_function,NULL);

    pthread_join(thread1,NULL);
    pthread_join(thread2,NULL);

if(check_win('X')){
    printf("Game end\n");
    printf("Winner is %c\n",'X');
}
else if(check_win('O')){
    printf("Game end\n");
    printf("Winner is %c\n",'O');
}
else if(check_full()){
    printf("Game end\n");
    printf("It is a tie\n");
}
for (r=0; r<N; r++){
    for(c=0; c<N; c++){
         printf("%c     ", table[r][c]);
    }
    printf("\n");
}
    return 0;
}