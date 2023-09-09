#include <cstdlib>
#include <iostream>
using namespace std;

int memory[20];
int used[20] = {0};

int* my_malloc(int size){
    if(size <= 0 || size > 20) return 0;
    for (int i = 0; i < 20 - (size - 1); i++)
    {
        if( !used[i] ) {
            int not_used = 1;

            for (int k = 0; k < size; k++){
                if(used[i + k]) not_used = 0;
            }

            if(not_used) {
                for (int k = 0; k < size; k++) used[i + k] = size - k;
                return memory + i;
            }
        }
    }
    return 0;
}

void my_free(int* ptr){
    if(!ptr) return;

    int index = ptr - memory;
    int size = used[index];
    for (int i = 0; i < size; i++){
        used[i + index] = 0;
    }
}

int main(int argc, char *argv[]){
    int *a = my_malloc(10), *b = my_malloc(10);
    cout << "a address=" << &a << ", b address = " << &b << endl;


    my_free(a); // aを解放
    int *c = my_malloc(10);//aの領域と同じところが確保される
    int *d = my_malloc(10);//足りないので0

    cout << "c address=" << &c << ", d address = " << &d << endl;

    return 0;
}