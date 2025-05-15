#include <cstdio>

using Func = void* (*)();

namespace Hidden {
    namespace Details {
        inline auto secret_func() -> void* {
            return reinterpret_cast<void*>(secret_func);
        }
    }
    
    auto obtain_func() -> Func {
        return reinterpret_cast<Func>(Details::secret_func);
    }
}

auto check_identity(Func f1, Func f2) -> bool {
    return f1 == f2;
}

int execute_test() {
    auto primary = Hidden::obtain_func();
    auto secondary = reinterpret_cast<Func>(primary());
    
    return check_identity(primary, secondary) ? 1 : 0;
}

int main() {
    int result = execute_test();
    printf("%d\n", result);
    return 0;
}