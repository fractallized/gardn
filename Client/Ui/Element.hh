#pragma once

#include <vector>

namespace ui {
    class Element {
    public:
        Element();
        std::vector<Element *> children = {};
        Element *parent = nullptr;
        int h_justify = 0;
        int v_justify = 0;
        float x = 0;
        float y = 0;
        float abs_x = 0;
        float abs_y = 0;
        float width = 0;
        float height = 0;
        float animation = 1;
        Element *Add(Element *);
        virtual void Animate();
        virtual void OnEvent();
        virtual void OnHide();
        virtual void OnRender();
        virtual int ShouldShow();
    };
}