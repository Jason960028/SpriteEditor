// Layer.cpp
#include "Layer.h"

Layer::Layer(int width, int height)
    : image(width, height, QImage::Format_ARGB32), visible(true) {
    image.fill(Qt::transparent);
}

QImage& Layer::getImage() {
    return image;
}

bool Layer::isVisible() const {
    return visible;
}

void Layer::setVisible(bool v) {
    visible = v;
}
