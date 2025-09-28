#include <stdio.h>
#include <stdint.h>

// Basic bitfield struct
typedef struct basic_bitfield {
    unsigned int a: 1;
    unsigned int b: 2;
    unsigned int c: 3;
    unsigned int d: 7;
} basic_bitfield;

// Different sized bitfields
struct various_sizes {
    uint8_t  tiny: 1;
    uint8_t  small: 3;
    uint16_t medium: 5;
    uint16_t large: 11;
    uint32_t huge: 17;
    uint32_t massive: 15;
};

// Mixed bitfields and regular fields
struct mixed_fields {
    int normal_int;
    unsigned int bit1: 1;
    unsigned int bit2: 2;
    char normal_char;
    unsigned int bit3: 3;
    float normal_float;
    unsigned int bit4: 4;
};

// Bitfields with different base types
struct typed_bitfields {
    signed int   s_bit: 4;
    unsigned int u_bit: 4;
    int8_t       i8_bit: 3;
    uint8_t      u8_bit: 5;
    int16_t      i16_bit: 9;
    uint16_t     u16_bit: 7;
    int32_t      i32_bit: 20;
    uint32_t     u32_bit: 12;
};

// Nested structures with bitfields
struct outer_struct {
    int outer_field;
    struct inner_bitfield {
        unsigned int inner_a: 3;
        unsigned int inner_b: 5;
        unsigned int inner_c: 8;
    } inner;
    unsigned int outer_bit: 4;
};

// Union with bitfields
union bitfield_union {
    struct {
        unsigned int a: 8;
        unsigned int b: 8;
        unsigned int c: 16;
    } bits;
    uint32_t full_value;
};

// Union with direct bitfields (not in struct)
union direct_bitfield_union {
    unsigned int bit1: 4;
    unsigned int bit2: 8;
    unsigned int bit3: 16;
    unsigned int bit4: 32;
    uint32_t full_value;
};

// Union with anonymous bitfields
union anonymous_bitfield_union {
    struct {
        unsigned int : 3;  // anonymous padding
        unsigned int used1: 5;
        unsigned int : 8;  // more padding
        unsigned int used2: 16;
    };
    struct {
        unsigned int alt1: 10;
        unsigned int alt2: 22;
    };
    uint32_t raw_value;
};

// Complex union with mixed types and bitfields
union complex_union {
    struct {
        uint8_t byte1: 4;
        uint8_t byte2: 4;
    } nibbles;
    struct {
        uint16_t word1: 3;
        uint16_t word2: 5;
        uint16_t word3: 8;
    } words;
    struct {
        unsigned int : 2;  // anonymous start padding
        unsigned int flag1: 1;
        unsigned int flag2: 1;
        unsigned int data: 12;
        unsigned int : 16; // anonymous end padding
    } flags;
    uint8_t bytes[4];
    uint16_t shorts[2];
    uint32_t dword;
    float float_val;
};

// Namespace tests
namespace TestNamespace {
    struct namespaced_bitfield {
        unsigned int ns_bit1: 5;
        unsigned int ns_bit2: 11;
        unsigned int ns_bit3: 16;
    };
    
    namespace NestedNamespace {
        struct deeply_nested {
            uint8_t deep_bit: 7;
            uint16_t deeper_bit: 13;
        };
    }
}

// Class with bitfields (C++)
class BitfieldClass {
public:
    unsigned int public_bit: 3;
private:
    unsigned int private_bit: 5;
protected:
    unsigned int protected_bit: 8;
public:
    unsigned int another_public: 16;
};

// Packed struct with bitfields
#pragma pack(push, 1)
struct packed_bitfields {
    uint8_t packed_a: 3;
    uint8_t packed_b: 5;
    uint16_t packed_c: 7;
    uint16_t packed_d: 9;
    uint32_t packed_e: 24;
    uint8_t packed_f: 8;
};
#pragma pack(pop)

// Anonymous bitfields
struct anonymous_bits {
    unsigned int : 3;  // anonymous padding
    unsigned int used_bit: 5;
    unsigned int : 8;  // more padding
    unsigned int another_used: 16;
    unsigned int : 0;  // force alignment
    unsigned int aligned_bit: 4;
};

// Array tests
struct array_tests {
    basic_bitfield single_array[5];
    various_sizes multi_array[3][4];
    mixed_fields three_dim[2][3][4];
};

// Simple nested structure
struct simple_nested {
    struct level1 {
        struct level2 {
            unsigned int deep_bit: 12;
            int deep_array[5];
        } l2;
    } nested;
};

// Template with bitfields (C++)
template<typename T>
struct templated_bitfield {
    T bit_value: 8;
    T other_value: 8;
};

// Volatile bitfields
struct volatile_bits {
    volatile unsigned int vol_bit1: 4;
    volatile unsigned int vol_bit2: 12;
    volatile unsigned int vol_bit3: 16;
};

// Main function with test variables
int main() {
    // Basic arrays
    basic_bitfield basic_array[10];
    basic_bitfield basic_2d[3][5];
    basic_bitfield basic_3d[2][3][4];
    
    // Various sized bitfield arrays
    various_sizes var_array[7];
    various_sizes var_2d[2][6];
    
    // Mixed field arrays
    mixed_fields mixed_array[8];
    mixed_fields* mixed_ptr_array[5];
    
    // Typed bitfield tests
    typed_bitfields typed_single;
    typed_bitfields typed_array[4];
    
    // Nested structure tests
    outer_struct outer_single;
    outer_struct outer_array[5];
    
    // Union tests
    bitfield_union union_single;
    bitfield_union union_array[4];
    direct_bitfield_union direct_union;
    direct_bitfield_union direct_union_array[3];
    anonymous_bitfield_union anon_union;
    anonymous_bitfield_union anon_union_array[2];
    complex_union complex_u;
    complex_union complex_u_array[5];
    
    // Namespace tests
    TestNamespace::namespaced_bitfield ns_single;
    TestNamespace::namespaced_bitfield ns_array[6];
    TestNamespace::NestedNamespace::deeply_nested deep_single;
    TestNamespace::NestedNamespace::deeply_nested deep_array[3][2];
    
    // Class tests
    BitfieldClass class_single;
    BitfieldClass class_array[5];
    BitfieldClass* class_ptr = &class_single;
    BitfieldClass** class_ptr_ptr = &class_ptr;
    
    // Packed struct tests
    packed_bitfields packed_single;
    packed_bitfields packed_array[4];
    
    // Anonymous bitfield tests
    anonymous_bits anon_single;
    anonymous_bits anon_array[3];
    
    // Simple nested tests
    simple_nested simple_single;
    simple_nested simple_array[3];
    
    // Template tests
    templated_bitfield<int> template_int;
    templated_bitfield<uint16_t> template_uint16;
    templated_bitfield<int> template_array[4];
    
    // Volatile tests
    volatile_bits volatile_single;
    volatile_bits volatile_array[4];
    
    // Pointer to bitfield struct
    basic_bitfield* basic_ptr = &basic_array[0];
    various_sizes** var_ptr_ptr;
    
    // Large arrays to test array size handling
    basic_bitfield large_1d[100];
    various_sizes large_2d[20][30];
    mixed_fields large_3d[10][15][20];
    
    // Initialize some values for testing
    basic_array[0].a = 1;
    basic_array[0].b = 2;
    basic_array[0].c = 3;
    basic_array[0].d = 7;
    
    var_array[0].tiny = 1;
    var_array[0].small = 7;
    var_array[0].medium = 31;
    
    mixed_array[0].normal_int = 42;
    mixed_array[0].bit1 = 1;
    mixed_array[0].normal_char = 'A';
    mixed_array[0].bit2 = 3;
    
    typed_single.s_bit = -8;
    typed_single.u_bit = 15;
    typed_single.i8_bit = -4;
    typed_single.u8_bit = 31;
    
    outer_single.outer_field = 100;
    outer_single.inner.inner_a = 7;
    outer_single.inner.inner_b = 31;
    outer_single.outer_bit = 15;
    
    union_single.bits.a = 255;
    union_single.bits.b = 128;
    union_single.bits.c = 65535;
    
    direct_union.bit1 = 15;
    direct_union.bit2 = 255;
    direct_union.bit3 = 32767;
    
    anon_union.used1 = 31;
    anon_union.used2 = 65535;
    
    complex_u.flags.flag1 = 1;
    complex_u.flags.flag2 = 0;
    complex_u.flags.data = 2047;
    
    ns_single.ns_bit1 = 31;
    ns_single.ns_bit2 = 2047;
    ns_single.ns_bit3 = 65535;
    
    class_single.public_bit = 7;
    class_single.another_public = 32767;
    
    packed_single.packed_a = 7;
    packed_single.packed_b = 31;
    packed_single.packed_c = 127;
    
    anon_single.used_bit = 31;
    anon_single.another_used = 65535;
    anon_single.aligned_bit = 15;
    
    // Test return value
    return basic_array[0].a + var_array[0].tiny + mixed_array[0].bit1;
}