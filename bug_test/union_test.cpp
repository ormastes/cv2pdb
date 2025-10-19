union SimpleUnion {
    int a;
    float b;
};

int main() {
    SimpleUnion u;
    u.a = 42;
    return u.a;
}
