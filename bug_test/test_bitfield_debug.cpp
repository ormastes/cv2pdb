#include <stdio.h>
#include <stdint.h>
#include <string.h>

// Basic bitfield test with specific values
struct BitfieldTest {
    unsigned int flag1 : 1;   // bit 0
    unsigned int flag2 : 2;   // bits 1-2
    unsigned int value : 5;   // bits 3-7
    unsigned int mode  : 3;   // bits 8-10
    unsigned int state : 4;   // bits 11-14
    unsigned int reserved : 17; // bits 15-31
};

// Large bitfield test (spans multiple storage units)
struct LargeBitfield {
    uint64_t part1 : 20;  // bits 0-19
    uint64_t part2 : 30;  // bits 20-49
    uint64_t part3 : 14;  // bits 50-63
};

// Very large bitfield (128-bit total)
struct VeryLargeBitfield {
    uint64_t field1 : 10;  // bits 0-9
    uint64_t field2 : 25;  // bits 10-34
    uint64_t field3 : 29;  // bits 35-63 (rest of first uint64)
    uint64_t field4 : 40;  // bits 0-39 of second uint64
    uint64_t field5 : 24;  // bits 40-63 of second uint64
};

// Mixed size bitfields
struct MixedBitfield {
    uint8_t  byte1 : 3;
    uint8_t  byte2 : 5;
    uint16_t word1 : 7;
    uint16_t word2 : 9;
    uint32_t dword1 : 15;
    uint32_t dword2 : 17;
    uint64_t qword1 : 33;
    uint64_t qword2 : 31;
};

// Edge case: single bit fields
struct SingleBits {
    unsigned int bit0 : 1;
    unsigned int bit1 : 1;
    unsigned int bit2 : 1;
    unsigned int bit3 : 1;
    unsigned int bit4 : 1;
    unsigned int bit5 : 1;
    unsigned int bit6 : 1;
    unsigned int bit7 : 1;
};

void print_bytes(const char* name, void* ptr, size_t size) {
    printf("%s raw bytes: ", name);
    unsigned char* bytes = (unsigned char*)ptr;
    for (size_t i = 0; i < size; i++) {
        printf("%02X ", bytes[i]);
    }
    printf("\n");
}

int main() {
    printf("=== Bitfield Debugger Test ===\n\n");

    // Test 1: Basic bitfield with specific values
    BitfieldTest test = {};
    test.flag1 = 1;      // 0b1
    test.flag2 = 2;      // 0b10
    test.value = 0x15;   // 0b10101 (21 decimal)
    test.mode = 6;       // 0b110
    test.state = 0xB;    // 0b1011 (11 decimal)
    test.reserved = 0x1234; // Some pattern

    printf("BitfieldTest values:\n");
    printf("  flag1 = %u (expected: 1)\n", test.flag1);
    printf("  flag2 = %u (expected: 2)\n", test.flag2);
    printf("  value = %u (expected: 21)\n", test.value);
    printf("  mode = %u (expected: 6)\n", test.mode);
    printf("  state = %u (expected: 11)\n", test.state);
    printf("  reserved = %u (expected: 4660/0x1234)\n", test.reserved);
    print_bytes("BitfieldTest", &test, sizeof(test));

    // Calculate expected raw value
    // flag1=1 (bit 0): 0x00000001
    // flag2=2 (bits 1-2): 0x00000004
    // value=21 (bits 3-7): 0x000000A8
    // mode=6 (bits 8-10): 0x00000600
    // state=11 (bits 11-14): 0x00005800
    // reserved=0x1234 (bits 15-31): 0x91A00000
    // Total: 0x91A05EAD
    printf("  Expected raw: 0x91A05EAD\n\n");

    // Test 2: Large bitfield (64-bit)
    LargeBitfield large = {};
    large.part1 = 0xABCDE;     // 20 bits: 703710
    large.part2 = 0x12345678;  // 30 bits: 305419896
    large.part3 = 0x1FFF;      // 14 bits: 8191

    printf("LargeBitfield values:\n");
    printf("  part1 = %llu (expected: 703710/0xABCDE)\n", (unsigned long long)large.part1);
    printf("  part2 = %llu (expected: 305419896/0x12345678)\n", (unsigned long long)large.part2);
    printf("  part3 = %llu (expected: 8191/0x1FFF)\n", (unsigned long long)large.part3);
    print_bytes("LargeBitfield", &large, sizeof(large));
    printf("\n");

    // Test 3: Very large bitfield (128-bit)
    VeryLargeBitfield very = {};
    very.field1 = 0x3FF;        // 10 bits: all 1s
    very.field2 = 0x1FFFFFF;    // 25 bits: all 1s
    very.field3 = 0x1FFFFFFF;   // 29 bits: all 1s
    very.field4 = 0xFFFFFFFFFF; // 40 bits: all 1s
    very.field5 = 0xFFFFFF;     // 24 bits: all 1s

    printf("VeryLargeBitfield values:\n");
    printf("  field1 = %llu (expected: 1023/0x3FF)\n", (unsigned long long)very.field1);
    printf("  field2 = %llu (expected: 33554431/0x1FFFFFF)\n", (unsigned long long)very.field2);
    printf("  field3 = %llu (expected: 536870911/0x1FFFFFFF)\n", (unsigned long long)very.field3);
    printf("  field4 = %llu (expected: 1099511627775/0xFFFFFFFFFF)\n", (unsigned long long)very.field4);
    printf("  field5 = %llu (expected: 16777215/0xFFFFFF)\n", (unsigned long long)very.field5);
    print_bytes("VeryLargeBitfield", &very, sizeof(very));
    printf("\n");

    // Test 4: Mixed size bitfields
    MixedBitfield mixed = {};
    mixed.byte1 = 7;         // 3 bits: 0b111
    mixed.byte2 = 31;        // 5 bits: 0b11111
    mixed.word1 = 127;       // 7 bits: 0x7F
    mixed.word2 = 511;       // 9 bits: 0x1FF
    mixed.dword1 = 32767;    // 15 bits: 0x7FFF
    mixed.dword2 = 131071;   // 17 bits: 0x1FFFF
    mixed.qword1 = 0x1FFFFFFFF; // 33 bits
    mixed.qword2 = 0x7FFFFFFF;  // 31 bits

    printf("MixedBitfield values:\n");
    printf("  byte1 = %u (expected: 7)\n", mixed.byte1);
    printf("  byte2 = %u (expected: 31)\n", mixed.byte2);
    printf("  word1 = %u (expected: 127)\n", mixed.word1);
    printf("  word2 = %u (expected: 511)\n", mixed.word2);
    printf("  dword1 = %u (expected: 32767)\n", mixed.dword1);
    printf("  dword2 = %u (expected: 131071)\n", mixed.dword2);
    printf("  qword1 = %llu (expected: 8589934591/0x1FFFFFFFF)\n", (unsigned long long)mixed.qword1);
    printf("  qword2 = %llu (expected: 2147483647/0x7FFFFFFF)\n", (unsigned long long)mixed.qword2);
    print_bytes("MixedBitfield", &mixed, sizeof(mixed));
    printf("\n");

    // Test 5: Single bit fields
    SingleBits bits = {};
    bits.bit0 = 1;
    bits.bit1 = 0;
    bits.bit2 = 1;
    bits.bit3 = 1;
    bits.bit4 = 0;
    bits.bit5 = 1;
    bits.bit6 = 0;
    bits.bit7 = 1;

    printf("SingleBits values:\n");
    printf("  Pattern: %d%d%d%d%d%d%d%d (10110101 = 0xAD from bit7 to bit0)\n",
           bits.bit7, bits.bit6, bits.bit5, bits.bit4,
           bits.bit3, bits.bit2, bits.bit1, bits.bit0);
    print_bytes("SingleBits", &bits, sizeof(bits));

    // Expected: bit0=1, bit2=1, bit3=1, bit5=1, bit7=1
    // Binary: 10101101 = 0xAD
    unsigned char* byte_ptr = (unsigned char*)&bits;
    printf("  Actual byte value: 0x%02X (expected: 0xAD)\n", *byte_ptr);
    printf("\n");

    printf("=== Set breakpoint here to inspect in debugger ===\n");
    printf("Suggested debugger commands:\n");
    printf("  dt BitfieldTest test\n");
    printf("  dt LargeBitfield large\n");
    printf("  dt VeryLargeBitfield very\n");
    printf("  dt MixedBitfield mixed\n");
    printf("  dt SingleBits bits\n");
    printf("\nPress Enter to continue...\n");
    getchar();

    return 0;
}