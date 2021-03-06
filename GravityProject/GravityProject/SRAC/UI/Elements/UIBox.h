#pragma once

#include "UIElement.h"

class Texture;

class UIBox : public UIElement
{
public:
	struct Data : public UIElement::Data
	{
		Data() { }
		Data(const BasicString& dataId, RectF dataRect, Texture* dataTexture) : UIElement::Data(dataId, dataRect), texture(dataTexture) { }
		Texture* texture = nullptr;
#if DEBUG_MODE
		bool drawRect = false;
#endif
	};


public:
	UIBox();
	UIBox(Data& data);
	UIBox(const StringMap& attributes);
	virtual ~UIBox() { }

	void fill(const StringMap& attributes);

	void setTexture(Texture* texture) { mTexture = texture; }

	// TODO: make this...better
	// Keeps the original ratio, clipping the texture if required
	void setTextureClipping();

	const Texture* texture() const { return mTexture; }

	bool isPointInBounds(VectorF point);

	virtual void render() override;
	virtual void render(RectF subRect);

	virtual Type type() const override { return Type::Box; }

protected:
	Texture* mTexture;

	RectF mSubrect;

#if DEBUG_MODE
	bool mDrawRect;
#endif
};
