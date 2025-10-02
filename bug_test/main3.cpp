class my_class {
public:
    int pub_a: 1;
    int pub_b: 2;
private:
    int priv_c: 3;
    int priv_d: 7;
protected:
    int prot_e: 5;
    int prot_f: 10;
};

typedef struct my_struct{
    int a: 1;
    int b: 2;
    int c: 3;
    int d: 7;
} my_struct;

int main() {
    my_struct my_struct_array_var[3];
    my_class cls;
    return my_struct_array_var[0].a + cls.pub_a;
}