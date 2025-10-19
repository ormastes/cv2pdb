union SimpleUnion {
    int a;
    float b;
};

int main() {
    union SimpleUnion u;
    u.a = 42;
    return u.a;
}
