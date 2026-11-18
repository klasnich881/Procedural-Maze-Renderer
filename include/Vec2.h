#pragma once
#include <cmath>

struct Vec2 {
    float x = 0.0f;
    float y = 0.0f;


    //Vector operations
    float dot(const Vec2& other) const{
        return {x * other.x + y * other.y};
    }
    float length() const{
        return(std::sqrt(x*x + y*y));
    }
    Vec2 normalized() const{
        float magnitude{length(*this)};


    }

    //Rotates vector ccw by angleRadians via cos and sin
    Vec2 rotated(float angleRadians) const;


    Vec2 operator+(const Vec2& other) const{
        return {x + other.x, y + other.y};
    }

    Vec2 operator-(const Vec2& other) const{
        return {x - other.x, y - other.y};
    }
    Vec2 operator*(float scalar) const{
        return {x * scalar, y * scalar};
    }
    Vec2 operator/(float scalar) const{
        if(std::abs(scalar) > 0.0f){
            return {x / scalar, y / scalar};
        }
        return {0.0f, 0.0f};
    }
    Vec2 rotated(float angleRadians) const{
        float c = std:: cos(angleRadians);
        float s = std:: sin(angleRadians);

        float newX{x * c - y * s};
        float newY{x * s + y * c};

        return {newX, newY};
}
};
