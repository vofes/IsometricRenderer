#include "IsometricMath.h"

Vector2 IsometricMath::ConvertGridToIsometric(const Vector2& grid)
{
    Vector2 scale = Vector2(1.0f, 1.0f);

    // Matrix
    float a = 1.0f * scale.x / 2.0f;
    float b = -1.0f * scale.x / 2.0f;
    float c = 0.5f * scale.y / 2.0f;
    float d = 0.5f * scale.y / 2.0f;

    return Vector2(
        grid.x * a + grid.y * b,
        grid.x * c + grid.y * d
    );
}

Vector2 IsometricMath::ConvertIsometricToGrid(const Vector2& iso)
{
    Vector2 scale = Vector2(1.0f, 1.0f);

    // Matrix
    float a = 1.0f * scale.x / 2.0f;
    float b = -1.0f * scale.x / 2.0f;
    float c = 0.5f * scale.y / 2.0f;
    float d = 0.5f * scale.y / 2.0f;

    // Inverse matrix
    float dec = 1.0f / (a * d - b * c);
    float i_a = dec * d;
    float i_b = dec * -b;
    float i_c = dec * -c;
    float i_d = dec * a;

    return Vector2(
        iso.x * i_a + iso.y * i_b,
        iso.x * i_c + iso.y * i_d
    );
}
