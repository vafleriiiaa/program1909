#include <windows.h>
#include <stdio.h>

typedef double (*CalcArea)(double, double);
typedef double (*CalcPerimeter)(double, double);
typedef void (*DescribeRect)(double, double);
typedef void (*SetColorFn)(const char*);
typedef void (*IsFilledFn)(BOOL);

int main() {
    HINSTANCE hLib = LoadLibrary("Dll1.dll");
    if (hLib == NULL) {
        printf("Error: Cannot load library.\n");
        return 1;
    }

    CalcArea CalculateArea = (CalcArea)GetProcAddress(hLib, "CalculateArea");
    CalcPerimeter CalculatePerimeter = (CalcPerimeter)GetProcAddress(hLib, "CalculatePerimeter");
    DescribeRect DescribeRectangle = (DescribeRect)GetProcAddress(hLib, "DescribeRectangle");
    SetColorFn SetColor = (SetColorFn)GetProcAddress(hLib, "SetColor");
    IsFilledFn IsFilled = (IsFilledFn)GetProcAddress(hLib, "IsFilled");

    if (CalculateArea == NULL || CalculatePerimeter == NULL || DescribeRectangle == NULL || SetColor == NULL || IsFilled == NULL) {
        printf("Error: Cannot find one or more functions in the DLL.\n");
        FreeLibrary(hLib);
        return 1;
    }

    double width = 5.0;
    double height = 3.0;

    double area = CalculateArea(width, height);
    double perimeter = CalculatePerimeter(width, height);

    printf("Area of the rectangle: %.2f\n", area);
    printf("Perimeter of the rectangle: %.2f\n", perimeter);

    DescribeRectangle(width, height);
    SetColor("Blue");
    IsFilled(TRUE);

    FreeLibrary(hLib);
    return 0;
}
