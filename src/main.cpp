#include <iostream>
#include <string>
#include <string_view>
#include <array>

#include "macros.h"
#include "Vertex.h"
#include "Board.h"

#define RECTANGLE   0
#define TRIANGLE    0
#define WINDOW      0
#define HEXAGRAM    1

#if RECTANGLE
#include "Rectangle.h"
void printInfo(const Rectangle&);
#endif

#if TRIANGLE
#include "Triangle.h"
void printInfo(const Triangle&);
#endif

#if WINDOW
#include "Window.h"
void printInfo(const Window&);
#endif

#if HEXAGRAM
#include "Hexagram.h"
void printInfo(const Hexagram&);
#endif

void waitForEnter();
Vertex readVertex(std::string_view vertexName, std::string_view shapeName);

template <typename Shape>
void useShape(Shape& shape, std::string_view shapeName);

template <typename Shape>
void draw(const Shape& shape, Board&);

template <typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName);

int main()
{
#if RECTANGLE
    {
        static constexpr auto shapeName = std::string_view("rectangle");

        const auto vertices = std::array<Vertex, 2>
        {
            readVertex("bottom-left", shapeName),
            readVertex("top-right", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto rectangle = Rectangle(vertices.data());
        useShape(rectangle, shapeName);
    }
#endif // RECTANGLE

#if TRIANGLE
    {
        static constexpr auto shapeName = std::string_view("triangle");

        const auto vertices = std::array<Vertex, 3>
        {
            readVertex("first", shapeName),
            readVertex("second", shapeName),
            readVertex("third", shapeName)
        };

        std::cin.ignore(); // ignore the enter

        auto triangle = Triangle(vertices.data());
        useShape(triangle, shapeName);
    }
#endif // TRIANGLE

#if WINDOW
    {
        const auto readRectangle = [](std::string_view partOfShapeName)
        {
            auto vertices = std::array<Vertex, 2>();
            vertices[0] = readVertex("bottom-left", partOfShapeName);
            vertices[1] = readVertex("top-right", partOfShapeName);

            std::cin.ignore(); // ignore the enter

            return Rectangle(vertices.data());
        };

        static constexpr auto shapeName = std::string_view("window");

        const auto outer = readRectangle("outer rectangle of the " + std::string(shapeName));
        const auto inner = readRectangle("inner rectangle of the " + std::string(shapeName));

        auto window = Window(outer, inner);
        useShape(window, shapeName);
    }
#endif // WINDOW

#if HEXAGRAM
    {
        const auto readTriangle = [](std::string_view partOfShapeName)
        {
            auto vertices = std::array<Vertex, 3>();
            vertices[0] = readVertex("first", partOfShapeName);
            vertices[1] = readVertex("second", partOfShapeName);
            vertices[2] = readVertex("third", partOfShapeName);

            std::cin.ignore(); // ignore the enter

            return Triangle(vertices.data());
        };

        static constexpr auto shapeName = std::string_view("hexagram");

        const auto first = readTriangle("first triangle of the " + std::string(shapeName));
        const auto second = readTriangle("second triangle of the " + std::string(shapeName));

        auto hexagram = Hexagram(first, second);
        useShape(hexagram, shapeName);
    }
#endif // HEXAGRAM
}

#if RECTANGLE
void printInfo(const Rectangle& rectangle)
{
    static constexpr auto shapeName = std::string_view("rectangle");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::cout << "The " << vertexName << " vertex of the " << shapeName
            << " is: " << v << '\n';
    };

    printVertex(rectangle.getBottomLeft(), "bottom-left");
    printVertex(rectangle.getTopRight(), "top-right");
}
#endif // RECTANGLE

#if TRIANGLE
void printInfo(const Triangle& triangle)
{
    static constexpr auto shapeName = std::string_view("triangle");

    std::cout << "The vertices of the " << shapeName << " are:\n";
    for (int i = 0; i < 3; ++i)
    {
        std::cout << triangle.getVertex(i) << '\n';
    }

    std::cout << "The length of each side of the " << shapeName << " is: "
        << triangle.getLength() << '\n';
}
#endif // TRIANGLE

#if WINDOW
void printInfo(const Window& window)
{
    static constexpr auto shapeName = std::string_view("window");

    const auto printVertex = [](const Vertex& v, std::string_view vertexName)
    {
        std::cout << "The " << vertexName << " vertex of the " << shapeName
            << " is: " << v << '\n';
    };

    printVertex(window.getBottomLeft(), "bottom-left");
    printVertex(window.getTopRight(), "top-right");

    const auto printThickness = [](double d, std::string_view direction)
    {
        std::cout << "The " << direction << " thickness of the " << shapeName
            << " is: " << d << '\n';
    };

    printThickness(window.getVerticalThickness(), "vertical");
    printThickness(window.getHorizontalThickness(), "horizontal");
}
#endif // WINDOW

#if HEXAGRAM
void printInfo(const Hexagram& hexagram)
{
    static constexpr auto shapeName = std::string_view("hexagram");

    std::cout << "The length of each side of the " << shapeName << " is: "
        << hexagram.getLength() << '\n';

    std::cout << "The total height of the " << shapeName << " is: "
        << hexagram.getTotalHeight() << '\n';
}
#endif // HEXAGRAM

void waitForEnter()
{
    std::cout << "Press Enter to continue...\n";
    auto line = std::string();
    std::getline(std::cin, line);
}

Vertex readVertex(std::string_view vertexName, std::string_view shapeName)
{
    std::cout << "Please enter x and y coordinates for the " << vertexName
        << " vertex of the " << shapeName << ":\n";
    auto v = Vertex();
    std::cin >> v;
    return v;
}

template<typename Shape>
void useShape(Shape& shape, std::string_view shapeName)
{
    auto board = Board();
    auto print = [&]
    {
        draw(shape, board);
        printInfo(shape);
        printGenericInfo(shape, shapeName);
        waitForEnter();
    };

    print();

    board.clear();
    std::cout << "Now scaled by factor of 2:\n\n";
    if (shape.scale(2))
    {
        print();
    }
    else
    {
        std::cout << "Scaling failed!\n";
        waitForEnter();
    }
}

template<typename Shape>
void draw(const Shape& shape, Board& board)
{
    shape.draw(board);
    board.print();
    waitForEnter();

    std::cout << "Now with the bounding rectangle:\n";
    auto boundingRect = shape.getBoundingRectangle();
    boundingRect.draw(board);
    board.print();
    waitForEnter();
}

template<typename Shape>
void printGenericInfo(const Shape& shape, std::string_view shapeName)
{
    std::cout << "The perimeter of the " << shapeName << " is: " <<
        shape.getPerimeter() << '\n';

    std::cout << "The area of the " << shapeName << " is: " <<
        shape.getArea() << '\n';

    std::cout << "The center of the " << shapeName << " is: " <<
        shape.getCenter() << '\n';
}
