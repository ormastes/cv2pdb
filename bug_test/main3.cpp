typedef struct my_struct{
    int a: 1;
    int b: 2;
    int c: 3;
    int d: 7;
} my_struct;

int main() {
    my_struct my_struct_array_var[3];
    return my_struct_array_var[0].a;
}