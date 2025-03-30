// Layer.h
#ifndef LAYER_H
#define LAYER_H

#include <QImage>

class Layer {
public:
    Layer(int width, int height);
    QImage& getImage();
    bool isVisible() const;
    void setVisible(bool v);

private:
    QImage image;
    bool visible;
};

#endif // LAYER_H
