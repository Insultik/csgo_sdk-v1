# insulation sdk v1.0 #
### source navigation
1. `@note:`
2. `@todo:`
3. `@test: [date]`
4. `@credits:`
5. `@ref:`

#

### code style 
code style: lower case
some conventions:
```cpp
class c_some_class;
struct some_struct_t;
enum e_some_enum;
bool some_bool = false;
int some_int = 0;
float some_flaot = 0.f;
```
class members has `m_` prefix

small code example:
```cpp
bool test_value = true;
if ( test_value && g_settings.m_test_bool != 1 ) { 
    test_value = false;
    return;
}
else 
    test_value = true;
    
*( ( bool* )( g::m_local.get_base( ) + 0x4c ) ) = false;
}
```

# 

### additional dependencies
1. [dear imgui](https://github.com/ocornut/imgui/)
2. [json](https://github.com/nlohmann/json/)
3. [freetype font rasterizer](https://www.freetype.org/)
4. [minhook](https://github.com/TsudaKageyu/minhook/)
