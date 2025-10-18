struct basic_bitfield { unsigned int a: 1; unsigned int b: 2; unsigned int c: 3; unsigned int d: 7; };
int main() { basic_bitfield bf = {1, 3, 5, 127}; return 0; }
