#define DIPLEX(code) interpret(code)

int main() {
    // Inline DIPLEX code
    DIPLEX(R"(
        var x = 10;
        var y = 20;
        output(x + y);
    )");
    return 0;
}
