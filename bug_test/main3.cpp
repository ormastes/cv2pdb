// Test all primitive types and common constructs
// Purpose: Verify no regression in type handling

// Primitive types
char g_char = 'A';
signed char g_schar = -1;
unsigned char g_uchar = 255;
short g_short = -1000;
unsigned short g_ushort = 60000;
int g_int = -100000;
unsigned int g_uint = 200000;
long g_long = -1000000;
unsigned long g_ulong = 2000000;
long long g_llong = -9223372036854775807LL;
unsigned long long g_ullong = 18446744073709551615ULL;
float g_float = 3.14f;
double g_double = 2.718281828;
long double g_ldouble = 1.41421356237;
bool g_bool = true;
void* g_ptr = nullptr;

// Arrays of primitives
int  g_int_array[100] = {0,};
char g_char_array[50] = "Hello World";
float g_float_array[10] = {1.0f, 2.0f, 3.0f};
double g_double_array[5] = {1.0, 2.0, 3.0, 4.0, 5.0};

// Pointers
int* g_pint = &g_int;
char* g_pchar = &g_char;
void** g_ppvoid = &g_ptr;

// Bitfield struct
typedef struct my_struct{
    int a: 1;
    int b: 2;
    int c: 3;
    int d: 7;
} my_struct;

// Bitfield class
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

// Union with anonymous struct (the reported bug case)
union XX {
    int  a;
    struct {
        int  b:1;
        int  c:2;
        int  d:3;
    } ;
};

// Regular struct
struct Point {
    int x;
    int y;
    int z;
};

// Nested struct
struct Container {
    Point pt;
    int value;
    float factor;
};

// Enum
enum Color {
    RED = 0,
    GREEN = 1,
    BLUE = 2
};

// Const and volatile
const int g_const_int = 42;
volatile int g_volatile_int = 100;
const volatile int g_const_volatile_int = 200;

// Typedef
typedef unsigned int uint32_t;
typedef long long int64_t;

uint32_t g_uint32 = 0xDEADBEEF;
int64_t g_int64 = 0x123456789ABCDEF0LL;

int main() {
    // Local variables to test
    XX  xx;
    my_struct my_struct_array_var[3];
    my_class cls;
    Point pt = {10, 20, 30};
    Container cont = {{1, 2, 3}, 100, 2.5f};
    Color col = RED;

    // Test array access
    g_int_array[0] = 42;
    g_float_array[0] = 1.23f;
    xx.a = 5;

    return my_struct_array_var[0].a + cls.pub_a + pt.x + cont.value + col + xx.a;
}
