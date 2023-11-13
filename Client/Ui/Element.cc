#include <Client/Ui/Element.hh>

using namespace ui;

Element::Element() {}

Element *Element::Add(Element *child) {
    children.emplace_back(child);
    child->parent = this;
    return child;
}
