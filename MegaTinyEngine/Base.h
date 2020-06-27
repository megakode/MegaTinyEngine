//
// Created by Peter Bone on 25/06/2020.
//

#ifndef SDLTEST_BASE_H
#define SDLTEST_BASE_H


struct Vec2f {
    float x  = 0;
    float y = 0;


};


struct Vec2i {
    int x  = 0;
    int y = 0;

    explicit operator Vec2f() const { return {static_cast<float>(x),static_cast<float>(y)}; };
};



//#define ENABLE_ASSERTS

#define ENGINE_ASSERT(x, msg) { if(!(x)) { assert(msg,0); } }



struct DeltaTime {
public:

    operator float() const { return m_time; }

private:
    float m_time;
};

#endif //SDLTEST_BASE_H