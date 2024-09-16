#pragma once

/*
pda component/component.h

Base component definitions
*/

// Component base class
class Component
{
public:
    Component();
    virtual ~Component();

    virtual void Update(float dt) = 0;
    virtual void Render() = 0;
};

// Derived component classes

// Sprite component
class SpriteComponent : public Component
{
public:
    SpriteComponent();
    virtual ~SpriteComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

// Text component
class TextComponent : public Component
{
public:
    TextComponent();
    virtual ~TextComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

// Line component
class LineComponent : public Component
{
public:
    LineComponent();
    virtual ~LineComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

class PolylineComponent : public Component
{
public:
    PolylineComponent();
    virtual ~PolylineComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

class CircleComponent : public Component
{
public:
    CircleComponent();
    virtual ~CircleComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

class RectangleComponent : public Component
{
public:
    RectangleComponent();
    virtual ~RectangleComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};

class PolygonComponent : public Component
{
public:
    PolygonComponent();
    virtual ~PolygonComponent();

    virtual void Update(float dt) override;
    virtual void Render() override;
};
